// Generated from /media/angelo/WorkData/git/General Abstraction Tool for CGS/abstraction/src/main/antlr4/StrategyLogic.g4 by ANTLR 4.10.1
package core.parser;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link StrategyLogicParser}.
 */
public interface StrategyLogicListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by the {@code Binding}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterBinding(StrategyLogicParser.BindingContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Binding}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitBinding(StrategyLogicParser.BindingContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Evaluation}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterEvaluation(StrategyLogicParser.EvaluationContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Evaluation}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitEvaluation(StrategyLogicParser.EvaluationContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Universal}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterUniversal(StrategyLogicParser.UniversalContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Universal}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitUniversal(StrategyLogicParser.UniversalContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Negation}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterNegation(StrategyLogicParser.NegationContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Negation}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitNegation(StrategyLogicParser.NegationContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Grouping}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterGrouping(StrategyLogicParser.GroupingContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Grouping}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitGrouping(StrategyLogicParser.GroupingContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Disjunction}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterDisjunction(StrategyLogicParser.DisjunctionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Disjunction}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitDisjunction(StrategyLogicParser.DisjunctionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Implies}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterImplies(StrategyLogicParser.ImpliesContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Implies}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitImplies(StrategyLogicParser.ImpliesContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Next}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterNext(StrategyLogicParser.NextContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Next}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitNext(StrategyLogicParser.NextContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Eventually}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterEventually(StrategyLogicParser.EventuallyContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Eventually}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitEventually(StrategyLogicParser.EventuallyContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Conjunction}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterConjunction(StrategyLogicParser.ConjunctionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Conjunction}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitConjunction(StrategyLogicParser.ConjunctionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Existential}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterExistential(StrategyLogicParser.ExistentialContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Existential}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitExistential(StrategyLogicParser.ExistentialContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Always}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterAlways(StrategyLogicParser.AlwaysContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Always}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitAlways(StrategyLogicParser.AlwaysContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Release}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterRelease(StrategyLogicParser.ReleaseContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Release}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitRelease(StrategyLogicParser.ReleaseContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Until}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void enterUntil(StrategyLogicParser.UntilContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Until}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 */
	void exitUntil(StrategyLogicParser.UntilContext ctx);
	/**
	 * Enter a parse tree produced by {@link StrategyLogicParser#atomExpr}.
	 * @param ctx the parse tree
	 */
	void enterAtomExpr(StrategyLogicParser.AtomExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link StrategyLogicParser#atomExpr}.
	 * @param ctx the parse tree
	 */
	void exitAtomExpr(StrategyLogicParser.AtomExprContext ctx);
}