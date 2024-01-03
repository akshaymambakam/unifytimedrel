#include <iostream>
#include "./paramtimedrel/zone_parambox.hpp"
#include "./paramtimedrel/utils.hpp"

using namespace std;

using namespace timedrel;

using namespace paramtimedrel;

int main(){
    auto z1 = zone<int>::make({1,2,3,4,0,3});
    cout<<z1<<endl;
    auto pb1 = parambox<float>::make({1,2,3},{5,6,7});
    cout<<pb1<<endl;
    
    auto zpb1 = zone_parambox<int,float>(z1, pb1);
    cout<<zpb1<<endl;
    auto zpb2 = zpb1;
    shared_ptr<gen_zone> pzpb2 = zpb2.clone();
    cout<<zpb1.includes(pzpb2)<<endl;

    auto fz1 = zone<float>::make({1.1,2.1,3.1,4.1,0,3.1});
    cout<<fz1<<endl;
    auto fpb1 = parambox<float>::make({1,2,3},{5,6,7});
    cout<<fpb1<<endl;

    auto fzpb1 = zone_parambox<float,float>(fz1, fpb1);
    cout<<fzpb1<<endl;
    auto fzpb2 = fzpb1;
    shared_ptr<gen_zone> fpzpb2 = fzpb2.clone();
    cout<<fzpb1.includes(fpzpb2)<<endl;


    return 0;
}