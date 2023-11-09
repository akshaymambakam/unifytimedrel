# Generated from Query.g4 by ANTLR 4.7.1
# encoding: utf-8
from antlr4 import *
from io import StringIO
from typing.io import TextIO
import sys

def serializedATN():
    with StringIO() as buf:
        buf.write("\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\35")
        buf.write("P\4\2\t\2\4\3\t\3\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2")
        buf.write("\3\2\3\2\3\2\3\2\3\2\3\2\5\2\26\n\2\3\2\3\2\3\2\3\2\3")
        buf.write("\2\5\2\35\n\2\3\2\3\2\3\2\3\2\3\2\3\2\5\2%\n\2\3\2\3\2")
        buf.write("\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3")
        buf.write("\2\3\2\3\2\3\2\3\2\3\2\5\2<\n\2\3\2\3\2\5\2@\n\2\3\2\7")
        buf.write("\2C\n\2\f\2\16\2F\13\2\3\3\3\3\3\3\7\3K\n\3\f\3\16\3N")
        buf.write("\13\3\3\3\2\3\2\4\2\4\2\3\3\2\22\24\2b\2$\3\2\2\2\4G\3")
        buf.write("\2\2\2\6\7\b\2\1\2\7%\7\3\2\2\b\t\7\4\2\2\t\n\7\32\2\2")
        buf.write("\n%\7\5\2\2\13\f\7\4\2\2\f%\7\32\2\2\r\16\7\32\2\2\16")
        buf.write("%\7\5\2\2\17%\7\32\2\2\20\21\7\t\2\2\21%\5\2\2\13\22\23")
        buf.write("\7\21\2\2\23\25\t\2\2\2\24\26\7\25\2\2\25\24\3\2\2\2\25")
        buf.write("\26\3\2\2\2\26\27\3\2\2\2\27\30\7\26\2\2\30%\5\2\2\5\31")
        buf.write("\32\7\n\2\2\32\34\t\2\2\2\33\35\7\25\2\2\34\33\3\2\2\2")
        buf.write("\34\35\3\2\2\2\35\36\3\2\2\2\36\37\7\f\2\2\37%\5\2\2\4")
        buf.write(" !\7\27\2\2!\"\5\2\2\2\"#\7\30\2\2#%\3\2\2\2$\6\3\2\2")
        buf.write("\2$\b\3\2\2\2$\13\3\2\2\2$\r\3\2\2\2$\17\3\2\2\2$\20\3")
        buf.write("\2\2\2$\22\3\2\2\2$\31\3\2\2\2$ \3\2\2\2%D\3\2\2\2&\'")
        buf.write("\f\t\2\2\'(\7\r\2\2(C\5\2\2\n)*\f\b\2\2*+\7\16\2\2+C\5")
        buf.write("\2\2\t,-\f\7\2\2-.\7\17\2\2.C\5\2\2\b/\60\f\6\2\2\60\61")
        buf.write("\7\20\2\2\61C\5\2\2\7\62\63\f\16\2\2\63C\7\6\2\2\64\65")
        buf.write("\f\r\2\2\65C\7\7\2\2\66\67\f\f\2\2\67C\7\b\2\289\f\n\2")
        buf.write("\29;\7\n\2\2:<\7\34\2\2;:\3\2\2\2;<\3\2\2\2<=\3\2\2\2")
        buf.write("=?\7\13\2\2>@\7\34\2\2?>\3\2\2\2?@\3\2\2\2@A\3\2\2\2A")
        buf.write("C\7\f\2\2B&\3\2\2\2B)\3\2\2\2B,\3\2\2\2B/\3\2\2\2B\62")
        buf.write("\3\2\2\2B\64\3\2\2\2B\66\3\2\2\2B8\3\2\2\2CF\3\2\2\2D")
        buf.write("B\3\2\2\2DE\3\2\2\2E\3\3\2\2\2FD\3\2\2\2GL\7\32\2\2HI")
        buf.write("\7\31\2\2IK\7\32\2\2JH\3\2\2\2KN\3\2\2\2LJ\3\2\2\2LM\3")
        buf.write("\2\2\2M\5\3\2\2\2NL\3\2\2\2\n\25\34$;?BDL")
        return buf.getvalue()


class QueryParser ( Parser ):

    grammarFileName = "Query.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "'True'", "'<:'", "':>'", "'*'", "'+'", 
                     "'?'", "'~'", "'['", "':'", "']'", "';'", "'|'", "'&'", 
                     "'/'", "'<'", "'A'", "'B'", "'E'", "'i'", "'>'", "'('", 
                     "')'", "','" ]

    symbolicNames = [ "<INVALID>", "<INVALID>", "<INVALID>", "<INVALID>", 
                      "<INVALID>", "<INVALID>", "<INVALID>", "<INVALID>", 
                      "<INVALID>", "<INVALID>", "<INVALID>", "<INVALID>", 
                      "<INVALID>", "<INVALID>", "<INVALID>", "<INVALID>", 
                      "<INVALID>", "<INVALID>", "<INVALID>", "<INVALID>", 
                      "<INVALID>", "<INVALID>", "<INVALID>", "<INVALID>", 
                      "IDENTIFIER", "LETTER", "NUMBER", "WS" ]

    RULE_expr = 0
    RULE_idlist = 1

    ruleNames =  [ "expr", "idlist" ]

    EOF = Token.EOF
    T__0=1
    T__1=2
    T__2=3
    T__3=4
    T__4=5
    T__5=6
    T__6=7
    T__7=8
    T__8=9
    T__9=10
    T__10=11
    T__11=12
    T__12=13
    T__13=14
    T__14=15
    T__15=16
    T__16=17
    T__17=18
    T__18=19
    T__19=20
    T__20=21
    T__21=22
    T__22=23
    IDENTIFIER=24
    LETTER=25
    NUMBER=26
    WS=27

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.7.1")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None



    class ExprContext(ParserRuleContext):

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser


        def getRuleIndex(self):
            return QueryParser.RULE_expr

     
        def copyFrom(self, ctx:ParserRuleContext):
            super().copyFrom(ctx)


    class IntersectionContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.left = None # ExprContext
            self.right = None # ExprContext
            self.copyFrom(ctx)

        def expr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(QueryParser.ExprContext)
            else:
                return self.getTypedRuleContext(QueryParser.ExprContext,i)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterIntersection" ):
                listener.enterIntersection(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitIntersection" ):
                listener.exitIntersection(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitIntersection" ):
                return visitor.visitIntersection(self)
            else:
                return visitor.visitChildren(self)


    class RiseAtomicContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.name = None # Token
            self.copyFrom(ctx)

        def IDENTIFIER(self):
            return self.getToken(QueryParser.IDENTIFIER, 0)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterRiseAtomic" ):
                listener.enterRiseAtomic(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitRiseAtomic" ):
                listener.exitRiseAtomic(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitRiseAtomic" ):
                return visitor.visitRiseAtomic(self)
            else:
                return visitor.visitChildren(self)


    class FallAtomicContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.name = None # Token
            self.copyFrom(ctx)

        def IDENTIFIER(self):
            return self.getToken(QueryParser.IDENTIFIER, 0)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterFallAtomic" ):
                listener.enterFallAtomic(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitFallAtomic" ):
                listener.exitFallAtomic(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitFallAtomic" ):
                return visitor.visitFallAtomic(self)
            else:
                return visitor.visitChildren(self)


    class TrueContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.copyFrom(ctx)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterTrue" ):
                listener.enterTrue(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitTrue" ):
                listener.exitTrue(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitTrue" ):
                return visitor.visitTrue(self)
            else:
                return visitor.visitChildren(self)


    class AtomicContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.name = None # Token
            self.copyFrom(ctx)

        def IDENTIFIER(self):
            return self.getToken(QueryParser.IDENTIFIER, 0)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterAtomic" ):
                listener.enterAtomic(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitAtomic" ):
                listener.exitAtomic(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitAtomic" ):
                return visitor.visitAtomic(self)
            else:
                return visitor.visitChildren(self)


    class DiamondContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.relation = None # Token
            self.inverse = None # Token
            self.child = None # ExprContext
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(QueryParser.ExprContext,0)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterDiamond" ):
                listener.enterDiamond(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitDiamond" ):
                listener.exitDiamond(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitDiamond" ):
                return visitor.visitDiamond(self)
            else:
                return visitor.visitChildren(self)


    class BoxContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.relation = None # Token
            self.inverse = None # Token
            self.child = None # ExprContext
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(QueryParser.ExprContext,0)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterBox" ):
                listener.enterBox(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitBox" ):
                listener.exitBox(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitBox" ):
                return visitor.visitBox(self)
            else:
                return visitor.visitChildren(self)


    class GroupingContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.child = None # ExprContext
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(QueryParser.ExprContext,0)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterGrouping" ):
                listener.enterGrouping(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitGrouping" ):
                listener.exitGrouping(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitGrouping" ):
                return visitor.visitGrouping(self)
            else:
                return visitor.visitChildren(self)


    class DifferenceContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.left = None # ExprContext
            self.right = None # ExprContext
            self.copyFrom(ctx)

        def expr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(QueryParser.ExprContext)
            else:
                return self.getTypedRuleContext(QueryParser.ExprContext,i)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterDifference" ):
                listener.enterDifference(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitDifference" ):
                listener.exitDifference(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitDifference" ):
                return visitor.visitDifference(self)
            else:
                return visitor.visitChildren(self)


    class UnionContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.left = None # ExprContext
            self.right = None # ExprContext
            self.copyFrom(ctx)

        def expr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(QueryParser.ExprContext)
            else:
                return self.getTypedRuleContext(QueryParser.ExprContext,i)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterUnion" ):
                listener.enterUnion(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitUnion" ):
                listener.exitUnion(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitUnion" ):
                return visitor.visitUnion(self)
            else:
                return visitor.visitChildren(self)


    class RestrictionContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.child = None # ExprContext
            self.l = None # Token
            self.u = None # Token
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(QueryParser.ExprContext,0)

        def NUMBER(self, i:int=None):
            if i is None:
                return self.getTokens(QueryParser.NUMBER)
            else:
                return self.getToken(QueryParser.NUMBER, i)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterRestriction" ):
                listener.enterRestriction(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitRestriction" ):
                listener.exitRestriction(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitRestriction" ):
                return visitor.visitRestriction(self)
            else:
                return visitor.visitChildren(self)


    class ConcatenationContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.left = None # ExprContext
            self.right = None # ExprContext
            self.copyFrom(ctx)

        def expr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(QueryParser.ExprContext)
            else:
                return self.getTypedRuleContext(QueryParser.ExprContext,i)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterConcatenation" ):
                listener.enterConcatenation(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitConcatenation" ):
                listener.exitConcatenation(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitConcatenation" ):
                return visitor.visitConcatenation(self)
            else:
                return visitor.visitChildren(self)


    class StarContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.child = None # ExprContext
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(QueryParser.ExprContext,0)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterStar" ):
                listener.enterStar(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitStar" ):
                listener.exitStar(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitStar" ):
                return visitor.visitStar(self)
            else:
                return visitor.visitChildren(self)


    class DualAtomicContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.name = None # Token
            self.copyFrom(ctx)

        def IDENTIFIER(self):
            return self.getToken(QueryParser.IDENTIFIER, 0)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterDualAtomic" ):
                listener.enterDualAtomic(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitDualAtomic" ):
                listener.exitDualAtomic(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitDualAtomic" ):
                return visitor.visitDualAtomic(self)
            else:
                return visitor.visitChildren(self)


    class ComplementationContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.child = None # ExprContext
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(QueryParser.ExprContext,0)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterComplementation" ):
                listener.enterComplementation(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitComplementation" ):
                listener.exitComplementation(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitComplementation" ):
                return visitor.visitComplementation(self)
            else:
                return visitor.visitChildren(self)


    class QuestionContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.child = None # ExprContext
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(QueryParser.ExprContext,0)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterQuestion" ):
                listener.enterQuestion(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitQuestion" ):
                listener.exitQuestion(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitQuestion" ):
                return visitor.visitQuestion(self)
            else:
                return visitor.visitChildren(self)


    class PlusContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a QueryParser.ExprContext
            super().__init__(parser)
            self.child = None # ExprContext
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(QueryParser.ExprContext,0)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterPlus" ):
                listener.enterPlus(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitPlus" ):
                listener.exitPlus(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitPlus" ):
                return visitor.visitPlus(self)
            else:
                return visitor.visitChildren(self)



    def expr(self, _p:int=0):
        _parentctx = self._ctx
        _parentState = self.state
        localctx = QueryParser.ExprContext(self, self._ctx, _parentState)
        _prevctx = localctx
        _startState = 0
        self.enterRecursionRule(localctx, 0, self.RULE_expr, _p)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 34
            self._errHandler.sync(self)
            la_ = self._interp.adaptivePredict(self._input,2,self._ctx)
            if la_ == 1:
                localctx = QueryParser.TrueContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx

                self.state = 5
                self.match(QueryParser.T__0)
                pass

            elif la_ == 2:
                localctx = QueryParser.DualAtomicContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 6
                self.match(QueryParser.T__1)
                self.state = 7
                localctx.name = self.match(QueryParser.IDENTIFIER)
                self.state = 8
                self.match(QueryParser.T__2)
                pass

            elif la_ == 3:
                localctx = QueryParser.RiseAtomicContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 9
                self.match(QueryParser.T__1)
                self.state = 10
                localctx.name = self.match(QueryParser.IDENTIFIER)
                pass

            elif la_ == 4:
                localctx = QueryParser.FallAtomicContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 11
                localctx.name = self.match(QueryParser.IDENTIFIER)
                self.state = 12
                self.match(QueryParser.T__2)
                pass

            elif la_ == 5:
                localctx = QueryParser.AtomicContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 13
                localctx.name = self.match(QueryParser.IDENTIFIER)
                pass

            elif la_ == 6:
                localctx = QueryParser.ComplementationContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 14
                self.match(QueryParser.T__6)
                self.state = 15
                localctx.child = self.expr(9)
                pass

            elif la_ == 7:
                localctx = QueryParser.DiamondContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 16
                self.match(QueryParser.T__14)
                self.state = 17
                localctx.relation = self._input.LT(1)
                _la = self._input.LA(1)
                if not((((_la) & ~0x3f) == 0 and ((1 << _la) & ((1 << QueryParser.T__15) | (1 << QueryParser.T__16) | (1 << QueryParser.T__17))) != 0)):
                    localctx.relation = self._errHandler.recoverInline(self)
                else:
                    self._errHandler.reportMatch(self)
                    self.consume()
                self.state = 19
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if _la==QueryParser.T__18:
                    self.state = 18
                    localctx.inverse = self.match(QueryParser.T__18)


                self.state = 21
                self.match(QueryParser.T__19)
                self.state = 22
                localctx.child = self.expr(3)
                pass

            elif la_ == 8:
                localctx = QueryParser.BoxContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 23
                self.match(QueryParser.T__7)
                self.state = 24
                localctx.relation = self._input.LT(1)
                _la = self._input.LA(1)
                if not((((_la) & ~0x3f) == 0 and ((1 << _la) & ((1 << QueryParser.T__15) | (1 << QueryParser.T__16) | (1 << QueryParser.T__17))) != 0)):
                    localctx.relation = self._errHandler.recoverInline(self)
                else:
                    self._errHandler.reportMatch(self)
                    self.consume()
                self.state = 26
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if _la==QueryParser.T__18:
                    self.state = 25
                    localctx.inverse = self.match(QueryParser.T__18)


                self.state = 28
                self.match(QueryParser.T__9)
                self.state = 29
                localctx.child = self.expr(2)
                pass

            elif la_ == 9:
                localctx = QueryParser.GroupingContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 30
                self.match(QueryParser.T__20)
                self.state = 31
                localctx.child = self.expr(0)
                self.state = 32
                self.match(QueryParser.T__21)
                pass


            self._ctx.stop = self._input.LT(-1)
            self.state = 66
            self._errHandler.sync(self)
            _alt = self._interp.adaptivePredict(self._input,6,self._ctx)
            while _alt!=2 and _alt!=ATN.INVALID_ALT_NUMBER:
                if _alt==1:
                    if self._parseListeners is not None:
                        self.triggerExitRuleEvent()
                    _prevctx = localctx
                    self.state = 64
                    self._errHandler.sync(self)
                    la_ = self._interp.adaptivePredict(self._input,5,self._ctx)
                    if la_ == 1:
                        localctx = QueryParser.ConcatenationContext(self, QueryParser.ExprContext(self, _parentctx, _parentState))
                        localctx.left = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 36
                        if not self.precpred(self._ctx, 7):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 7)")
                        self.state = 37
                        self.match(QueryParser.T__10)
                        self.state = 38
                        localctx.right = self.expr(8)
                        pass

                    elif la_ == 2:
                        localctx = QueryParser.UnionContext(self, QueryParser.ExprContext(self, _parentctx, _parentState))
                        localctx.left = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 39
                        if not self.precpred(self._ctx, 6):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 6)")
                        self.state = 40
                        self.match(QueryParser.T__11)
                        self.state = 41
                        localctx.right = self.expr(7)
                        pass

                    elif la_ == 3:
                        localctx = QueryParser.IntersectionContext(self, QueryParser.ExprContext(self, _parentctx, _parentState))
                        localctx.left = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 42
                        if not self.precpred(self._ctx, 5):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 5)")
                        self.state = 43
                        self.match(QueryParser.T__12)
                        self.state = 44
                        localctx.right = self.expr(6)
                        pass

                    elif la_ == 4:
                        localctx = QueryParser.DifferenceContext(self, QueryParser.ExprContext(self, _parentctx, _parentState))
                        localctx.left = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 45
                        if not self.precpred(self._ctx, 4):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 4)")
                        self.state = 46
                        self.match(QueryParser.T__13)
                        self.state = 47
                        localctx.right = self.expr(5)
                        pass

                    elif la_ == 5:
                        localctx = QueryParser.StarContext(self, QueryParser.ExprContext(self, _parentctx, _parentState))
                        localctx.child = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 48
                        if not self.precpred(self._ctx, 12):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 12)")
                        self.state = 49
                        self.match(QueryParser.T__3)
                        pass

                    elif la_ == 6:
                        localctx = QueryParser.PlusContext(self, QueryParser.ExprContext(self, _parentctx, _parentState))
                        localctx.child = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 50
                        if not self.precpred(self._ctx, 11):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 11)")
                        self.state = 51
                        self.match(QueryParser.T__4)
                        pass

                    elif la_ == 7:
                        localctx = QueryParser.QuestionContext(self, QueryParser.ExprContext(self, _parentctx, _parentState))
                        localctx.child = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 52
                        if not self.precpred(self._ctx, 10):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 10)")
                        self.state = 53
                        self.match(QueryParser.T__5)
                        pass

                    elif la_ == 8:
                        localctx = QueryParser.RestrictionContext(self, QueryParser.ExprContext(self, _parentctx, _parentState))
                        localctx.child = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 54
                        if not self.precpred(self._ctx, 8):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 8)")
                        self.state = 55
                        self.match(QueryParser.T__7)
                        self.state = 57
                        self._errHandler.sync(self)
                        _la = self._input.LA(1)
                        if _la==QueryParser.NUMBER:
                            self.state = 56
                            localctx.l = self.match(QueryParser.NUMBER)


                        self.state = 59
                        self.match(QueryParser.T__8)
                        self.state = 61
                        self._errHandler.sync(self)
                        _la = self._input.LA(1)
                        if _la==QueryParser.NUMBER:
                            self.state = 60
                            localctx.u = self.match(QueryParser.NUMBER)


                        self.state = 63
                        self.match(QueryParser.T__9)
                        pass

             
                self.state = 68
                self._errHandler.sync(self)
                _alt = self._interp.adaptivePredict(self._input,6,self._ctx)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.unrollRecursionContexts(_parentctx)
        return localctx

    class IdlistContext(ParserRuleContext):

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser
            self.param = None # Token

        def IDENTIFIER(self, i:int=None):
            if i is None:
                return self.getTokens(QueryParser.IDENTIFIER)
            else:
                return self.getToken(QueryParser.IDENTIFIER, i)

        def getRuleIndex(self):
            return QueryParser.RULE_idlist

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterIdlist" ):
                listener.enterIdlist(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitIdlist" ):
                listener.exitIdlist(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitIdlist" ):
                return visitor.visitIdlist(self)
            else:
                return visitor.visitChildren(self)




    def idlist(self):

        localctx = QueryParser.IdlistContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_idlist)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 69
            localctx.param = self.match(QueryParser.IDENTIFIER)
            self.state = 74
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==QueryParser.T__22:
                self.state = 70
                self.match(QueryParser.T__22)
                self.state = 71
                localctx.param = self.match(QueryParser.IDENTIFIER)
                self.state = 76
                self._errHandler.sync(self)
                _la = self._input.LA(1)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx



    def sempred(self, localctx:RuleContext, ruleIndex:int, predIndex:int):
        if self._predicates == None:
            self._predicates = dict()
        self._predicates[0] = self.expr_sempred
        pred = self._predicates.get(ruleIndex, None)
        if pred is None:
            raise Exception("No predicate with index:" + str(ruleIndex))
        else:
            return pred(localctx, predIndex)

    def expr_sempred(self, localctx:ExprContext, predIndex:int):
            if predIndex == 0:
                return self.precpred(self._ctx, 7)
         

            if predIndex == 1:
                return self.precpred(self._ctx, 6)
         

            if predIndex == 2:
                return self.precpred(self._ctx, 5)
         

            if predIndex == 3:
                return self.precpred(self._ctx, 4)
         

            if predIndex == 4:
                return self.precpred(self._ctx, 12)
         

            if predIndex == 5:
                return self.precpred(self._ctx, 11)
         

            if predIndex == 6:
                return self.precpred(self._ctx, 10)
         

            if predIndex == 7:
                return self.precpred(self._ctx, 8)
         




