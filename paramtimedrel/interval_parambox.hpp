#include <cassert>

// For debug:
#include <iostream>
#include <utility>
#include <memory>
// end debug:


#include "compound_interval.hpp"
#include "timed_interval.hpp"
#include "parambox.hpp"


#ifndef INTERVAL_PARAMBOX_HPP
#define INTERVAL_PARAMBOX_HPP 1

namespace paramtimedrel {

template <class T1, class T2>
class interval_parambox: public compound_interval{
    timed_interval<T1> sub_timed_interval = timed_interval<T1>::make(0,0);
    parambox<T2> sub_parambox = parambox<T2>::make({0},{0});

template<typename T3, typename T4>
friend std::ostream& operator<<(std::ostream &os, const interval_parambox<T3,T4>&);

  public:
    interval_parambox(const timed_interval<T1> &st, const parambox<T2> &spb):
        sub_timed_interval(st),sub_parambox(spb){}
  	
    timed_interval<T1> get_sub_timed_interval() const {
  	    return sub_timed_interval;
  	}
  	parambox<T2> get_sub_parambox() const {
  		return sub_parambox;
  	}
    std::shared_ptr<interval_parambox<T1,T2>> add_lower_bound_on_parameter(T2 bminval, bool is_closed,
        int param_index){
        
        parambox<T2> sub_parambox_res = parambox<T2>::add_lower_bound_on_parameter(sub_parambox, 
            bminval, is_closed, param_index);
        return std::make_shared<interval_parambox<T1,T2>>(sub_timed_interval, sub_parambox_res);
    }
    std::shared_ptr<interval_parambox<T1,T2>> add_upper_bound_on_parameter(T2 bmaxval, bool is_closed, 
        int param_index){
        
        parambox<T2> sub_parambox_res = parambox<T2>::add_upper_bound_on_parameter(sub_parambox, 
            bmaxval, is_closed, param_index);
        return std::make_shared<interval_parambox<T1,T2>>(sub_timed_interval, sub_parambox_res);
    }
  	virtual bool compare_less_compound_interval(const std::shared_ptr<compound_interval> &c){
        std::shared_ptr<interval_parambox<T1,T2>> ipb = std::dynamic_pointer_cast<interval_parambox<T1,T2>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = (ipb->get_sub_timed_interval()).get_time_interval_as_pair(); 
        if(a.first < b.first){
            return true;
        }else if(a.first == b.first){
            return a.second < b.second;
        }else{
            return false;
        }
    }
    virtual bool compare_less_begin_compound_interval(const std::shared_ptr<compound_interval> &c){
        std::shared_ptr<interval_parambox<T1,T2>> ipb = std::dynamic_pointer_cast<interval_parambox<T1,T2>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = (ipb->get_sub_timed_interval()).get_time_interval_as_pair(); 
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
        std::shared_ptr<interval_parambox<T1,T2>> ipb = std::dynamic_pointer_cast<interval_parambox<T1,T2>>(c);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = (ipb->get_sub_timed_interval()).get_time_interval_as_pair();
        return ( (a==b) and 
            parambox<T2>::includes(sub_parambox,ipb->get_sub_parambox()) );
    }
    virtual std::shared_ptr<compound_interval> clone(){
        return std::make_shared<interval_parambox<T1,T2>>(sub_timed_interval, sub_parambox);
    }
    virtual std::shared_ptr<compound_interval> intersection(const std::shared_ptr<compound_interval> &gz){
        std::shared_ptr<interval_parambox<T1,T2>> ipb = std::dynamic_pointer_cast<interval_parambox<T1,T2>>(gz);
        if(not (sub_timed_interval == ipb->get_sub_timed_interval())){ // TODO: add an assert here
            exit(0);
        }
        parambox<T2> pbres = parambox<T2>::intersection(sub_parambox, ipb->get_sub_parambox());
        return std::make_shared<interval_parambox<T1,T2>>(sub_timed_interval, pbres);
    }
    virtual std::shared_ptr<compound_interval> concatenation(const std::shared_ptr<compound_interval> &gz){
        std::shared_ptr<interval_parambox<T1,T2>> ipb = std::dynamic_pointer_cast<interval_parambox<T1,T2>>(gz);
        std::pair<T1,T1> a = sub_timed_interval.get_time_interval_as_pair();
        std::pair<T1,T1> b = (ipb->get_sub_timed_interval()).get_time_interval_as_pair();
        assert(((void)"concatenation error", a.second == b.first));
        std::pair<T1,T1> tires(a.first, b.second);
        parambox<T2> pbres = parambox<T2>::intersection(sub_parambox, ipb->get_sub_parambox());
        return std::make_shared<interval_parambox<T1,T2>>(tires, pbres);
    }
    virtual bool is_nonempty(){
        return (sub_timed_interval.is_nonempty() and sub_parambox.is_nonempty());
    }
};

} // namespace paramtimedrel

#endif // PARAMTIMEDREL_INTERVAL_PARAMBOX_HPP