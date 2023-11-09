#include <boost/icl/interval.hpp>
#include <boost/icl/interval_set.hpp>


#ifndef TIMEDREL_INTERVAL_SET_HPP
#define TIMEDREL_INTERVAL_SET_HPP 1


#include "bound.hpp"
#include "zone.hpp"
#include "zone_set.hpp"

namespace timedrel {

template<typename T, typename Container>
interval_set<T> to_intervals (const zone_set<T, Container>& zs) {
    auto result = interval_set<T>();
    for(const auto &z : zs){
        result.insert(interval::left_open(z.get_emin(), z.get_emax()));
    }
}

template<typename T, typename Container>
zone_set<T, Container> make_from_intervals (const interval_set<T>& intv_set) {
    auto result = zone_set<T, Container>();
    for(const auto &intv : intv_set){
        result.insert(interval::left_open(z.get_emin(), z.get_emax()));
    }
}

} //namespace timedrel

#endif