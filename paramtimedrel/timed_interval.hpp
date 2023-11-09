#include <utility>

#include "gen_interval.hpp"


#ifndef TIMED_INTERVAL_HPP
#define TIMED_INTERVAL_HPP 1

namespace paramtimedrel{

template <class T>
class timed_interval: public gen_interval{
    std::pair<T,T> time_interval_by_pair;

template<typename T1>
friend std::ostream& operator<<(std::ostream &os, const timed_interval<T>&);

  public:
    timed_interval(const std::pair<T,T> &tip):
        time_interval_by_pair(tip){}

    static timed_interval<T> make(T tb, T te){
        std::pair<T,T> tpair(tb,te);
        return timed_interval<T>(tpair);
    }
    
    bool operator==(const timed_interval<T>& other) const {
        return time_interval_by_pair == other.get_time_interval_as_pair();
    }
    std::pair<T,T> get_time_interval_as_pair() const {
        return time_interval_by_pair;
    }
    T get_start_time_interval() const {
        return time_interval_by_pair.first;
    }
    T get_end_time_interval() const {
        return time_interval_by_pair.second;
    }
    virtual bool is_nonempty(){
        return time_interval_by_pair.first <= time_interval_by_pair.second;
    }
};

} // namespace paramtimedrel


#endif // PARAMTIMEDREL_TIMED_INTERVAL_HPP