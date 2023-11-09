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
    return 0;
}