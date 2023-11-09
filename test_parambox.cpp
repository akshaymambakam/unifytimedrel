#include <iostream>
#include "./paramtimedrel/parambox.hpp"
#include "./paramtimedrel/utils.hpp"

using namespace std;

using namespace paramtimedrel;

int main(){
    auto pb1 = parambox<float>::make({1,2,3},{5,6,7});
    cout<<pb1<<endl;
    auto pb2 = parambox<float>::make_from({1,2,3},{5,6,7},{true,true,true},{true,true,true});
    cout<<pb2<<endl;
    cout<<(pb1==pb2)<<endl;
    cout<<pb1.num_of_params()<<endl;
    float f = 1.5;
    auto pb3 = parambox<float>::add_lower_bound_on_parameter(pb1, f, 1, 0);
    cout<<pb3<<endl;
    auto pb4 = parambox<float>::add_upper_bound_on_parameter(pb1, f, 0, 0);
    cout<<pb4<<endl;
    cout<<parambox<float>::includes(pb1,pb3)<<endl;
    cout<<parambox<float>::includes(pb1,pb4)<<endl;
    auto pb5 = parambox<float>::intersection(pb3,pb4);
    cout<<pb5<<endl;
    cout<<pb5.is_nonempty()<<endl;
	return 0;
}