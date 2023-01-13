#include "sl_perfect_recall.hh"


sl_solution::sl_solution(const modal_formula & formula,
                         const vector<quantifier> & prefix,
                         const game & parity_game,
                         const pair<BDD, BDD> & winning_regions):
    formula(formula), prefix(prefix), parity_game(parity_game),
    winning_regions(winning_regions)
{
}

const modal_formula &
sl_solution::get_formula() const
{
  return formula;
}

const vector<quantifier> &
sl_solution::get_prefix() const
{
  return prefix;
}

const game &
sl_solution::get_parity_game() const
{
  return parity_game;
}

const pair<BDD, BDD> &
sl_solution::get_winning_regions() const
{
  return winning_regions;
}

void
sl_solution::print_witness(const vector<BDD> reachable_states,
                           bdd_parameters *para) const
{
  bool is_witness = get_prefix()[1].is_existential();
  BDD restriction = para->bddmgr->bddOne();
  const BDD &region = is_witness ?
      get_winning_regions().first : get_winning_regions().second;

  for (unsigned int w = 1; w < get_prefix().size() - 1 &&
       get_prefix()[w].is_existential() == is_witness; w++) {
    vector<BDD> automaton_states;

    cout << "    Strategy " << get_prefix()[w].get_quantifier() << ":" << endl;

    // Start state.
    cout << "      start:" << endl;
    for (unsigned int i = 0; i < reachable_states.size(); i++) {
      BDD initial_state = reachable_states[i] *
          get_parity_game().get_initial_state();
      if (initial_state != para->bddmgr->bddZero()) {
        cout << "        g" << i << "->s" << determine_state_index(
            initial_state, automaton_states, para);
        if (reachable_states[i] * *para->in_st != para->bddmgr->bddZero()) {
          cout << " (initial)";
        }
        cout << endl;
      }
    }

    // Automaton states.
    for (unsigned int i = 0; i < automaton_states.size(); i++) {
      bool is_winning = is_witness && automaton_states[i] *
          get_winning_regions().first != para->bddmgr->bddZero() ||
          !is_witness && automaton_states[i] *
          get_winning_regions().second != para->bddmgr->bddZero();
      cout << "      s" << i;
      if (is_winning) {
        cout << " (winning)";
      }
      cout << ":" << endl;

      BDD starting_state = Exists(para->bddmgr,
          &get_parity_game().get_inflated_variables(),
          get_parity_game().swap_variables(Exists(para->bddmgr,
              &get_parity_game().get_action_variables(), Exists(para->bddmgr,
                  &get_parity_game().get_state_variables(),
                  automaton_states[i] * (get_winning_regions().first +
                      get_winning_regions().second) *
                  get_parity_game().get_transition_relation()))));

      // Action.
      BDD restricted_state = starting_state * restriction *
          get_parity_game().get_inflated_counter()[w];
      bool possible_action = false;
      bool winning_action = false;
      cout << "        action: ";
      for (unsigned int a = 0; a < get_parity_game().get_actions()[w].size();
           a++) {
        if (starting_state * get_parity_game().get_transition_relation() *
            get_parity_game().get_inflated_counter()[w] *
            get_parity_game().get_transition_actions()[a] !=
            para->bddmgr->bddZero()) {
          possible_action = true;
        }
        if (restricted_state * get_parity_game().get_transition_actions()[a] *
            region != para->bddmgr->bddZero()) {
          winning_action = true;
          cout << get_parity_game().get_action_names()[w][a];
          restriction *= !starting_state +
              get_parity_game().get_actions()[w][a];
          break;
        }
      }
      if (!possible_action) {
        cout << "<no possible action>";
      } else if (!winning_action) {
        cout << "<no winning action>";
      }
      cout << endl;

      // Temporal transition.
      bool possible_transition = false;
      for (unsigned int j = 0; j < reachable_states.size(); j++) {
        BDD next_state = reachable_states[j] *
            get_parity_game().get_inflated_counter()[0] *
            get_parity_game().swap_variables(Exists(para->bddmgr,
                &get_parity_game().get_action_variables(), Exists(para->bddmgr,
                    &get_parity_game().get_state_variables(), starting_state *
                    get_parity_game().get_transition_relation())));
        if (next_state != para->bddmgr->bddZero()) {
          possible_transition = true;
          assert(Exists(para->bddmgr, &get_parity_game().get_state_variables(),
              next_state) == para->bddmgr->bddOne());
          cout << "        g" << j << "->s" << determine_state_index(next_state,
              automaton_states, para) << endl;
        }
      }
      if (!possible_transition) {
        cout << "        <deadend>" << endl;
      }
    }
  }
}

void
sl_solution::print(const vector<BDD> reachable_states,
                   bdd_parameters *para) const
{
  vector<BDD> automaton_states;

  // Start state.
  cout << "    start:" << endl;
  for (unsigned int i = 0; i < reachable_states.size(); i++) {
    BDD initial_state = reachable_states[i] *
        get_parity_game().get_initial_state();
    if (initial_state != para->bddmgr->bddZero()) {
      cout << "      g" << i << "->s" << determine_state_index(initial_state,
          automaton_states, para);
      if (reachable_states[i] * *para->in_st != para->bddmgr->bddZero()) {
        cout << " (initial)";
      }
      cout << endl;
    }
  }

  // Automaton states.
  for (unsigned int i = 0; i < automaton_states.size(); i++) {
    cout << "    s" << i;
    if (automaton_states[i] * get_winning_regions().first !=
        para->bddmgr->bddZero()) {
      cout << " (winning)";
    }
    cout << ":" << endl;

    // Temporal transition.
    bool possible_transition = false;
    cout << "      temporal transition:" << endl;
    BDD starting_state = Exists(para->bddmgr,
        &get_parity_game().get_inflated_variables(),
        get_parity_game().swap_variables(Exists(para->bddmgr,
            &get_parity_game().get_action_variables(), Exists(para->bddmgr,
                &get_parity_game().get_state_variables(),
                automaton_states[i] * (get_winning_regions().first +
                    get_winning_regions().second) *
                get_parity_game().get_transition_relation()))));

    for (unsigned int j = 0; j < reachable_states.size(); j++) {
      BDD next_state = reachable_states[j] *
          get_parity_game().get_inflated_counter()[0] *
          get_parity_game().swap_variables(Exists(para->bddmgr,
            &get_parity_game().get_action_variables(), Exists(para->bddmgr,
                &get_parity_game().get_state_variables(), starting_state *
                get_parity_game().get_transition_relation())));
      if (next_state != para->bddmgr->bddZero()) {
        possible_transition = true;
        assert(Exists(para->bddmgr, &get_parity_game().get_state_variables(),
            next_state) == para->bddmgr->bddOne());
        cout << "        g" << j << "->s" << determine_state_index(next_state,
            automaton_states, para) << endl;
      }
    }
    if (!possible_transition) {
      cout << "        <deadend>" << endl;
    }

    // Strategies.
    cout << "      strategies:";
    print_strategy(reachable_states,
        starting_state * get_parity_game().get_inflated_counter()[1], 1,
        para);
    cout << endl;
  }
}

unsigned int
sl_solution::determine_state_index(const BDD & state,
                                   vector<BDD> & automaton_states,
                                   bdd_parameters *para)
{
  for (unsigned int i = 0; i < automaton_states.size(); i++) {
    if (automaton_states[i] * state != para->bddmgr->bddZero()) {
      assert(automaton_states[i] == state);
      return i;
    }
  }
  automaton_states.push_back(state);
  return automaton_states.size() - 1;
}

void
sl_solution::print_strategy(const vector<BDD> reachable_states,
                            const BDD & state, unsigned int index,
                            bdd_parameters *para) const
{
  if (index >= get_parity_game().get_action_names().size()) {
    cout << " {";
    bool is_first = true;
    for (unsigned int i = 0; i < reachable_states.size(); i++) {
      BDD reachable_state_next = get_parity_game().swap_variables(
          reachable_states[i]);
      if (reachable_state_next * state * get_parity_game()
          .get_transition_relation() != para->bddmgr->bddZero()) {
        if (is_first) {
          is_first = false;
        } else {
          cout << ", ";
        }
        cout << "g" << i;
      }
    }
    cout << "}";
  } else {
    const vector<string> & action_names =
        get_parity_game().get_action_names()[index];
    string indentation(6 + 2 * index, ' ');
    bool possible_action = false;

    for (unsigned int i = 0; i < action_names.size(); i++) {
      BDD move = state * get_parity_game().get_transition_actions()[i];
      BDD tmp = move * get_parity_game().get_transition_relation();

      if (tmp != para->bddmgr->bddZero()) {
        possible_action = true;
        BDD next_state = get_parity_game().swap_variables(Exists(para->bddmgr,
            &get_parity_game().get_action_variables(), Exists(para->bddmgr,
                &get_parity_game().get_state_variables(), tmp)));
        cout << endl << indentation << get_prefix()[index].get_quantifier()
            << "=" << action_names[i];
        if ((get_prefix()[index].is_existential() ?
                get_winning_regions().first : get_winning_regions().second)
            * move != para->bddmgr->bddZero()) {
          cout << "*";
        }
        cout << ":";
        print_strategy(reachable_states, next_state, index + 1, para);
      }
    }
    if (!possible_action) {
      cout << endl << indentation << get_prefix()[index].get_quantifier()
          << "=<no possible action>";
    }
  }
}
