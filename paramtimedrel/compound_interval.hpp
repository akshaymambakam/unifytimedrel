#include <iostream>
#include <memory>

#include "gen_interval.hpp"

#ifndef COMPOUND_INTERVAL_HPP
#define COMPOUND_INTERVAL_HPP 1

// TODO: Use pure virtual function instead.
class compound_interval {
  public:
    virtual bool compare_less_compound_interval(const std::shared_ptr<compound_interval> &c) = 0;
    virtual bool compare_less_begin_compound_interval(const std::shared_ptr<compound_interval> &c) = 0;
    virtual bool begin_same_as_gen_interval(const std::shared_ptr<gen_interval> c) = 0;
    virtual bool end_same_as_gen_interval(const std::shared_ptr<gen_interval> c) = 0;
    virtual bool begin_less_gen_interval(const std::shared_ptr<gen_interval> c) = 0;
    virtual bool end_less_gen_interval(const std::shared_ptr<gen_interval> c) = 0;
    virtual bool begin_same_as_end_gen_interval(const std::shared_ptr<gen_interval> c) = 0;
    virtual bool begin_less_than_end_gen_interval(const std::shared_ptr<gen_interval> c) = 0;
    virtual bool matches_gen_interval(const std::shared_ptr<gen_interval> c) = 0;
    virtual std::shared_ptr<gen_interval> get_sub_interval_ptr() = 0;
    virtual bool includes(const std::shared_ptr<compound_interval> &gz) = 0;
    virtual std::shared_ptr<compound_interval> clone() = 0;
    virtual std::shared_ptr<compound_interval> intersection(const std::shared_ptr<compound_interval> &gz) = 0;
    virtual std::shared_ptr<compound_interval> concatenation(const std::shared_ptr<compound_interval> &gz) = 0;
    virtual bool is_nonempty() = 0;
};


#endif
