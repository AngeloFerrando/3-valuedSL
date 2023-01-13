#Model checker for 3-valued ATL
#author: Emily Yu

#!/usr/bin/python

import re
import sys
import os
import signal
from enum import Enum
from subprocess import Popen, PIPE
from pyparsing import nestedExpr
import pyparsing as pp
import re
import time
from lark import Lark, Transformer

lineNo = 0
line = ""
groupLineStart = 0
allAgents = []
groups = {}
ATLFormulae = ""
model = ""
fileCount = 0
strategyFormulas = {}

class NodeType (Enum):
    ROOT = 0
    AND = 1
    OR = 2
    ATOM = 3
    X = 4
    F = 5
    G = 6
    U = 7
    STRA = 8
    NOT = 9
    IMPLIES = 10
class Value(Enum):
    TT = 0
    FF = 1

class ATLNode:
    def __init__(self, type):
        self.type = type
        self.children = []
        self.groupName = ""
        self.atomName = ""

atl_parser = Lark(r"""
       ?phi: "!" phi ->not_formula
            | phi "and" phi ->and_formula
            | phi "or" phi ->or_formula
            | phi "->" phi ->imp_formula
            | "<" group ">" psi  ->stra_formula
            | "(" phi ")"
            | p_formula
       ?psi: "X" phi ->next_formula
            | phi "U" phi ->u_formula
            | "F" phi ->f_formula
            | "G" phi ->g_formula
            | "(" psi ")"

       group: CNAME
       p_formula: CNAME
       %import common.ESCAPED_STRING
       %import common.CNAME
       %import common.WS
       %ignore WS
       """, start='phi')

class TreeToATL(Transformer):
    def stra_formula(self, args):
        node = ATLNode(NodeType.STRA)
        node.groupName = args[0]
        node.children.append(args[1])
        return node

    def group(self, args):
        return args[0]

    def not_formula(self, args):
        node = ATLNode(NodeType.NOT)
        node.children.extend(args)
        return node

    def next_formula(self, args):
        node = ATLNode(NodeType.X)
        node.children.extend(args)
        return node

    def imp_formula(self, args):
        node = ATLNode(NodeType.IMPLY)
        node.children.extend(args)
        return node

    def and_formula(self, args):
        node = ATLNode(NodeType.AND)
        node.children.extend(args)
        return node

    def or_formula(self, args):
        node = ATLNode(NodeType.OR)
        node.children.extend(args)
        return node

    def f_formula(self, args):
        node = ATLNode(NodeType.F)
        node.children.extend(args)
        print(args)
        return node

    def g_formula(self, args):
        node = ATLNode(NodeType.G)
        node.children.extend(args)
        return node

    def p_formula(self, args):
        atom_name = args[0]
        node = ATLNode(NodeType.ATOM)
        node.atomName = atom_name
        return node


# get next line of ISPL file.
def getNextLine (file):
    global line
    global lineNo
    global groupLineStart

    line = file.readline()
    lineNo += 1
    while line and not line.strip():
        line = file.readline()

    if line:
        line = line.decode('utf8', 'ignore').strip ()
    if line.startswith("Groups"):
        groupLineStartt = lineNo

def parseISPL (ISFile):
    global ATLFormulae
    global allAgents
    global groups
    global model

    getNextLine(ISFile)

    # Get agent names
    while line:
        model += "\n" + line
        if line.startswith("Agent "):
            words = line.split()
            allAgents.append(words[1])
        if line.startswith("Evaluation"):
            break
        getNextLine(ISFile)

    # Get Evaluation information
    getNextLine(ISFile)
    while line:
        if line.startswith("end Evaluation"):
            break
        model+="\n" + line
        words = line.split(" ")
        atom_name = words[0].strip()

        getNextLine(ISFile)

    # Continue reading
    while line:
        model += "\n" + line
        if line.startswith("Groups"):
            break
        getNextLine(ISFile)

    # Get groups information
    getNextLine(ISFile)
    while line:
        if line.startswith("end Groups"):
            break

        model += "\n" + line
        words = line.split("=")
        names = (words[1].strip())[1:-2];
        names = [x.strip() for x in names.split(",")]
        groupName = words[0].strip();
        groups.update({groupName: names})
        insertGroups(groupName, complementGroup(groupName))

        getNextLine(ISFile)


    model += "\nend Groups\n\nFormulae\n"
    while line:
        if line.startswith("Formulae"):
            getNextLine(ISFile)
            break
        getNextLine(ISFile)

    while line:
        if not line.strip().startswith("--"):
            break
        getNextLine(ISFile)

    ATLFormulae = ""
    while line:
        if not line.strip() or line.startswith("end Formulae"):
            break
        ATLFormulae += line.strip()
        getNextLine(ISFile)
    print("Original Formula: ", ATLFormulae)

    ISFile.close()


def complementFormula(phi):

    txt = re.findall(r"\<(.*?)\>", phi)

    groupName = txt[0]
    s = "<"+groupName+">"
    s = phi.split(s)[1]
    #add tempGroup to new ISFile
    tempGroup = complementGroup(groupName)

    negF = negateCTLFormula(s)
    print(negF)
    result = "<" +groupName + "_> " + negF
    return result

def negateCTLFormula(phi):
    f = ""
    phi = phi.strip()
    if phi.startswith("X"):
        return "X ! (" + phi[1:-1] + ");"
    elif phi.startswith("F"):
        return "G ! (" + phi[1:-1] + ");"
    elif phi.startswith("G"):
        return "F ! (" + phi[1:-1] + ");"
    else:
        # !(a U b) <=> !b U ((!a ^ !b) V G!b)
        txt = findBrackets(phi)
        data = txt.split("U")
        if '(' in data[0]:
            a = findBrackets(data[0].strip())
        else:
            a = data[0].strip()

        if '(' in data[1]:
            b = findBrackets(data[1].strip())
        else:
            b = data[1].strip()
        f = "(!(" + b + ") U ((!(" + a + ") and !(" + b + ")) or AG !(" + b + ")));"
        print(f)

    return f

def findBrackets( aString ):
    if '(' in aString:
        match = aString.split('(',1)[1]
        open = 1
        for index in range(len(match)):
            if match[index] in '()':
                open = (open + 1) if match[index] == '(' else (open - 1)
            if not open:
                return match[:index]

def complementGroup(name):
    agents = groups[name]
    compl = diff(allAgents, agents)
    return compl

def diff(first, second):
    second = set(second)
    return [item for item in first if item not in second]

def runMcmas(n, newISFile):
    exe = sys.path[0] + "/mcmas_br "
    brflag = "-bpr " + str(n) + " -atlk 2 "
    f = " " + sys.path[0] + "/" + newISFile.name
    cmd = exe + brflag + f
    print("cmd: ", cmd)

    signal.signal(signal.SIGPIPE, signal.SIG_IGN);

    p = Popen(cmd, shell=True, stdout=PIPE)
    output = p.communicate()[0]
    output = output.splitlines()
    exe_time = output[-3].decode('utf8')
    print(exe_time)
    states = output[-2].decode('utf8')

    print(states)
    memory = output[-1].decode('utf8')

    print(memory)
    result = output[-5]

    result = result.split()[-4]
    result = result.decode('utf8')

    if result == 'TRUE':
        print ("MCMAS - TRUE")
        return 1
    else:
        print ("MCMAS - FALSE")
        return 0

def insertGroups(groupName, agents):
    global model
    gstr = "\n"+ groupName + "_ = {"
    for a in agents:
        gstr += a + ","
    gstr = gstr[:-1] + "};\n"

    model += gstr

# Algorithm MC3, Figure 4 in the paper
# v==1: tt
# v==0: ff
# v==-1: uu
def MC3(atltt, atlff, n):
    global model
    global fileCount

    f = open(str(fileCount) + ".ispl","w")
    fileCount += 1
    f.write(model)
    f.write("\n"+atltt+"\nend Formulae")
    f.close()
    print("check Formula ", atltt)
    result1 = runMcmas(n, f)

    f = open(str(fileCount) + ".ispl","w")
    fileCount += 1
    f.write(model)
    f.write("\n"+atlff+"\nend Formulae")
    f.close()
    print("check Formula ", atlff)
    result2 = runMcmas(n, f)

    print("Verification result:")
    if result1:
        print("TRUE")
        return 1
    if result2:
        print("FALSE")
        return 0

    print("UNDEFINED")
    return -1

# Figure 5 in the paper
# 1: tt
# 0: ff
# -1: uu
def iterative_MC(phi, n):
    j=0
    #j=n-1
    k=-1

    atltt = transl(phi, Value.TT)
    atlff = transl(phi, Value.FF)
    atltt = atltt+";"
    atlff = atlff+";"

    while j<n: #and k==-1:
        j += 1
        print("-------bound=",j,": ---------")
        start_time = time.time()
        k = MC3(atltt, atlff, j)
        print("verification time = ", time.time() - start_time)
    if k!=-1:
        print("----------\nBound: "+ str(j) + "\nVerification Result: ")
        if k==1:
            print("TRUE\n")
        else:
            print("FALSE\n")
        return (j,k)
    print("Verification Result: UNDEFINED\n")
    return (-1, -1)

def transl(node, v):
    type = node.type
    TT = Value.TT
    FF = Value.FF
    if(type == NodeType.ATOM):
        if(v==Value.TT):
            return node.atomName
        if(v==Value.FF):
            return node.atomName + "_ff"
    if(type == NodeType.NOT):
        sub_f = node.children[0]
        if(v==Value.TT):
            return transl(sub_f, FF)
        if(v==Value.FF):
            return transl(sub_f, TT)
    if(type == NodeType.AND):
        sub_f1 = node.children[0]
        sub_f2 = node.children[1]
        if(v==Value.TT):
            return "(" + transl(sub_f1, TT)  + ") and (" + transl(sub_f2, TT) + ")"
        if(v==Value.FF):
            return "(" + transl(sub_f1, FF) + ") or (" + transl(sub_f2, FF)  + ")"
    if(type == NodeType.OR):
        sub_f1 = node.children[0]
        sub_f2 = node.children[1]
        if(v==Value.TT):
            return "(" + transl(sub_f1, TT)  + ") or (" + transl(sub_f2, TT) + ")"
        if(v==Value.FF):
            return "(" + transl(sub_f1, FF) + ") and (" + transl(sub_f2, FF)  + ")"
    if(type == NodeType.STRA):
        groupName = str(node.groupName)
        sub_f = node.children[0]
        if(v==Value.TT):
            return "<"+groupName+">"+transl(sub_f, TT)
        if(v==Value.FF):
            return "<"+groupName+"_>"+transl(sub_f,FF)
    if(type == NodeType.X):
        sub_f = node.children[0]
        if(v==Value.TT):
            return "X ("+transl(sub_f, TT) + ")"
        if(v==Value.FF):
            return "X ("+transl(sub_f, FF) + ")"
    if(type == NodeType.F):
        sub_f = node.children[0]
        if(v==Value.TT):
            return "F ("+transl(sub_f, TT) + ")"
        if(v==Value.FF):
            return "G ("+transl(sub_f, FF) + ")"
    if(type == NodeType.G):
        sub_f = node.children[0]
        if(v==Value.TT):
            return "G ("+transl(sub_f, TT) + ")"
        if(v==Value.FF):
            return "F ("+transl(sub_f, FF) + ")"
    if(type == NodeType.U):
        sub_f1 = node.children[0]
        sub_f2 = node.children[1]
        if(v==Value.TT):
            return "(" + transl(sub_f1, TT)  + ") U ("  + transl(sub_f2, TT) + ")"
        if(v==Value.FF):
            s1 = transl(sub_f1, FF)
            s2 = transl(sub_f2, FF)
            return "(!(" + s2 + ") U ((!(" + s1 + ") and !(" + s2 + ")) or AG !(" + s2 + ")));"

def clean():
    exe = " cd " + sys.path[0] + " && rm -rf *.ispl"

    signal.signal(signal.SIGPIPE, signal.SIG_IGN);

    p = Popen(exe, shell=True, stdout=PIPE)
    output = p.communicate()[0]
    output = output.splitlines()


############ main #############

ISFile = open (sys.argv[2], "rb")
print("###########################\n Verifying...\n###########################")
parseISPL(ISFile)

ATLFormulae = ATLFormulae[:-1]
parser = atl_parser.parse(ATLFormulae)
print(parser)
rootNode = TreeToATL().transform(parser)
#iterative_MC(rootNod, int(sys.argv[1]))
#MC3(rootNode,int(sys.argv[1]))
iterative_MC(rootNode, int(sys.argv[1]))
clean()
