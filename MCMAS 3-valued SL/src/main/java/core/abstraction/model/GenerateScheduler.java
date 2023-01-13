package core.abstraction.model;

import core.parser.StrategyLogic;
import org.checkerframework.checker.units.qual.A;

import java.util.*;
import java.util.stream.Collectors;

public class GenerateScheduler {
    public static String generateRandomProperty(int nProcesses) {
        Random random = new Random();
        StringBuilder formula = new StringBuilder();
//        if(random.nextBoolean()) {
            formula.append("<<e>> ");
            formula.append("<<x>> ");
            for(int i = 1; i <= nProcesses; i++) {
                formula.append("<<y").append(i).append(">> ");
            }
//        } else {
//            formula.append("[[e]] ");
//            formula.append("[[x]] ");
//            for(int i = 1; i <= nProcesses; i++) {
//                formula.append("[[y").append(i).append("]] ");
//            }
//        }
        formula.append("(Environment, e) ");
        formula.append("(Arbiter, x) ");
        for(int i = 1; i <= nProcesses; i++) {
            formula.append("(Process").append(i).append(", y").append(i).append(") ");
        }
        int nTOp = random.nextInt(2)+1;
        for(int i = 0; i < nTOp; i++) {
            if(random.nextBoolean()) {
                if(random.nextBoolean()) {
                    formula.append("F(");
                } else {
                    formula.append("X(");
                }
            } else {
                if(random.nextBoolean()) {
                    formula.append("G(");
                } else {
                    formula.append("!(");
                }
            }
        }
        int nAt = random.nextInt(nProcesses)+1;
        for(int i = 1; i <= nAt; i++) {
            if(random.nextBoolean()) {
                if(random.nextBoolean()) {
                    formula.append("rs").append(i);
                } else {
                    formula.append("!rs").append(i);
                }
            } else {
                if(random.nextBoolean()) {
                    formula.append("wt").append(i);
                } else {
                    formula.append("!wt").append(i);
                }
            }
            if(i != nAt) {
                if(random.nextBoolean()) {
                    formula.append(" and ");
                } else {
                    formula.append(" or ");
                }
            }
        }
        formula.append(")".repeat(nTOp));
        return formula.toString();
    }
    public static CGSModel generate(int nProcesses) {
        CGSModel model = new CGSModel();
        List<String> arbiterActionsS = new ArrayList<>();
        arbiterActionsS.add("id");
        for(int i = 1; i <= nProcesses; i++) {
            arbiterActionsS.add("p" + String.valueOf(i));
        }
        model.getAgents().add(new Agent("Arbiter", arbiterActionsS, new ArrayList<>()));
        for(int i = 1; i <= nProcesses; i++) {
            List<String> processActionsS = new ArrayList<>();
            processActionsS.add("id");
            processActionsS.add("rq");
            processActionsS.add("rn");
            processActionsS.add("rl");
            model.getAgents().add(new Agent("Process" + i, processActionsS, new ArrayList<>()));
        }
        String empty = "z".repeat(Math.max(0, nProcesses));
        List<State> states = new ArrayList<>();
        StringBuilder initialState = new StringBuilder();
        initialState.append("fr");
        for(int i = 1; i <= nProcesses; i++) {
            initialState.append("_in");
        }
        states.add(new State(initialState.toString(), true));
        List<State> alreadySeen = new ArrayList<>();
        alreadySeen.add(new State(initialState.toString(), true));
        while(states.size() > 0) {
            State state = states.get(states.size() - 1);
            states.remove(states.size()-1);
            List<AgentAction> arbiterActions = new ArrayList<>();
            String arbiterState = state.getName().split("_")[0];
            if(arbiterState.equals("fr")) {
                arbiterActions.add(new AgentAction("Arbiter", "id"));
            } else if(arbiterState.equals(empty)){
                arbiterActions.add(new AgentAction("Arbiter", "id"));
            } else {
                for(int i = 0; i < arbiterState.length(); i++) {
                    if(arbiterState.charAt(i) == 'u') {
                        arbiterActions.add(new AgentAction("Arbiter", "p" + String.valueOf(i + 1)));
                    }
                }
            }
            List<List<AgentAction>> processesActions = new ArrayList<>();
            for(int i = 1; i <= nProcesses; i++) {
                processesActions.add(new ArrayList<>());
                String processState = state.getName().split("_")[i];
                if(processState.equals("in")) {
                    processesActions.get(i-1).add(new AgentAction("Process" + i, "id"));
                    processesActions.get(i-1).add(new AgentAction("Process" + i, "rq"));
                } else if(processState.equals("wt")) {
                    processesActions.get(i-1).add(new AgentAction("Process" + i, "id"));
                    processesActions.get(i-1).add(new AgentAction("Process" + i, "rn"));
                } else {
                    processesActions.get(i-1).add(new AgentAction("Process" + i, "id"));
                    processesActions.get(i-1).add(new AgentAction("Process" + i, "rl"));
                }
            }

            int[] combinations = new int[nProcesses + 1];

            for(int i = 0; i < arbiterActions.size() * processesActions.stream().map(List::size).reduce(1, (a, b) -> a * b); i++) {
                List<List<AgentAction>> agentsActions = new ArrayList<>();
                List<AgentAction> agentsActions1 = new ArrayList<>();
                agentsActions.add(agentsActions1);
                agentsActions1.add(arbiterActions.get(combinations[0]));
                for (int j = 1; j <= nProcesses; j++) {
                    agentsActions1.add(processesActions.get(j-1).get(combinations[j]));
                }
                String nextArbiterState;
                if(arbiterState.equals("fr")) {
                    int count = 0;
                    for(AgentAction act : agentsActions1) {
                        if(act.getAction().equals("rq")) {
                            count++;
                        }
                    }
                    if(count == 0) {
                        nextArbiterState = "fr";
                    } else if(count == 1) {
                        nextArbiterState = empty;
                    } else {
                        List<Integer> aux = agentsActions1.stream().filter(a -> a.getAction().equals("rq")).map(a -> Integer.valueOf(a.getAgent().replace("Process", ""))).toList();
                        StringBuilder s = new StringBuilder();
                        for(int j = 1; j <= nProcesses; j++) {
                            if(aux.contains(j)) {
                                s.append("u");
                            } else {
                                s.append("z");
                            }
                        }
                        nextArbiterState = s.toString();
                    }
                } else if(arbiterState.equals(empty)){
                    int countRQ = 0, countRL = 0;
                    for(AgentAction act : agentsActions1) {
                        if(act.getAction().equals("rq")) {
                            countRQ++;
                        }
                        if(act.getAction().equals("rl")) {
                            countRL++;
                        }
                    }
                    if(countRL == 1 && countRQ == 0) {
                        nextArbiterState = "fr";
                    } else if(countRL == countRQ) {
                        nextArbiterState = empty;
                    } else {
                        List<Integer> aux = agentsActions1.stream().filter(a -> a.getAction().equals("rq")).map(a -> Integer.valueOf(a.getAgent().replace("Process", ""))).toList();
                        StringBuilder s = new StringBuilder();
                        for(int j = 1; j <= nProcesses; j++) {
                            if(aux.contains(j)) {
                                s.append("u");
                            } else {
                                s.append("z");
                            }
                        }
                        nextArbiterState = s.toString();
                    }
                } else {
                    Set<Integer> aux = new HashSet<>();
                    for(int j = 0; j < nProcesses; j++) {
                        if(arbiterState.charAt(j) == 'u') {
                            aux.add(j+1);
                        }
                    }
                    Set<Integer> aux1 = agentsActions1.stream().filter(a -> a.getAction().equals("rn")).map(a -> Integer.valueOf(a.getAgent().replace("Process", ""))).collect(Collectors.toSet());
                    if(!agentsActions1.get(0).getAction().equals("id")) {
                        aux1.add(Integer.valueOf(agentsActions1.get(0).getAction().replace("p", "")));
                    }
                    aux.removeAll(aux1);
                    aux.addAll(agentsActions1.stream().filter(a -> a.getAction().equals("rq")).map(a -> Integer.valueOf(a.getAgent().replace("Process", ""))).toList());
                    StringBuilder s = new StringBuilder();
                    for(int j = 1; j <= nProcesses; j++) {
                        if(aux.contains(j)) {
                            s.append("u");
                        } else {
                            s.append("z");
                        }
                    }
                    nextArbiterState = s.toString();
                }

                List<String> labels = new ArrayList<>();
                String[] nextProcessesState = new String[nProcesses];
                for(int j = 1; j <= nProcesses; j++) {
                    String processState = state.getName().split("_")[j];
                    if(processState.equals("in") && arbiterState.equals("fr")) {
                        List<Integer> aux = agentsActions1.stream().filter(a -> a.getAction().equals("rq")).map(a -> Integer.valueOf(a.getAgent().replace("Process", ""))).toList();
                        if(agentsActions1.get(j).getAction().equals("id")) {
                            nextProcessesState[j-1] = "in";
                        } else if(aux.size() == 1 && aux.get(0) == j) {
                            nextProcessesState[j-1] = "rs";
                            labels.add("rs" + j);
                        } else {
                            nextProcessesState[j-1] = "wt";
                            labels.add("wt" + j);
                        }
                    } else if(processState.equals("in") && arbiterState.equals(empty)) {
                        List<Integer> aux = agentsActions1.stream().filter(a -> a.getAction().equals("rq")).map(a -> Integer.valueOf(a.getAgent().replace("Process", ""))).toList();
                        List<Integer> aux1 = agentsActions1.stream().filter(a -> a.getAction().equals("rl")).map(a -> Integer.valueOf(a.getAgent().replace("Process", ""))).toList();
                        if(agentsActions1.get(j).getAction().equals("id")) {
                            nextProcessesState[j-1] = "in";
                        } else if(aux1.size() == 1 && aux.size() == 1) {
                            nextProcessesState[j-1] = "rs";
                            labels.add("rs" + j);
                        } else {
                            nextProcessesState[j-1] = "wt";
                            labels.add("wt" + j);
                        }
                    } else if(processState.equals("in")) {
                        if(agentsActions1.get(j).getAction().equals("id")) {
                            nextProcessesState[j-1] = "in";
                        } else {
                            nextProcessesState[j-1] = "wt";
                            labels.add("wt" + j);
                        }
                    } else if(processState.equals("rs") && arbiterState.equals(empty)) {
                        if(agentsActions1.get(j).getAction().equals("rl")) {
                            nextProcessesState[j-1] = "in";
                        } else {
                            nextProcessesState[j-1] = "rs";
                            labels.add("rs" + j);
                        }
                    } else if(processState.equals("rs") && !arbiterState.equals("fr")) {
                        if(agentsActions1.get(j).getAction().equals("rl") || !agentsActions1.get(0).getAction().equals("p" + String.valueOf(j))) {
                            nextProcessesState[j-1] = "in";
                        } else {
                            nextProcessesState[j-1] = "rs";
                            labels.add("rs" + j);
                        }
                    } else {
                        if(agentsActions1.get(j).getAction().equals("rn")) {
                            nextProcessesState[j-1] = "in";
                        } else if(agentsActions1.get(j).getAction().equals("id") && agentsActions1.get(0).getAction().equals("p" + String.valueOf(j))) {
                            nextProcessesState[j-1] = "rs";
                            labels.add("rs" + j);
                        } else {
                            nextProcessesState[j-1] = "wt";
                            labels.add("wt" + j);
                        }
                    }
                }

                State newState = new State(nextArbiterState + "_" + String.join("_", nextProcessesState), false, labels.toArray(new String[0]));
                if(!alreadySeen.contains(newState)) {
                    alreadySeen.add(newState);
                    states.add(newState);
                }
                model.getTransitions().add(new Transition(state.getName(), nextArbiterState + "_" + String.join("_", nextProcessesState), agentsActions));

                for (int j = 0; j <= nProcesses; j++) {
                    if (j == 0) {
                        combinations[j] = (combinations[j] + 1) % arbiterActions.size();
                    } else {
                        combinations[j] = (combinations[j] + 1) % processesActions.get(j-1).size();
                    }
                    if (combinations[j] != 0) {
                        break;
                    }
                }
            }
        }
        model.setStates(alreadySeen);
        StringBuilder formula = new StringBuilder();
        formula.append("<<e>> ");
        formula.append("<<x>> ");
        formula.append("<<y1>>");
        for(int i = 2; i <= nProcesses; i++) {
            formula.append("[[y").append(i).append("]] ");
        }
        formula.append("(Environment, e) ");
        formula.append("(Arbiter, x) ");
        for(int i = 1; i <= nProcesses; i++) {
            formula.append("(Process").append(i).append(", y").append(i).append(") ");
        }
        formula.append("F(rs1)");
//        for(int i = 1; i < nProcesses; i++) {
//            formula.append("(");
//            formula.append("rs").append(i);
////            for(int j = 1; j <= nProcesses; j++) {
////                if(i != j) {
////                    formula.append(" and ").append("!rs").append(j);
////                }
////            }
//            formula.append(")");
//            if(i != nProcesses - 1) {
//                formula.append(" or ");
//            }
//        }
//        formula.append(")");
        model.setFormula(formula.toString());
        Group group = new Group();
        group.setName("g");
        group.setAgents(model.getAgents().stream().map(Agent::getName).toList());
        model.getGroups().add(group);
        return model;
    }
}
