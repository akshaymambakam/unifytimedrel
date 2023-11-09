#include <iostream>
#include <memory>


#ifndef GEN_INTERVAL_HPP
#define GEN_INTERVAL_HPP 1

// TODO: Use pure virtual function instead.
class gen_interval {
  public:
    virtual bool is_nonempty() = 0;
};


#endif
