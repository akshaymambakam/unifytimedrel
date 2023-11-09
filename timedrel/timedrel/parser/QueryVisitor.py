# Generated from Query.g4 by ANTLR 4.7.1
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .QueryParser import QueryParser
else:
    from QueryParser import QueryParser

# This class defines a complete generic visitor for a parse tree produced by QueryParser.

class QueryVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by QueryParser#Intersection.
    def visitIntersection(self, ctx:QueryParser.IntersectionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#RiseAtomic.
    def visitRiseAtomic(self, ctx:QueryParser.RiseAtomicContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#FallAtomic.
    def visitFallAtomic(self, ctx:QueryParser.FallAtomicContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#True.
    def visitTrue(self, ctx:QueryParser.TrueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Atomic.
    def visitAtomic(self, ctx:QueryParser.AtomicContext):
        return self.visitChildren(ctx)


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
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Union.
    def visitUnion(self, ctx:QueryParser.UnionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Restriction.
    def visitRestriction(self, ctx:QueryParser.RestrictionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Concatenation.
    def visitConcatenation(self, ctx:QueryParser.ConcatenationContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Star.
    def visitStar(self, ctx:QueryParser.StarContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#DualAtomic.
    def visitDualAtomic(self, ctx:QueryParser.DualAtomicContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Complementation.
    def visitComplementation(self, ctx:QueryParser.ComplementationContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Question.
    def visitQuestion(self, ctx:QueryParser.QuestionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#Plus.
    def visitPlus(self, ctx:QueryParser.PlusContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by QueryParser#idlist.
    def visitIdlist(self, ctx:QueryParser.IdlistContext):
        return self.visitChildren(ctx)



del QueryParser