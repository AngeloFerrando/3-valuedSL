package core.abstraction;

import com.google.common.base.Stopwatch;
import core.abstraction.model.*;
import core.parser.*;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.instrument.Instrumentation;
import java.util.*;
import java.util.stream.Collectors;

public class TestParser {

    public static void main1(String[] args) throws Exception {
        String mcmasExecPath = "/media/angelo/WorkData/mcmas-1.3.0/mcmas-sl/MCMAS-SL[1G]/mcmas64";
        int maxProcesses = 2, nRuns = 10000;
        for(int nProcesses = 2; nProcesses <= maxProcesses; nProcesses++) {
            CGSModel model = GenerateScheduler.generate(nProcesses);
            AbstractionUtils.validateCGS(model);
            int finalNProcesses = nProcesses;
            CGSModel mustModel = model.createAbstraction(CGSModel.Abstraction.Must, (s ->
            {
                for(int i = 1; i <= finalNProcesses; i++) {
                    if(s.getLabels().contains("wt"+i+"_tt")) {
                        return true;
                    }
                }
                return false;
            }));
            CGSModel mayModel = model.createAbstraction(CGSModel.Abstraction.May, (s ->
            {
                for(int i = 1; i <= finalNProcesses; i++) {
                    if(s.getLabels().contains("wt"+i+"_tt")) {
                        return true;
                    }
                }
                return false;
            }));
            int successes = 0;
            for(int j = 0; j < nRuns; j++){
                String formula = GenerateScheduler.generateRandomProperty(nProcesses);
                mustModel.setFormula(formula);
                mustModel.setSL(null);
                mayModel.setFormula(formula);
                mayModel.setSL(null);
                CGSModel.Outcome outcome = CGSModel.modelCheck3(mustModel, mayModel, mcmasExecPath);
                if (outcome != CGSModel.Outcome.Undefined) {
                    successes++;
                }
            }
            System.out.println("N. Processes " + nProcesses + ": " + ((((double)successes)/nRuns)*100) + "%");
        }
    }

    public static void runExperiments(int maxNProcesses) throws Exception {
        String mcmasExecPath1g = "../mcmas-1.3.0/mcmas-sl/MCMAS-SL[1G]/mcmas64";
        String mcmasExecPathK = "../mcmas-1.3.0/mcmas-sl/MCMAS-SLK/mcmas-slk_64";
        FileWriter fw = new FileWriter("results.txt", false);
        fw.write("");
        fw.close();
        for(int nProcesses = 2; nProcesses <= maxNProcesses; nProcesses++) {
            long startTime, endTime, duration;
            CGSModel model = GenerateScheduler.generate(nProcesses);
            AbstractionUtils.validateCGS(model);

            StringBuilder toPrint = new StringBuilder();
            toPrint.append("Processes: ").append(nProcesses).append("\n");
            toPrint.append("Number of states in CGS: ").append(model.getStates().size()).append("\n");
            toPrint.append("Number of transitions in CGS: ").append(model.getTransitions().size()).append("\n");

            startTime = System.nanoTime();
            int finalNProcesses = nProcesses;
            CGSModel mustModel = model.createAbstraction(CGSModel.Abstraction.Must, (s ->
            {
                for(int i = 1; i <= finalNProcesses; i++) {
                    if(s.getLabels().contains("wt"+i+"_tt")) {
                        return true;
                    }
                }
                return false;
//            if(s.getLabels().contains("rs"+1+"_tt")) {
//                return true;
//            }
//            return false;
            }));
            CGSModel mayModel = model.createAbstraction(CGSModel.Abstraction.May, (s ->
            {
                for(int i = 1; i <= finalNProcesses; i++) {
                    if(s.getLabels().contains("wt"+i+"_tt")) {
                        return true;
                    }
                }
                return false;
//            if(s.getLabels().contains("rs"+1+"_tt")) {
//                return true;
//            }
//            return false;
            }));
            endTime = System.nanoTime();
            duration = (endTime - startTime) / 1000000;
            toPrint.append("## Abstraction" + "\n");
            toPrint.append("Number of states in 3-valued CGS: ").append(Integer.min(mustModel.getStates().size(), mayModel.getStates().size())).append("\n");
            toPrint.append("Number of transitions in 3-valued CGS [must]: ").append(mustModel.getTransitions().size()).append("\n");
            toPrint.append("Number of transitions in 3-valued CGS [may]: ").append(mayModel.getTransitions().size()).append("\n");
            toPrint.append("#### Abstraction time: ").append(duration).append(" [ms]").append("\n");

            startTime = System.nanoTime();
            sl1g = true;
            toPrint.append("Verdict: ").append(CGSModel.modelCheck3(mustModel, mayModel, mcmasExecPath1g)).append("\n");
            endTime = System.nanoTime();
            duration = (endTime - startTime) / 1000000;
            toPrint.append("#### Verification time (SL[1G]): ").append(duration).append(" [ms]").append("\n");
            startTime = System.nanoTime();
            sl1g = false;
            toPrint.append("Verdict: ").append(CGSModel.modelCheck3(mustModel, mayModel, mcmasExecPathK)).append("\n");
            endTime = System.nanoTime();
            duration = (endTime - startTime) / 1000000;
            toPrint.append("#### Verification time (SLK): ").append(duration).append(" [ms]").append("\n");
            toPrint.append("\n##########################################################\n");
            System.out.println(toPrint);
            fw = new FileWriter("results.txt", true);
            fw.write(toPrint.toString());
            fw.close();
        }
    }

    public static void mainExperiments(String[] args) throws Exception {
        runExperiments(9);
    }

    private static void test() throws Exception {
        CGSModel test = new CGSModel();
        List<State> states = new ArrayList<>();
        states.add(new State("s1", true, "ap"));
        states.add(new State("s2", false, "ap"));
        states.add(new State("s3", false, "bp"));
        states.add(new State("s4", false, "cp"));
        test.setStates(states);
        List<Transition> transitions = new ArrayList<>();
        List<List<AgentAction>> agentActions = new ArrayList<>();
        List<AgentAction> agentActions1 = new ArrayList<>();
        agentActions1.add(new AgentAction("Ag1", "a"));
        agentActions1.add(new AgentAction("Ag2", "b"));
        agentActions.add(agentActions1);
        transitions.add(new Transition("s1", "s3", agentActions));
        agentActions = new ArrayList<>();
        agentActions1 = new ArrayList<>();
        agentActions1.add(new AgentAction("Ag1", "a"));
        agentActions1.add(new AgentAction("Ag2", "b"));
        agentActions.add(agentActions1);
        transitions.add(new Transition("s2", "s3", agentActions));
        agentActions = new ArrayList<>();
        agentActions1 = new ArrayList<>();
        agentActions1.add(new AgentAction("Ag1", "a"));
        agentActions1.add(new AgentAction("Ag2", "c"));
        agentActions.add(agentActions1);
        transitions.add(new Transition("s2", "s4", agentActions));
        test.setTransitions(transitions);
        List<Agent> agents = new ArrayList<>();
        List<String> actions = new ArrayList<>();
        actions.add("a");
        agents.add(new Agent("Ag1", actions, new ArrayList<>()));
        actions = new ArrayList<>();
        actions.add("b");
        actions.add("c");
        agents.add(new Agent("Ag2", actions, new ArrayList<>()));
        test.setAgents(agents);
        test.setFormula("<<x>> <<y>> (Ag1, x) (Ag2, y) X p");

        AbstractionUtils.validateCGS(test);

        CGSModel mustTest = test.createAbstraction(CGSModel.Abstraction.Must, (s -> s.getLabels().contains("ap_tt")));
        CGSModel mayTest = test.createAbstraction(CGSModel.Abstraction.May, (s -> s.getLabels().contains("ap_tt")));
    }

    public static boolean sl1g = true;
    public static void main(String[] args) throws Exception {
        String mcmasExecPath = "../mcmas-1.3.0/mcmas-sl/MCMAS-SL[1G]/mcmas64";
        int nProcesses;
        if(args.length != 0) {
            nProcesses = Integer.parseInt(args[0]);
            if (args[1].equals("-1g")) {
                mcmasExecPath = "../mcmas-1.3.0/mcmas-sl/MCMAS-SL[1G]/mcmas64";
            } else {
                sl1g = false;
                mcmasExecPath = "../mcmas-1.3.0/mcmas-sl/MCMAS-SLK/mcmas-slk_64";
            }
        } else {
            nProcesses = 2;
        }
        long startTime, endTime, duration;
        CGSModel model = GenerateScheduler.generate(nProcesses);

        AbstractionUtils.validateCGS(model);

        System.out.println("Number of states in CGS: " + model.getStates().size());
        System.out.println("Number of transitions in CGS: " + model.getTransitions().size());

        if(args.length != 3 || !args[2].equals("-only_abstraction")) {
            startTime = System.nanoTime();
            System.out.println("Verdict: " + CGSModel.modelCheck(model, mcmasExecPath));
            endTime = System.nanoTime();
            duration = (endTime - startTime) / 1000000;
            System.out.println("#### Verification time: " + duration + " [ms]");
        }

        startTime = System.nanoTime();
        CGSModel mustModel = model.createAbstraction(CGSModel.Abstraction.Must, (s ->
        {
            for(int i = 1; i <= nProcesses; i++) {
                if(s.getLabels().contains("wt"+i+"_tt")) {
                    return true;
                }
            }
            return false;
//            if(s.getLabels().contains("rs"+1+"_tt")) {
//                return true;
//            }
//            return false;
        }));
        CGSModel mayModel = model.createAbstraction(CGSModel.Abstraction.May, (s ->
        {
            for(int i = 1; i <= nProcesses; i++) {
                if(s.getLabels().contains("wt"+i+"_tt")) {
                    return true;
                }
            }
            return false;
//            if(s.getLabels().contains("rs"+1+"_tt")) {
//                return true;
//            }
//            return false;
        }));
        endTime = System.nanoTime();
        duration = (endTime - startTime) / 1000000;
        System.out.println("## Abstraction");
        System.out.println("Number of states in 3-valued CGS: " + Integer.min(mustModel.getStates().size(), mayModel.getStates().size()));
        System.out.println("Number of transitions in 3-valued CGS [must]: " + mustModel.getTransitions().size());
        System.out.println("Number of transitions in 3-valued CGS [may]: " + mayModel.getTransitions().size());
        System.out.println("#### Abstraction time: " + duration + " [ms]");

        startTime = System.nanoTime();
        System.out.println("Verdict: " + CGSModel.modelCheck3(mustModel, mayModel, mcmasExecPath));
        endTime = System.nanoTime();
        duration = (endTime - startTime) / 1000000;
        System.out.println("#### Verification time: " + duration + " [ms]");
    }
}
