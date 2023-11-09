#include <limits>
#include <iostream>

#ifndef TIMEDREL_BOUND_HPP
#define TIMEDREL_BOUND_HPP

namespace timedrel {

// using T = int;

template <class T> struct bound;
template <class T> struct lower_bound;
template <class T> struct upper_bound;

template <class T>
struct bound {

template<typename T1>
friend std::ostream& operator<<(std::ostream &os, const bound<T1>&);

    typedef T              value_type;
    typedef bound<T>       bound_type;

    typedef lower_bound<T> lower_bound_type;
    typedef upper_bound<T> upper_bound_type;
    
    T value;
    bool sign;

    /** 
     * The max is divided by 2 to prevent overflow since we currently 
     * need to add two numbers in several operations.
     */
    constexpr static T infinity = (std::numeric_limits<T>::has_infinity) ? std::numeric_limits<T>::infinity() : std::numeric_limits<T>::max()/2;
    constexpr static T minus_infinity = (std::numeric_limits<T>::has_infinity) ? std::numeric_limits<T>::infinity() : -std::numeric_limits<T>::max()/2;

    
    constexpr static T zero = 0;

    bound(T v, bool p){
        value = v;
        sign = p;
    }

    bool operator==(const bound_type& other) const {
        return value == other.value and sign == other.sign;
    }

    bool operator<(const bound_type& other) const {
        if(this->value < other.value){
            return true;
        } else if (this->value == other.value and this->sign < other.sign){
            return true;
        } else {
            return false;
        }
    }

    static bool is_valid_interval(const lower_bound_type& l, const upper_bound_type& u){

        if (l.value < u.value) {
            return true;
        } else if (l.value == u.value and l.sign and u.sign) {
            return true;
        } else {
            return false;
        }
    }

};

template <class T>
struct lower_bound : bound<T>{

    typedef T              value_type;
    typedef lower_bound<T> type;

    typedef lower_bound<T> lower_bound_type;
    typedef upper_bound<T> upper_bound_type;
    
    lower_bound(T v, bool p) : bound<T>(v, p){}

    /* 
     *  Non-strict inclusion order 
     *  e.g. (x >= 3) includes (x > 4)
     *  e.g. (x >= 3) includes (x > 3)
     *  e.g. (x >= 3) includes (x > 3)
     */
    bool operator<(const lower_bound_type& other) const {
        if(this->value < other.value){
            return true;
        } else if (this->value == other.value and this->sign > other.sign){
            return true;
        } else {
            return false;
        }
    }

    bool operator<(const upper_bound_type& other) const {
        if(this->value < other.value){
            return true;
        } else if (this->value == other.value and this->sign > other.sign){
            return true;
        } else {
            return false;
        }
    }

    upper_bound_type complement(){
        return lower_bound_type::complementation(*this);
    }

    static bool includes (const lower_bound_type& b1, const lower_bound_type& b2){
        if(b1.value < b2.value){
            return true;
        } else if (b1.value == b2.value and b1.sign >= b2.sign){
            return true;
        } else {
            return false;
        }   
    }



    static lower_bound_type intersection (const lower_bound_type& b1, const lower_bound_type& b2){
        if(b1.value < b2.value){
            return b2;
        } else if (b1.value == b2.value and b1.sign >= b2.sign){
            return b2;
        } else {
            return b1;
        }
       
    }

    static lower_bound_type add (const lower_bound_type& b1, const lower_bound_type& b2){
        return lower_bound_type(b1.value + b2.value, b1.sign && b2.sign);    
    }
    static lower_bound_type add (const lower_bound_type& b1, const upper_bound_type& b2){
        return lower_bound_type(b1.value - b2.value, b1.sign && b2.sign);    
    }
    static lower_bound_type add (const upper_bound_type& b1, const lower_bound_type& b2){
        return lower_bound_type(b2.value - b1.value, b1.sign && b2.sign);    
    }

    static upper_bound_type complementation(const lower_bound_type& b1){
        return upper_bound_type(b1.value, not b1.sign);
    }

    static lower_bound_type strict(T v){ return lower_bound_type(v, false);}
    static lower_bound_type nonstrict(T v){ return lower_bound_type(v, true);}
    
    static lower_bound_type open(T v){ return lower_bound_type(v, false);}
    static lower_bound_type closed(T v){ return lower_bound_type(v, true);}

    static lower_bound_type unbounded(){ return lower_bound_type(type::minus_infinity, false);}

};

template <class T>
struct upper_bound : public bound<T> {

    typedef T              value_type;
    typedef upper_bound<T> type;

    typedef lower_bound<T> lower_bound_type;
    typedef upper_bound<T> upper_bound_type;

    upper_bound(T v, bool p) : bound<T>(v, p){}
    
    /* 
     *  Sorting order
     */
    bool operator<(const upper_bound_type& other) const {
        if(this->value < other.value){
            return true;
        } else if (this->value == other.value and this->sign < other.sign){
            return true;
        } else {
            return false;
        }
    }

    bool operator<(const lower_bound_type& other) const {
        if(this->value < other.value){
            return true;
        } else if (this->value == other.value and this->sign < other.sign){
            return true;
        } else {
            return false;
        }
    }

    lower_bound_type complement(){
        return upper_bound_type::complementation(*this);
    }

    /* 
     *  Non-strict inclusion order 
     *  e.g. (x >= 3) includes (x > 4)
     *  e.g. (x >= 3) includes (x > 3)
     *  e.g. (x >= 3) includes (x > 3)
     */
    static bool includes (const upper_bound_type& b1, const upper_bound_type& b2){
        if(b1.value > b2.value){
            return true;
        } else if (b1.value == b2.value and b1.sign >= b2.sign){
            return true;
        } else {
            return false;
        }
    }

    static upper_bound_type intersection (const upper_bound_type& b1, const upper_bound_type& b2){
        if(b1.value > b2.value){
            return b2;
        } else if (b1.value == b2.value and b1.sign >= b2.sign){
            return b2;
        } else {
            return b1;
        }       
    }

    static upper_bound_type add (const upper_bound_type& b1, const upper_bound_type& b2){
        return upper_bound_type(b1.value + b2.value, b1.sign && b2.sign);    
    }
    static upper_bound_type add (const lower_bound_type& b1, const upper_bound_type& b2){
        return upper_bound_type(b2.value - b1.value, b1.sign && b2.sign);    
    }
    static upper_bound_type add (const upper_bound_type& b1, const lower_bound_type& b2){
        return upper_bound_type(b1.value - b2.value, b1.sign && b2.sign);    
    }

    static lower_bound_type complementation(const upper_bound_type& b1){
        return lower_bound_type(b1.value, not b1.sign);
    }

    static upper_bound_type strict(T v){ return upper_bound_type(v, false);}
    static upper_bound_type nonstrict(T v){ return upper_bound_type(v, true);}

    static upper_bound_type open(T v){ return upper_bound_type(v, false);}
    static upper_bound_type closed(T v){ return upper_bound_type(v, true);}

    static upper_bound_type unbounded(){ return upper_bound_type(type::infinity, false);}

};


} // namespace timedrel

#endif // TIMEDREL_BOUND_HPP
