from antlr4 import *

from timedrel.parser.QueryLexer import QueryLexer
from timedrel.parser.QueryParser import QueryParser
from timedrel.parser.QueryVisitor import QueryVisitor

# import intervals
from timedrel import zoneset, zonesetf

def eval(df, expr, timescale=1, projection=None, dtype="int", **kwargs):

    lexer = QueryLexer(InputStream(expr))
    stream = CommonTokenStream(lexer)
    parser = QueryParser(stream)
    tree = parser.expr()

    kwargs['timescale'] = timescale

    evaluator = QueryEvaluator(df, dtype, **kwargs)
    zones = evaluator.visit(tree)


    if projection == None:
        result = zones
    elif projection == 'span':
        result = [(z.bmin().value/timescale, z.emax().value/timescale) for z in zones]

    return result



class QueryEvaluator(QueryVisitor):

    def __init__(self, df, dtype="int", **kwargs):
        self.df = df
        self.kwargs = kwargs

        if dtype == "int":
            self.dtype = int
            self.zoneset = zoneset
        elif dtype == "float":
            self.dtype = float
            self.zoneset = zonesetf

    # Visit a parse tree produced by QueryParser#Intersection.
    def visitIntersection(self, ctx:QueryParser.IntersectionContext):
        left = self.visit(ctx.left)
        right = self.visit(ctx.right)
        return self.zoneset.intersection(left, right)


    # Visit a parse tree produced by QueryParser#True.
    def visitTrue(self, ctx:QueryParser.TrueContext):
        return self.zoneset.true()


    # Visit a parse tree produced by QueryParser#Atomic.
    def visitAtomic(self, ctx:QueryParser.AtomicContext):
        name = ctx.name.text
        periods = self.collect(self.df, self.kwargs[name])
        return self.zoneset.from_periods(periods)

    # Visit a parse tree produced by QueryParser#NegAtomic.
    def visitRiseAtomic(self, ctx:QueryParser.RiseAtomicContext):
        name = ctx.name.text
        periods = self.collect(self.df, self.kwargs[name])
        return self.zoneset.from_periods(periods, anchor='rise')

    # Visit a parse tree produced by QueryParser#NegAtomic.
    def visitFallAtomic(self, ctx:QueryParser.FallAtomicContext):
        name = ctx.name.text
        periods = self.collect(self.df, self.kwargs[name])
        return self.zoneset.from_periods(periods, anchor='fall')

    # Visit a parse tree produced by QueryParser#NegAtomic.
    def visitDualAtomic(self, ctx:QueryParser.DualAtomicContext):
        name = ctx.name.text
        periods = self.collect(self.df, self.kwargs[name])
        return self.zoneset.from_periods(periods, anchor='both')

    # Visit a parse tree produced by QueryParser#Diamond.
    def visitDiamond(self, ctx:QueryParser.DiamondContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Box.
    def visitBox(self, ctx:QueryParser.BoxContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Grouping.
    def visitGrouping(self, ctx:QueryParser.GroupingContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Difference.
    def visitDifference(self, ctx:QueryParser.DifferenceContext):
        left = self.visit(ctx.left)
        right = self.visit(ctx.right)
        return self.zoneset.difference(left, right)


    # Visit a parse tree produced by QueryParser#Union.
    def visitUnion(self, ctx:QueryParser.UnionContext):
        left = self.visit(ctx.left)
        right = self.visit(ctx.right)
        return self.zoneset.union(left, right)

    # Visit a parse tree produced by QueryParser#Restriction.
    def visitRestriction(self, ctx:QueryParser.RestrictionContext):
        child = self.visit(ctx.child)
        
        lbound = self.dtype(ctx.l.text) * self.kwargs['timescale']
        ubound = self.dtype(ctx.u.text) * self.kwargs['timescale']

        return self.zoneset.duration_restriction(child, lbound, ubound)


    # Visit a parse tree produced by QueryParser#Concatenation.
    def visitConcatenation(self, ctx:QueryParser.ConcatenationContext):
        left = self.visit(ctx.left)
        right = self.visit(ctx.right)
        return self.zoneset.concatenation(left, right)

    # Visit a parse tree produced by QueryParser#Star.
    def visitStar(self, ctx:QueryParser.StarContext):
        return self.zoneset.transitive_closure(child)

    # Visit a parse tree produced by QueryParser#Complementation.
    def visitComplementation(self, ctx:QueryParser.ComplementationContext):
        child = self.visit(ctx.left)
        return self.zoneset.complementation(child)

    # Visit a parse tree produced by QueryParser#Question.
    def visitQuestion(self, ctx:QueryParser.QuestionContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by QueryParser#Plus.
    def visitPlus(self, ctx:QueryParser.PlusContext):
        return self.zoneset.transitive_closure(child)

    # Visit a parse tree produced by QueryParser#Plus.
    def visitDiamond(self, ctx:QueryParser.DiamondContext):
        relation = ctx.relation.text
        lbound = self.dtype(ctx.l.text) * self.kwargs['timescale']
        ubound = self.dtype(ctx.u.text) * self.kwargs['timescale']

        return self.zoneset.modal_diamond(child, relation, lbound, ubound)

    def visitBox(self, ctx:QueryParser.BoxContext):
        relation = ctx.relation.text
        lbound = self.dtype(ctx.l.text) * self.kwargs['timescale']
        ubound = self.dtype(ctx.u.text) * self.kwargs['timescale']

        return self.zoneset.modal_box(child, relation, lbound, ubound)

    def collect(self, df, predicate):

        def _collect(df, predicate):
            value = False
            prev = None
            for row in df.itertuples():
                prev = row
                if predicate(row) != value:
                    value = not value
                    yield(int(row.Index))

            if value:
                yield(int(prev.Index))

        value = False
        begin = end = None
        for ts in _collect(df, predicate):
            if value:
                end = ts
                yield (begin, end)          
            else:
                begin = ts 
            value = not value



