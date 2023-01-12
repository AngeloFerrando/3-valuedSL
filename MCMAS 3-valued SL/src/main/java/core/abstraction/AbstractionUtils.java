package core.abstraction;


import java.io.File;
import java.io.IOException;
import java.text.MessageFormat;
import java.util.*;
import java.util.Map.Entry;
import java.util.stream.Collectors;

import com.google.common.collect.Lists;
import core.abstraction.model.*;
import org.apache.commons.collections4.CollectionUtils;
import org.apache.commons.collections4.Predicate;
import org.apache.commons.io.FileUtils;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.core.io.ClassPathResource;

public class AbstractionUtils {
	
    private static final String MODEL_JSON_FILE_NAME = "modelsimple1.json"; // "modelVoter.json"; //"modelKR.json"; //"modelCards.json";
	private final static Log logger = LogFactory.getLog(AbstractionUtils.class);
	private static CGSModel must;

	public static List<StateCluster> getStateClusters(CGSModel CGSModel, Predicate<State> toAbstract) {
		List<StateCluster> stateClusters = new ArrayList<>();
		StateCluster cluster = new StateCluster();
		CGSModel.getStates().forEach(s -> {
			if(toAbstract.evaluate(s)) {
				cluster.addChildState(s);
				if(s.isInitial()) {
					cluster.setInitial(true);
				}
			}
		});
		stateClusters.add(cluster);
		for (State state : CGSModel.getStates()) {
			if(!toAbstract.evaluate(state)) {
				stateClusters.add(state.clone().toStateCluster());
			}
		}
		return stateClusters.stream().distinct().collect(Collectors.toList());
	}

	public static List<StateCluster> getStateClusters(CGSModel CGSModel, List<State> statesToAbstract) {
		List<StateCluster> stateClusters = new ArrayList<>();
		StateCluster cluster = new StateCluster();
		statesToAbstract.forEach(cluster::addChildState);
		cluster.setInitial(statesToAbstract.stream().anyMatch(State::isInitial));
		stateClusters.add(cluster);
		for (State state : CGSModel.getStates()) {
			if(!statesToAbstract.contains(state)) {
				stateClusters.add(state.clone().toStateCluster());
			}
		}
		return stateClusters.stream().distinct().collect(Collectors.toList());
	}
	
	public static List<Transition> getMayTransitions(final CGSModel CGSModel, final List<StateCluster> stateClusters) {
		List<Transition> transitions = new ArrayList<>();
		for (StateCluster fromStateCluster : stateClusters) {
			for (StateCluster toStateCluster : stateClusters) {
				List<List<AgentAction>> agentActions = fromStateCluster.hasMayTransition(toStateCluster, CGSModel);
				createTransition(fromStateCluster, transitions, toStateCluster, agentActions);
			}
		}
		
		return transitions;
	}

	public static List<Transition> getAbstractTransitions(final CGSModel CGSModel, final List<StateCluster> stateClusters, Set<String> mustAgents) {
		List<Transition> transitions = new ArrayList<>();
		State sinkState = new State();
		sinkState.setName("sink");
		Set<String> aux = new HashSet<>();
		Set<String> aux1 = new HashSet<>();
		for(String l : CGSModel.getStates().get(0).getLabels()) {
			aux.add(l.replace("_tt", "_uu").replace("_ff", "_uu"));
			if(!l.contains("_uu")) aux1.add(l);
		}
		sinkState.setLabels(new ArrayList<>(aux));
		sinkState.setFalseLabels(new ArrayList<>(aux1));
		sinkState = new StateCluster(sinkState);
		boolean sinkAdded = false;
		for (StateCluster fromStateCluster : stateClusters) {
			boolean found = false;
			for (StateCluster toStateCluster : stateClusters) {
				List<List<AgentAction>> agentActions = fromStateCluster.hasAbstractTransition(toStateCluster, CGSModel, mustAgents);
				if(!agentActions.isEmpty()) found = true;
				createTransition(fromStateCluster, transitions, toStateCluster, agentActions);
			}
			if(!found) {
				List<AgentAction> acts = new ArrayList<>();
				for (Agent ag : CGSModel.getAgents()) {
					AgentAction act = new AgentAction();
					act.setAgent(ag.getName());
					act.setAction(ag.getActions().get(0));
					acts.add(act);
				}
				List<List<AgentAction>> actsL = new ArrayList<>();
				actsL.add(acts);
				createTransition(fromStateCluster, transitions, sinkState, actsL);
				if(!sinkAdded) {
					sinkAdded = true;
					createTransition(sinkState, transitions, sinkState, actsL);
				}
			}
		}
		if(sinkAdded) {
			stateClusters.add((StateCluster) sinkState);
		}
		return transitions;
	}
	
	public static List<Transition> getMustTransitions(final CGSModel CGSModel, final List<StateCluster> stateClusters) {
		List<Transition> transitions = new ArrayList<>();
		State sinkState = new State();
		sinkState.setName("sink");
		Set<String> aux = new HashSet<>();
		Set<String> aux1 = new HashSet<>();
		for(String l : CGSModel.getStates().get(0).getLabels()) {
			aux.add(l.replace("_tt", "_uu").replace("_ff", "_uu"));
			if(!l.contains("_uu")) aux1.add(l);
		}
		sinkState.setLabels(new ArrayList<>(aux));
		sinkState.setFalseLabels(new ArrayList<>(aux1));
		sinkState = new StateCluster(sinkState);
		boolean sinkAdded = false;
		for (StateCluster fromStateCluster : stateClusters) {
			boolean found = false;
			for (StateCluster toStateCluster : stateClusters) {
				List<List<AgentAction>> agentActions = fromStateCluster.hasMustTransition(toStateCluster, CGSModel);
				if(!agentActions.isEmpty()) found = true;
				createTransition(fromStateCluster, transitions, toStateCluster, agentActions);
			}
			if(!found) {
				List<AgentAction> acts = new ArrayList<>();
				for (Agent ag : CGSModel.getAgents()) {
					AgentAction act = new AgentAction();
					act.setAgent(ag.getName());
					act.setAction(ag.getActions().get(0));
					acts.add(act);
				}
				List<List<AgentAction>> actsL = new ArrayList<>();
				actsL.add(acts);
				createTransition(fromStateCluster, transitions, sinkState, actsL);
				if(!sinkAdded) {
					sinkAdded = true;
					createTransition(sinkState, transitions, sinkState, actsL);
				}
			}
		}
		if(sinkAdded) {
			stateClusters.add((StateCluster) sinkState);
		}
		return transitions;
	}
	
	public static void removeDuplicates(List<List<AgentAction>> agentActions) {
		Map<String, List<AgentAction>> actionMap = new HashMap<>();
		for (List<AgentAction> actionList : agentActions) {
			actionMap.put(actionList.toString(), actionList);
		}
		agentActions.clear();
		agentActions.addAll(actionMap.values());
	}
	
	public static String generateDotGraph(CGSModel CGSModel) {
		StringBuilder stringBuilder = new StringBuilder("digraph G {").append(System.lineSeparator());
		List<Transition> transitions = CGSModel.getTransitions();
		for (Transition transition : transitions) {
			if (CollectionUtils.isEmpty(CGSModel.getState(transition.getFromState()).getLabels())) {
				stringBuilder.append(transition.getFromState());
			} else {
				stringBuilder
						.append("\"").append(transition.getFromState()).append("(").append(String.join(", ", CGSModel.getState(transition.getFromState()).getLabels())).append(")\"");
			}
			stringBuilder.append("->");
			if (CollectionUtils.isEmpty(CGSModel.getState(transition.getToState()).getLabels())) {
				stringBuilder.append(transition.getToState());
			} else {
				stringBuilder
						.append("\"").append(transition.getToState()).append("(").append(String.join(", ", CGSModel.getState(transition.getToState()).getLabels())).append(")\"");
			}
			List<String> list1 = new ArrayList<>();
			for(List<AgentAction> agentActionList: transition.getAgentActions()) {
				List<String> list2 = new ArrayList<>();
				for (AgentAction agentAction : agentActionList) {
					list2.add(agentAction.getAgent()+ "." +agentAction.getAction());
				}
				list1.add(MessageFormat.format("({0})", String.join(",", list2)));
			}
			stringBuilder.append("[ label = \"" + String.join("\\n", list1) + "\" ];").append(System.lineSeparator());
		}
		stringBuilder.append("}").append(System.lineSeparator());
		return stringBuilder.toString();
	}
	
	public static void validateCGS(CGSModel CGSModel) throws Exception {
		validateTransitions(CGSModel);
		validateGroup(CGSModel);
//		if(explicit) {
		Set<String> labels = new HashSet<>();
		for (State s : CGSModel.getStates()) {
			labels.addAll(s.getLabels());
			labels.addAll(s.getFalseLabels());
		}
		for (State s : CGSModel.getStates()) {
			List<String> sLabels = new ArrayList<>();
			for (String l : labels) {
				if (s.getLabels().contains(l)) {
					sLabels.add(l + "_tt");
				} else {
					sLabels.add(l + "_ff");
				}
			}
			s.setLabels(sLabels);
			s.setFalseLabels(sLabels.stream().map(l -> l.endsWith("_tt") ? l.replace("_tt", "_ff") : l.replace("_ff", "_tt")).collect(Collectors.toList()));
		}
//		}
	}
		
	private static void validateTransitions(CGSModel CGSModel) throws Exception {
		for(Transition transition : CGSModel.getTransitions()) {
			if (!CGSModel.getStateMap().containsKey(transition.getFromState())) {
				throw new Exception(MessageFormat.format("invalid state {0} in transition : {1} {2}",
						transition.getFromState(), System.lineSeparator(), transition));
			}
			if (!CGSModel.getStateMap().containsKey(transition.getToState())) {
				throw new Exception(MessageFormat.format("invalid state {0} in transition : {1} {2}",
						transition.getToState(), System.lineSeparator(), transition));
			}
			if (transition.isDefaultTransition() && CollectionUtils.isNotEmpty(transition.getAgentActions())) {
				throw new Exception(MessageFormat.format("The transition cannot be a default one and have explicit agent actions : {0} {1}",
								System.lineSeparator(), transition));
			}
			for(List<AgentAction> agentActionList : transition.getAgentActions()) {
				validateAgentActionList(CGSModel, transition, agentActionList);
			}
		}
	}
	
	private static void validateAgentActionList(CGSModel CGSModel, Transition transition, List<AgentAction> agentActionList) throws Exception {
		for (AgentAction agentAction : agentActionList) {
			validateAgentAction(CGSModel, transition, agentAction);
		}
		List<String> agents = agentActionList.parallelStream().map(AgentAction::getAgent).collect(Collectors.toList());
		Collection<String> agentNotDefinedList = CollectionUtils.subtract(agents, CGSModel.getAgentMap().keySet());
		if (CollectionUtils.isNotEmpty(agentNotDefinedList)) {
			throw new Exception (MessageFormat.format("Some agents have not been defined : {0} for the transition : {1} {2}", 
					agentNotDefinedList, System.lineSeparator(), transition));
		}
		Collection<String> missingAgentActionsList = CollectionUtils.subtract(CGSModel.getAgentMap().keySet(), agents);
		if (CollectionUtils.isNotEmpty(missingAgentActionsList)) {
			throw new Exception (MessageFormat.format("Some agent actions have not been defined : {0} for the transition : {1} {2}", 
					missingAgentActionsList, System.lineSeparator(), transition));
		}
	}
	
	private static void validateAgentAction(CGSModel CGSModel, Transition transition, AgentAction agentAction) throws Exception {
		if (!CGSModel.getAgentMap().containsKey(agentAction.getAgent())) {
			throw new Exception (MessageFormat.format("Invalid agent {0} in agentAction : {1} for the transition : {2} {3}", 
					agentAction.getAgent(), agentAction, System.lineSeparator(), transition));
		}
		Agent agent = CGSModel.getAgentMap().get(agentAction.getAgent());
		if (!agent.getActions().contains(agentAction.getAction())) {
			throw new Exception (MessageFormat.format("Invalid action {0} in agentAction : {1} for the transition : {2} {3}", 
					agentAction.getAction(), agentAction, System.lineSeparator(), transition));
		}
	}
	
	private static void validateGroup(CGSModel CGSModel) throws Exception {
		for(Group g : CGSModel.getGroups()) {
			List<String> groupAgents = g.getAgents();
			Collection<String> agentNotDefinedList = CollectionUtils.subtract(groupAgents, CGSModel.getAgentMap().keySet());
			if (CollectionUtils.isNotEmpty(agentNotDefinedList)) {
				throw new Exception(MessageFormat.format("Some agents in the group have not been defined : {0}",
						agentNotDefinedList, System.lineSeparator(), CGSModel));
			}
		}
	}
	
	
	public static String readSampleFile() {
		try {
			File sampleFile = new ClassPathResource(MODEL_JSON_FILE_NAME).getFile();
			return new String(FileUtils.readFileToByteArray(sampleFile));
		} catch (IOException ioe) {
			logger.error("Error while trying to read the sample file.", ioe);
		}
		
		return null;
	}
	
	public static void processDefaultTransitions(CGSModel CGSModel) throws Exception {
		for(Entry<String, List<Transition>> entry : CGSModel.getTransitionMap().entrySet()) {
			List<Transition> transitions = entry.getValue();
			List<Transition> defaultTransitions = transitions.parallelStream().filter(transition -> transition.isDefaultTransition()).collect(Collectors.toList());
			if (CollectionUtils.isEmpty(defaultTransitions)) {
				continue;
			}
			if (defaultTransitions.size() > 1) {
				throw new Exception (MessageFormat.format("The state {0} has {1} default transition, only one is allowed. Transitions : {2} {3}", 
						entry.getKey(), defaultTransitions.size(), System.lineSeparator(), defaultTransitions));
			}
			Collection<Transition> explicitTransitions = CollectionUtils.subtract(transitions, defaultTransitions);
			List<List<List<AgentAction>>> existingActionLists = explicitTransitions.parallelStream().map(Transition::getAgentActions).collect(Collectors.toList());
			Set<List<AgentAction>> actions = defaultTransitions.get(0).getMultipleAgentActions()
												.parallelStream()
												.map(
													multipleAgentAction->multipleAgentAction.getActions()
																	.stream()
																	.map(action -> new AgentAction(multipleAgentAction.getAgent(), action))
												.collect(Collectors.toList()))
												.collect(Collectors.toSet()); 
			List<List<AgentAction>> possibleActions = Lists.cartesianProduct(actions.toArray(new ArrayList<?>[actions.size()])).parallelStream().map(list->list.stream().map(action->(AgentAction) action).collect(Collectors.toList())).collect(Collectors.toList());
			for (List<List<AgentAction>> agentActionsList : existingActionLists) {
				for (List<AgentAction> agentActionList : agentActionsList) {
					Iterator<List<AgentAction>> iterator = possibleActions.iterator();
					while (iterator.hasNext()) {
						if (CollectionUtils.isEqualCollection(iterator.next(), agentActionList)) {
							iterator.remove();
						}
					}
				}
			}
			CGSModel.getTransitions().add(new Transition(entry.getKey(), defaultTransitions.get(0).getToState(), possibleActions));
			CGSModel.setTransitions(Lists.newLinkedList(CollectionUtils.removeAll(CGSModel.getTransitions(), defaultTransitions)));
		}
	}

	public static String generateMCMASProgram(CGSModel CGSModel, boolean isMayModel) {
		StringBuilder stringBuilder = new StringBuilder();
		stringBuilder.append(System.lineSeparator()).append("Agent Environment").append(System.lineSeparator());
		stringBuilder.append("\t").append("Vars :").append(System.lineSeparator());
		Set<String> alreadyAddedLabels = new HashSet<>();
		for (State state: CGSModel.getStates()) {
			stringBuilder.append("\t").append("\t").append(state.getName()).append(" : boolean;").append(System.lineSeparator());
			for (String label: state.getLabels()) {
//				if(label.endsWith("_tt") || label.endsWith("_ff")) {
				label = label.substring(0, label.length() - 3);
				if (!alreadyAddedLabels.contains(label)) {
					stringBuilder.append("\t").append("\t").append(label).append("_tt").append(" : boolean;").append(System.lineSeparator());
					stringBuilder.append("\t").append("\t").append(label).append("_ff").append(" : boolean;").append(System.lineSeparator());
					stringBuilder.append("\t").append("\t").append(label).append("_uu").append(" : boolean;").append(System.lineSeparator());
					alreadyAddedLabels.add(label);
				}
//				} else {
//					label = label.substring(0, label.length() - 3);
//					if (!alreadyAddedLabels.contains(label)) {
//						stringBuilder.append("\t").append("\t").append(label).append(" : boolean;").append(System.lineSeparator());
//						alreadyAddedLabels.add(label);
//					}
//				}
			}
			for (String label: state.getFalseLabels()) {
//				if(!label.contains("atom")) {
				label = label.substring(0, label.length() - 3);
//				if(label.endsWith("_tt") || label.endsWith("_ff")) {
				if (!alreadyAddedLabels.contains(label)) {
					stringBuilder.append("\t").append("\t").append(label).append("_tt").append(" : boolean;").append(System.lineSeparator());
					stringBuilder.append("\t").append("\t").append(label).append("_ff").append(" : boolean;").append(System.lineSeparator());
					stringBuilder.append("\t").append("\t").append(label).append("_uu").append(" : boolean;").append(System.lineSeparator());
					alreadyAddedLabels.add(label);
				}
//				} else {
//					if (!alreadyAddedLabels.contains(label)) {
//						stringBuilder.append("\t").append("\t").append(label).append("_tt").append(" : boolean;").append(System.lineSeparator());
//						alreadyAddedLabels.add(label);
//					}
//				}
			}
		}
		stringBuilder.append("\t").append("end Vars").append(System.lineSeparator());
		stringBuilder.append("\t").append("Actions = {idle};").append(System.lineSeparator());
		stringBuilder.append("\t").append("Protocol :").append(System.lineSeparator());
		for(State s : CGSModel.getStates()) {
			stringBuilder.append("\t").append(s.getName()).append("=true : {idle};").append(System.lineSeparator());
		}
		stringBuilder.append("\t").append("end Protocol").append(System.lineSeparator());
		stringBuilder.append("\t").append("Evolution :").append(System.lineSeparator());
		for (Transition transition: CGSModel.getTransitions()) {
			State toState = CGSModel.getState(transition.getToState());
			State fromState = CGSModel.getState(transition.getFromState());
			stringBuilder.append("\t").append("\t");
			if (!toState.equals(fromState)) {
				stringBuilder.append(fromState.getName()).append(" = false ");
//				if (CollectionUtils.isNotEmpty(fromState.getLabels())) {
//					for (String label: fromState.getLabels()) {
//						if(!toState.getLabels().contains(label)) {
//							stringBuilder.append("and ").append(label).append(" = false ");
//						}
//					}
//				}
				stringBuilder.append("and ");
			}

			stringBuilder.append(toState.getName()).append(" = true ");
			if (CollectionUtils.isNotEmpty(toState.getLabels())) {
				for (String label : toState.getLabels()) {
					stringBuilder.append("and ").append(label).append(" = true ");
				}
			}
			if (CollectionUtils.isNotEmpty(toState.getFalseLabels())) {
				for (String label : toState.getFalseLabels()) {
					stringBuilder.append("and ").append(label).append(" = false ");
				}
			}
			stringBuilder.append(" if ");

			stringBuilder.append(fromState.getName()).append(" = true ");
			if (CollectionUtils.isNotEmpty(fromState.getLabels())) {
				for (String label: fromState.getLabels()) {
					stringBuilder.append("and ").append(label).append(" = true ");
				}
			}

			if (!toState.equals(fromState)) {
				stringBuilder.append("and ").append(toState.getName()).append(" = false ");
				if (CollectionUtils.isNotEmpty(toState.getLabels())) {
					for (String label : toState.getLabels()) {
						if(!fromState.getLabels().contains(label)) {
							stringBuilder.append("and ").append(label).append(" = false ");
						}
					}
				}
			}

			stringBuilder.append("and ");
			if (transition.getAgentActions().size()>1)
				stringBuilder.append("(");
			for (int i = 0; i < transition.getAgentActions().size(); i++) {
				List<AgentAction> agentActionList = transition.getAgentActions().get(i);
				stringBuilder.append("(");
				for (int j = 0; j < agentActionList.size(); j++) {
					AgentAction agentAction = agentActionList.get(j);
					stringBuilder.append(agentAction.getAgent()).append(".Action").append(" = ").append(agentAction.getAction());
					if (j<agentActionList.size()-1)
						stringBuilder.append(" and ");
				}
				stringBuilder.append(")");
				if (i<transition.getAgentActions().size()-1)
					stringBuilder.append(" or ").append(System.lineSeparator()).append("\t\t\t\t\t");
			}
			if (transition.getAgentActions().size()>1)
				stringBuilder.append(")");

			if (transition.getMultipleAgentActions().size()>1)
				stringBuilder.append("(");
			for (int i = 0; i < transition.getMultipleAgentActions().size(); i++) {
				MultipleAgentAction multiAction = transition.getMultipleAgentActions().get(i);
				stringBuilder.append("(");
				for (int j = 0; j < multiAction.getActions().size(); j++) {
					String agentAction = multiAction.getActions().get(j);
					stringBuilder.append(multiAction.getAgent()).append(".Action").append(" = ").append(agentAction);
					if (j<multiAction.getActions().size()-1)
						stringBuilder.append(" or ");
				}
				stringBuilder.append(")");
				if (i<transition.getMultipleAgentActions().size()-1)
					stringBuilder.append(" and ").append(System.lineSeparator()).append("\t\t\t\t\t");
			}
			if (transition.getMultipleAgentActions().size()>1)
				stringBuilder.append(")");

			stringBuilder.append(";").append(System.lineSeparator());
		}
		stringBuilder.append("\t").append("end Evolution").append(System.lineSeparator());
		stringBuilder.append("end Agent").append(System.lineSeparator());

		for (Agent agent : CGSModel.getAgents()) {
			stringBuilder.append("Agent ").append(agent.getName()).append(System.lineSeparator());
			alreadyAddedLabels.clear();
			List<String> lobsvars = new ArrayList<>();
			for (State state : CGSModel.getStates()) {
				boolean consider = true;
				for(List<String> lIndS : agent.getIndistinguishableStates()){
					if(lIndS.contains(state.getName())) {
						consider = false;
						break;
					}
				}
				if(consider) {
					lobsvars.add(state.getName());
				}
				for (String label : state.getLabels()) {
					if(!alreadyAddedLabels.contains(label)) {
						lobsvars.add(label);
						alreadyAddedLabels.add(label);
					}
				}
			}
			stringBuilder.append("\t").append("Lobsvars = {").append(String.join(", ", lobsvars)).append("};").append(System.lineSeparator());
			stringBuilder.append("\t").append("Vars : ").append(System.lineSeparator());
			if(CollectionUtils.isNotEmpty(agent.getIndistinguishableStates())) {
//				boolean first = true;
				for (List<String> lIndS : agent.getIndistinguishableStates()) {
//					if (first) {
//						first = false;
//					} else {
//						stringBuilder.append(",").append(System.lineSeparator());
//					}
					stringBuilder.append("\t").append("\t").append("imp_").append(String.join("_", lIndS)).append(": boolean;");
				}
			}
			stringBuilder.append(System.lineSeparator()).append("\t").append("\t").append("play : boolean;");

			stringBuilder.append(System.lineSeparator()).append("\t").append("end Vars").append(System.lineSeparator());
			stringBuilder.append("\t").append("Actions = {").append(String.join(",", agent.getActions())).append("};");
			Map<String, List<String>> availableActionMap = getAvailableActions(CGSModel, agent);
			stringBuilder.append(System.lineSeparator()).append("\t").append("Protocol : ").append(System.lineSeparator());
//            stringBuilder.append("Other : {").append(String.join(",", agent.getActions())).append("};");
			for (Entry<String, List<String>> availableActionsEntry: availableActionMap.entrySet()) {
				stringBuilder.append("\t").append("\t");
				if(!availableActionsEntry.getKey().startsWith("imp_")) {
					stringBuilder.append("Environment.");
				}
				stringBuilder.append(availableActionsEntry.getKey()).append(" = true");
				if(!availableActionsEntry.getKey().startsWith("imp_")) {
					State state = CGSModel.getState(availableActionsEntry.getKey());
					if (CollectionUtils.isNotEmpty(state.getLabels())) {
						for (String label : state.getLabels())
							stringBuilder.append(" and ").append("Environment.").append(label).append(" = true");
					}
					stringBuilder.append(" : {")
							.append(String.join(",", availableActionsEntry.getValue())).append("};").append(System.lineSeparator());
				} else {
					for(String s : availableActionsEntry.getKey().substring(4).split("_")) {
						State state = CGSModel.getState(s);
						if (CollectionUtils.isNotEmpty(state.getLabels())) {
							for (String label : state.getLabels())
								stringBuilder.append(" and ").append("Environment.").append(label).append(" = true");
						}
					}
					stringBuilder.append(" : {")
							.append(String.join(",", availableActionsEntry.getValue())).append("};").append(System.lineSeparator());
				}
			}
			stringBuilder.append("\t").append("end Protocol").append(System.lineSeparator());
			stringBuilder.append("\t").append("Evolution : ").append(System.lineSeparator());
			stringBuilder.append("\t").append("\t").append("play = true if play = true;").append(System.lineSeparator());
			if(CollectionUtils.isNotEmpty(agent.getIndistinguishableStates())) {
				for (Transition transition : CGSModel.getTransitions()) {
					State toState = CGSModel.getState(transition.getToState());
					State fromState = CGSModel.getState(transition.getFromState());
					State toStateAux = toState, fromStateAux = fromState;
					for (List<String> lIndS : agent.getIndistinguishableStates()) {
						if (lIndS.contains(toState.getName())) {
							toState = new State();
							toState.setName("imp_" + String.join("_", lIndS));
							toState.setInitial(CGSModel.getStates().stream().anyMatch(s -> lIndS.contains(s.getName()) && s.isInitial()));
							toState.setLabels(new ArrayList<>());
							for (List<String> labels : CGSModel.getStates().stream().filter(s -> lIndS.contains(s.getName())).map(State::getLabels).collect(Collectors.toSet())) {
								toState.getLabels().addAll(labels);
							}
						}
						if (lIndS.contains(fromState.getName())) {
							fromState = new State();
							fromState.setName("imp_" + String.join("_", lIndS));
							fromState.setInitial(CGSModel.getStates().stream().anyMatch(s -> lIndS.contains(s.getName()) && s.isInitial()));
							fromState.setLabels(new ArrayList<>());
							for (List<String> labels : CGSModel.getStates().stream().filter(s -> lIndS.contains(s.getName())).map(State::getLabels).collect(Collectors.toSet())) {
								fromState.getLabels().addAll(labels);
							}
						}
					}
					if (toState == toStateAux) { // && fromState == fromStateAux) {
						continue;
					}
//                if(toState == toStateAux) {
//                toState.setName("Environment." + toState.getName());
//                }
					if (fromState == fromStateAux) {
						fromState.setName("Environment." + fromState.getName());
					}
					stringBuilder.append("\t").append("\t");
//                if (!fromState.equals(toState)) {
//                    stringBuilder.append("(").append(fromState.getName()).append(" = false ").append(")");
//                    if (CollectionUtils.isNotEmpty(fromState.getLabels())) {
//                        for (String label: fromState.getLabels()) {
//                            if(!toState.getLabels().contains(label)) {
//                                stringBuilder.append("and ").append("(").append(label).append(" = false ").append(")");
//                            }
//                        }
//                    }
//                    stringBuilder.append("and ");
//                }

					stringBuilder.append("(").append(toState.getName()).append(" = true ").append(")");
//                    if (CollectionUtils.isNotEmpty(toState.getLabels())) {
//                        for (String label : toState.getLabels()) {
//                            stringBuilder.append("and ").append("(").append(label).append(" = true ").append(")");
//                        }
//                    }
					stringBuilder.append(" if ");

					stringBuilder.append("(").append(fromState.getName()).append(" = true ").append(")");
					if (CollectionUtils.isNotEmpty(fromState.getLabels())) {
						for (String label : fromState.getLabels()) {
							stringBuilder.append("and ").append("(").append("Environment.").append(label).append(" = true ").append(")");
						}
					}

					if (!toState.equals(fromState)) {
						stringBuilder.append("and ").append("(").append(toState.getName()).append(" = false ").append(")");
						if (CollectionUtils.isNotEmpty(toState.getLabels())) {
							for (String label : toState.getLabels()) {
								if (!fromState.getLabels().contains(label)) {
									stringBuilder.append("and ").append("(").append("Environment.").append(label).append(" = false ").append(")");
								}
							}
						}
					}

					stringBuilder.append("and ");
					if (transition.getAgentActions().size() > 1)
						stringBuilder.append("(");
					for (int i = 0; i < transition.getAgentActions().size(); i++) {
						List<AgentAction> agentActionList = transition.getAgentActions().get(i);
						stringBuilder.append("(");
						for (int j = 0; j < agentActionList.size(); j++) {
							AgentAction agentAction = agentActionList.get(j);
							stringBuilder.append(agentAction.getAgent()).append(".Action").append(" = ").append(agentAction.getAction());
							if (j < agentActionList.size() - 1)
								stringBuilder.append(" and ");
						}
						stringBuilder.append(")");
						if (i < transition.getAgentActions().size() - 1)
							stringBuilder.append(" or ").append(System.lineSeparator()).append("\t\t\t\t\t");
					}
					if (transition.getAgentActions().size() > 1)
						stringBuilder.append(")");

					if (transition.getMultipleAgentActions().size() > 1)
						stringBuilder.append("(");
					for (int i = 0; i < transition.getMultipleAgentActions().size(); i++) {
						MultipleAgentAction multiAction = transition.getMultipleAgentActions().get(i);
						stringBuilder.append("(");
						for (int j = 0; j < multiAction.getActions().size(); j++) {
							String agentAction = multiAction.getActions().get(j);
							stringBuilder.append(multiAction.getAgent()).append(".Action").append(" = ").append(agentAction);
							if (j < multiAction.getActions().size() - 1)
								stringBuilder.append(" or ");
						}
						stringBuilder.append(")");
						if (i < transition.getMultipleAgentActions().size() - 1)
							stringBuilder.append(" and ").append(System.lineSeparator()).append("\t\t\t\t\t");
					}
					if (transition.getMultipleAgentActions().size() > 1)
						stringBuilder.append(")");

					stringBuilder.append(";").append(System.lineSeparator());
//                if(toState == toStateAux) {
//                toState.setName(toState.getName().substring(12));
//                }
					if (fromState == fromStateAux) {
						fromState.setName(fromState.getName().substring(12));
					}
				}
			}
			stringBuilder.append("\t").append("end Evolution").append(System.lineSeparator());
			stringBuilder.append("end Agent").append(System.lineSeparator());
		}

		stringBuilder.append("Evaluation").append(System.lineSeparator());
		for (String term: CGSModel.getSL().getTerms()) {
			stringBuilder.append("\t").append(term).append(" if (Environment.").append(term).append(" = true);").append(System.lineSeparator());
		}
		stringBuilder.append("\t").append("end Evaluation").append(System.lineSeparator());

		alreadyAddedLabels.clear();
		HashMap<String, Boolean> initialLabels = new HashMap<>();
//        HashMap<String, Boolean> initialLabelsAgents = new HashMap<>();
		stringBuilder.append("\t").append("InitStates").append(System.lineSeparator());
		for (int i = 0; i < CGSModel.getStates().size(); i++) {
			State state = CGSModel.getStates().get(i);
			stringBuilder.append("\t").append("\t").append("Environment.").append(state.getName()).append(" = ").append(state.isInitial());
			if (CollectionUtils.isNotEmpty(state.getLabels())) {
				for (int j = 0; j < state.getLabels().size(); j++) {
					String label = state.getLabels().get(j);
					if(initialLabels.containsKey(label)) {
						if(state.isInitial()) {
							initialLabels.put(label, state.isInitial());
						}
					} else {
						initialLabels.put(label, state.isInitial());
					}
				}
			}

			if (CollectionUtils.isNotEmpty(state.getFalseLabels())) {
				for (int j = 0; j < state.getFalseLabels().size(); j++) {
					String label = state.getFalseLabels().get(j);
					initialLabels.putIfAbsent(label, false);
				}
			}

			if (i<CGSModel.getStates().size()-1) {
				stringBuilder.append(" and ").append(System.lineSeparator());
			}
		}

		for(Agent agent : CGSModel.getAgents()) {
			for(List<String> lIndS : agent.getIndistinguishableStates()) {
				stringBuilder.append(" and ").append(System.lineSeparator());
				stringBuilder.append("\t").append("\t").append(agent.getName()).append(".").append("imp_").append(String.join("_", lIndS)).append(" = ").append(CGSModel.getStates().stream().anyMatch(s -> lIndS.contains(s.getName()) && s.isInitial()));
//                for(String s : lIndS) {
//                    List<String> l = CGSModel.getState(s).getLabels();
//                    if(CollectionUtils.isNotEmpty(l)) {
//                        for (String label : l) {
//                            if (initialLabelsAgents.containsKey(label)) {
//                                if (CGSModel.getState(s).isInitial()) {
//                                    initialLabelsAgents.put(agent.getName() + "." + label, CGSModel.getState(s).isInitial());
//                                }
//                            } else {
//                                initialLabelsAgents.put(agent.getName() + "." + label, CGSModel.getState(s).isInitial());
//                            }
//                        }
//                    }
//                }
			}
		}

		for(Entry<String, Boolean> initialLabel : initialLabels.entrySet()) {
			stringBuilder.append(" and ").append(System.lineSeparator());
			stringBuilder.append("\t").append("\t").append("Environment.").append(initialLabel.getKey()).append(" = ").append(initialLabel.getValue());
		}
//        for(Entry<String, Boolean> initialLabel : initialLabelsAgents.entrySet()) {
//            stringBuilder.append(" and ").append(System.lineSeparator());
//            stringBuilder.append("\t").append("\t").append(initialLabel.getKey()).append(" = ").append(initialLabel.getValue());
//        }

//        if (CollectionUtils.isNotEmpty(CGSModel.getAgents())) {
//            stringBuilder.append(" and ").append(System.lineSeparator());
//            for (int i = 0; i < CGSModel.getAgents().size(); i++) {
//                Agent agent = CGSModel.getAgents().get(i);
//                stringBuilder.append("\t").append("\t").append(agent.getName()).append(".play = true");
//                if (i<CGSModel.getAgents().size()-1)
//                    stringBuilder.append(" and ").append(System.lineSeparator());
//            }
//        }

		stringBuilder.append(";").append(System.lineSeparator()).append("\t").append("end InitStates").append(System.lineSeparator());

		stringBuilder.append("Groups").append(System.lineSeparator());
		for(Group g : CGSModel.getGroups()) {
			stringBuilder.append("\t").append(g.getName()).append("=").append("{").append(String.join(",", g.getAgents())).append("};").append(System.lineSeparator());
		}
		stringBuilder.append("end Groups").append(System.lineSeparator());

		stringBuilder.append("Formulae").append(System.lineSeparator());
		stringBuilder.append("\t");
//		if (isMayModel)
//			stringBuilder.append("!(");
		stringBuilder.append(CGSModel.getSL());
//		stringBuilder.append("<").append(CGSModel.getGroup().getName()).append(">").append(CGSModel.getFormula().getSubformula());
//		if (isMayModel)
//			stringBuilder.append(")");
		stringBuilder.append(";").append(System.lineSeparator());
		stringBuilder.append("end Formulae").append(System.lineSeparator());



		return stringBuilder.toString();
	}


	private static Map<String, List<String>> getAvailableActions(CGSModel CGSModel, Agent agent) {
		Map<String, List<String>> availableActionMap = new HashMap<>();
		for (Transition transition : CGSModel.getTransitions()) {
			if (!availableActionMap.containsKey(transition.getFromState())) {
				availableActionMap.put(transition.getFromState(), new ArrayList<>());
			}

			for (List<AgentAction> agentActionList : transition.getAgentActions()) {
				for (AgentAction agentAction : agentActionList) {
					if (agentAction.getAgent().equals(agent.getName())
							&&
								!availableActionMap.get(transition.getFromState()).contains(agentAction.getAction())) {
						availableActionMap.get(transition.getFromState()).add(agentAction.getAction());
					}

				}
			}
			for(MultipleAgentAction multAgentAction : transition.getMultipleAgentActions()) {
				if(multAgentAction.getAgent().equals(agent.getName())) {
					for(String action : multAgentAction.getActions()) {
						if(!availableActionMap.get(transition.getFromState()).contains(action)) {
							availableActionMap.get(transition.getFromState()).add(action);
						}
					}
				}
			}
		}

		return availableActionMap;
	}


	public static String modelCheck(String mcmasExecPath, String mcmasFilePath) throws IOException {
		try(Scanner scanner = new Scanner(Runtime.getRuntime().exec(mcmasExecPath + " " + mcmasFilePath).getInputStream()).useDelimiter("\\A")) {
			return scanner.hasNext() ? scanner.next() : "";
		}
	}

	public static boolean getMcmasResult(String mcmasOutput) {
//		if(mcmasOutput.contains("error")) throw new RuntimeException("MCMAS error: \n\n" + mcmasOutput);
		return  (mcmasOutput.contains("is TRUE in the model"));
	}

	private static void createTransition(State v, List<Transition> transitions, State s, List<List<AgentAction>> agentActions) {
		if(!agentActions.isEmpty() && transitions.stream().noneMatch(t -> t.getFromState().equals(v.getName()) && t.getToState().equals(s.getName()))) {
			removeDuplicates(agentActions);
			Transition transition = new Transition();
			transition.setFromState(v.getName());
			transition.setToState(s.getName());
			transition.setAgentActions(agentActions);
			transitions.add(transition);
		}
	}


//	public static Automaton.Outcome modelCheckingProcedure(CGSModel CGSModel) throws IOException {
//		CGSModel.getAgentActionsByStates();
//		CGSModel CGSModelMust = CGSModel.createAbstraction(CGSModel.Abstraction.Must);
//		must = CGSModelMust;
//		CGSModel CGSModelMay = CGSModel.createAbstraction(CGSModel.Abstraction.May);
//		State state = CGSModel.getStates().stream().filter(State::isInitial).findAny().get();
//		CGSModelMust.getStates().forEach(s -> s.setInitial(s instanceof StateCluster && ((StateCluster) s).containsChildState(state)));
//		CGSModelMay.getStates().forEach(s -> s.setInitial(s instanceof StateCluster && ((StateCluster) s).containsChildState(state)));
//		Automaton.Outcome outcome = CGSModel.modelCheck(CGSModel.getATL(), CGSModelMust, CGSModelMay);
//		if (outcome == Automaton.Outcome.Unknown) {
//			TestParser.good = true;
//			int i = 0;
//			ATL innermostFormula = CGSModel.getATL().innermostFormula();
//			while (innermostFormula != CGSModel.getATL()) {
////				CGSModelMust.setATL(innermostFormula.transl(true));
////				CGSModelMay.setATL(innermostFormula.transl(false));
//				List<StateCluster> goodStates = new ArrayList<>();
//				for (StateCluster stateCluster : AbstractionUtils.getStateClusters(CGSModel)) {
//					String stateClusterName = stateCluster.getName();
//					if(stateCluster.getChildStates().size() == 1 ||
//						CGSModelMust.getStates().stream().noneMatch(s -> s.getName().equals(stateClusterName)) ||
//						CGSModelMay.getStates().stream().noneMatch(s -> s.getName().equals(stateClusterName))) {
//						continue;
//					}
//					CGSModelMust.getStates().forEach(s -> s.setInitial(s.getName().equals(stateClusterName)));
//					CGSModelMay.getStates().forEach(s -> s.setInitial(s.getName().equals(stateClusterName)));
//
//					outcome = CGSModel.modelCheck(innermostFormula, CGSModelMust, CGSModelMay);
//					boolean split = true;
//					while (outcome == Automaton.Outcome.Unknown && split) {
//						FailureState failureState = failureState(CGSModelMust, CGSModelMay, CGSModel, stateCluster, innermostFormula);
//						boolean getVorW = false;
//						if(failureState.getState().getName().equals(stateCluster.getName())) {
//							getVorW = true;
//						}
//						split = refinement(CGSModelMust, CGSModelMay, CGSModel, failureState.getState());
//						if(getVorW) {
//							stateCluster = (StateCluster) CGSModelMust.getState(failureState.getState().getName());
//						}
//						outcome = CGSModel.modelCheck(innermostFormula, CGSModelMust, CGSModelMay);
//					}
//					if(outcome != Automaton.Outcome.Unknown) {
//						goodStates.add(stateCluster);
//					}
//				}
//				String atom = "atom" + i;
//				String atom_tt = atom + "_tt";
//				String atom_ff = atom + "_ff";
////				CGSModel.getState(state.getName()).getLabels().add(atom); // add(atom, s) from paper (removed because it seems pointless)
//				CGSModelMust.updateModel(atom_tt, atom_ff, goodStates);
//				CGSModelMay.updateModel(atom_tt, atom_ff, goodStates);
//				CGSModel.setATL(CGSModel.getATL().updateInnermostFormula(atom));
//				i++;
//				innermostFormula = CGSModel.getATL().innermostFormula();
//			}
//			CGSModelMust.getStates().forEach(s -> s.setInitial(s instanceof StateCluster && ((StateCluster) s).containsChildState(state)));
//			CGSModelMay.getStates().forEach(s -> s.setInitial(s instanceof StateCluster && ((StateCluster) s).containsChildState(state)));
//			StateCluster sCluster = (StateCluster) CGSModelMust.getStates().stream().filter(s -> s instanceof StateCluster && ((StateCluster) s).containsChildState(state)).findAny().get();
////			CGSModelMust.setATL(innermostFormula);
////			CGSModelMay.setATL(innermostFormula);
//			outcome = CGSModel.modelCheck(CGSModel.getATL(), CGSModelMust, CGSModelMay);
//			boolean split = true;
//			while (outcome == Automaton.Outcome.Unknown && split) {
////				sCluster = (StateCluster) CGSModelMust.getStates().stream().filter(s -> s instanceof StateCluster && ((StateCluster) s).getChildStates().size()>1).findAny().get();
//				FailureState failureState = failureState(CGSModelMust, CGSModelMay, CGSModel, sCluster, innermostFormula);
//				boolean getVorW = false;
//				if(failureState.getState().getName().equals(sCluster.getName())) {
//					getVorW = true;
//				}
//				split = refinement(CGSModelMust, CGSModelMay, CGSModel, failureState.getState());
//				if(getVorW) {
//					sCluster = (StateCluster) CGSModelMust.getState(failureState.getState().getName());
//				}
//				outcome = CGSModel.modelCheck(CGSModel.getATL(), CGSModelMust, CGSModelMay);
//			}
//		}
//		return outcome;
//	}
}
