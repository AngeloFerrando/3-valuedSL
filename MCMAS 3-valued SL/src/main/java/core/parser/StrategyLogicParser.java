// Generated from /media/angelo/WorkData/git/General Abstraction Tool for CGS/abstraction/src/main/antlr4/StrategyLogic.g4 by ANTLR 4.10.1
package core.parser;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class StrategyLogicParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.10.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, ATOM=26, WS=27;
	public static final int
		RULE_slExpr = 0, RULE_atomExpr = 1;
	private static String[] makeRuleNames() {
		return new String[] {
			"slExpr", "atomExpr"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'!'", "'not'", "'next'", "'X'", "'eventually'", "'F'", "'always'", 
			"'G'", "'until'", "'U'", "'release'", "'R'", "'&&'", "'and'", "'||'", 
			"'or'", "'->'", "'implies'", "'<<'", "'>>'", "'[['", "']]'", "'('", "','", 
			"')'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, "ATOM", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "StrategyLogic.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public StrategyLogicParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class SlExprContext extends ParserRuleContext {
		public SlExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_slExpr; }
	 
		public SlExprContext() { }
		public void copyFrom(SlExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class BindingContext extends SlExprContext {
		public Token agent;
		public Token var;
		public SlExprContext child;
		public List<TerminalNode> ATOM() { return getTokens(StrategyLogicParser.ATOM); }
		public TerminalNode ATOM(int i) {
			return getToken(StrategyLogicParser.ATOM, i);
		}
		public SlExprContext slExpr() {
			return getRuleContext(SlExprContext.class,0);
		}
		public BindingContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterBinding(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitBinding(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitBinding(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class EvaluationContext extends SlExprContext {
		public AtomExprContext child;
		public AtomExprContext atomExpr() {
			return getRuleContext(AtomExprContext.class,0);
		}
		public EvaluationContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterEvaluation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitEvaluation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitEvaluation(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class UniversalContext extends SlExprContext {
		public Token var;
		public SlExprContext child;
		public TerminalNode ATOM() { return getToken(StrategyLogicParser.ATOM, 0); }
		public SlExprContext slExpr() {
			return getRuleContext(SlExprContext.class,0);
		}
		public UniversalContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterUniversal(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitUniversal(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitUniversal(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class NegationContext extends SlExprContext {
		public SlExprContext child;
		public SlExprContext slExpr() {
			return getRuleContext(SlExprContext.class,0);
		}
		public NegationContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterNegation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitNegation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitNegation(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class GroupingContext extends SlExprContext {
		public SlExprContext slExpr() {
			return getRuleContext(SlExprContext.class,0);
		}
		public GroupingContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterGrouping(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitGrouping(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitGrouping(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class DisjunctionContext extends SlExprContext {
		public SlExprContext left;
		public SlExprContext right;
		public List<SlExprContext> slExpr() {
			return getRuleContexts(SlExprContext.class);
		}
		public SlExprContext slExpr(int i) {
			return getRuleContext(SlExprContext.class,i);
		}
		public DisjunctionContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterDisjunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitDisjunction(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitDisjunction(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ImpliesContext extends SlExprContext {
		public SlExprContext left;
		public SlExprContext right;
		public List<SlExprContext> slExpr() {
			return getRuleContexts(SlExprContext.class);
		}
		public SlExprContext slExpr(int i) {
			return getRuleContext(SlExprContext.class,i);
		}
		public ImpliesContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterImplies(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitImplies(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitImplies(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class NextContext extends SlExprContext {
		public SlExprContext child;
		public SlExprContext slExpr() {
			return getRuleContext(SlExprContext.class,0);
		}
		public NextContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterNext(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitNext(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitNext(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class EventuallyContext extends SlExprContext {
		public SlExprContext child;
		public SlExprContext slExpr() {
			return getRuleContext(SlExprContext.class,0);
		}
		public EventuallyContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterEventually(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitEventually(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitEventually(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ConjunctionContext extends SlExprContext {
		public SlExprContext left;
		public SlExprContext right;
		public List<SlExprContext> slExpr() {
			return getRuleContexts(SlExprContext.class);
		}
		public SlExprContext slExpr(int i) {
			return getRuleContext(SlExprContext.class,i);
		}
		public ConjunctionContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterConjunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitConjunction(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitConjunction(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ExistentialContext extends SlExprContext {
		public Token var;
		public SlExprContext child;
		public TerminalNode ATOM() { return getToken(StrategyLogicParser.ATOM, 0); }
		public SlExprContext slExpr() {
			return getRuleContext(SlExprContext.class,0);
		}
		public ExistentialContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterExistential(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitExistential(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitExistential(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class AlwaysContext extends SlExprContext {
		public SlExprContext child;
		public SlExprContext slExpr() {
			return getRuleContext(SlExprContext.class,0);
		}
		public AlwaysContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterAlways(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitAlways(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitAlways(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ReleaseContext extends SlExprContext {
		public SlExprContext left;
		public SlExprContext right;
		public List<SlExprContext> slExpr() {
			return getRuleContexts(SlExprContext.class);
		}
		public SlExprContext slExpr(int i) {
			return getRuleContext(SlExprContext.class,i);
		}
		public ReleaseContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterRelease(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitRelease(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitRelease(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class UntilContext extends SlExprContext {
		public SlExprContext left;
		public SlExprContext right;
		public List<SlExprContext> slExpr() {
			return getRuleContexts(SlExprContext.class);
		}
		public SlExprContext slExpr(int i) {
			return getRuleContext(SlExprContext.class,i);
		}
		public UntilContext(SlExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterUntil(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitUntil(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitUntil(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SlExprContext slExpr() throws RecognitionException {
		return slExpr(0);
	}

	private SlExprContext slExpr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		SlExprContext _localctx = new SlExprContext(_ctx, _parentState);
		SlExprContext _prevctx = _localctx;
		int _startState = 0;
		enterRecursionRule(_localctx, 0, RULE_slExpr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(32);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				{
				_localctx = new NegationContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(5);
				_la = _input.LA(1);
				if ( !(_la==T__0 || _la==T__1) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(6);
				((NegationContext)_localctx).child = slExpr(14);
				}
				break;
			case 2:
				{
				_localctx = new NextContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(7);
				_la = _input.LA(1);
				if ( !(_la==T__2 || _la==T__3) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(8);
				((NextContext)_localctx).child = slExpr(13);
				}
				break;
			case 3:
				{
				_localctx = new EventuallyContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(9);
				_la = _input.LA(1);
				if ( !(_la==T__4 || _la==T__5) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(10);
				((EventuallyContext)_localctx).child = slExpr(12);
				}
				break;
			case 4:
				{
				_localctx = new AlwaysContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(11);
				_la = _input.LA(1);
				if ( !(_la==T__6 || _la==T__7) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(12);
				((AlwaysContext)_localctx).child = slExpr(11);
				}
				break;
			case 5:
				{
				_localctx = new ExistentialContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(13);
				match(T__18);
				setState(14);
				((ExistentialContext)_localctx).var = match(ATOM);
				setState(15);
				match(T__19);
				setState(16);
				((ExistentialContext)_localctx).child = slExpr(5);
				}
				break;
			case 6:
				{
				_localctx = new UniversalContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(17);
				match(T__20);
				setState(18);
				((UniversalContext)_localctx).var = match(ATOM);
				setState(19);
				match(T__21);
				setState(20);
				((UniversalContext)_localctx).child = slExpr(4);
				}
				break;
			case 7:
				{
				_localctx = new BindingContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(21);
				match(T__22);
				setState(22);
				((BindingContext)_localctx).agent = match(ATOM);
				setState(23);
				match(T__23);
				setState(24);
				((BindingContext)_localctx).var = match(ATOM);
				setState(25);
				match(T__24);
				setState(26);
				((BindingContext)_localctx).child = slExpr(3);
				}
				break;
			case 8:
				{
				_localctx = new GroupingContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(27);
				match(T__22);
				setState(28);
				slExpr(0);
				setState(29);
				match(T__24);
				}
				break;
			case 9:
				{
				_localctx = new EvaluationContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(31);
				((EvaluationContext)_localctx).child = atomExpr();
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(51);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
			while ( _alt!=2 && _alt!= ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(49);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
					case 1:
						{
						_localctx = new UntilContext(new SlExprContext(_parentctx, _parentState));
						((UntilContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_slExpr);
						setState(34);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(35);
						_la = _input.LA(1);
						if ( !(_la==T__8 || _la==T__9) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(36);
						((UntilContext)_localctx).right = slExpr(11);
						}
						break;
					case 2:
						{
						_localctx = new ReleaseContext(new SlExprContext(_parentctx, _parentState));
						((ReleaseContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_slExpr);
						setState(37);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(38);
						_la = _input.LA(1);
						if ( !(_la==T__10 || _la==T__11) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(39);
						((ReleaseContext)_localctx).right = slExpr(10);
						}
						break;
					case 3:
						{
						_localctx = new ConjunctionContext(new SlExprContext(_parentctx, _parentState));
						((ConjunctionContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_slExpr);
						setState(40);
						if (!(precpred(_ctx, 8))) throw new FailedPredicateException(this, "precpred(_ctx, 8)");
						setState(41);
						_la = _input.LA(1);
						if ( !(_la==T__12 || _la==T__13) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(42);
						((ConjunctionContext)_localctx).right = slExpr(9);
						}
						break;
					case 4:
						{
						_localctx = new DisjunctionContext(new SlExprContext(_parentctx, _parentState));
						((DisjunctionContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_slExpr);
						setState(43);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(44);
						_la = _input.LA(1);
						if ( !(_la==T__14 || _la==T__15) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(45);
						((DisjunctionContext)_localctx).right = slExpr(8);
						}
						break;
					case 5:
						{
						_localctx = new ImpliesContext(new SlExprContext(_parentctx, _parentState));
						((ImpliesContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_slExpr);
						setState(46);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(47);
						_la = _input.LA(1);
						if ( !(_la==T__16 || _la==T__17) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(48);
						((ImpliesContext)_localctx).right = slExpr(7);
						}
						break;
					}
					} 
				}
				setState(53);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class AtomExprContext extends ParserRuleContext {
		public TerminalNode ATOM() { return getToken(StrategyLogicParser.ATOM, 0); }
		public AtomExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atomExpr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).enterAtomExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof StrategyLogicListener ) ((StrategyLogicListener)listener).exitAtomExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof StrategyLogicVisitor ) return ((StrategyLogicVisitor<? extends T>)visitor).visitAtomExpr(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AtomExprContext atomExpr() throws RecognitionException {
		AtomExprContext _localctx = new AtomExprContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_atomExpr);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(54);
			match(ATOM);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 0:
			return slExpr_sempred((SlExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean slExpr_sempred(SlExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 10);
		case 1:
			return precpred(_ctx, 9);
		case 2:
			return precpred(_ctx, 8);
		case 3:
			return precpred(_ctx, 7);
		case 4:
			return precpred(_ctx, 6);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u001b9\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0003\u0000!\b\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0005\u00002\b\u0000\n\u0000\f\u00005\t"+
		"\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0000\u0001\u0000\u0002\u0000"+
		"\u0002\u0000\t\u0001\u0000\u0001\u0002\u0001\u0000\u0003\u0004\u0001\u0000"+
		"\u0005\u0006\u0001\u0000\u0007\b\u0001\u0000\t\n\u0001\u0000\u000b\f\u0001"+
		"\u0000\r\u000e\u0001\u0000\u000f\u0010\u0001\u0000\u0011\u0012C\u0000"+
		" \u0001\u0000\u0000\u0000\u00026\u0001\u0000\u0000\u0000\u0004\u0005\u0006"+
		"\u0000\uffff\uffff\u0000\u0005\u0006\u0007\u0000\u0000\u0000\u0006!\u0003"+
		"\u0000\u0000\u000e\u0007\b\u0007\u0001\u0000\u0000\b!\u0003\u0000\u0000"+
		"\r\t\n\u0007\u0002\u0000\u0000\n!\u0003\u0000\u0000\f\u000b\f\u0007\u0003"+
		"\u0000\u0000\f!\u0003\u0000\u0000\u000b\r\u000e\u0005\u0013\u0000\u0000"+
		"\u000e\u000f\u0005\u001a\u0000\u0000\u000f\u0010\u0005\u0014\u0000\u0000"+
		"\u0010!\u0003\u0000\u0000\u0005\u0011\u0012\u0005\u0015\u0000\u0000\u0012"+
		"\u0013\u0005\u001a\u0000\u0000\u0013\u0014\u0005\u0016\u0000\u0000\u0014"+
		"!\u0003\u0000\u0000\u0004\u0015\u0016\u0005\u0017\u0000\u0000\u0016\u0017"+
		"\u0005\u001a\u0000\u0000\u0017\u0018\u0005\u0018\u0000\u0000\u0018\u0019"+
		"\u0005\u001a\u0000\u0000\u0019\u001a\u0005\u0019\u0000\u0000\u001a!\u0003"+
		"\u0000\u0000\u0003\u001b\u001c\u0005\u0017\u0000\u0000\u001c\u001d\u0003"+
		"\u0000\u0000\u0000\u001d\u001e\u0005\u0019\u0000\u0000\u001e!\u0001\u0000"+
		"\u0000\u0000\u001f!\u0003\u0002\u0001\u0000 \u0004\u0001\u0000\u0000\u0000"+
		" \u0007\u0001\u0000\u0000\u0000 \t\u0001\u0000\u0000\u0000 \u000b\u0001"+
		"\u0000\u0000\u0000 \r\u0001\u0000\u0000\u0000 \u0011\u0001\u0000\u0000"+
		"\u0000 \u0015\u0001\u0000\u0000\u0000 \u001b\u0001\u0000\u0000\u0000 "+
		"\u001f\u0001\u0000\u0000\u0000!3\u0001\u0000\u0000\u0000\"#\n\n\u0000"+
		"\u0000#$\u0007\u0004\u0000\u0000$2\u0003\u0000\u0000\u000b%&\n\t\u0000"+
		"\u0000&\'\u0007\u0005\u0000\u0000\'2\u0003\u0000\u0000\n()\n\b\u0000\u0000"+
		")*\u0007\u0006\u0000\u0000*2\u0003\u0000\u0000\t+,\n\u0007\u0000\u0000"+
		",-\u0007\u0007\u0000\u0000-2\u0003\u0000\u0000\b./\n\u0006\u0000\u0000"+
		"/0\u0007\b\u0000\u000002\u0003\u0000\u0000\u00071\"\u0001\u0000\u0000"+
		"\u00001%\u0001\u0000\u0000\u00001(\u0001\u0000\u0000\u00001+\u0001\u0000"+
		"\u0000\u00001.\u0001\u0000\u0000\u000025\u0001\u0000\u0000\u000031\u0001"+
		"\u0000\u0000\u000034\u0001\u0000\u0000\u00004\u0001\u0001\u0000\u0000"+
		"\u000053\u0001\u0000\u0000\u000067\u0005\u001a\u0000\u00007\u0003\u0001"+
		"\u0000\u0000\u0000\u0003 13";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}