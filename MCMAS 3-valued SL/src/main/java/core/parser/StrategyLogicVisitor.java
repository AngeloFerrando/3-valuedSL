// Generated from /media/angelo/WorkData/git/General Abstraction Tool for CGS/abstraction/src/main/antlr4/StrategyLogic.g4 by ANTLR 4.10.1
package core.parser;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link StrategyLogicParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface StrategyLogicVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by the {@code Binding}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBinding(StrategyLogicParser.BindingContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Evaluation}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEvaluation(StrategyLogicParser.EvaluationContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Universal}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUniversal(StrategyLogicParser.UniversalContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Negation}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNegation(StrategyLogicParser.NegationContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Grouping}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGrouping(StrategyLogicParser.GroupingContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Disjunction}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDisjunction(StrategyLogicParser.DisjunctionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Implies}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitImplies(StrategyLogicParser.ImpliesContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Next}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNext(StrategyLogicParser.NextContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Eventually}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEventually(StrategyLogicParser.EventuallyContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Conjunction}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConjunction(StrategyLogicParser.ConjunctionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Existential}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExistential(StrategyLogicParser.ExistentialContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Always}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAlways(StrategyLogicParser.AlwaysContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Release}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelease(StrategyLogicParser.ReleaseContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Until}
	 * labeled alternative in {@link StrategyLogicParser#slExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUntil(StrategyLogicParser.UntilContext ctx);
	/**
	 * Visit a parse tree produced by {@link StrategyLogicParser#atomExpr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAtomExpr(StrategyLogicParser.AtomExprContext ctx);
}