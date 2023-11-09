#include <gmp.h>
#include <gmpxx.h>
#include <type_traits>
#include <iostream>
#include "generic_trel.hpp"
#include "./timedrel/include/timedrel/zone_set.hpp"
#include "./timedrel/include/timedrel/utils.hpp"
#include "ided_zone.hpp"
// #include "tre_tree.hpp"

using namespace std;

using namespace timedrel;

int main(){
    /*
    mpq_class rat1(1,2), rat2(1,3), rat3(1,4), rat4(20,100), rat5(44,100), rat6(1,8);
    mpq_class ratinfinity(numeric_limits<double>::max());
    mpq_class ratminusinfinity(-numeric_limits<double>::max());
    float ft = 0.01;
    auto r1, r2;
    if(1){
        r1 = 0.01;
    }
    cout<<"testrat:"<<mpq_class(ft)<<endl;
    exit(0);
    zone<mpq_class> zsum = zone<mpq_class>::make({rat1,rat2,rat3,rat4,rat5,rat6});
    */
    auto zl1 = zone_set<float>();
    auto zl2 = zone_set<float>();
    auto zl3 = zone_set<float>();

    zl1.add_from_period(1,3);
    zl2.add_from_period(2,4);
    zl3.add_from_period(2.5,6);
    auto zrt = zone_set<float>::set_union(zl3,zl2);
    auto zr  = zone_set<float>::set_union(zrt, zl1);
    auto ztc = zone_set<float>::transitive_closure(zr);
    cout<<"In transitive closure"<<endl;
    cout<<zr<<endl;
    cout<<"Out transitive closure"<<endl;
    cout<<ztc<<endl;
    vector<shared_ptr<ided_zone<float>>> ingen;
    int i = 0;
    for(auto zn : zr){
        vector<int> vt = {i};
        ingen.push_back(make_shared<ided_zone<float>>(zn, -1, vt));
        i++;
    }
    vector<shared_ptr<gen_zone>> gzt;
    for(auto gz : ingen){
        gzt.push_back(gz);
    }
    vector<shared_ptr<gen_zone>> gres = gen_transitive_closure(gzt);
    for(auto a: gres){
        vector<int> tchids = (dynamic_pointer_cast<ided_zone<float>>(a))->get_chids();
        cout<<*dynamic_pointer_cast<ided_zone<float>>(a)<<endl;
        auto tz = zone<float>::make({0,0,0,0,0});
        for(int i=0; i < tchids.size(); i++){
            auto it1 = zr.cbegin();
            if(i == 0){
                tz = *(it1+tchids[i]);
            }else{
                tz = zone<float>::concatenation(tz, *(it1+tchids[i]));
            }
        }
        cout<<tz<<endl;
        cout<<"*****************"<<endl;
    }
    /*
    // tre_tree trea;
	zone<float> za = zone<float>::make_from_period(5,5.5);
	zone<float> zb = zone<float>::make_from_period(5.1,5.2);
	zone<float> zc = zone<float>::make_from_period(10,10.5);
	zone<float> zd = zone<float>::make_from_period(10.1,10.2);

    /*
    shared_ptr<ided_zone> A = make_shared<ided_zone>(za, 1, 10, 20);
	shared_ptr<ided_zone> B = make_shared<ided_zone>(zb, 2, 11, 21);
	shared_ptr<ided_zone> C = make_shared<ided_zone>(zc, 3, 12, 22);
	shared_ptr<ided_zone> D = make_shared<ided_zone>(zd, 4, 13, 23);
	vector<shared_ptr<gen_zone>> gz = {A,B,C,D};
    vector<shared_ptr<gen_zone>> gempty;

    /*
	vector<shared_ptr<gen_zone>> gres = gen_filter(gz);
	for(int i=0; i<gres.size(); i++){
		dynamic_pointer_cast<ided_zone>(gres[i])->set_myid(i);
	}
	for(auto a: gres){
		cout<<*dynamic_pointer_cast<ided_zone>(a)<<endl;
	}
    cout<<"zone_includes:"<<zone<float>::includes(zb, za)<<endl;
    cout<<"gen_fr:"<<gen_includes(gres, gempty)<<endl;

    // Test copy of ided_zone
    // vector<ided_zone> list1 = {*A,*B,*C,*D};
    auto newlist = list1;
    */
    /*
    for(auto z : newlist){
        cout<<z<<endl;
    }
    */
	return 0;
}