#include "sl_perfect_recall.hh"
#include <stack>
#include <map>
#include <algorithm>


pair<BDD, list<sl_solution> >
check_perfect_recall_formula(modal_formula *formula, bdd_parameters *para)
{
  if (options["verbosity"] > 0) {
    cout << "    Checking perfect recall formula " << formula->to_string()
        << endl;
  }

  // Store the current state variables.
  unsigned int old_next_bdd_variable = next_bdd_variable;

  // Process the quantification and binding prefix.
  BENCHMARK_START("prefix");
  if (options["verbosity"] > 0) {
    cout << "    Processing quantification and binding prefix." << endl;
  }
  pair<modal_formula *, vector<quantifier> > processed_prefix =
      process_prefix(formula);
  modal_formula *ltl_formula = processed_prefix.first;
  vector<quantifier> prefix = processed_prefix.second;
  BENCHMARK_END();

  // Determinize each conjunct separately to a parity automaton.
  pair<vector<parity_automaton>, list<sl_solution> > subresult =
      determinize_formula(ltl_formula, para);
  vector<parity_automaton> parity_automata = subresult.first;
  list<sl_solution> solutions = subresult.second;

  // Construct the arena.
  BENCHMARK_START("arena");
  if (options["verbosity"] > 0) {
    cout << "    Constructing arena" << endl;
  }
  arena a = construct_arena(&prefix, para);
  if (options["verbosity"] > 5) {
    a.print();
  }
  BENCHMARK_END();

  // Combine the automaton and arena.
  BENCHMARK_START("game");
  if (options["verbosity"] > 0) {
    cout << "    Combining automaton and arena to parity game" << endl;
  }
  game game = combine_game(&parity_automata, &a, &prefix, para);
  if (options["verbosity"] > 5) {
    game.print();
  }
  BENCHMARK_END();

  // Solve the parity game.
  BENCHMARK_START("solve");
  if (options["verbosity"] > 0) {
    cout << "    Solving parity game" << endl;;
  }
  pair<BDD, BDD> winning_regions = solve_game(&game, para);
  if (options["verbosity"] > 5) {
    cout << "      Initial states:" << endl;
    automaton::print_state(game.get_initial_state(),
        &game.get_state_variables(), game.get_parameters());
    cout << "      Even winning region:" << endl;
    automaton::print_transition(
        winning_regions.first * game.get_transition_relation(),
        &game.get_state_variables(), &game.get_state_next_variables(),
        &game.get_action_variables(), game.get_parameters());
    cout << "      Odd winning region:" << endl;
    automaton::print_transition(
        winning_regions.second * game.get_transition_relation(),
        &game.get_state_variables(), &game.get_state_next_variables(),
        &game.get_action_variables(), game.get_parameters());
  }
  solutions.push_front(sl_solution(*formula, prefix, game, winning_regions));
  BENCHMARK_END();

  // Determine states satisfying the formula.
  BDD result = Exists(para->bddmgr, &game.get_action_variables(),
      Exists(para->bddmgr, &game.get_extra_variables(),
          winning_regions.first * game.get_initial_state()));
  if (options["verbosity"] > 5) {
    cout << "      Resulting states:" << endl;
    automaton::print_state(result, para->v, para);
  }

  // Restore the current state variables.
  next_bdd_variable = old_next_bdd_variable;

  return make_pair(result, solutions);
}

pair<modal_formula *, vector<quantifier> >
process_prefix(modal_formula *formula)
{
  vector<pair<string, bool> > quantifiers;
  map<string, unsigned int> quantifier_position;
  map<string, unsigned int> binding_position;

  bool break_loop = false;
  while (!break_loop) {
    switch(formula->get_op()) {
      case 50:
        {
          string variable_name = ((atomic_proposition *) ((modal_formula *)
              formula->get_operand(0))->get_operand(0))->get_proposition();
          quantifier_position[variable_name] = quantifiers.size();
          quantifiers.push_back(make_pair(variable_name, true));
          formula = ((modal_formula *) formula->get_operand(1));
          break;
        }
      case 51:
        {
          string variable_name = ((atomic_proposition *) ((modal_formula *)
              formula->get_operand(0))->get_operand(0))->get_proposition();
          quantifier_position[variable_name] = quantifiers.size();
          quantifiers.push_back(make_pair(variable_name, false));
          formula = ((modal_formula *) formula->get_operand(1));
          break;
        }
      case 52:
        {
          string agent_name = ((atomic_proposition *) ((modal_formula *)
              formula->get_operand(0))->get_operand(0))->get_proposition();
          string variable_name = ((atomic_proposition *) ((modal_formula *)
              formula->get_operand(1))->get_operand(0))->get_proposition();
          binding_position[agent_name] = quantifier_position[variable_name];
          formula = ((modal_formula *) formula->get_operand(2));
          break;
        }
      default:
        break_loop = true;
    }
  }

  vector<vector<basic_agent *> > bound_agents(quantifiers.size());
  for (map<string, unsigned int>::iterator it = binding_position.begin();
       it != binding_position.end(); it++) {
    bound_agents[it->second].push_back((*is_agents)[it->first]);
  }

  vector<quantifier> prefix;

  // Add an existential quantifier to represent sub-strategy selection.
  prefix.push_back(quantifier("$pre", true, true));

  for (unsigned int i = 0; ; i++) {
    // Drop strategies without agents bound to them.
    while (i < quantifiers.size() && bound_agents[i].size() == 0) {
      i++;
    }

    if (i >= quantifiers.size()) {
      break;
    }

    prefix.push_back(quantifier(quantifiers[i].first, quantifiers[i].second,
        false, bound_agents[i]));
  }

  // Add a universal quantifier to represent nondeterminism.
  prefix.push_back(quantifier("$post", false, true));

  return make_pair(formula, prefix);
}

pair<vector<parity_automaton>, list<sl_solution> >
determinize_formula(modal_formula *formula, bdd_parameters *para)
{
  list<modal_formula *> conjuncts;
  if (options["separate_determinization"] == 1) {
    conjuncts = get_conjuncts(formula);
  } else {
    conjuncts.push_back(formula);
  }

  list<sl_solution> solutions;
  vector<parity_automaton> parity_automata;

  for (list<modal_formula *>::iterator it = conjuncts.begin();
       it != conjuncts.end(); it++) {
    if (options["verbosity"] > 0) {
      cout << "    Processing conjunct " << (*it)->to_string() << endl;
    }

    // Construct a generalized non-deterministic Büchi automaton.
    BENCHMARK_START("generalized");
    if (options["verbosity"] > 0) {
      cout << "    Constructing generalized non-deterministic Büchi automaton"
          << endl;
    }
    pair<generalized_automaton, list<sl_solution> > subresult =
        construct_generalized_automaton(*it, para);
    generalized_automaton ga = subresult.first;
    solutions.splice(solutions.end(), subresult.second);
    if (options["verbosity"] > 5) {
      ga.print();
    }
    BENCHMARK_END();

    // Convert to a non-deterministic Büchi automaton.
    BENCHMARK_START("nondeterministic");
    if (options["verbosity"] > 0) {
      cout << "    Converting to nondeterministic Büchi automaton" << endl;
    }
    nondeterministic_automaton na = convert_automaton(&ga, para);
    if (options["verbosity"] > 5) {
      na.print();
    }
    BENCHMARK_END();

    // Determinize the automaton.
    BENCHMARK_START("determinize");
    if (options["verbosity"] > 0) {
      cout << "    Determinizing to parity automaton" << endl;
    }
    parity_automaton pa = determinize_automaton(&na, para);
    parity_automata.push_back(pa);
    if (options["verbosity"] > 5) {
      pa.print();
    }
    BENCHMARK_END();
  }

  return make_pair(parity_automata, solutions);
}

list<modal_formula *> get_conjuncts(modal_formula *formula)
{
  list<modal_formula *> conjuncts;

  if (formula->get_op() == 1) {
    list<modal_formula *> conjuncts1 = get_conjuncts(
        (modal_formula *) formula->get_operand(0));
    list<modal_formula *> conjuncts2 = get_conjuncts(
        (modal_formula *) formula->get_operand(1));
    conjuncts.splice(conjuncts.end(), conjuncts1);
    conjuncts.splice(conjuncts.end(), conjuncts2);
  } else {
    conjuncts.push_back(formula);
  }

  return conjuncts;
}

pair<generalized_automaton, list<sl_solution> >
construct_generalized_automaton(modal_formula *formula, bdd_parameters *para)
{
  pair<intermediate_automaton, list<sl_solution> > result =
      construct_intermediate_automaton(formula, para);
  intermediate_automaton a = finalize_automaton(&result.first, para);
  assert(a.is_auxiliary());

  return make_pair(generalized_automaton(
      a.get_initial_state() * a.get_formula(), a.get_transition_relation(),
      a.get_state_variables(), a.get_state_next_variables(),
      a.get_action_variables(), a.get_fairness_constraints(),
      a.get_parameters()), result.second);
}

pair<intermediate_automaton, list<sl_solution> >
construct_intermediate_automaton(modal_formula *formula, bdd_parameters *para)
{
  switch (formula->get_op()) {
    case 1:       // AND
      {
        pair<intermediate_automaton, list<sl_solution> > s1 =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(0), para);
        pair<intermediate_automaton, list<sl_solution> > s2 =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(1), para);
        intermediate_automaton & a1 = s1.first;
        intermediate_automaton & a2 = s2.first;

        list<sl_solution> solutions;
        solutions.splice(solutions.end(), s1.second);
        solutions.splice(solutions.end(), s2.second);

        return make_pair(intermediate_automaton::product(a1, a2,
            a1.get_formula() * a2.get_formula(),
            a1.is_auxiliary() && a2.is_auxiliary()), solutions);
      }
    case 2:       // OR
      {
        pair<intermediate_automaton, list<sl_solution> > s1 =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(0), para);
        pair<intermediate_automaton, list<sl_solution> > s2 =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(1), para);
        intermediate_automaton & a1 = s1.first;
        intermediate_automaton & a2 = s2.first;

        list<sl_solution> solutions;
        solutions.splice(solutions.end(), s1.second);
        solutions.splice(solutions.end(), s2.second);

        return make_pair(intermediate_automaton::product(a1, a2,
            a1.get_formula() + a2.get_formula(),
            a1.is_auxiliary() && a2.is_auxiliary()), solutions);
      }
    case 4:       // IMPLIES
      {
        pair<intermediate_automaton, list<sl_solution> > s1 =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(0), para);
        pair<intermediate_automaton, list<sl_solution> > s2 =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(1), para);
        intermediate_automaton & a1 = s1.first;
        intermediate_automaton & a2 = s2.first;

        list<sl_solution> solutions;
        solutions.splice(solutions.end(), s1.second);
        solutions.splice(solutions.end(), s2.second);

        return make_pair(intermediate_automaton::product(a1, a2,
            !a1.get_formula() + a2.get_formula(),
            a1.is_auxiliary() && a2.is_auxiliary()), solutions);
      }
    case 3:       // NOT
      {
        pair<intermediate_automaton, list<sl_solution> > s =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(0), para);
        intermediate_automaton & a = s.first;

        return make_pair(intermediate_automaton(a.get_initial_state(),
            a.get_transition_relation(), a.get_state_variables(),
            a.get_state_next_variables(), a.get_action_variables(),
            a.get_fairness_constraints(), !a.get_formula(), a.is_auxiliary(),
            a.get_parameters()), s.second);
      }
    case 53:      // SL X
      {
        pair<intermediate_automaton, list<sl_solution> > s =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(0), para);
        intermediate_automaton a = finalize_automaton(&s.first, para);
        assert(a.is_auxiliary());

        BDD variable = para->bddmgr->bddVar(next_bdd_variable++);
        BDD variable_next = para->bddmgr->bddVar(next_bdd_variable++);

        vector<BDD> state_variables(a.get_state_variables());
        state_variables.push_back(variable);
        vector<BDD> state_next_variables(a.get_state_next_variables());
        state_next_variables.push_back(variable_next);

        return make_pair(intermediate_automaton(a.get_initial_state(),
            a.get_transition_relation() * equivalent(
                a.swap_variables(a.get_formula()), variable),
            state_variables, state_next_variables, a.get_action_variables(),
            a.get_fairness_constraints(), variable, true, a.get_parameters()),
            s.second);
      }
    case 54:      // SL F
      {
        pair<intermediate_automaton, list<sl_solution> > s =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(0), para);
        intermediate_automaton a = finalize_automaton(&s.first, para);
        assert(a.is_auxiliary());

        BDD variable = para->bddmgr->bddVar(next_bdd_variable++);
        BDD variable_next = para->bddmgr->bddVar(next_bdd_variable++);

        vector<BDD> state_variables(a.get_state_variables());
        state_variables.push_back(variable);
        vector<BDD> state_next_variables(a.get_state_next_variables());
        state_next_variables.push_back(variable_next);
        vector<BDD> fairness_constraints(a.get_fairness_constraints());
        fairness_constraints.push_back(!variable + a.get_formula());

        return make_pair(intermediate_automaton(a.get_initial_state(),
            a.get_transition_relation() * equivalent(
                a.get_formula() + variable_next, variable),
            state_variables, state_next_variables, a.get_action_variables(),
            fairness_constraints, variable, true, a.get_parameters()),
            s.second);
      }
    case 55:      // SL G
      {
        pair<intermediate_automaton, list<sl_solution> > s =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(0), para);
        intermediate_automaton a = finalize_automaton(&s.first, para);
        assert(a.is_auxiliary());

        BDD variable = para->bddmgr->bddVar(next_bdd_variable++);
        BDD variable_next = para->bddmgr->bddVar(next_bdd_variable++);

        vector<BDD> state_variables(a.get_state_variables());
        state_variables.push_back(variable);
        vector<BDD> state_next_variables(a.get_state_next_variables());
        state_next_variables.push_back(variable_next);
        vector<BDD> fairness_constraints(a.get_fairness_constraints());
        fairness_constraints.push_back(variable + !a.get_formula());

        return make_pair(intermediate_automaton(a.get_initial_state(),
            a.get_transition_relation() * equivalent(
                a.get_formula() * variable_next, variable),
            state_variables, state_next_variables, a.get_action_variables(),
            fairness_constraints, variable, true, a.get_parameters()),
            s.second);
      }
    case 56:      // SL U
      {
        pair<intermediate_automaton, list<sl_solution> > s1 =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(0), para);
        pair<intermediate_automaton, list<sl_solution> > s2 =
            construct_intermediate_automaton(
                (modal_formula *) formula->get_operand(1), para);
        intermediate_automaton & a1 = s1.first;
        intermediate_automaton a2 = finalize_automaton(&s2.first, para);
        assert(a2.is_auxiliary());

        list<sl_solution> solutions;
        solutions.splice(solutions.end(), s1.second);
        solutions.splice(solutions.end(), s2.second);

        intermediate_automaton a = intermediate_automaton::product(a1, a2,
            para->bddmgr->bddOne(), false);

        BDD variable = para->bddmgr->bddVar(next_bdd_variable++);
        BDD variable_next = para->bddmgr->bddVar(next_bdd_variable++);

        vector<BDD> state_variables(a.get_state_variables());
        state_variables.push_back(variable);
        vector<BDD> state_next_variables(a.get_state_next_variables());
        state_next_variables.push_back(variable_next);
        vector<BDD> fairness_constraints(a.get_fairness_constraints());
        fairness_constraints.push_back(!variable + a2.get_formula());

        return make_pair(intermediate_automaton(a.get_initial_state(),
            a.get_transition_relation() * equivalent(
                a2.get_formula() + a1.get_formula() * variable_next, variable),
            state_variables, state_next_variables, a.get_action_variables(),
            fairness_constraints, variable, true, a.get_parameters()),
            solutions);
      }
    case 50:      // SL <<x>>
    case 51:      // SL [[x]]
    case 52:      // SL (a, x)
      {
        pair<BDD, list<sl_solution> > subresult = check_perfect_recall_formula(
            formula, para);

        return make_pair(intermediate_automaton(para->bddmgr->bddOne(),
            para->bddmgr->bddOne(), vector<BDD>(), vector<BDD>(), *para->v,
            vector<BDD>(), subresult.first, false, para), subresult.second);
      }
    case 0:       // atomic proposition
      {
        return make_pair(intermediate_automaton(para->bddmgr->bddOne(),
            para->bddmgr->bddOne(), vector<BDD>(), vector<BDD>(), *para->v,
            vector<BDD>(), formula->check_formula(para), false, para),
            list<sl_solution>());
      }
  }
}

intermediate_automaton
finalize_automaton(intermediate_automaton *automaton, bdd_parameters *para)
{
  if (automaton->is_auxiliary()) {
    return *automaton;
  } else {
    BDD variable = para->bddmgr->bddVar(next_bdd_variable++);
    BDD variable_next = para->bddmgr->bddVar(next_bdd_variable++);

    vector<BDD> state_variables(automaton->get_state_variables());
    state_variables.push_back(variable);
    vector<BDD> state_next_variables(automaton->get_state_next_variables());
    state_next_variables.push_back(variable_next);

    return intermediate_automaton(automaton->get_initial_state(),
        automaton->get_transition_relation() * equivalent(variable,
            automaton->get_formula()), state_variables, state_next_variables,
        *para->v, automaton->get_fairness_constraints(), variable, true, para);
  }
}

nondeterministic_automaton
convert_automaton(generalized_automaton *automaton, bdd_parameters *para)
{
  if (automaton->get_fairness_constraints().size() == 1) {
    return nondeterministic_automaton(automaton->get_initial_state(),
        automaton->get_transition_relation(), automaton->get_state_variables(),
        automaton->get_state_next_variables(),
        automaton->get_action_variables(),
        automaton->get_fairness_constraints()[0], automaton->get_parameters());
  }

  int extra_states = automaton->get_fairness_constraints().size() + 1;

  // Allocate extra variables.
  vector<BDD> state_variables = automaton->get_state_variables();
  vector<BDD> state_next_variables = automaton->get_state_next_variables();
  int extra_variables_count = extra_states == 1 ? 0 : log_2(extra_states);
  vector<BDD> extra_variables(extra_variables_count);
  vector<BDD> extra_variables_next(extra_variables_count);
  for (int i = 0; i < extra_variables_count; i++) {
    extra_variables[i] = para->bddmgr->bddVar(next_bdd_variable++);
    extra_variables_next[i] = para->bddmgr->bddVar(next_bdd_variable++);
    state_variables.push_back(extra_variables[i]);
    state_next_variables.push_back(extra_variables_next[i]);
  }

  // Extend initial state.
  BDD initial_state = para->bddmgr->bddOne();
  for (int i = 0; i < extra_variables_count; i++) {
    initial_state *= !extra_variables[i];
  }

  // Encode transition.
  BDD transition = para->bddmgr->bddZero();
  BDD current_state = initial_state;
  for (int s = 0; s < extra_states - 1; s++) {
    BDD next_state = para->bddmgr->bddOne();
    for (int i = 0; i < extra_variables_count; i++) {
      if ((s + 1) & (1 << i)) {
        next_state *= extra_variables[i];
      } else {
        next_state *= ~extra_variables[i];
      }
    }
    transition += current_state * (
        ~automaton->get_fairness_constraints()[s] *
        current_state.SwapVariables(state_variables, state_next_variables) +
        automaton->get_fairness_constraints()[s] *
        next_state.SwapVariables(state_variables, state_next_variables));
    current_state = next_state;
  }
  transition += current_state * initial_state.SwapVariables(state_variables,
      state_next_variables);

  return nondeterministic_automaton(
      initial_state * automaton->get_initial_state(),
      transition * automaton->get_transition_relation(),
      state_variables, state_next_variables, automaton->get_action_variables(),
      current_state, automaton->get_parameters());
}

vector<BDD>
calculate_reachable_states(nondeterministic_automaton *automaton,
                           bdd_parameters *para)
{
  // Remove non-state variables from the transition relation.
  BDD existential_transition_relation = Exists(para->bddmgr,
      &automaton->get_action_variables(), automaton->get_transition_relation());

  // Calculate states which are not deadends.
  BDD tmp = para->bddmgr->bddZero();
  BDD serial_states = para->bddmgr->bddOne();
  while (tmp != serial_states) {
    tmp = serial_states;
    serial_states = Exists(para->bddmgr, &automaton->get_state_next_variables(),
        automaton->swap_variables(serial_states) *
            existential_transition_relation);
  }

  vector<BDD> local_states = enumerate_states(
      automaton->get_reachable_states() * serial_states,
      automaton->get_state_variables(), para);

  if (options["verbosity"] > 5) {
    cout << "      Possible states (" << local_states.size() << "):" << endl;
  }

  for (vector<BDD>::iterator it = local_states.begin();
       it != local_states.end(); it++) {
    assert(Exists(para->bddmgr, &automaton->get_state_variables(), *it) ==
        para->bddmgr->bddOne());
    if (options["verbosity"] > 5) {
      automaton::print_state(*it, &automaton->get_state_variables(), para);
    }
  }

  return local_states;
}

vector<BDD>
enumerate_states(const BDD & states, const vector<BDD> & variables,
                 bdd_parameters *para)
{
  vector<BDD> local_states;

  // Enumerate local states.
  vector<BDD>::const_iterator it = variables.begin();
  stack<pair<BDD, bool> > state_stack;
  state_stack.push(make_pair(para->bddmgr->bddOne(), true));
  while (true) {
    while (it != variables.end()) {
      BDD state = state_stack.top().first * !*it * states;
      state_stack.push(make_pair(state, false));
      it++;
      if (state == para->bddmgr->bddZero()) {
        break;
      }
    }

    BDD current_state = state_stack.top().first;
    if (current_state != para->bddmgr->bddZero()) {
      local_states.push_back(current_state);
    }

    while (!state_stack.empty() && state_stack.top().second) {
      state_stack.pop();
      it--;
    }

    if (!state_stack.empty()) {
      state_stack.pop();
      it--;
      BDD state = state_stack.top().first * *it * states;
      state_stack.push(make_pair(state, true));
      it++;
    } else {
      break;
    }
  }

  return local_states;
}

parity_automaton
determinize_automaton(nondeterministic_automaton *automaton,
                      bdd_parameters *para)
{
  // Calculate reachable states.
  vector<BDD> reachable_states = calculate_reachable_states(automaton, para);
  unsigned int reachable_states_count = reachable_states.size();
  vector<bool> accepting_states = vector<bool>(reachable_states_count);
  for (unsigned int i = 0; i < reachable_states_count; i++) {
    accepting_states[i] = reachable_states[i] *
        automaton->get_fairness_constraint() != para->bddmgr->bddZero();
  }

  // Symbolic subset encoding.
  unsigned int max_tuple_size = reachable_states_count + 1;

  vector<vector<BDD> > q;
  vector<vector<BDD> > q_next;
  vector<BDD> mark;
  vector<BDD> mark_next;

  vector<vector<BDD> > phi;
  vector<BDD> smallM;
  vector<BDD> bigM;
  vector<BDD> empty;
  vector<BDD> empty_next;

  vector<BDD> state;
  vector<BDD> state_next;

  BDD initial_state = para->bddmgr->bddOne();
  vector<BDD> colouring;

  BDD cumulative_colour = para->bddmgr->bddZero();

  for (unsigned int t = 0; t < max_tuple_size; t++) {
    if (options["verbosity"] > 4) {
      cout << "      Calculating parity automaton with bound " << (t + 1)
          << endl;
    }

    // Allocate q and mark.
    q.push_back(vector<BDD>(reachable_states_count));
    q_next.push_back(vector<BDD>(reachable_states_count));
    for (unsigned int j = 0; j < reachable_states_count; j++) {
      q[t][j] = para->bddmgr->bddVar(next_bdd_variable++);
      q_next[t][j] = para->bddmgr->bddVar(next_bdd_variable++);
      state.push_back(q[t][j]);
      state_next.push_back(q_next[t][j]);
    }

    mark.push_back(para->bddmgr->bddVar(next_bdd_variable++));
    mark_next.push_back(para->bddmgr->bddVar(next_bdd_variable++));
    state.push_back(mark[t]);
    state_next.push_back(mark_next[t]);

    // Precalculate phi, gammas, and empty.
    phi.push_back(vector<BDD>(reachable_states_count));
    if (t == 0) {
      BDD h = para->bddmgr->bddZero();
      for (unsigned int i = 0; i < reachable_states.size(); i++) {
        h += q[0][i] * reachable_states[i];
      }
      for (unsigned int j = 0; j < reachable_states_count; j++) {
        phi[0][j] = Exists(para->bddmgr, &automaton->get_state_variables(),
            Exists(para->bddmgr, &automaton->get_state_next_variables(),
                h * automaton->get_transition_relation() *
                    automaton->swap_variables(reachable_states[j])));
      }
    } else {
      for (unsigned int j = 0; j < reachable_states_count; j++) {
          phi[t][j] = phi[0][j].SwapVariables(q[t], q[0]);
      }
    }

    smallM.push_back(para->bddmgr->bddOne());
    for (unsigned int j = 0; j < reachable_states_count; j++) {
      smallM[t] *= !q[t][j];
    }
    if (t > 0) {
      smallM[t] += smallM[t - 1];
    }

    bigM.push_back(para->bddmgr->bddZero());
    for (unsigned int j = 0; j < reachable_states_count; j++) {
      bigM[t] += q[t][j];
    }
    for (unsigned int i = 0; i < t; i++) {
      bigM[i] *= !bigM[t];
    }

    empty.push_back(para->bddmgr->bddOne());
    empty_next.push_back(para->bddmgr->bddOne());
    for (unsigned int j = 0; j < reachable_states_count; j++) {
      empty[t] *= !q[t][j];
      empty_next[t] *= !q_next[t][j];
    }

    // Initial state.
    if (t == 0) {
      for (unsigned int j = 0; j < reachable_states.size(); j++) {
        BDD state = Exists(para->bddmgr, &automaton->get_state_variables(),
            Exists(para->bddmgr, &automaton->get_state_next_variables(),
                reachable_states[j] * automaton->get_initial_state()));
        assert(state == para->bddmgr->bddOne() ||
            state == para->bddmgr->bddZero());
        initial_state *= equivalent(q[0][j], state);
      }
    } else {
      for (unsigned int j = 0; j < reachable_states_count; j++) {
        initial_state *= !q[t][j];
      }
    }
    initial_state *= !mark[t];

    // Transition function (recalculate completely each time).
    BDD transition_relation = para->bddmgr->bddOne();
    for (unsigned int i = 0; i <= t; i++) {
      BDD tmp = !empty_next[i];
      for (unsigned int k = 0; k < reachable_states_count; k++) {
        if (!accepting_states[k]) {
          BDD tmp2 = !q_next[i][k];
          for (unsigned int j = i + 1; j <= t; j++) {
            tmp2 += phi[j][k];
          }
          tmp *= tmp2;
        }
      }
      transition_relation *= equivalent(mark_next[i], tmp);
    }

    for (unsigned int i = 0; i <= t; i++) {
      for (unsigned int k = 0; k < reachable_states_count; k++) {
        BDD tmp = !smallM[i] * phi[i][k];
        if (i > 0) {
          if (i <= t - 1) {
            tmp += smallM[i] * phi[i + 1][k];
          }
          if (accepting_states[k]) {
            tmp += !smallM[i - 1] * bigM[i - 1] * phi[0][k];
            tmp += smallM[i] * bigM[i] * phi[0][k];
          }
          for (unsigned int j = 0; j < i; j++) {
            tmp *= !(q_next[j][k] * mark_next[j]);
          }
        }
        transition_relation *= equivalent(q_next[i][k], tmp);
      }
    }

    // Colouring function.
    if (t == 0) {
      // Set colouring[0].
      colouring.push_back(!empty[0] * mark[0]);
      cumulative_colour += colouring.back();

      assert(colouring.size() == 1);
    } else {
      // Remove residual colour.
      colouring.pop_back();

      BDD tmp = para->bddmgr->bddOne();
      for (unsigned int j = 0; j < t; j++) {
        tmp *= !empty[j] * !mark[j];
      }

      // Set colouring[2 * t - 1];
      if (t == 1) {
        colouring.push_back(tmp * empty[t] + empty[0]);
      } else {
        colouring.push_back(tmp * empty[t]);
      }
      cumulative_colour += colouring.back();

      // Set colouring[2 * t];
      colouring.push_back(tmp * mark[t] * !empty[t]);
      cumulative_colour += colouring.back();

      assert(colouring.size() == 2 * t + 1);
    }

    // Add residual colour (odd).
    colouring.push_back(!cumulative_colour);
    assert(colouring.size() % 2 == 0);


    parity_automaton result = parity_automaton(initial_state,
        transition_relation, state, state_next,
        automaton->get_action_variables(), colouring,
        automaton->get_parameters());

    // Condition on increasing the bound.
    BDD increase_condition = para->bddmgr->bddZero();
    for (unsigned int j = 0; j < reachable_states_count; j++) {
      if (accepting_states[j]) {
        BDD tmp = phi[0][j];
        for (unsigned int i = 0; i <= t; i++) {
          tmp *= !(q_next[i][j] * mark_next[i]);
        }
        increase_condition += tmp;
      }
    }
    increase_condition *= bigM[t] * !smallM[t];
    increase_condition *= result.get_reachable_states() * transition_relation;

    if (increase_condition == para->bddmgr->bddZero()) {
      return result;
    }
  }

  assert(false); // Should never get here (due to non-confluence).
}

arena
construct_arena(vector<quantifier> *prefix, bdd_parameters *para)
{
  unsigned int inflated_counter_variables_count = log_2(prefix->size());
  vector<BDD> inflated_counter_variables(inflated_counter_variables_count);
  vector<BDD> inflated_counter_next_variables(inflated_counter_variables_count);
  for (unsigned int i = 0; i < inflated_counter_variables_count; i++) {
    inflated_counter_variables[i] = para->bddmgr->bddVar(next_bdd_variable++);
    inflated_counter_next_variables[i] = para->bddmgr->bddVar(
        next_bdd_variable++);
  }

  vector<BDD> inflated_counter(prefix->size());
  vector<BDD> inflated_counter_next(prefix->size());
  for (unsigned int i = 0; i < prefix->size(); i++) {
    inflated_counter[i] = para->bddmgr->bddOne();
    inflated_counter_next[i] = para->bddmgr->bddOne();
    for (unsigned int j = 0; j < inflated_counter_variables_count; j++) {
      if ((i & (1 << j)) == 0) {
        inflated_counter[i] *= !inflated_counter_variables[j];
        inflated_counter_next[i] *= !inflated_counter_next_variables[j];
      } else {
        inflated_counter[i] *= inflated_counter_variables[j];
        inflated_counter_next[i] *= inflated_counter_next_variables[j];
      }
    }
  }

  vector<vector<string> > actions_names(prefix->size());
  vector<vector<BDD> > actions_variables(prefix->size() - 1);
  vector<vector<BDD> > actions_next_variables(prefix->size() - 1);

  vector<BDD> cumulated_actions;
  vector<BDD> cumulated_actions_next;

  vector<vector<BDD> > actions(prefix->size() - 1);
  vector<vector<BDD> > actions_next(prefix->size() - 1);

  if (options["verbosity"] > 5) {
    cout << "      Inflated states:" << endl;
  }
  unsigned int max_actions = 2; // Necessary for generalized parity game memory.
  for (unsigned int i = 0; i < actions_names.size(); i++) {
    set<string> tmp;
    for (unsigned int j = 0; j < (*prefix)[i].get_agents().size(); j++) {
      set<string> *agent_actions = (*prefix)[i].get_agents()[j]->get_actions();
      if (j == 0) {
        tmp = *agent_actions;
      } else {
        set<string> tmp2;
        set_intersection(tmp.begin(), tmp.end(), agent_actions->begin(),
            agent_actions->end(), inserter(tmp2, tmp2.end()));
        tmp = tmp2;
      }
    }

    unsigned int actions_variables_count = tmp.size() <= 1 ?
        0 : log_2(tmp.size());
    max_actions = max(max_actions, (unsigned int) tmp.size());
    actions_names[i] = vector<string>(tmp.begin(), tmp.end());

    if (i < actions_names.size() - 1) {
      actions_variables[i] = vector<BDD>(actions_variables_count);
      actions_next_variables[i] = vector<BDD>(actions_variables_count);

      for (unsigned int j = 0; j < actions_variables_count; j++) {
        actions_variables[i][j] = para->bddmgr->bddVar(next_bdd_variable++);
        actions_next_variables[i][j] = para->bddmgr->bddVar(
            next_bdd_variable++);
        cumulated_actions.push_back(actions_variables[i][j]);
        cumulated_actions_next.push_back(actions_next_variables[i][j]);
      }

      actions[i] = vector<BDD>(tmp.size());
      actions_next[i] = vector<BDD>(tmp.size());

      for (unsigned int j = 0; j < tmp.size(); j++) {
        actions[i][j] = para->bddmgr->bddOne();
        actions_next[i][j] = para->bddmgr->bddOne();

        for (unsigned int k = 0; k < actions_variables_count; k++) {
          actions[i][j] *= (j & (1 << k)) ?
              actions_variables[i][k] : !actions_variables[i][k];
          actions_next[i][j] *= (j & (1 << k)) ?
              actions_next_variables[i][k] : !actions_next_variables[i][k];
        }
      }
    }
    if (options["verbosity"] > 5) {
      cout << "        " << (*prefix)[i].get_variable_name() << ": "
          << tmp.size() << " actions, " << (*prefix)[i].get_agents().size()
          << " agents, " << actions_variables_count << " variables" << endl;
    }
  }

  unsigned int transition_actions_variables_count = log_2(max_actions);
  vector<BDD> transition_actions_variables(transition_actions_variables_count);
  for (unsigned int i = 0; i < transition_actions_variables_count; i++) {
    transition_actions_variables[i] = para->bddmgr->bddVar(next_bdd_variable++);
  }
  vector<BDD> transition_actions(max_actions);
  for (unsigned int i = 0; i < max_actions; i++) {
    transition_actions[i] = para->bddmgr->bddOne();
    for (unsigned int j = 0; j < transition_actions_variables_count; j++) {
      transition_actions[i] *= (i & (1 << j)) ?
          transition_actions_variables[j] : !transition_actions_variables[j];
    }
  }

  BDD equal_transition = equivalent_vectors(*para->v, *para->pv, para);

  // Initial state.
  BDD initial_state = inflated_counter[0];
  for (unsigned int i = 0; i < actions.size(); i++) {
    if (actions[i].size() > 0) {
      initial_state *= actions[i][0];
    }
  }

  // Transition relation.
  BDD transition_relation = para->bddmgr->bddZero();
  for (unsigned int s = 0; s < prefix->size() - 1; s++) {
    BDD tmp = equal_transition;
    for (unsigned int i = s; i < prefix->size() - 1; i++) {
      if (actions[i].size() > 0) {
        tmp *= actions[i][0];
        if (i > s) {
          tmp *= actions_next[i][0];
        }
      }
    }
    tmp *= inflated_counter[s] * inflated_counter_next[s + 1];
    if (!(*prefix)[s].is_auxiliary()) {
      BDD valid_actions = para->bddmgr->bddZero();
      for (unsigned int a = 0; a < actions_names[s].size(); a++) {
        BDD tmp2 = para->bddmgr->bddOne();
        const vector<basic_agent *> sharing_agents = (*prefix)[s].get_agents();
        for (unsigned int k = 0; k < sharing_agents.size(); k++) {
          BDD tmp3 = para->bddmgr->bddZero();
          vector<protocol_line *> *protocol = sharing_agents[k]->get_protocol();
          BDD other_branch = para->bddmgr->bddOne();
          for (unsigned int l = 0; l < protocol->size(); l++) {
            BDD condition;
            if ((*protocol)[l]->get_condition()->is_other_branch()) {
              condition = other_branch;
            } else {
              condition = (*protocol)[l]->get_condition()
                  ->encode_bdd_flat(para, para->bddmgr->bddOne());
              other_branch *= !condition;
            }
            set<string> *line_actions = (*protocol)[l]->get_actions();
            if (line_actions->find(actions_names[s][a]) !=
                line_actions->end()) {
              tmp3 += condition;
            }
          }
          tmp2 *= tmp3;
        }
        tmp2 *= transition_actions[a];
        tmp2 *= actions_next[s][a];
        valid_actions += tmp2;
      }
      if (!Exists(para->bddmgr, &transition_actions_variables, Exists(
              para->bddmgr, &actions_next_variables[s], valid_actions)) *
          *para->reach != para->bddmgr->bddZero()) {
        cout << "Warning: global state with no shared action for strategy '"
            << (*prefix)[s].get_variable_name() << "'." << endl;
      }
      transition_relation += tmp * valid_actions;
    } else {
      if (s == 0) {
        // Sub-strategy selection.
        tmp *= transition_actions[0] + transition_actions[1];
      } else {
        tmp *= transition_actions[0];
      }
      transition_relation += tmp;
    }
    equal_transition *= equivalent_vectors(actions_variables[s],
        actions_next_variables[s], para);
  }

  BDD action_connector = para->bddmgr->bddOne();
  for (unsigned int s = 0; s < prefix->size(); s++) {
    BDD tmp = para->bddmgr->bddZero();
    if (!(*prefix)[s].is_auxiliary()) {
      for (unsigned int a = 0; a < actions_names[s].size(); a++) {
        BDD tmp2 = (s < prefix->size() - 1 ?
            actions[s] : transition_actions)[a];
        for (unsigned int j = 0; j < (*prefix)[s].get_agents().size(); j++) {
          tmp2 *= (*prefix)[s].get_agents()[j]->encode_action(para,
              actions_names[s][a]);
        }
        tmp += tmp2;
      }
      action_connector *= tmp;
    }
  }

  BDD temporal_transition = para->bddmgr->bddOne();
  for (unsigned int i = 0; i < (*para->vRT).size(); i++) {
    temporal_transition *= (*para->vRT)[i];
  }
  temporal_transition *= inflated_counter[prefix->size() - 1];
  temporal_transition *= inflated_counter_next[0];
  for (unsigned int i = 0; i < actions_next.size(); i++) {
    if (actions_next[i].size() > 0) {
      temporal_transition *= actions_next[i][0];
    }
  }
  temporal_transition *= action_connector;
  vector<string> &last_actions_names = actions_names[actions_names.size() - 1];
  if (!(*prefix)[prefix->size() - 1].is_auxiliary()) {
    BDD last_actions = para->bddmgr->bddZero();
    for (unsigned int a = 0; a < last_actions_names.size(); a++) {
      BDD tmp = transition_actions[a];
      for (unsigned int j = 0; j < (*prefix)[prefix->size() - 1].get_agents()
           .size(); j++) {
        tmp *= (*prefix)[prefix->size() - 1].get_agents()[j]
            ->encode_action(para, last_actions_names[a]);
      }
      last_actions += tmp;
    }
    temporal_transition *= last_actions;
  } else {
    temporal_transition *= transition_actions[0];
  }

  transition_relation += Exists(para->bddmgr, para->a, temporal_transition);

  vector<BDD> inflated_variables(cumulated_actions);
  inflated_variables.insert(inflated_variables.end(),
      inflated_counter_variables.begin(), inflated_counter_variables.end());
  vector<BDD> inflated_next_variables(cumulated_actions_next);
  inflated_next_variables.insert(inflated_next_variables.end(),
      inflated_counter_next_variables.begin(),
      inflated_counter_next_variables.end());

  vector<BDD> state_variables(*para->v);
  state_variables.insert(state_variables.end(), inflated_variables.begin(),
      inflated_variables.end());
  vector<BDD> state_next_variables(*para->pv);
  state_next_variables.insert(state_next_variables.end(),
      inflated_next_variables.begin(), inflated_next_variables.end());

  // Existential player.
  BDD existential_player = para->bddmgr->bddZero();
  for (unsigned int i = 0; i < prefix->size(); i++) {
    if ((*prefix)[i].is_existential()) {
      existential_player += inflated_counter[i];
    }
  }

  return arena(initial_state, transition_relation, state_variables,
      state_next_variables, transition_actions_variables, inflated_variables,
      inflated_next_variables, inflated_counter, inflated_counter_next,
      vector<vector<string> >(actions_names.begin(), actions_names.end() - 1),
      actions, actions_next, transition_actions, existential_player, para);
}

game
combine_game(vector<parity_automaton> *automata, arena *arena,
             vector<quantifier> *prefix, bdd_parameters *para)
{
  for (unsigned int i = 0; i < automata->size(); i++) {
    assert((*automata)[i].get_parameters() == arena->get_parameters());
  }

  // Add a counter for selecting sub-strategies.
  unsigned int sub_strategy_counter_variables_count = automata->size() <= 1 ?
      0 : log_2(automata->size());
  vector<BDD> sub_strategy_counter_variables(
      sub_strategy_counter_variables_count);
  vector<BDD> sub_strategy_counter_next_variables(
      sub_strategy_counter_variables_count);
  for (unsigned int i = 0; i < sub_strategy_counter_variables_count; i++) {
    sub_strategy_counter_variables[i] = para->bddmgr->bddVar(
        next_bdd_variable++);
    sub_strategy_counter_next_variables[i] = para->bddmgr->bddVar(
        next_bdd_variable++);
  }
  vector<BDD> sub_strategy_counter(automata->size());
  vector<BDD> sub_strategy_counter_next(automata->size());
  for (unsigned int i = 0; i < automata->size(); i++) {
    sub_strategy_counter[i] = para->bddmgr->bddOne();
    sub_strategy_counter_next[i] = para->bddmgr->bddOne();
    for (unsigned int j = 0; j < sub_strategy_counter_variables_count; j++) {
      sub_strategy_counter[i] *= (i & (1 << j)) ?
          sub_strategy_counter_variables[j] :
          !sub_strategy_counter_variables[j];
      sub_strategy_counter_next[i] *= (i & (1 << j)) ?
          sub_strategy_counter_next_variables[j] :
          !sub_strategy_counter_next_variables[j];
    }
  }

  // Extend parity automaton initial state.
  BDD initial_state = arena->get_initial_state() * sub_strategy_counter[0];
  for (unsigned int i = 0; i < automata->size(); i++) {
    initial_state *= (*automata)[i].get_initial_state();
  }

  // Extend parity automaton transition relation.
  BDD transition_relation = para->bddmgr->bddZero();
  BDD equal_transition = equivalent_vectors(*para->v, *para->pv, para);
  for (unsigned int i = 0; i < automata->size(); i++) {
    equal_transition *= equivalent_vectors((*automata)[i].get_state_variables(),
        (*automata)[i].get_state_next_variables(), para);
  }
  for (unsigned int i = 0; i < prefix->size() - 1; i++) {
    transition_relation += equal_transition * arena->get_inflated_counter()[i] *
        arena->get_inflated_counter_next()[i + 1];
  }
  BDD temporal_transition = arena->get_inflated_counter()[prefix->size() - 1] *
      arena->get_inflated_counter_next()[0];
  for (unsigned int i = 0; i < automata->size(); i++) {
    temporal_transition *= (*automata)[i].get_transition_relation();
  }
  transition_relation += temporal_transition;
  transition_relation *= arena->get_transition_relation();
  BDD memory_connector = para->bddmgr->bddZero();
  for (unsigned int i = 0; i < automata->size(); i++) {
    memory_connector += sub_strategy_counter[i] * (
        (arena->get_transition_actions()[0] +
            !arena->get_inflated_counter()[0]) * sub_strategy_counter_next[i] +
            (arena->get_transition_actions()[1] *
                arena->get_inflated_counter()[0]) * sub_strategy_counter_next[
                (i + 1) % automata->size()]);
  }
  transition_relation *= memory_connector;

  // Extra and state variables.
  vector<BDD> extra_variables;
  for (unsigned int i = 0; i < automata->size(); i++) {
    extra_variables.insert(extra_variables.end(),
        (*automata)[i].get_state_variables().begin(),
        (*automata)[i].get_state_variables().end());
  }
  extra_variables.insert(extra_variables.end(),
      arena->get_inflated_variables().begin(),
      arena->get_inflated_variables().end());
  extra_variables.insert(extra_variables.end(),
      sub_strategy_counter_variables.begin(),
      sub_strategy_counter_variables.end());
  vector<BDD> state_variables(*para->v);
  state_variables.insert(state_variables.end(), extra_variables.begin(),
      extra_variables.end());

  // Next extra and next state variables.
  vector<BDD> extra_next_variables;
  for (unsigned int i = 0; i < automata->size(); i++) {
    extra_next_variables.insert(extra_next_variables.end(),
        (*automata)[i].get_state_next_variables().begin(),
        (*automata)[i].get_state_next_variables().end());
  }
  extra_next_variables.insert(extra_next_variables.end(),
      arena->get_inflated_next_variables().begin(),
      arena->get_inflated_next_variables().end());
  extra_next_variables.insert(extra_next_variables.end(),
      sub_strategy_counter_next_variables.begin(),
      sub_strategy_counter_next_variables.end());
  vector<BDD> state_next_variables(*para->pv);
  state_next_variables.insert(state_next_variables.end(),
      extra_next_variables.begin(), extra_next_variables.end());

  // Colouring variables.
  vector<vector<BDD> > colourings(automata->size());
  for (unsigned int i = 0; i < automata->size(); i++) {
    colourings[i] = (*automata)[i].get_colouring();
  }

  return game(initial_state, transition_relation, state_variables,
      state_next_variables, arena->get_action_variables(),
      arena->get_inflated_counter(), arena->get_inflated_counter_next(),
      arena->get_action_names(), arena->get_actions(),
      arena->get_actions_next(), arena->get_transition_actions(),
      arena->get_inflated_variables(), arena->get_inflated_next_variables(),
      arena->get_existential_player(), colourings, sub_strategy_counter,
      sub_strategy_counter_next, extra_variables, extra_next_variables,
      arena->get_parameters());
}

pair<BDD, BDD>
solve_game(game *game, bdd_parameters *para)
{
  // Find finite winning regions (from which deadends can be forced).
  BDD world = game->get_reachable_states();
  pair<BDD, BDD> finite_regions = deadend_regions(game, world, para);

  // Find infinite winning regions (parity game).
  BDD serial_world = world * !Exists(para->bddmgr,
      &game->get_action_variables(),
      finite_regions.first + finite_regions.second);

  pair<BDD, BDD> infinite_regions;
  if (options["separate_determinization"] == 1) {
    infinite_regions = winning_regions_separate(game, serial_world, para);
  } else {
    infinite_regions = winning_regions_simple(game, serial_world, para);
  }

  assert(Exists(para->bddmgr, &game->get_action_variables(),
      finite_regions.first) * Exists(para->bddmgr,
      &game->get_action_variables(), infinite_regions.first) ==
      para->bddmgr->bddZero());
  assert(Exists(para->bddmgr, &game->get_action_variables(),
      finite_regions.second) * Exists(para->bddmgr,
      &game->get_action_variables(), infinite_regions.second) ==
      para->bddmgr->bddZero());

  // Combine the regions.
  pair<BDD, BDD> regions = make_pair(
      finite_regions.first + infinite_regions.first,
      finite_regions.second + infinite_regions.second);
  assert(Exists(para->bddmgr, &game->get_action_variables(),
      regions.first + regions.second) == world);
  assert(Exists(para->bddmgr, &game->get_action_variables(), regions.first) *
        Exists(para->bddmgr, &game->get_action_variables(), regions.second) ==
        para->bddmgr->bddZero());

  return regions;
}

pair<BDD, BDD>
deadend_regions(game *game, BDD world, bdd_parameters *para)
{
  BDD deadends = world * !Exists(para->bddmgr,
      &game->get_state_next_variables(), Exists(para->bddmgr,
          &game->get_action_variables(), game->get_transition_relation()));

  BDD deadends_player = deadends * game->get_existential_player();
  BDD deadends_opponent = deadends * !game->get_existential_player();

  return make_pair(
      calculate_attractor(game, deadends_opponent, world, true, para),
      calculate_attractor(game, deadends_player, world, false, para));
}

pair<BDD, BDD>
winning_regions_simple(game *game, BDD world, bdd_parameters *para)
{
  assert(game->get_colourings().size() == 1);

  if (world == para->bddmgr->bddZero()) {
    return make_pair(para->bddmgr->bddZero(), para->bddmgr->bddZero());
  }

  // Find the lowest non-empty priority.
  unsigned int priority = 0;
  while (priority + 1 < game->get_colourings()[0].size() &&
         world * game->get_colourings()[0][priority] ==
         para->bddmgr->bddZero()) {
    priority++;
  }
  if (options["verbosity"] > 5) {
    cout << "      Priority " << priority << endl;
  }

  // Determine the player.
  bool existential_player = priority % 2 == 0;
  if (options["verbosity"] > 5) {
    cout << "      " << (existential_player ? "Existential" : "Universal")
        << " player" << endl;
  }

  // Calculate the attractor of the lowest priority.
  BDD attr = calculate_attractor(game, Exists(para->bddmgr,
      &game->get_state_next_variables(), world *
          game->get_colourings()[0][priority] *
          game->get_transition_relation() * game->swap_variables(world)),
      world, existential_player, para);
  if (options["verbosity"] > 5) {
    cout << "      Attractor A:" << endl;
    automaton::print_transition(attr * game->get_transition_relation(),
        &game->get_state_variables(), &game->get_state_next_variables(),
        &game->get_action_variables(), para);
  }

  // Calculate winning regions with the lowest priority removed.
  pair<BDD, BDD> subresult = winning_regions_simple(game,
      world * !Exists(para->bddmgr, &game->get_action_variables(), attr), para);

  // First case - opponent has no winning region.
  if (existential_player && subresult.second == para->bddmgr->bddZero()) {
    return make_pair(subresult.first + attr, para->bddmgr->bddZero());
  } else if (!existential_player &&
             subresult.first == para->bddmgr->bddZero()) {
    return make_pair(para->bddmgr->bddZero(), subresult.second + attr);
  }

  // Second case - opponent has a winning region.
  // Calculate the attractor of opponent's winning region.
  BDD attr2 = calculate_attractor(game,
      world * (existential_player ? subresult.second : subresult.first),
          world, !existential_player, para);
  if (options["verbosity"] > 5) {
    cout << "      Attractor B:" << endl;
    automaton::print_transition(attr2 * game->get_transition_relation(),
        &game->get_state_variables(), &game->get_state_next_variables(),
        &game->get_action_variables(), para);
  }

  // Calculate the winning regions with the opponent's attractor removed.
  pair<BDD, BDD> subresult2 = winning_regions_simple(game, world * !Exists(
      para->bddmgr, &game->get_action_variables(), attr2), para);
  if (existential_player) {
    return make_pair(subresult2.first, subresult2.second + attr2);
  } else {
    return make_pair(subresult2.first + attr2, subresult2.second);
  }
}

pair<BDD, BDD>
winning_regions_separate(game *game, BDD world, bdd_parameters *para)
{
  // Determine the lowest priorities.
  vector<unsigned int> highest_priorities(game->get_colourings().size());
  bool all_empty = true;
  for (unsigned int i = 0; i < game->get_colourings().size(); i++) {
    const vector<BDD> & colouring = game->get_colourings()[i];
    unsigned int d = 0;
    while (2 * d < colouring.size() &&
           colouring[2 * d] * world == para->bddmgr->bddZero() &&
           (2 * d + 1 >= colouring.size() ||
            colouring[2 * d + 1] * world == para->bddmgr->bddZero())) {
      d++;
    }
    highest_priorities[i] = d;
    all_empty &= 2 * d >= colouring.size();
  }

  // Base case.
  if (all_empty) {
    assert(world == para->bddmgr->bddZero());
    return make_pair(para->bddmgr->bddZero(), para->bddmgr->bddZero());
  }
  assert(world != para->bddmgr->bddZero());

  BDD existential_strategy = para->bddmgr->bddZero();

  for (unsigned int i = 0; i < highest_priorities.size(); i++) {
    const vector<BDD> & colouring = game->get_colourings()[i];
    if (2 * highest_priorities[i] < colouring.size()) {
      BDD min_even = world * colouring[2 * highest_priorities[i]];
      BDD min_odd = (2 * highest_priorities[i] + 1 < colouring.size()) ?
        world * colouring[2 * highest_priorities[i] + 1] :
        para->bddmgr->bddZero();
      assert(min_even != para->bddmgr->bddZero() ||
          min_odd != para->bddmgr->bddZero());

      BDD g = world * !Exists(para->bddmgr, &game->get_action_variables(),
          calculate_attractor(game, min_even, world, true, para));
      BDD h = g * !Exists(para->bddmgr, &game->get_action_variables(),
          calculate_attractor(game, g * min_odd, g, false, para));
      BDD previous_h;

      pair<BDD, BDD> subresult;
      BDD w;

      do {
        assert(h * world == h);
        assert(h != world);
        previous_h = h;

        subresult = winning_regions_separate(game, h, para);
        w = Exists(para->bddmgr, &game->get_action_variables(),
            subresult.second);
        assert(Exists(para->bddmgr, &game->get_action_variables(),
            subresult.first) == h * !w);

        // Existential strategy: attract to subresult.
        existential_strategy += calculate_attractor(game, subresult.first, g,
            true, para);

        g = g * !Exists(para->bddmgr, &game->get_action_variables(),
            calculate_attractor(game, h * !w, g, true, para));
        h = g * !Exists(para->bddmgr, &game->get_action_variables(),
            calculate_attractor(game, g * min_odd, g, false, para));
      } while (w != previous_h);

      // Case 1.
      if (g != para->bddmgr->bddZero()) {
        // Universal Strategy: attract to min_odd or play according to
        // subresult.
        BDD restrictor = Exists(para->bddmgr, &game->get_state_next_variables(),
            game->get_transition_relation() * game->swap_variables(g));
        BDD universal_strategy = calculate_attractor(game,
            g * (min_odd * restrictor + subresult.second), world, false, para);
        assert(universal_strategy != para->bddmgr->bddZero());

        // Keep memory constant (not strictly necessary).
        universal_strategy *= !game->get_inflated_counter()[0] +
            game->get_transition_actions()[0];

        // Solve subgame.
        BDD subgame = world * !Exists(para->bddmgr,
            &game->get_action_variables(), universal_strategy);
        assert(subgame != world);
        pair<BDD, BDD> subresult2 = winning_regions_separate(game, subgame,
            para);

        return make_pair(subresult2.first, subresult2.second +
            universal_strategy);
      }
    }
  }

  // Existential strategy: Attract to min_even accorging to counter.
  BDD restrictor = Exists(para->bddmgr, &game->get_state_next_variables(),
      game->get_transition_relation() * game->swap_variables(world));
  for (unsigned int i = 0; i < highest_priorities.size(); i++) {
    BDD min_even = world * restrictor *
        game->get_colourings()[i][2 * highest_priorities[i]];
    BDD min_even_strategy = calculate_attractor(game, min_even, world, true,
        para) * !Exists(para->bddmgr, &game->get_action_variables(), min_even);

    // Update the memory appropriately.
    min_even *= !game->get_inflated_counter()[0] +
        game->get_transition_actions()[1];
    min_even_strategy *= !game->get_inflated_counter()[0] +
        game->get_transition_actions()[0];

    existential_strategy += (min_even_strategy + min_even) *
        game->get_sub_strategy_counter()[i];
  }

  // Case 2.
  assert(Exists(para->bddmgr, &game->get_action_variables(),
      existential_strategy) == world);
  return make_pair(existential_strategy, para->bddmgr->bddZero());
}

BDD
calculate_attractor(game *game, BDD states, BDD world, bool existential_player,
                    bdd_parameters *para)
{
  BDD world_next = game->swap_variables(world);
  BDD tmp = para->bddmgr->bddOne();
  while (tmp != states) {
    tmp = states;

    BDD target = Exists(para->bddmgr, &game->get_action_variables(), states);
    BDD target_next = game->swap_variables(target);

    BDD transition_player = target_next * game->get_transition_relation();
    states += !target * world * Exists(
        para->bddmgr, &game->get_state_next_variables(), transition_player) *
            (existential_player ? game->get_existential_player() :
                !game->get_existential_player());

    BDD transition_opponent = world_next * !target_next *
        game->get_transition_relation();
    states += !target * world * !Exists(
        para->bddmgr, &game->get_action_variables(), Exists(para->bddmgr,
            &game->get_state_next_variables(), transition_opponent)) * (
                existential_player ? !game->get_existential_player() :
                    game->get_existential_player());
  }
  return states;
}

BDD equivalent(const BDD & a, const BDD & b)
{
  return !a * !b + a * b;
}

BDD equivalent_vectors(const vector<BDD> & a, const vector<BDD> & b,
                       bdd_parameters *para)
{
  assert(a.size() == b.size());

  BDD result = para->bddmgr->bddOne();
  for (unsigned int i = 0; i < a.size(); i++) {
    result *= equivalent(a[i], b[i]);
  }
  return result;
}
