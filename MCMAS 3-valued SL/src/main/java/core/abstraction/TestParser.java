package core.abstraction;

import com.google.common.base.Stopwatch;
import core.abstraction.model.*;
import core.parser.*;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import java.io.FileWriter;
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

    public static void main(String[] args) throws Exception {
        String mcmasExecPath = "/media/angelo/WorkData/mcmas-1.3.0/mcmas-sl/MCMAS-SL[1G]/mcmas64";;
        int nProcesses;
        if(args.length != 0) {
            nProcesses = Integer.parseInt(args[0]);
            if (args[1].equals("-1g")) {
                mcmasExecPath = "/media/angelo/WorkData/mcmas-1.3.0/mcmas-sl/MCMAS-SL[1G]/mcmas64";
            } else {
                mcmasExecPath = "/media/angelo/WorkData/mcmas-1.3.0/mcmas-sl/MCMAS-SLK/mcmas-slk_64";
            }
        } else {
            nProcesses = 2;
        }
        long startTime, endTime, duration;
        CGSModel model = GenerateScheduler.generate(nProcesses);

        AbstractionUtils.validateCGS(model);

        System.out.println("Number of states in CGS: " + model.getStates().size());
        System.out.println("Number of transitions in CGS: " + model.getTransitions().size());

//        if(args.length != 3 || !args[2].equals("-only_abstraction")) {
//            startTime = System.nanoTime();
//            System.out.println("Verdict: " + CGSModel.modelCheck(model, mcmasExecPath));
//            endTime = System.nanoTime();
//            duration = (endTime - startTime) / 1000000;
//            System.out.println("#### Verification time: " + duration + " [ms]");
//        }

        startTime = System.nanoTime();
        CGSModel mustModel = model.createAbstraction(CGSModel.Abstraction.Must, (s ->
        {
            for(int i = 2; i <= nProcesses; i++) {
                if(s.getLabels().contains("rs"+i+"_tt")) {
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
            for(int i = 2; i <= nProcesses; i++) {
                if(s.getLabels().contains("rs"+i+"_tt")) {
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
        System.out.println("Number of states in 3-valued CGS: " + mustModel.getStates().size());
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
