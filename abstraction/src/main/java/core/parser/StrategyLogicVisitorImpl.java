package core.parser;

public class StrategyLogicVisitorImpl extends StrategyLogicBaseVisitor<StrategyLogic> {
    @Override
    public StrategyLogic visitImplies(StrategyLogicParser.ImpliesContext ctx) {
        return new StrategyLogic.Implies(visit(ctx.left), visit(ctx.right));
    }

    @Override
    public StrategyLogic visitNegation(StrategyLogicParser.NegationContext ctx) {
        return new StrategyLogic.Not(visit(ctx.getChild(1)));
    }

    @Override
    public StrategyLogic visitNext(StrategyLogicParser.NextContext ctx) {
        return new StrategyLogic.Next(visit(ctx.getChild(1)));
    }

    @Override
    public StrategyLogic visitEventually(StrategyLogicParser.EventuallyContext ctx) {
        StrategyLogic subFormula = visit(ctx.getChild(1));
        return new StrategyLogic.Eventually(subFormula);
    }

    @Override
    public StrategyLogic visitConjunction(StrategyLogicParser.ConjunctionContext ctx) {
        return new StrategyLogic.And(visit(ctx.left), visit(ctx.right));
    }

    @Override
    public StrategyLogic visitDisjunction(StrategyLogicParser.DisjunctionContext ctx) {
        return new StrategyLogic.Or(visit(ctx.left), visit(ctx.right));
    }

    @Override
    public StrategyLogic visitAlways(StrategyLogicParser.AlwaysContext ctx) {
        StrategyLogic subFormula = visit(ctx.getChild(1));
        return new StrategyLogic.Globally(subFormula);
    }

    @Override
    public StrategyLogic visitUntil(StrategyLogicParser.UntilContext ctx) {
        return new StrategyLogic.Until(visit(ctx.left), visit(ctx.right));
    }

    @Override
    public StrategyLogic visitRelease(StrategyLogicParser.ReleaseContext ctx) {
        return new StrategyLogic.Release(visit(ctx.left), visit(ctx.right));
    }

    @Override
    public StrategyLogic visitAtomExpr(StrategyLogicParser.AtomExprContext ctx) {
        return new StrategyLogic.Atom(ctx.getText());
    }

    @Override
    public StrategyLogic visitExistential(StrategyLogicParser.ExistentialContext ctx) {
        return new StrategyLogic.Existential(ctx.var.getText(), visit(ctx.getChild(3)));
    }

    @Override
    public StrategyLogic visitUniversal(StrategyLogicParser.UniversalContext ctx) {
        return new StrategyLogic.Universal(ctx.var.getText(), visit(ctx.getChild(3)));
    }

    @Override
    public StrategyLogic visitBinding(StrategyLogicParser.BindingContext ctx) {
        return new StrategyLogic.Binding(ctx.agent.getText(), ctx.var.getText(), visit(ctx.getChild(5)));
    }

    @Override
    public StrategyLogic visitGrouping(StrategyLogicParser.GroupingContext ctx) {
        return visit(ctx.getChild(1));
    }
}
