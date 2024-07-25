#include <cassert>
#include <ppl.hh>

// For debug:
#include <iostream>
#include <utility>
#include <memory>
// end debug:


#include "compound_interval.hpp"
#include "timed_interval.hpp"

using namespace Parma_Polyhedra_Library;
using namespace Parma_Polyhedra_Library::IO_Operators;

#ifndef PARAMETRIC_INTERVAL_HPP
#define PARAMETRIC_INTERVAL_HPP 1

namespace paramtimedrel {

template <class T1>
class parametric_interval: public compound_interval{
    timed_interval<T1> sub_timed_interval = timed_interval<T1>::make(0,0);
    C_Polyhedron sub_poly;

template<typename T3>
friend std::ostream& operator<<(std::ostream &os, const parametric_interval<T3>&);

  public:
    parametric_interval(const timed_interval<T1> &st, const C_Polyhedron &spoly):
        sub_timed_interval(st),sub_poly(spoly){}
  	
    timed_interval<T1> get_sub_timed_interval() const {
  	    return sub_timed_interval;
  	}
  	C_Polyhedron get_sub_poly() const {
  		return sub_poly;
  	}
    std::shared_ptr<parametric_interval<T1>> add_duration_constraints(Constraint A, Constraint B){
        C_Polyhedron pt = sub_poly;
        pt.add_constraint(A);
        pt.add_constraint(B);
        return std::make_shared<parametric_interval<T1>>(sub_timed_interval, pt);
    }
  	virtual bool compare_less_compound_interval(const std::shared_ptr<compound_interval> &c){
        std::shared_ptr<parametric_interval<T1>> pi = std::dynamic_pointer_cast<parametric_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = (pi->get_sub_timed_interval()).get_time_interval_as_pair(); 
        if(a.first < b.first){
            return true;
        }else if(a.first == b.first){
            return a.second < b.second;
        }else{
            return false;
        }
    }
    virtual bool compare_less_begin_compound_interval(const std::shared_ptr<compound_interval> &c){
        std::shared_ptr<parametric_interval<T1>> pi = std::dynamic_pointer_cast<parametric_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = (pi->get_sub_timed_interval()).get_time_interval_as_pair(); 
        return a.first < b.first;
    }
    virtual bool begin_same_as_gen_interval(const std::shared_ptr<gen_interval> c){
        std::shared_ptr<timed_interval<T1>> tival = std::dynamic_pointer_cast<timed_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = tival->get_time_interval_as_pair();
        return a.first == b.first;
    }
    virtual bool end_same_as_gen_interval(const std::shared_ptr<gen_interval> c){
        std::shared_ptr<timed_interval<T1>> tival = std::dynamic_pointer_cast<timed_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = tival->get_time_interval_as_pair();
        return a.second == b.second;
    }
    virtual bool begin_less_gen_interval(const std::shared_ptr<gen_interval> c){
        std::shared_ptr<timed_interval<T1>> tival = std::dynamic_pointer_cast<timed_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = tival->get_time_interval_as_pair();
        return a.first < b.first;
    }
    virtual bool end_less_gen_interval(const std::shared_ptr<gen_interval> c){
        std::shared_ptr<timed_interval<T1>> tival = std::dynamic_pointer_cast<timed_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = tival->get_time_interval_as_pair();
        return a.second < b.second;
    }
    virtual bool begin_same_as_end_gen_interval(const std::shared_ptr<gen_interval> c){
        std::shared_ptr<timed_interval<T1>> tival = std::dynamic_pointer_cast<timed_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = tival->get_time_interval_as_pair();
        return a.first == b.second;
    }
    virtual bool begin_less_than_end_gen_interval(const std::shared_ptr<gen_interval> c){
        std::shared_ptr<timed_interval<T1>> tival = std::dynamic_pointer_cast<timed_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = tival->get_time_interval_as_pair();
        return a.first < b.second;
    }
    virtual bool matches_gen_interval(const std::shared_ptr<gen_interval> c){
        std::shared_ptr<timed_interval<T1>> tival = std::dynamic_pointer_cast<timed_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = tival->get_time_interval_as_pair();
        return a == b;
    }
    virtual std::shared_ptr<gen_interval> get_sub_interval_ptr(){
        return std::make_shared<timed_interval<T1>>(sub_timed_interval.get_time_interval_as_pair());
    }
    virtual bool includes(const std::shared_ptr<compound_interval> &c){
        std::shared_ptr<parametric_interval<T1>> pi = std::dynamic_pointer_cast<parametric_interval<T1>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = (pi->get_sub_timed_interval()).get_time_interval_as_pair();
        return ( (a==b) and 
            sub_poly.contains(pi->get_sub_poly()) );
    }
    virtual std::shared_ptr<compound_interval> clone(){
        return std::make_shared<parametric_interval<T1>>(sub_timed_interval, sub_poly);
    }
    virtual std::shared_ptr<compound_interval> intersection(const std::shared_ptr<compound_interval> &gz){
        std::shared_ptr<parametric_interval<T1>> pi = std::dynamic_pointer_cast<parametric_interval<T1>>(gz);
        if(not (sub_timed_interval == pi->get_sub_timed_interval())){ // TODO: add an assert here
            exit(0);
        }
        C_Polyhedron pt = sub_poly;
        pt.intersection_assign(pi->get_sub_poly());
        return std::make_shared<parametric_interval<T1>>(sub_timed_interval, pt);
    }
    virtual std::shared_ptr<compound_interval> concatenation(const std::shared_ptr<compound_interval> &gz){
        std::shared_ptr<parametric_interval<T1>> pi = std::dynamic_pointer_cast<parametric_interval<T1>>(gz);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = (pi->get_sub_timed_interval()).get_time_interval_as_pair();
        assert(((void)"concatenation error", a.second == b.first));
        std::pair<T1,T1> tires(a.first, b.second);
        
        Constraint_System cs1 = sub_poly.minimized_constraints();
        Constraint_System cs2 = (pi->get_sub_poly()).minimized_constraints();

        Constraint_System cssc;
        Constraint_System csnew;

        Variable t0(0),t1(1),t2(2);
        // Swap t' with t''
        for(Constraint_System_const_iterator csit=cs1.begin();csit!=cs1.end();csit++){
            Constraint ctemp=*csit;
            ctemp.swap_space_dimensions(t1,t2);
            csnew.insert(ctemp);
        }
        // Swap t with t''
        for(Constraint_System_const_iterator csit=cs2.begin();csit!=cs2.end();csit++){
            Constraint ctemp=*csit;
            ctemp.swap_space_dimensions(t0,t2);
            csnew.insert(ctemp);
        }

        C_Polyhedron polyres(csnew);
        polyres.unconstrain(t2);
        return std::make_shared<parametric_interval<T1>>(tires, polyres);
    }
    virtual bool is_nonempty(){
        return (sub_timed_interval.is_nonempty() and (not sub_poly.is_empty()));
    }
};

} // namespace paramtimedrel

#endif // PARAMTIMEDREL_PARAMETRIC_INTERVAL_HPP