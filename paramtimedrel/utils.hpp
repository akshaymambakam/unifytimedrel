#ifndef PARAM_TIMEDREL_UTILS_HPP
#define PARAM_TIMEDREL_UTILS_HPP 1

#include <iostream>

#include "parambox.hpp"
#include "zone_parambox.hpp"
#include "timed_interval.hpp"
#include "interval_parambox.hpp"
#include "../timedrel/include/timedrel/utils.hpp"

namespace paramtimedrel {

template <typename T>
inline std::ostream& operator<< (std::ostream &os, const parambox<T>& pb) {
    for(int i=0; i<pb.num_of_params(); i++){
        if(i!=(pb.num_of_params()-1)){
            os << pb.get_lower_by_index(i) << " p" << i << " " << pb.get_upper_by_index(i) << ", ";    
        }else{
            os << pb.get_lower_by_index(i) << " p" << i << " " << pb.get_upper_by_index(i);
        }
        
    }

    return os;
}

template <typename T>
inline std::ostream& operator<< (std::ostream &os, const timed_interval<T>& pb) {
    os << "t1 = " << pb.get_start_time_interval() << ", t2 = " << pb.get_end_time_interval();
    return os;
}

template <typename T1, typename T2>
inline std::ostream& operator<< (std::ostream &os, const zone_parambox<T1,T2>& zpb) {
    os << "(" << zpb.get_sub_zone() << " ; " << zpb.get_sub_parambox() << ")";
    return os;
}

template <typename T1, typename T2>
inline std::ostream& operator<< (std::ostream &os, const interval_parambox<T1,T2>& ipb) {
    os << "(" << ipb.get_sub_timed_interval() << " ; " << ipb.get_sub_parambox() << ")";
    return os;
}

} //namespace paramtimedrel

#endif
