#ifndef IDED_ZONE_HPP
#define IDED_ZONE_HPP 1

#define NUM_TRIES (1000000)

#include <cassert>
#include <bits/stdc++.h>
#include <utility>
#include "gen_zone.hpp"
#include "./timedrel/include/timedrel/utils.hpp"
#include "./timedrel/include/timedrel/zone.hpp"

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace timedrel;

template <class T>
class ided_zone: public gen_zone{
    int myid;
    vector<int> chids;
    zone<T> myzone = zone<T>::make({0,0,0,0,0,0});
  public:
  	ided_zone(zone<T> &mz, int inmyid, int inchid1, int inchid2){
  	    this->myzone = mz;
  		this->myid   = inmyid;
        (this->chids).push_back(inchid1);
        (this->chids).push_back(inchid2);
  	}
    ided_zone(zone<T> &mz, int inmyid, vector<int> chids){
        this->myzone = mz;
        this->myid = inmyid;
        this->set_chids(chids);
    }
    const vector<int> get_chids() const{
        return this->chids;
    }
    void set_chids(vector<int> inchids){
        this->chids = inchids;
    }
  	void set_myid(int inid){
  		myid = inid;
  	}
  	zone<T> get_myzone() const {
  	    return myzone;
  	}
  	int get_myid() const {
  		return myid;
  	}
  	virtual bool compare_less_bmin(const shared_ptr<gen_zone> &c){
  	    shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(c);
        return myzone.get_bmin() < (iz->get_myzone()).get_bmin();
    }
    virtual bool compare_less_emin(const shared_ptr<gen_zone> &c){
    	shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(c);
        return myzone.get_emin() < (iz->get_myzone()).get_emin();
    }
    virtual bool compare_less_bmax_bmin(const shared_ptr<gen_zone> &c){
    	shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(c);
        return myzone.get_bmax() < (iz->get_myzone()).get_bmin();
    }
    virtual bool compare_less_emin_bmin(const shared_ptr<gen_zone> &c){
    	shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(c);
        return myzone.get_emin() < (iz->get_myzone()).get_bmin();
    }
    virtual bool compare_less_bmax_emin(const shared_ptr<gen_zone> &c){
        shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(c);
        return myzone.get_bmax() < (iz->get_myzone()).get_emin();   
    }
    virtual bool compare_less_emax_bmin(const shared_ptr<gen_zone> &c){
        shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(c);
        return myzone.get_emax() < (iz->get_myzone()).get_bmin();
    }
    virtual bool compare_less_bmin_bmax(const shared_ptr<gen_zone> &c){
        shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(c);
        return myzone.get_bmin() < (iz->get_myzone()).get_bmax();   
    }
    virtual bool includes(const shared_ptr<gen_zone> &c){
    	shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(c);
        return zone<T>::includes(myzone, iz->get_myzone());
    }
    virtual shared_ptr<gen_zone> clone(){
        return make_shared<ided_zone<T>>(myzone, myid, chids);
    }
    virtual shared_ptr<gen_zone> intersection(const shared_ptr<gen_zone> &gz){
    	shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(gz);
    	zone<T> izres = zone<T>::intersection(this->get_myzone(), iz->get_myzone());
    	// Put the invalid -1 for myid
    	return make_shared<ided_zone<T>>(izres, -1, this->get_myid(), iz->get_myid());
    }
    virtual shared_ptr<gen_zone> concatenation(const shared_ptr<gen_zone> &gz){
        shared_ptr<ided_zone<T>> iz = dynamic_pointer_cast<ided_zone<T>>(gz);
        zone<T> izres = zone<T>::concatenation(this->get_myzone(), iz->get_myzone());
        // Put the invalid -1 for myid
        vector<int> reschids1 = this->get_chids();
        vector<int> reschids2 = iz->get_chids();
        reschids1.insert(reschids1.end(), reschids2.begin(), reschids2.end() );
        return make_shared<ided_zone<T>>(izres, -1, reschids1);
    }
    virtual bool is_nonempty(){
    	return (this->get_myzone()).is_nonempty();
    }
};

template <class T>
inline std::ostream& operator<<(
    std::ostream &os, const ided_zone<T> &z){
	cout<<"("<<z.get_myzone()<<")-->";
	cout<<"("<<z.get_myid()<<")-->(";
    vector<int> chvec = z.get_chids();
    for(int i=0; i < chvec.size(); i++){
        if(not (i == (chvec.size()-1) ) ){
            cout<<chvec[i]<<",";    
        }else{
            cout<<chvec[i];
        }
        
    }
    cout<<")";
    return os;
}

// Check if interval is in zone.
template <class T>
bool zone_contains_interval(zone<T> &z, T t1, T t2){
    auto t1_t2 = zone<T>::make({t1,t1,t2,t2,t2-t1,t2-t1},{1,1,1,1,1,1});
    return zone<T>::includes(z, t1_t2);
}

// Intended to work for only float, double and mpq_class (rationals).
// Get interior point of zone.
template <class T>
pair<T,T> zone_interior_point(zone<T> &z){
    assertm((std::is_same<float, T>::value or
            std::is_same<double, T>::value or 
            std::is_same<mpq_class, T>::value)
            , "Type not supported (only float, double and rationals supported).");
    srand(time(0));
    for(int i=0;i < NUM_TRIES; i++){
        // Code repetition avoidable?
        if(is_same<mpq_class,T>::value){
            double dr1 = (double)(rand()) / (double)(RAND_MAX);
            double dr2 = (double)(rand()) / (double)(RAND_MAX);
            auto r1 = mpq_class(dr1);
            auto r2 = mpq_class(dr2);
            auto lb = z.get_bmin().value + r1 * (z.get_bmax().value-z.get_bmin().value);
            auto ub = z.get_emin().value + r2 * (z.get_emax().value-z.get_emin().value);
            if(zone_contains_interval(z, lb, ub)){
                return pair<T,T>(lb, ub);
            }
        }else if(is_same<float,T>::value or is_same<double,T>::value){
            auto r1 = (T)(rand()) / (T)(RAND_MAX);
            auto r2 = (T)(rand()) / (T)(RAND_MAX);
            auto lb = z.get_bmin().value + r1 * (z.get_bmax().value-z.get_bmin().value);
            auto ub = z.get_emin().value + r2 * (z.get_emax().value-z.get_emin().value);
            if(zone_contains_interval(z, lb, ub)){
                return pair<T,T>(lb, ub);
            }
        }
    }
    // If we can't find an interior point return an invalid point.
    return pair<T,T>(-1,-1);
}

// Intended to work for only float, double and mpq_class (rationals).
// Find t2 such that (t1,t2) in z1 and (t2,t3) in z2 and (t1, t3) in zres.
template <class T>
T infer_seq_comp(zone<T> &zres, zone<T> &z1, zone<T> &z2, 
    pair<T,T> &inival){
    assertm((std::is_same<float, T>::value or
            std::is_same<double, T>::value or 
            std::is_same<mpq_class, T>::value)
            , "Type not supported (only float, double and rationals supported).");
    T t1 = inival.first;
    T t3 = inival.second;
    // TODO: Check if (t1,t3) in zres
    auto t1_t3 = zone<T>::make({t1,t1,t3,t3,t3-t1,t3-t1},{1,1,1,1,1,1});
    assertm(zone<T>::includes(zres, t1_t3), "Point not in the zone!");

    // TODO: This might be violated due to floating point imprecision
    if(std::is_same<mpq_class, T>::value){
        assertm(zres==zone<T>::concatenation(z1, z2), "Inconsistency infer seq comp!");    
    }

    // Find upper bound on t2
    auto c2 =    z1.get_emax();
    auto cp1 =   z2.get_bmax();

    auto ubc3 =  z1.get_dmax();
    auto ubt1 =  timedrel::upper_bound<T>(t1, 1);
    auto ubr3 =  timedrel::upper_bound<T>::add(ubc3, ubt1);

    auto ubcp4 = timedrel::upper_bound<T>(z2.get_dmin().value, 
                 z2.get_dmin().sign);
    auto ubt3 =  timedrel::upper_bound<T>(t3, 1);
    auto ubr4 =  timedrel::upper_bound<T>::add(ubcp4, ubt3);
    
    auto uba =   timedrel::upper_bound<T>::intersection(c2, cp1);
    auto ubb =   timedrel::upper_bound<T>::intersection(ubr3, ubr4);

    auto ubt2 =  timedrel::upper_bound<T>::intersection(uba, ubb);

    // Find lower bound on t2
    auto c5 =    z1.get_emin();
    auto cp6 =   z2.get_bmin();

    auto lbc4 =  z1.get_dmin();
    auto lbt1 =  timedrel::lower_bound<T>(t1, 1);
    auto lbr3 =  timedrel::lower_bound<T>::add(lbc4, lbt1);

    auto lbcp3 = timedrel::lower_bound<T>(z2.get_dmax().value, 
                 z2.get_dmax().sign);
    auto lbt3 =  timedrel::lower_bound<T>(t3, 1);
    auto lbr4 =  timedrel::lower_bound<T>::add(lbcp3, lbt3);
    
    auto lba =   timedrel::lower_bound<T>::intersection(c5, cp6);
    auto lbb =   timedrel::lower_bound<T>::intersection(lbr3, lbr4);

    auto lbt2  = timedrel::lower_bound<T>::intersection(lba, lbb);

    // Return the mean of lower and upper bounds
    return (lbt3.value+ubt3.value)/2;
}

template <class T>
vector<pair<T,T>> infer_mult_seq_comp(zone<T> &res, 
    vector<zone<T>> &zlist, pair<T,T> &inival){
    assertm((std::is_same<float, T>::value or
            std::is_same<double, T>::value or 
            std::is_same<mpq_class, T>::value)
            , "Type not supported (only float, double and rationals supported).");
    T lb = inival.first;
    T ub = inival.second;

    // Check inclusion of (lb,ub) in res
    auto lb_ub = zone<T>::make({lb,lb,ub,ub,ub-lb,ub-lb},{1,1,1,1,1,1});
    assertm(zone<T>::includes(res, lb_ub), "Point not in the zone!");

    vector<pair<T,T>> ival_res(zlist.size(),{-1,-1});

    // Initialize accumulation vector
    auto tz = zone<T>::make({0,0,0,0,0});
    vector<zone<T>> seq_comp_acc(zlist.size(),tz);

    if(zlist.size()==0){
        return ival_res;
    }

    // Populate accumulation vector
    auto temp_acc = zlist[1];
    for(int i = 0; i < zlist.size(); i++){
        if(i == 0){
            seq_comp_acc[i] = temp_acc;
        }else{
            temp_acc = zone<T>::concatenation(temp_acc, zlist[i]);
            seq_comp_acc[i] = temp_acc;
        }
    }

    // Check if the zones indeed lead to the result.
    // TODO: This might be violated due to floating point imprecision.
    if(std::is_same<mpq_class, T>::value){
        assertm(res == seq_comp_acc.back(),
            "Sequential composition of zones doesn't produce the result!");    
    }
    

    int j = zlist.size()-1;
    pair<T,T> temp_ival = inival;
    while(j >= 1){
        zone<T> tzres = seq_comp_acc[j]; 
        zone<T> tz1 = seq_comp_acc[j-1];
        zone<T> tz2  = zlist[j];
        T tmid = infer_seq_comp(tzres, tz1, tz2, temp_ival);
        ival_res[j] = {tmid, temp_ival.second};
        temp_ival.second = tmid;

        j--;
    }
    ival_res[0] = temp_ival;
    return ival_res;
}

#endif