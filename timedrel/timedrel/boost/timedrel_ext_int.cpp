// #include "../include/timedrel/interval_set.hpp"

#include <array>
#include <cstdint>
#include <boost/python.hpp>

#include "timedrel/bound.hpp"
#include "timedrel/zone.hpp"
#include "timedrel/zone_set.hpp"
#include "timedrel/utils.hpp"

using T = int64_t;

BOOST_PYTHON_MODULE(ext_int)
{
    using namespace boost::python;
    using namespace timedrel;

    typedef lower_bound<T> lower_bound_type;
    typedef upper_bound<T> upper_bound_type;

    class_<lower_bound_type>("lower_bound", init<T, bool>())
        .def_readonly("value", &lower_bound_type::value)
        .def_readonly("sign", &lower_bound_type::sign)
        .def(self_ns::str(self_ns::self))
    ;

    def("lt", &upper_bound_type::strict);
    def("leq", &upper_bound_type::nonstrict);

    class_<upper_bound_type>("upper_bound", init<T, bool>())
        .def_readonly("value", &upper_bound_type::value)
        .def_readonly("sign", &upper_bound_type::sign)
        .def(self_ns::str(self_ns::self))
    ;

    def("gt", &lower_bound_type::strict);
    def("geq", &lower_bound_type::nonstrict);

    typedef zone<T> zone_type;
    typedef zone_set<T> zone_set_type;

    class_<zone_type>("zone", no_init)

        .def("bmin", &zone_type::get_bmin)
        .def("bmax", &zone_type::get_bmax)
        .def("emin", &zone_type::get_emin)
        .def("emax", &zone_type::get_emax)
        .def("dmin", &zone_type::get_dmin)
        .def("dmax", &zone_type::get_dmax)

        .def<zone_type (*)(
            const lower_bound_type&, const upper_bound_type&, 
            const lower_bound_type&, const upper_bound_type&, 
            const lower_bound_type&, const upper_bound_type&)>
        ("make", &zone_type::make)

        .def(self_ns::str(self_ns::self))
    ;

    class_<zone_set_type>("zone_set")
        .def<void (zone_set_type::*)(const zone_type&)>("add", &zone_set_type::add)
        .def<void (zone_set_type::*)(const std::array<T, 6>&)>("add", &zone_set_type::add)
        .def<void (zone_set_type::*)(const std::array<T, 6>&, const std::array<bool, 6>&)>("add", &zone_set_type::add)
        .def("add_from_period", &zone_set_type::add_from_period)
        .def("add_from_period_rise_anchor", &zone_set_type::add_from_period_rise_anchor)
        .def("add_from_period_fall_anchor", &zone_set_type::add_from_period_fall_anchor)
        .def("add_from_period_both_anchor", &zone_set_type::add_from_period_both_anchor)
        .def("empty", &zone_set_type::empty)
        .def("__iter__", range(&zone_set_type::cbegin, &zone_set_type::cend))
    ;

    def("filter", &zone_set_type::filter);
    def("includes", &zone_set_type::includes);

    // Set operations
    def<zone_set_type (*)(const zone_set_type&)>("complementation", &zone_set_type::complementation);
    def<zone_set_type (*)(const zone_set_type&, const zone_set_type&)>("union", &zone_set_type::set_union);
    def<zone_set_type (*)(const zone_set_type&, const zone_set_type&)>("intersection", &zone_set_type::intersection);
    def<zone_set_type (*)(const zone_set_type&, const zone_set_type&)>("difference", &zone_set_type::set_difference);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("duration_restriction", &zone_set_type::duration_restriction);

    // Sequential operations
    def<zone_set_type (*)(const zone_set_type&, const zone_set_type&)>("concatenation", &zone_set_type::concatenation);
    def<zone_set_type (*)(const zone_set_type&)>("transitive_closure", &zone_set_type::transitive_closure);

    // Modal operations of the logic of time periods
    def<zone_set_type (*)(const zone_set_type&, T, T)>("diamond_starts", &zone_set_type::diamond_starts);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("diamond_started_by", &zone_set_type::diamond_started_by);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("diamond_finishes", &zone_set_type::diamond_finishes);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("diamond_finished_by", &zone_set_type::diamond_finished_by);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("diamond_meets", &zone_set_type::diamond_meets);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("diamond_met_by", &zone_set_type::diamond_met_by);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("box_starts", &zone_set_type::box_starts);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("box_started_by", &zone_set_type::box_started_by);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("box_finishes", &zone_set_type::box_finishes);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("box_finished_by", &zone_set_type::box_finished_by);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("box_meets", &zone_set_type::box_meets);
    def<zone_set_type (*)(const zone_set_type&, T, T)>("box_met_by", &zone_set_type::box_met_by);

}