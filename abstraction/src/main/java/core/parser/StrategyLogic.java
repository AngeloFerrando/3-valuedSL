package core.parser;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public abstract class StrategyLogic implements Cloneable {

    @Override
    public int hashCode() {
        return toString().hashCode();
    }

    @Override
    public boolean equals(Object o) {
        if(!(o instanceof StrategyLogic)) { return false; }
        return o.toString().equals(this.toString());
    }

    public abstract List<String> getTerms();
    @Override
    public abstract StrategyLogic clone();
    public abstract StrategyLogic normalForm(boolean v);
    public StrategyLogic normalForm() {
        return normalForm(true);
    }
    public StrategyLogic transl(boolean v) {
        return transl(v, false);
    }
    public abstract StrategyLogic transl(boolean v, boolean check);

    public static class Atom extends StrategyLogic {
        private String atom;

        public Atom(String atom) {
            this.atom = atom;
        }

        @Override
        public String toString() {
            return atom;
        }

        public String getAtom() {
            return atom;
        }

        public void setAtom(String atom) {
            this.atom = atom;
        }

        @Override
        public List<String> getTerms() {
            List<String> list = new ArrayList<>();
            if(!atom.equals("true") && !atom.equals("false")) list.add(atom);
            return list;
        }

        @Override
        public Atom clone() {
            return new Atom(atom);
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            if(v) {
                return this;
            } else {
                return new Not(this);
            }
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            if(atom.equals("true")) {
                return v ? new Atom("true") : new Atom("false");
            } else if (atom.equals("false")) {
                return v ? new Atom("false") : new Atom("true");
            } else if(check){
                if(v) {
                    if(atom.contains("_tt")) {
                        return new Or(new Atom(atom), new Atom(atom.replace("_tt", "") + "_uu"));
                    } else if(atom.contains("_ff")) {
                        return new Or(new Atom(atom), new Atom(atom.replace("_ff", "") + "_uu"));
                    } else {
                        return new Or(new Atom(atom + "_tt"), new Atom(atom + "_uu"));
                    }
                } else {
                    if(atom.contains("_tt")) {
                        return new Or(new Atom(atom.replace("_tt", "_ff")), new Atom(atom.replace("_tt", "") + "_uu"));
                    } else if(atom.contains("_ff")) {
                        return new Or(new Atom(atom.replace("_ff", "_tt")), new Atom(atom.replace("_ff", "") + "_uu"));
                    } else {
                        return new Or(new Atom(atom + "_ff"), new Atom(atom + "_uu"));
                    }
                }
            } else {
                if(atom.contains("_tt")) {
                    return new Atom(atom.replace("_tt", "") + (v ? "_tt" : "_ff"));
                } else if(atom.contains("_ff")) {
                    return new Atom(atom.replace("_ff", "") + (v ? "_ff" : "_tt"));
                } else {
                    return new Atom(atom + (v ? "_tt" : "_ff"));
                }
            }
        }
    }

    public static class Next extends StrategyLogic {
        private StrategyLogic subFormula;

        public Next(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        @Override
        public String toString() {
            return "X(" + subFormula.toString() + ")";
        }

        public StrategyLogic getSubFormula() {
            return subFormula;
        }

        public void setSubFormula(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        @Override
        public List<String> getTerms() {
            return subFormula.getTerms();
        }

        @Override
        public Next clone() {
            return new Next(this.subFormula.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            return new Next(this.subFormula.normalForm(v));
        }

        public Next transl(boolean v, boolean check) {
            return new Next(subFormula.transl(v, check));
        }
    }

    public static class And extends StrategyLogic {
        private StrategyLogic left;
        private StrategyLogic right;

        public And(StrategyLogic left, StrategyLogic right) {
            this.left = left;
            this.right = right;
        }

        @Override
        public String toString() {
            return "(" + left.toString() + " and " + right.toString() + ")";
        }

        public StrategyLogic getLeft() {
            return left;
        }

        public void setLeft(StrategyLogic left) {
            this.left = left;
        }

        public StrategyLogic getRight() {
            return right;
        }

        public void setRight(StrategyLogic right) {
            this.right = right;
        }

        @Override
        public List<String> getTerms() {
            List<String> list = new ArrayList<>();
            list.addAll(left.getTerms());
            list.addAll(right.getTerms());
            return list;
        }

        @Override
        public And clone() {
            return new And(left.clone(), right.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            if(v) {
                return new And(this.left.normalForm(true), this.right.normalForm(true));
            } else {
                return new Or(this.left.normalForm(false), this.right.normalForm(false));
            }
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            if(v) {
                return new And(left.transl(true, check), right.transl(true, check));
            } else {
                return new Or(left.transl(false, check), right.transl(false, check));
            }
        }
    }

    public static class Or extends StrategyLogic {
        private StrategyLogic left;
        private StrategyLogic right;

        public Or(StrategyLogic left, StrategyLogic right) {
            this.left = left;
            this.right = right;
        }

        @Override
        public String toString() {
            return "(" + left.toString() + " or " + right.toString() + ")";
        }

        public StrategyLogic getLeft() {
            return left;
        }

        public void setLeft(StrategyLogic left) {
            this.left = left;
        }

        public StrategyLogic getRight() {
            return right;
        }

        public void setRight(StrategyLogic right) {
            this.right = right;
        }

        @Override
        public List<String> getTerms() {
            List<String> list = new ArrayList<>();
            list.addAll(left.getTerms());
            list.addAll(right.getTerms());
            return list;
        }

        @Override
        public Or clone() {
            return new Or(left.clone(), right.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            if(v) {
                return new Or(this.left.normalForm(true), this.right.normalForm(true));
            } else {
                return new And(this.left.normalForm(false), this.right.normalForm(false));
            }
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            if(v) {
                return new Or(left.transl(true, check), right.transl(true, check));
            } else {
                return new And(left.transl(false, check), right.transl(false, check));
            }
        }
    }

    public static class Implies extends StrategyLogic {
        private StrategyLogic left;
        private StrategyLogic right;

        public Implies(StrategyLogic left, StrategyLogic right) {
            this.left = left;
            this.right = right;
        }

        @Override
        public String toString() {
            return "(" + left.toString() + " -> " + right.toString() + ")";
        }

        public StrategyLogic getLeft() {
            return left;
        }

        public void setLeft(StrategyLogic left) {
            this.left = left;
        }

        public StrategyLogic getRight() {
            return right;
        }

        public void setRight(StrategyLogic right) {
            this.right = right;
        }

        @Override
        public List<String> getTerms() {
            List<String> list = new ArrayList<>();
            list.addAll(left.getTerms());
            list.addAll(right.getTerms());
            return list;
        }

        @Override
        public Implies clone() {
            return new Implies(left.clone(), right.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            return new Or(new Not(this.left), this.right).normalForm(v);
        }

        @Override
        public Implies transl(boolean v, boolean check) {
            return new Implies(left.transl(v, check), right.transl(v, check));
        }
    }

    public static class Eventually extends StrategyLogic {
        private StrategyLogic subFormula;

        public Eventually(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        @Override
        public String toString() {
            return "F(" + subFormula.toString() + ")";
        }

        public StrategyLogic getSubFormula() {
            return subFormula;
        }

        public void setSubFormula(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        @Override
        public List<String> getTerms() {
            return subFormula.getTerms();
        }

        @Override
        public Eventually clone() {
            return new Eventually(subFormula.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            return new Until(new Atom("true"), this.subFormula).normalForm(v);
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            if(v) {
                return new Eventually(subFormula.transl(true, check));
            } else {
                return new Globally(subFormula.transl(false, check));
            }
        }
    }

    public static class Globally extends StrategyLogic {
        private StrategyLogic subFormula;

        public Globally(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        @Override
        public String toString() {
            return "G(" + subFormula.toString() + ")";
        }

        public StrategyLogic getSubFormula() {
            return subFormula;
        }

        public void setSubFormula(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        @Override
        public List<String> getTerms() {
            return subFormula.getTerms();
        }

        @Override
        public Globally clone() {
            return new Globally(subFormula.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            return new Release(new Atom("false"), this.subFormula).normalForm(v);
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            if(v) {
                return new Globally(subFormula.transl(true, check));
            } else {
                return new Eventually(subFormula.transl(false, check));
            }
        }
    }

    public static class Until extends StrategyLogic {
        private StrategyLogic left;
        private StrategyLogic right;

        public Until(StrategyLogic left, StrategyLogic right) {
            this.left = left;
            this.right = right;
        }

        @Override
        public String toString() {
            return "(" + left.toString() + " U " + right.toString() + ")";
        }

        public StrategyLogic getLeft() {
            return left;
        }

        public void setLeft(StrategyLogic left) {
            this.left = left;
        }

        public StrategyLogic getRight() {
            return right;
        }

        public void setRight(StrategyLogic right) {
            this.right = right;
        }

        @Override
        public List<String> getTerms() {
            List<String> list = new ArrayList<>();
            list.addAll(left.getTerms());
            list.addAll(right.getTerms());
            return list;
        }

        @Override
        public Until clone() {
            return new Until(left.clone(), right.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            if(v) {
                return new Until(this.left.normalForm(true), this.right.normalForm(true));
            } else {
                return new Release(this.left.normalForm(false), this.right.normalForm(false));
            }
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            return v ? new Until(left.transl(true, check), right.transl(true, check)) : new Or(new Until(right.transl(false, check), new And(left.transl(false, check), right.transl(false))), new Globally(right.transl(false)));
        }
    }

    // to be removed
    public static class Release extends StrategyLogic {
        private StrategyLogic left;
        private StrategyLogic right;

        public Release(StrategyLogic left, StrategyLogic right) {
            this.left = left;
            this.right = right;
        }

        @Override
        public String toString() {
            return "(" + left.toString() + " R " + right.toString() + ")";
        }

        public StrategyLogic getLeft() {
            return left;
        }

        public void setLeft(StrategyLogic left) {
            this.left = left;
        }

        public StrategyLogic getRight() {
            return right;
        }

        public void setRight(StrategyLogic right) {
            this.right = right;
        }

        @Override
        public List<String> getTerms() {
            List<String> list = new ArrayList<>();
            list.addAll(left.getTerms());
            list.addAll(right.getTerms());
            return list;
        }

        @Override
        public Release clone() {
            return new Release(left.clone(), right.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            if(v) {
                return new Release(this.left.normalForm(true), this.right.normalForm(true));
            } else {
                return new Until(this.left.normalForm(false), this.right.normalForm(false));
            }
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            return v ? new Release(left.transl(true, check), right.transl(true, check)) : new Until(left.transl(false, check), right.transl(false, check));
        }
    }

    public static class Not extends StrategyLogic {
        private StrategyLogic subFormula;

        public Not(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        @Override
        public String toString() {
            return "!(" + subFormula.toString() + ")";
        }

        public StrategyLogic getSubFormula() {
            return subFormula;
        }

        public void setSubFormula(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        @Override
        public List<String> getTerms() {
            return subFormula.getTerms();
        }

        @Override
        public Not clone() {
            return new Not(subFormula.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            return this.subFormula.normalForm(!v);
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            return subFormula.transl(!v, check);
        }
    }

    public static class Existential extends StrategyLogic {
        private String var;
        private StrategyLogic subFormula;

        public Existential(String var, StrategyLogic subFormula) {
            this.var = var;
            this.subFormula = subFormula;
        }

        @Override
        public String toString() {
            String s = subFormula.toString();
            return "<<" + var + ">>" + s; }

        public StrategyLogic getSubFormula() {
            return subFormula;
        }

        public void setSubFormula(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        public String getVar() { return var; }

        @Override
        public List<String> getTerms() {
            return subFormula.getTerms();
        }

        @Override
        public Existential clone() {
            return new Existential(var, subFormula.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            if(v) {
                return new Existential(this.var, this.subFormula.normalForm(true));
            } else {
                return new Universal(this.var, this.subFormula.normalForm(false));
            }
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            if(v) {
                return new Existential(var, subFormula.transl(true, check));
            } else {
                return new Universal(var, subFormula.transl(false, check));
            }
        }
    }

    public static class Universal extends StrategyLogic {
        private String var;
        private StrategyLogic subFormula;

        public Universal(String var, StrategyLogic subFormula) {
            this.var = var;
            this.subFormula = subFormula;
        }

        @Override
        public String toString() { return "[[" + var + "]] " + this.subFormula.toString(); }//(new Not(subFormula).normalForm(true)).toString(); }

        public StrategyLogic getSubFormula() {
            return subFormula;
        }

        public void setSubFormula(StrategyLogic subFormula) {
            this.subFormula = subFormula;
        }

        public String getVar() { return var; }

        @Override
        public List<String> getTerms() {
            return subFormula.getTerms();
        }

        @Override
        public Universal clone() {
            return new Universal(var, subFormula.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            if(v) {
                return new Universal(this.var, this.subFormula.normalForm(true));
            } else {
                return new Existential(this.var, this.subFormula.normalForm(false));
            }
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            if(v) {
                return new Universal(var, subFormula.transl(true, check));
            } else {
                return new Existential(var, subFormula.transl(false, check));
            }
        }
    }

    public static class Binding extends StrategyLogic {
        private String agent;
        private String var;
        private StrategyLogic subFormula;

        public Binding(String agent, String var, StrategyLogic subFormula) {
            this.agent = agent;
            this.var = var;
            this.subFormula = subFormula;
        }

        @Override
        public String toString() {
            return "(" + this.agent + "," + this.var + ") " + this.subFormula;
        }

        @Override
        public List<String> getTerms() {
            return subFormula.getTerms();
        }

        @Override
        public Binding clone() {
            return new Binding(this.agent, this.var, this.subFormula.clone());
        }

        @Override
        public StrategyLogic normalForm(boolean v) {
            return new Binding(this.agent, this.var, this.subFormula.normalForm(v));
        }

        @Override
        public StrategyLogic transl(boolean v, boolean check) {
            return new Binding(this.agent, this.var, subFormula.transl(v, check));
        }
    }

}
