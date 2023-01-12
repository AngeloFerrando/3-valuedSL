package core.abstraction.model;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;

import core.abstraction.AbstractionUtils;
import core.parser.StrategyLogic;
import core.parser.StrategyLogicLexer;
import core.parser.StrategyLogicParser;
import core.parser.StrategyLogicVisitorImpl;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;
import org.apache.commons.collections4.MapUtils;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;
import org.apache.commons.collections4.Predicate;
import org.apache.commons.collections4.map.MultiKeyMap;

public class CGSModel extends JsonObject implements Cloneable {

	@SerializedName("states")
	@Expose
	private List<? extends State> states = null;
	@SerializedName("agents")
	@Expose
	private List<Agent> agents = new ArrayList<>();
	@SerializedName("transitions")
	@Expose
	private List<Transition> transitions = new ArrayList<>();
	@SerializedName("groups")
	@Expose
	private List<Group> groups = new ArrayList<>();
	@SerializedName("formula")
	@Expose
	private String formula;
	private StrategyLogic sl;

	private transient Map<String, State> stateMap;

	private transient Map<String, Agent> agentMap;

	private transient Map<String, List<Transition>> transitionMap;

	private transient MultiKeyMap<String, List<List<AgentAction>>> agentActionsByStates;

	public List<? extends State> getStates() {
		return states;
	}

	public void setStates(List<? extends State> states) {
		this.states = states;
	}

	public List<Agent> getAgents() {
		return agents;
	}

	public void setAgents(List<Agent> agents) {
		this.agents = agents;
	}

	public List<Transition> getTransitions() {
		return transitions;
	}

	public void setTransitions(List<Transition> transitions) {
		this.transitions = transitions;
	}

	public List<Group> getGroups() {
		return groups;
	}

	public void setGroups(List<Group> groups) {
		this.groups = groups;
	}

	public String getFormula() {return formula; }
	public void setFormula(String formula) { this.formula = formula; }

	public StrategyLogic getSL() {
		if(sl == null) {
			CharStream codePointCharStream = CharStreams.fromString(formula);
			StrategyLogicLexer lexer = new StrategyLogicLexer(codePointCharStream);
			StrategyLogicParser parser = new StrategyLogicParser(new CommonTokenStream(lexer));
			ParseTree tree = parser.slExpr();
			StrategyLogicVisitorImpl visitor = new StrategyLogicVisitorImpl();
			sl = visitor.visit(tree).transl(true);
		}
		return sl;
	}

	public void setSL(StrategyLogic formula) {
		this.sl = formula;
	}

	public Map<String, State> getStateMap() {
		if (stateMap == null) {
			stateMap = new HashMap<>();
			for (State state : getStates()) {
				stateMap.put(state.getName(), state);
			}
		}
		return stateMap;
	}

	public void setStateMap(Map<String, State> map) {
		this.stateMap = map;
	}

	public State getState(String stateName) {
		return getStateMap().get(stateName);
	}

	public Map<String, Agent> getAgentMap() {
		if (agentMap == null) {
			agentMap = new HashMap<>();
			for (Agent agent : getAgents()) {
				agentMap.put(agent.getName(), agent);
			}
		}
		return agentMap;
	}

	public MultiKeyMap<String, List<List<AgentAction>>> getAgentActionsByStates() {
		if (agentActionsByStates == null) {
			agentActionsByStates = new MultiKeyMap<>();
			for (Transition transition : getTransitions()) {
				if (!agentActionsByStates.containsKey(transition.getFromState(), transition.getToState())) {
					agentActionsByStates.put(transition.getFromState(), transition.getToState(), new ArrayList<>());
				}
				if(!transition.getAgentActions().isEmpty()) {
					agentActionsByStates.get(transition.getFromState(), transition.getToState()).addAll(transition.getAgentActions());
				}
				if(!transition.getMultipleAgentActions().isEmpty()) {
					int n = transition.getMultipleAgentActions().size();
					Integer[] aux = new Integer[n];
					for(int i = 0; i < n; i++) {
						aux[i] = 0;
					}
					int m = 1;
					for(MultipleAgentAction mAct : transition.getMultipleAgentActions()) {
						m *= mAct.getActions().size();
					}
					List<List<AgentAction>> agActsL = new ArrayList<>();
					for(int j = 0; j < m; j++) {
						List<AgentAction> agActs = new ArrayList<>();
						boolean inc = true;
						for(int i = 0; i < n; i++) {
							String agent = transition.getMultipleAgentActions().get(i).getAgent();
							String action = transition.getMultipleAgentActions().get(i).getActions().get(aux[i]);
							agActs.add(new AgentAction(agent, action));
							if(inc) {
								aux[i] = (aux[i] + 1) % transition.getMultipleAgentActions().get(i).getActions().size();
								if(aux[i] != 0) {
									inc = false;
								}
							}
						}
						agActsL.add(agActs);
					}
					agentActionsByStates.get(transition.getFromState(), transition.getToState()).addAll(agActsL);
				}

			}
		}

		return agentActionsByStates;
	}

	public void setAgentActionsByStates(MultiKeyMap<String, List<List<AgentAction>>> map) {
		this.agentActionsByStates = map;
	}

	public Map<String, List<Transition>> getTransitionMap() {
		if (MapUtils.isEmpty(transitionMap)) {
			transitionMap = new HashMap<>();
			for (Transition transition : getTransitions()) {
				if (!transitionMap.containsKey(transition.getFromState())) {
					transitionMap.put(transition.getFromState(), new ArrayList<>());
				}
				transitionMap.get(transition.getFromState()).add(transition);
			}
		}

		return transitionMap;
	}

	@Override
	public CGSModel clone() {
		CGSModel clone;
		try {
			clone = (CGSModel) super.clone();
		}
		catch (CloneNotSupportedException ex) {
			throw new RuntimeException("Superclass messed up", ex);
		}

		List<State> statesAuxList = new ArrayList<>();
		for (State state : states) {
			State newState = new State(state.getName(), state.isInitial());
			newState.setLabels(new ArrayList<>(state.getLabels()));
			newState.setFalseLabels(new ArrayList<>(state.getFalseLabels()));
			statesAuxList.add(newState);
		}
		clone.states = statesAuxList;
		List<Agent> agentsAuxList = new ArrayList<>();
		for(Agent agent : agents) {
			Agent newAgent = new Agent();
			newAgent.setName(agent.getName());
			newAgent.setActions(new ArrayList<>(agent.getActions()));
			newAgent.setIndistinguishableStates(new ArrayList<>());
			for(List<String> indS : agent.getIndistinguishableStates()) {
				newAgent.getIndistinguishableStates().add(new ArrayList<>(indS));
			}
			agentsAuxList.add(newAgent);
		}
		clone.agents = agentsAuxList;
		List<Transition> transitionsAuxList = new ArrayList<>();
		for(Transition tr : transitions) {
			Transition newTransition = new Transition();
			newTransition.setFromState(tr.getFromState());
			newTransition.setToState(tr.getToState());
			newTransition.setAgentActions(new ArrayList<>());
			for(List<AgentAction> aal : tr.getAgentActions()) {
				List<AgentAction> aalAux = new ArrayList<>();
				for(AgentAction aa : aal) {
					AgentAction newAa = new AgentAction();
					newAa.setAgent(aa.getAgent());
					newAa.setAction(aa.getAction());
					aalAux.add(newAa);
				}
				newTransition.getAgentActions().add(aalAux);
			}
			List<MultipleAgentAction> maalAux = new ArrayList<>();
			for(MultipleAgentAction maa : tr.getMultipleAgentActions()) {
				MultipleAgentAction newMaa = new MultipleAgentAction();
				newMaa.setAgent(maa.getAgent());
				newMaa.setActions(new ArrayList<>(maa.getActions()));
				maalAux.add(newMaa);
			}
			newTransition.setMultipleAgentActions(maalAux);
			newTransition.setDefaultTransition(tr.isDefaultTransition());
			transitionsAuxList.add(newTransition);
		}
		clone.transitions = transitionsAuxList;
		clone.groups = new ArrayList<>();
		for(Group g : groups) {
			Group ng = new Group();
			ng.setName(g.getName());
			ng.setAgents(new ArrayList<>(g.getAgents()));
			clone.groups.add(ng);
		}
		clone.formula = formula;
		clone.sl = getSL().clone();
		clone.agentMap = null;
		clone.stateMap = null;
		clone.agentActionsByStates = null;
		return clone;
	}

	public enum Abstraction { May, Must }

	public enum Outcome { True, False, Undefined }

	public CGSModel createAbstraction(Abstraction kind, Predicate<State> toAbstract) {
		Set<String> existentialAgents =  new HashSet<>();
		Set<String> universalAgents = new HashSet<>();
		this.getSL().existentialandUniversalAgents(existentialAgents, universalAgents);
		existentialAgents.remove("Environment");
		universalAgents.remove("Environment");
		if(kind == Abstraction.Must) {
			CGSModel mustAtlModel = this.clone();
			List<StateCluster> mustStateClusters = AbstractionUtils.getStateClusters(mustAtlModel, toAbstract);
			List<Transition> mustTransitions = AbstractionUtils.getAbstractTransitions(mustAtlModel, mustStateClusters, existentialAgents);
			mustAtlModel.setStates(mustStateClusters);
			mustAtlModel.setTransitions(mustTransitions);
			mustAtlModel.setStateMap(null);
			mustAtlModel.setAgentActionsByStates(null);
			return mustAtlModel;
		} else {
			CGSModel mayAtlModel = this.clone();
			List<StateCluster> mayStateClusters = AbstractionUtils.getStateClusters(mayAtlModel, toAbstract);
			List<Transition> mayTransitions = AbstractionUtils.getAbstractTransitions(mayAtlModel, mayStateClusters, universalAgents);
			mayAtlModel.setStates(mayStateClusters);
			mayAtlModel.setTransitions(mayTransitions);
			mayAtlModel.setStateMap(null);
			mayAtlModel.setAgentActionsByStates(null);
			return mayAtlModel;
		}
	}
	
	public CGSModel createAbstractionOld(Abstraction kind, Predicate<State> toAbstract) {
		if(kind == Abstraction.Must) {
			CGSModel mustAtlModel = this.clone();
			List<StateCluster> mustStateClusters = AbstractionUtils.getStateClusters(mustAtlModel, toAbstract);
			List<Transition> mustTransitions = AbstractionUtils.getMustTransitions(mustAtlModel, mustStateClusters);
			mustAtlModel.setStates(mustStateClusters);
			mustAtlModel.setTransitions(mustTransitions);
			mustAtlModel.setStateMap(null);
			mustAtlModel.setAgentActionsByStates(null);
			return mustAtlModel;
		} else {
			CGSModel mayAtlModel = this.clone();
			List<StateCluster> mayStateClusters = AbstractionUtils.getStateClusters(mayAtlModel, toAbstract);
			List<Transition> mayTransitions = AbstractionUtils.getMayTransitions(mayAtlModel, mayStateClusters);
			mayAtlModel.setStates(mayStateClusters);
			mayAtlModel.setTransitions(mayTransitions);
			mayAtlModel.setStateMap(null);
			mayAtlModel.setAgentActionsByStates(null);
			return mayAtlModel;
		}
	}

	public CGSModel createAbstraction(Abstraction kind, List<State> statesToAbstract) {
		if(kind == Abstraction.Must) {
			CGSModel mustAtlModel = this.clone();
			List<StateCluster> mustStateClusters = AbstractionUtils.getStateClusters(mustAtlModel, statesToAbstract);
			List<Transition> mustTransitions = AbstractionUtils.getMustTransitions(mustAtlModel, mustStateClusters);
			mustAtlModel.setStates(mustStateClusters);
			mustAtlModel.setTransitions(mustTransitions);
			mustAtlModel.setStateMap(null);
			mustAtlModel.setAgentActionsByStates(null);
//			mustAtlModel.setATL(this.getATL().transl(true));
			return mustAtlModel;
		} else {
			CGSModel mayAtlModel = this.clone();
			List<StateCluster> mayStateClusters = AbstractionUtils.getStateClusters(mayAtlModel, statesToAbstract);
			List<Transition> mayTransitions = AbstractionUtils.getMayTransitions(mayAtlModel, mayStateClusters);
			mayAtlModel.setStates(mayStateClusters);
			mayAtlModel.setTransitions(mayTransitions);
			mayAtlModel.setStateMap(null);
			mayAtlModel.setAgentActionsByStates(null);
//			mayAtlModel.setATL(this.getATL().transl(false));
			return mayAtlModel;
		}
	}

	public void makeTransitionsUnique() {
		int id = 0;
		for (Transition tr : transitions) {
			for (List<AgentAction> acts : tr.getAgentActions()) {
				for (AgentAction act : acts) {
					String actAux = act.getAction();
					act.setAction(act.getAction() + "_" + id++);
					for (Agent ag : agents) {
						if (ag.getName().equals(act.getAgent())) {
							ag.getActions().remove(actAux);
							ag.getActions().add(act.getAction());
						}
					}
				}
			}
			List<MultipleAgentAction> multActs = new ArrayList<>();
			for (MultipleAgentAction acts : tr.getMultipleAgentActions()) {
				MultipleAgentAction newAct = new MultipleAgentAction();
				newAct.setAgent(acts.getAgent());
				newAct.setActions(new ArrayList<>());
				for (String act : acts.getActions()) {
					newAct.getActions().add(act + "_" + id++);
				}
				multActs.add(newAct);
			}
			tr.setMultipleAgentActions(multActs);
		}
	}

	public static Outcome modelCheck(CGSModel model, String mcmasExecPath) throws IOException {
		String mcmasProgram = AbstractionUtils.generateMCMASProgram(model, false);
		String fileName = "/tmp/st.ispl";
		Files.write(Paths.get(fileName), mcmasProgram.getBytes());
		String mcmasOutputAtlModel = AbstractionUtils.modelCheck(mcmasExecPath, fileName);
		if (AbstractionUtils.getMcmasResult(mcmasOutputAtlModel)) {
			return Outcome.True;
		} else {
			return Outcome.False;
		}
	}

	public static Outcome modelCheck3(CGSModel modelMust, CGSModel modelMay, String mcmasExecPath) throws IOException {
		boolean universal = modelMust.getSL() instanceof StrategyLogic.Universal;
		if(universal) {
			modelMust.setSL(modelMust.getSL().transl(false));
			String mcmasMustProgram = AbstractionUtils.generateMCMASProgram(modelMust, false);
			String fileName = "/tmp/st.ispl";
			Files.write(Paths.get(fileName), mcmasMustProgram.getBytes());
			String mcmasOutputMustAtlModel = AbstractionUtils.modelCheck(mcmasExecPath, fileName);
			if (AbstractionUtils.getMcmasResult(mcmasOutputMustAtlModel)) {
				return Outcome.False;
			}
			String mcmasMayProgram = AbstractionUtils.generateMCMASProgram(modelMay, false);
			Files.write(Paths.get(fileName), mcmasMayProgram.getBytes());
			String mcmasOutputMayAtlModel = AbstractionUtils.modelCheck(mcmasExecPath, fileName);
			if (AbstractionUtils.getMcmasResult(mcmasOutputMayAtlModel)) {
				return Outcome.True;
			}
		} else {
			String mcmasMustProgram = AbstractionUtils.generateMCMASProgram(modelMust, false);
			String fileName = "/tmp/st.ispl";
			Files.write(Paths.get(fileName), mcmasMustProgram.getBytes());
			String mcmasOutputMustAtlModel = AbstractionUtils.modelCheck(mcmasExecPath, fileName);
			if (AbstractionUtils.getMcmasResult(mcmasOutputMustAtlModel)) {
				return Outcome.True;
			}
			modelMay.setSL(modelMay.getSL().transl(false));
			String mcmasMayProgram = AbstractionUtils.generateMCMASProgram(modelMay, false);
			Files.write(Paths.get(fileName), mcmasMayProgram.getBytes());
			String mcmasOutputMayAtlModel = AbstractionUtils.modelCheck(mcmasExecPath, fileName);
			if (AbstractionUtils.getMcmasResult(mcmasOutputMayAtlModel)) {
				return Outcome.False;
			}
		}
		return Outcome.Undefined;
	}

}
