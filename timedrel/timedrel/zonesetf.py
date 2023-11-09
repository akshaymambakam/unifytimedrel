import timedrel.ext_float as ext

class zoneset(object):
    """docstring for zoneset"""
    def __init__(self, data=None):
        super(zoneset, self).__init__()
        if data == None:
            self.container = ext.zone_set()
        else:
            self.container = data

    def __iter__(self):
        return iter(self.container)

    def __and__(self, other):
        return zoneset.intersection(self, other)

    def __or__(self, other):
        return zoneset.union(self, other)

    def __invert__(self, other):
        return zoneset.complementation(self)

    def __nonzero__(self):
        return not zoneset.empty(self)

    def __ge__(self, other):
        return zoneset.includes(self, other)

    def __le__(self, other):
        return zoneset.includes(other, self)

    def __eq__(self, other):
        return zoneset.includes(self, other) and zoneset.includes(other, self)

    def add(self, bmin, bmax, emin, emax, dmin, dmax):
        self.container.add(ext.zone.make(ext.geq(bmin), ext.lt(bmax),ext.gt(emin), ext.leq(emax), ext.gt(dmin), ext.leq(dmax)))

    def union(self, other):
        return zoneset.union(self, other)

    def intersect(self, other):
        return zoneset.intersection(self, other)

    def restrict(self, lower, upper):
        return zoneset.duration_restriction(self, lower, upper)

    def concatenate(self, other):
        return zoneset.concatenation(self, other)

    def iterate(self):
        return zoneset.transitive_closure(self)

    def empty(self):
        return self.container.empty()

    @classmethod
    def from_periods(cls, periods, anchor=None):

        zset = zoneset()

        if anchor == None:
            func = zset.container.add_from_period
        elif anchor == "rise":
            func = zset.container.add_from_period_rise_anchor
        elif anchor == "fall":
            func = zset.container.add_from_period_fall_anchor
        elif anchor == "both":
            func = zset.container.add_from_period_both_anchor
        elif anchor == "none":
            func = zset.container.add_from_period_both_anchor
        else:
            raise Exception(r"Unknown anchor: Options are {none, rise, fall, both}")

        for (begin, end) in periods:
            func(begin, end)

        return zset

    @classmethod
    def from_dataframe(cls, df, predicate, anchor=None):
        def collect(df, predicate):
            def _collect(df, predicate):
                value = False
                for row in df.itertuples():
                    if predicate(row) != value:
                        value = not value
                        yield(row.Index)

                if value:
                    yield(df.iloc[-1].Index)

            value = False
            begin = end = None
            for ts in _collect(df, predicate):
                if value:
                    end = ts
                    yield (begin, end)          
                else:
                    begin = ts 
                value = not value

        return cls.from_periods(collect(df, predicate), anchor)



    @classmethod
    def union(cls, first, *others):
        result = first.container
        for other in others:
            result = ext.union(result, other.container)

        return zoneset(result)

    @classmethod
    def intersection(cls, first, *others):
        result = first.container
        for other in others:
            result = ext.intersection(result, other.container)

        return zoneset(result)

    @classmethod
    def duration_restriction(cls, zset, lower, upper):
        return zoneset(ext.duration_restriction(zset.container, lower, upper))

    @classmethod
    def complementation(cls, zset):
        return zoneset(ext.complementation(zset.container))

    @classmethod
    def set_difference(cls, first, second):
        return zoneset(ext.set_difference(first.container, second.container))

    @classmethod
    def concatenation(cls, first, *others):
        result = first.container
        for other in others:
            result = ext.concatenation(result, other.container)

        return zoneset(result)

    @classmethod
    def transitive_closure(cls, zset):
        return zoneset(ext.transitive_closure(zset.container))

    @classmethod
    def modal_diamond(cls, zset, relation, lower, upper):
        if relation == "meets" or relation == "A":
            return zoneset(ext.diamond_meets(zset.container, lower, upper))
        elif relation == "met_by" or relation == "Ai":
            return zoneset(ext.diamond_met_by(zset.container, lower, upper))
        elif relation == "starts" or relation == "B":
            return zoneset(ext.diamond_starts(zset.container, lower, upper))
        elif relation == "started_by" or relation == "Bi":
            return zoneset(ext.diamond_started_by(zset.container, lower, upper))
        elif relation == "finishes" or relation == "E":
            return zoneset(ext.diamond_finishes(zset.container, lower, upper))
        elif relation == "finished_by" or relation == "Ei":
            return zoneset(ext.diamond_finished_by(zset.container, lower, upper))
        else:
            raise ValueError("Unknown relation")

    @classmethod
    def modal_box(cls, zset, relation, lower, upper):
        if relation == "meets" or relation == "A":
            return zoneset(ext.box_meets(zset.container, lower, upper))
        elif relation == "met_by" or relation == "Ai":
            return zoneset(ext.box_met_by(zset.container, lower, upper))
        elif relation == "starts" or relation == "B":
            return zoneset(ext.box_starts(zset.container, lower, upper))
        elif relation == "started_by" or relation == "Bi":
            return zoneset(ext.box_started_by(zset.container, lower, upper))
        elif relation == "finishes" or relation == "E":
            return zoneset(ext.box_finishes(zset.container, lower, upper))
        elif relation == "finished_by" or relation == "Ei":
            return zoneset(ext.box_finished_by(zset.container, lower, upper))
        else:
            raise ValueError("Unknown relation")
        
    def __str__(self):
        return "\n".join([str(zone) for zone in self.container])

