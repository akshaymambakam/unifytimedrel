# Generated from Query.g4 by ANTLR 4.7.1
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .QueryParser import QueryParser
else:
    from QueryParser import QueryParser

# This class defines a complete listener for a parse tree produced by QueryParser.
class QueryListener(ParseTreeListener):

    # Enter a parse tree produced by QueryParser#Intersection.
    def enterIntersection(self, ctx:QueryParser.IntersectionContext):
        pass

    # Exit a parse tree produced by QueryParser#Intersection.
    def exitIntersection(self, ctx:QueryParser.IntersectionContext):
        pass


    # Enter a parse tree produced by QueryParser#RiseAtomic.
    def enterRiseAtomic(self, ctx:QueryParser.RiseAtomicContext):
        pass

    # Exit a parse tree produced by QueryParser#RiseAtomic.
    def exitRiseAtomic(self, ctx:QueryParser.RiseAtomicContext):
        pass


    # Enter a parse tree produced by QueryParser#FallAtomic.
    def enterFallAtomic(self, ctx:QueryParser.FallAtomicContext):
        pass

    # Exit a parse tree produced by QueryParser#FallAtomic.
    def exitFallAtomic(self, ctx:QueryParser.FallAtomicContext):
        pass


    # Enter a parse tree produced by QueryParser#True.
    def enterTrue(self, ctx:QueryParser.TrueContext):
        pass

    # Exit a parse tree produced by QueryParser#True.
    def exitTrue(self, ctx:QueryParser.TrueContext):
        pass


    # Enter a parse tree produced by QueryParser#Atomic.
    def enterAtomic(self, ctx:QueryParser.AtomicContext):
        pass

    # Exit a parse tree produced by QueryParser#Atomic.
    def exitAtomic(self, ctx:QueryParser.AtomicContext):
        pass


    # Enter a parse tree produced by QueryParser#Diamond.
    def enterDiamond(self, ctx:QueryParser.DiamondContext):
        pass

    # Exit a parse tree produced by QueryParser#Diamond.
    def exitDiamond(self, ctx:QueryParser.DiamondContext):
        pass


    # Enter a parse tree produced by QueryParser#Box.
    def enterBox(self, ctx:QueryParser.BoxContext):
        pass

    # Exit a parse tree produced by QueryParser#Box.
    def exitBox(self, ctx:QueryParser.BoxContext):
        pass


    # Enter a parse tree produced by QueryParser#Grouping.
    def enterGrouping(self, ctx:QueryParser.GroupingContext):
        pass

    # Exit a parse tree produced by QueryParser#Grouping.
    def exitGrouping(self, ctx:QueryParser.GroupingContext):
        pass


    # Enter a parse tree produced by QueryParser#Difference.
    def enterDifference(self, ctx:QueryParser.DifferenceContext):
        pass

    # Exit a parse tree produced by QueryParser#Difference.
    def exitDifference(self, ctx:QueryParser.DifferenceContext):
        pass


    # Enter a parse tree produced by QueryParser#Union.
    def enterUnion(self, ctx:QueryParser.UnionContext):
        pass

    # Exit a parse tree produced by QueryParser#Union.
    def exitUnion(self, ctx:QueryParser.UnionContext):
        pass


    # Enter a parse tree produced by QueryParser#Restriction.
    def enterRestriction(self, ctx:QueryParser.RestrictionContext):
        pass

    # Exit a parse tree produced by QueryParser#Restriction.
    def exitRestriction(self, ctx:QueryParser.RestrictionContext):
        pass


    # Enter a parse tree produced by QueryParser#Concatenation.
    def enterConcatenation(self, ctx:QueryParser.ConcatenationContext):
        pass

    # Exit a parse tree produced by QueryParser#Concatenation.
    def exitConcatenation(self, ctx:QueryParser.ConcatenationContext):
        pass


    # Enter a parse tree produced by QueryParser#Star.
    def enterStar(self, ctx:QueryParser.StarContext):
        pass

    # Exit a parse tree produced by QueryParser#Star.
    def exitStar(self, ctx:QueryParser.StarContext):
        pass


    # Enter a parse tree produced by QueryParser#DualAtomic.
    def enterDualAtomic(self, ctx:QueryParser.DualAtomicContext):
        pass

    # Exit a parse tree produced by QueryParser#DualAtomic.
    def exitDualAtomic(self, ctx:QueryParser.DualAtomicContext):
        pass


    # Enter a parse tree produced by QueryParser#Complementation.
    def enterComplementation(self, ctx:QueryParser.ComplementationContext):
        pass

    # Exit a parse tree produced by QueryParser#Complementation.
    def exitComplementation(self, ctx:QueryParser.ComplementationContext):
        pass


    # Enter a parse tree produced by QueryParser#Question.
    def enterQuestion(self, ctx:QueryParser.QuestionContext):
        pass

    # Exit a parse tree produced by QueryParser#Question.
    def exitQuestion(self, ctx:QueryParser.QuestionContext):
        pass


    # Enter a parse tree produced by QueryParser#Plus.
    def enterPlus(self, ctx:QueryParser.PlusContext):
        pass

    # Exit a parse tree produced by QueryParser#Plus.
    def exitPlus(self, ctx:QueryParser.PlusContext):
        pass


    # Enter a parse tree produced by QueryParser#idlist.
    def enterIdlist(self, ctx:QueryParser.IdlistContext):
        pass

    # Exit a parse tree produced by QueryParser#idlist.
    def exitIdlist(self, ctx:QueryParser.IdlistContext):
        pass


