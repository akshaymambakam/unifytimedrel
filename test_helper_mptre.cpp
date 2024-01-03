#include <iostream>
#include "./paramtimedrel/algos_timed_relations.hpp"
#include "./paramtimedrel/zone_parambox.hpp"
#include "./paramtimedrel/utils.hpp"
#include "./paramtimedrel/helper_mptre.hpp"

using namespace std;

using namespace timedrel;

using namespace paramtimedrel;

int mfv = 1316134912; // TODO: fix this add maximum value of float

int main(int argc, char** argv){
    zone<int> zt = zone<int>::make_from({0,mfv,0,mfv,0,0},{1,1,1,1,1,1});
    cout<<zt<<endl;
    return 0;
}