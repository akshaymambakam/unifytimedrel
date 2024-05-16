#include "gen_zone.hpp"
#include "../timedrel/include/timedrel/zone.hpp"
#include "parambox.hpp"

using namespace timedrel;

#ifndef ZONE_PARAMBOX_HPP
#define ZONE_PARAMBOX_HPP 1

namespace paramtimedrel {

template <class T1, class T2>
class zone_parambox: public gen_zone{
    zone<T1> sub_zone = zone<T1>::make({0,0,0,0,0,0});
    parambox<T2> sub_parambox = parambox<T2>::make({0},{0});

template<typename T3, typename T4>
friend std::ostream& operator<<(std::ostream &os, const zone_parambox<T3,T4>&);

  public:
    zone_parambox(zone<T1> &sz, parambox<T2> &spb):
        sub_zone(sz),sub_parambox(spb){}
  	
    zone<T1> get_sub_zone() const {
  	    return sub_zone;
  	}
  	parambox<T2> get_sub_parambox() const {
  		return sub_parambox;
  	}
  	virtual bool compare_less_bmin(const std::shared_ptr<gen_zone> &c){
  	    std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(c);
        return sub_zone.get_bmin() < (zpb->get_sub_zone()).get_bmin();
    }
    virtual bool compare_less_emin(const std::shared_ptr<gen_zone> &c){
    	std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(c);
        return sub_zone.get_emin() < (zpb->get_sub_zone()).get_emin();
    }
    virtual bool compare_less_bmax_bmin(const std::shared_ptr<gen_zone> &c){
    	std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(c);
        return sub_zone.get_bmax() < (zpb->get_sub_zone()).get_bmin();
    }
    virtual bool compare_less_emin_bmin(const std::shared_ptr<gen_zone> &c){
    	std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(c);
        return sub_zone.get_emin() < (zpb->get_sub_zone()).get_bmin();
    }
    virtual bool compare_less_bmax_emin(const std::shared_ptr<gen_zone> &c){
        std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(c);
        return sub_zone.get_bmax() < (zpb->get_sub_zone()).get_emin();
    }
    virtual bool compare_less_emax_bmin(const std::shared_ptr<gen_zone> &c){
        std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(c);
        return sub_zone.get_emax() < (zpb->get_sub_zone()).get_bmin();
    }
    virtual bool compare_less_bmin_bmax(const std::shared_ptr<gen_zone> &c){
        std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(c);
        return sub_zone.get_bmin() < (zpb->get_sub_zone()).get_bmax();   
    }
    virtual bool includes(const std::shared_ptr<gen_zone> &c){
    	std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(c);
        return (zone<T1>::includes(sub_zone, zpb->get_sub_zone()) and
            parambox<T2>::includes(sub_parambox, zpb->get_sub_parambox()));
    }
    virtual std::shared_ptr<gen_zone> clone(){
        return std::make_shared<zone_parambox<T1,T2>>(sub_zone, sub_parambox);
    }
    virtual std::shared_ptr<gen_zone> intersection(const std::shared_ptr<gen_zone> &gz){
    	std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(gz);
    	zone<T1> zres = zone<T1>::intersection(this->get_sub_zone(), zpb->get_sub_zone());
    	parambox<T2> pbres = parambox<T2>::intersection(this->get_sub_parambox(), zpb->get_sub_parambox());
    	return std::make_shared<zone_parambox<T1,T2>>(zres, pbres);
    }
    virtual std::shared_ptr<gen_zone> concatenation(const std::shared_ptr<gen_zone> &gz){
        std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(gz);
        zone<T1> zres = zone<T1>::concatenation(this->get_sub_zone(), zpb->get_sub_zone());
        parambox<T2> pbres = parambox<T2>::intersection(this->get_sub_parambox(), zpb->get_sub_parambox());
        return std::make_shared<zone_parambox<T1,T2>>(zres, pbres);
    }
#ifdef ENABLE_CONDITIONAL
    virtual std::shared_ptr<gen_zone> left_conditional(const std::shared_ptr<gen_zone> &gz){
        std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(gz);
        zone<T1> zres = zone<T1>::left_conditional(this->get_sub_zone(), zpb->get_sub_zone());
        parambox<T2> pbres = parambox<T2>::intersection(this->get_sub_parambox(), zpb->get_sub_parambox());
        return std::make_shared<zone_parambox<T1,T2>>(zres, pbres);
    }
    virtual std::shared_ptr<gen_zone> right_conditional(const std::shared_ptr<gen_zone> &gz){
        std::shared_ptr<zone_parambox<T1,T2>> zpb = std::dynamic_pointer_cast<zone_parambox<T1,T2>>(gz);
        zone<T1> zres = zone<T1>::right_conditional(this->get_sub_zone(), zpb->get_sub_zone());
        parambox<T2> pbres = parambox<T2>::intersection(this->get_sub_parambox(), zpb->get_sub_parambox());
        return std::make_shared<zone_parambox<T1,T2>>(zres, pbres);
    }
#endif
    virtual bool is_nonempty(){
    	return ((this->get_sub_zone()).is_nonempty() and (this->get_sub_parambox()).is_nonempty());
    }
};

} // namespace paramtimedrel

#endif // PARAMTIMEDREL_ZONE_PARAMBOX_HPP