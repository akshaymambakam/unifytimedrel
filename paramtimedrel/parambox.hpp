#include <array>
#include <vector>
#include <limits>
#include <cstdint>
#include <iostream>
#include <cassert>

#include "../timedrel/include/timedrel/bound.hpp"

using namespace timedrel;

#ifndef PARAMTIMEDREL_PARAMBOX_HPP
#define PARAMTIMEDREL_PARAMBOX_HPP

namespace paramtimedrel {

template <class T>
class parambox {

template<typename T1>
friend std::ostream& operator<<(std::ostream &os, const parambox<T1>&);

public:

    typedef T              param_value_type;
    typedef bound<T>       param_bound_type;
    typedef lower_bound<T> param_lower_bound_type;
    typedef upper_bound<T> param_upper_bound_type;

    typedef parambox<T>        parambox_type;

private:

    std::vector<param_lower_bound_type> param_min_vec;
    std::vector<param_upper_bound_type> param_max_vec;

    // parambox(const parambox&) = default;
    
    /*
     *  The constructor is private. use `make` to construct a parambox.
     */
    parambox(const std::vector<param_lower_bound_type>& param_lower_vec_1, 
         const std::vector<param_upper_bound_type>& param_upper_vec_1): 
            param_min_vec(param_lower_vec_1),
            param_max_vec(param_upper_vec_1){}

public:

    constexpr static T infinity = param_bound_type::infinity; 
    constexpr static T zero = param_bound_type::zero;

    bool operator==(const parambox_type& other) const {
        assert((void("Boxes with different number of params"), this->num_of_params()==other.num_of_params()));
        bool boxes_equal = true;
        for(int i=0; i<(this->num_of_params()); i++){
            boxes_equal = boxes_equal and (this->get_lower_by_index(i) == other.get_lower_by_index(i));
            boxes_equal = boxes_equal and (this->get_upper_by_index(i) == other.get_upper_by_index(i));
        }

        return boxes_equal;
    }

    static parambox_type make(const std::vector<param_lower_bound_type>& param_lower_vec_1, 
        const std::vector<param_upper_bound_type>& param_upper_vec_1){
        return parambox_type(param_lower_vec_1, param_upper_vec_1);
    }

    static parambox_type make(const std::vector<T>& lb_values, const std::vector<T>& ub_values,
        const std::vector<bool>& lb_signs, const std::vector<bool>& ub_signs){
        std::vector<param_lower_bound_type> lbv;
        std::vector<param_upper_bound_type> ubv;
        
        for(int i=0; i<lb_values.size(); i++){
            lbv.push_back(param_lower_bound_type(lb_values[i], lb_signs[i]));
        }
        for(int i=0; i<ub_values.size(); i++){
            ubv.push_back(param_upper_bound_type(ub_values[i], ub_signs[i]));
        }

        return make(lbv, ubv);
    }

    static parambox_type make_from(const std::vector<T>& lb_values, const std::vector<T>& ub_values,
        const std::vector<bool>& lb_signs, const std::vector<bool>& ub_signs){
        return make(lb_values, ub_values, lb_signs, ub_signs);
    }

    static parambox_type make(const std::vector<T>& lb_values, const std::vector<T>& ub_values){
        std::vector<bool> lb_signs(lb_values.size(), true);
        std::vector<bool> ub_signs(ub_values.size(), true);
        return make(lb_values, ub_values, lb_signs, ub_signs);
    }

    int num_of_params() const{
        return param_min_vec.size();
    }

    param_lower_bound_type get_lower_by_index(int index) const{
        return param_min_vec[index];
    }

    param_upper_bound_type get_upper_by_index(int index) const{
        return param_max_vec[index];
    }

    bool is_nonempty() const {
        if((this->num_of_params())==0){
            return false;
        }
        bool box_nonempty = true;
        for(int i=0; i<(this->num_of_params()); i++){
            box_nonempty = box_nonempty and param_bound_type::is_valid_interval(this->get_lower_by_index(i), 
                this->get_upper_by_index(i));
        }

        return box_nonempty;
    }

    static bool includes(
        const parambox_type& z1, 
        const parambox_type& z2){
        bool box_includes = true;
        for(int i=0; i<(z1.num_of_params()); i++){
            box_includes = box_includes and 
                param_lower_bound_type::includes(z1.get_lower_by_index(i), z2.get_lower_by_index(i)) and
                param_upper_bound_type::includes(z1.get_upper_by_index(i), z2.get_upper_by_index(i));
        }

        return box_includes;
    }

    static parambox_type intersection(const parambox_type& z1, const parambox_type& z2){
        std::vector<param_lower_bound_type> lbv;
        std::vector<param_upper_bound_type> ubv;
        for(int i=0; i<(z1.num_of_params()); i++){
            lbv.push_back(param_lower_bound_type::intersection(z1.get_lower_by_index(i),
                z2.get_lower_by_index(i)));
            ubv.push_back(param_upper_bound_type::intersection(z1.get_upper_by_index(i),
                z2.get_upper_by_index(i)));
        }

        return make(lbv, ubv);
    }

    static parambox_type add_lower_bound_on_parameter(const parambox_type& z, 
        const param_lower_bound_type& bmin, int param_index){
        std::vector<param_lower_bound_type> lbv;
        std::vector<param_upper_bound_type> ubv;
        
        for(int i=0; i<z.num_of_params(); i++){
            if(i!=param_index){
                lbv.push_back(z.get_lower_by_index(i));    
            }else{
                lbv.push_back(param_lower_bound_type::intersection(z.get_lower_by_index(i),
                    bmin));
            }
            ubv.push_back(z.get_upper_by_index(i));
        }

        return make(lbv, ubv);
    }

    static parambox_type add_upper_bound_on_parameter(const parambox_type& z, 
        const param_upper_bound_type& bmax, int param_index){
        std::vector<param_lower_bound_type> lbv;
        std::vector<param_upper_bound_type> ubv;
        
        for(int i=0; i<z.num_of_params(); i++){
            if(i!=param_index){
                ubv.push_back(z.get_upper_by_index(i));    
            }else{
                ubv.push_back(param_upper_bound_type::intersection(z.get_upper_by_index(i),
                    bmax));
            }
            lbv.push_back(z.get_lower_by_index(i));
        }

        return make(lbv, ubv);
    }

    static parambox_type add_lower_bound_on_parameter(const parambox_type& z,
        param_value_type& bminval, bool is_closed, int param_index){
        param_lower_bound_type bmin = is_closed ? param_lower_bound_type::closed(bminval) :
            param_lower_bound_type::open(bminval);

        return add_lower_bound_on_parameter(z, bmin, param_index);
    }

    static parambox_type add_upper_bound_on_parameter(const parambox_type& z,
        param_value_type& bmaxval, bool is_closed, int param_index){
        param_upper_bound_type bmax = is_closed ? param_upper_bound_type::closed(bmaxval) :
            param_upper_bound_type::open(bmaxval);

        return add_upper_bound_on_parameter(z, bmax, param_index);
    }

};

} // namespace paramtimedrel


#endif // PARAMTIMEDREL_PARAMBOX_HPP
