#include <array>
#include <vector>
#include <limits>
#include <cstdint>
#include <iostream>

#include "bound.hpp"

#ifndef TIMEDREL_ZONE_HPP
#define TIMEDREL_ZONE_HPP

namespace timedrel {

template <class T>
class zone {

template<typename T1>
friend std::ostream& operator<<(std::ostream &os, const zone<T1>&);

public:

    typedef T              value_type;
    typedef bound<T>       bound_type;
    typedef lower_bound<T> lower_bound_type;
    typedef upper_bound<T> upper_bound_type;

    typedef zone<T>        zone_type;
    typedef zone<T>        type;

private:

    lower_bound_type bmin, emin, dmin;
    upper_bound_type bmax, emax, dmax;

    // zone(const zone&) = default;
    
    /*
     *  The constructor is private. use `make` to construct a zone.
     */
    zone(const lower_bound_type& bmin1, const upper_bound_type& bmax1,const lower_bound_type& emin1,const upper_bound_type& emax1, const lower_bound_type& dmin1, const upper_bound_type& dmax1): 
            bmin(bmin1),
            bmax(bmax1),
            emin(emin1),
            emax(emax1),
            dmin(dmin1),
            dmax(dmax1) {}

public:

    constexpr static T infinity = bound_type::infinity; 
    constexpr static T zero = bound_type::zero;

    bool operator==(const zone_type& other) const {
        return get_bmin() == other.get_bmin() and 
               get_bmax() == other.get_bmax() and 
               get_emin() == other.get_emin() and 
               get_emax() == other.get_emax() and 
               get_dmin() == other.get_dmin() and
               get_dmax() == other.get_dmax();
    }

    /*
     *  Constructs a zone with normalized bounds.  
     *  This is a canonical form if the zone is not empty. 
     */
    static zone_type make(const lower_bound_type& bmin, const upper_bound_type& bmax,const lower_bound_type& emin,const upper_bound_type& emax, const lower_bound_type& dmin, const upper_bound_type& dmax){

        return zone_type(
            lower_bound_type::intersection(
                bmin, 
                lower_bound_type::add(emin, dmax)),

            upper_bound_type::intersection(
                bmax, 
                upper_bound_type::add(emax, dmin)),

            lower_bound_type::intersection(
                emin, 
                lower_bound_type::add(bmin, dmin)),

            upper_bound_type::intersection(
                emax, 
                upper_bound_type::add(bmax, dmax)),

            lower_bound_type::intersection(
                dmin, 
                lower_bound_type::add(emin, bmax)),

            upper_bound_type::intersection(
                dmax, 
                upper_bound_type::add(emax, bmin))

        );

    }

    static zone_type make(const std::array<T, 6>& values, const std::array<bool, 6>& signs){
        return make(
            lower_bound_type(values[0], signs[0]),
            upper_bound_type(values[1], signs[1]),
            lower_bound_type(values[2], signs[2]),
            upper_bound_type(values[3], signs[3]),
            lower_bound_type(values[4], signs[4]),
            upper_bound_type(values[5], signs[5])
        );
    }

    static zone_type make_from(const std::array<T, 6>& values, const std::array<bool, 6>& signs){
        return make(values, signs);
    }

    static zone_type make(const std::array<T, 6>& values){
        return make(values, {1,0,0,1,0,1});
    }

    static zone_type make_from_period(value_type begin, value_type end){
        return make({begin, end, begin, end, 0, end-begin});
    }

    static zone_type make_from_period_rise_anchor(value_type begin, value_type end){
        return make({begin, begin, begin, end, 0, end-begin}, {1,1,1,1,0,1});
    }

    static zone_type make_from_period_fall_anchor(value_type begin, value_type end){
        return make({begin, end, end, end, 0, end-begin}, {1,1,1,1,0,1});
    }

    static zone_type make_from_period_both_anchor(value_type begin, value_type end){
        return make({begin, begin, end, end, end-begin, end-begin}, {1,1,1,1,1,1});
    }

    static zone_type universal(){
        return make(
            lower_bound_type::unbounded(), upper_bound_type::unbounded(),
            lower_bound_type::unbounded(), upper_bound_type::unbounded(),
            lower_bound_type::open(0), upper_bound_type::unbounded());
    }

    static zone_type normalize(const zone_type& z){

        return zone_type(
            lower_bound_type::intersection(
                z.get_bmin(), 
                lower_bound_type::add(z.get_emin(), z.get_dmax())),

            upper_bound_type::intersection(
                z.get_bmax(), 
                upper_bound_type::add(z.get_emax(), z.get_dmin())),

            lower_bound_type::intersection(
                z.get_emin(), 
                lower_bound_type::add(z.get_bmin(), z.get_dmin())),

            upper_bound_type::intersection(
                z.get_emax(), 
                upper_bound_type::add(z.get_bmax(), z.get_dmax())),

            lower_bound_type::intersection(
                z.get_dmin(), 
                lower_bound_type::add(z.get_emin(), z.get_bmax())),

            upper_bound_type::intersection(
                z.get_dmax(), 
                upper_bound_type::add(z.get_emax(), z.get_bmin()))

        );

    }

    bool is_nonempty() const {

        return bound_type::is_valid_interval(bmin, bmax) and
               bound_type::is_valid_interval(emin, emax) and
               bound_type::is_valid_interval(dmin, dmax);

    }

    inline lower_bound_type get_bmin() const {return bmin;}
    inline upper_bound_type get_bmax() const {return bmax;}
    inline lower_bound_type get_emin() const {return emin;}
    inline upper_bound_type get_emax() const {return emax;}
    inline lower_bound_type get_dmin() const {return dmin;}
    inline upper_bound_type get_dmax() const {return dmax;}

    static bool includes(
        const zone_type& z1, 
        const zone_type& z2){

        return lower_bound_type::includes(z1.get_bmin(), z2.get_bmin()) and
               upper_bound_type::includes(z1.get_bmax(), z2.get_bmax()) and
               lower_bound_type::includes(z1.get_emin(), z2.get_emin()) and
               upper_bound_type::includes(z1.get_emax(), z2.get_emax()) and
               lower_bound_type::includes(z1.get_dmin(), z2.get_dmin()) and
               upper_bound_type::includes(z1.get_dmax(), z2.get_dmax());
    }

    static zone_type concatenation(const zone_type& z1, const zone_type& z2){

        return make(

            lower_bound_type::intersection(
                z1.get_bmin(),
                lower_bound_type::intersection(
                    lower_bound_type::add(z1.get_emin(), z1.get_dmax()),
                    lower_bound_type::add(z2.get_bmin(), z1.get_dmax())
                    )
            ),

            upper_bound_type::intersection(
                z1.get_bmax(),                
                upper_bound_type::intersection(
                    upper_bound_type::add(z1.get_emax(), z1.get_dmin()),
                    upper_bound_type::add(z2.get_bmax(), z1.get_dmin())
                    )
            ),

            lower_bound_type::intersection(
                z2.get_emin(),                
                lower_bound_type::intersection(
                    lower_bound_type::add(z1.get_emin(), z2.get_dmin()),
                    lower_bound_type::add(z2.get_bmin(), z2.get_dmin())
                    )
            ),

            upper_bound_type::intersection(
                z2.get_emax(),                
                upper_bound_type::intersection(
                    upper_bound_type::add(z1.get_emax(), z2.get_dmax()),
                    upper_bound_type::add(z2.get_bmax(), z2.get_dmax())
                )
            ),

            lower_bound_type::add(z1.get_dmin(), z2.get_dmin()),
            upper_bound_type::add(z1.get_dmax(), z2.get_dmax())
        );

    }

    static zone_type intersection(const zone_type& z1, const zone_type& z2){

        return make(lower_bound_type::intersection(z1.bmin, z2.bmin),
                    upper_bound_type::intersection(z1.bmax, z2.bmax),
                    lower_bound_type::intersection(z1.emin, z2.emin),
                    upper_bound_type::intersection(z1.emax, z2.emax),
                    lower_bound_type::intersection(z1.dmin, z2.dmin),
                    upper_bound_type::intersection(z1.dmax, z2.dmax));

    }


    static zone_type duration_restriction(const zone_type& z, const lower_bound_type& dmin1, const upper_bound_type& dmax1){

        return make(
            z.get_bmin(),
            z.get_bmax(),
            z.get_emin(),
            z.get_emax(),
            lower_bound_type::intersection(z.get_dmin(), dmin1),
            upper_bound_type::intersection(z.get_dmax(), dmax1)
        );

    }

    static zone_type duration_restriction(const zone_type& z, const value_type dmin1, const value_type dmax1){
        return duration_restriction(z, 
            lower_bound_type::open(dmin1), 
            upper_bound_type::closed(dmax1)
        );

    }

};

} // namespace timedrel


#endif // TIMEDREL_ZONE_HPP
