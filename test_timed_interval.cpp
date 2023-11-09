#include <iostream>

#include "./paramtimedrel/timed_interval.hpp"
#include "./paramtimedrel/utils.hpp"

using namespace std;

using namespace paramtimedrel;

int main(){
	pair<float,float> pr1(1,2);
	auto pr2 = pr1;
	timed_interval<float> ti0({0,0});
	timed_interval<float> ti1(pr1);
	timed_interval<float> ti2(pr2);
	timed_interval<float> ti3 = timed_interval<float>::make(1,1);
	cout<<ti3<<endl;
	cout<<(ti1==ti2)<<endl;
	pair<float,float> prtest = ti2.get_time_interval_as_pair();
	cout<<prtest.first<<","<<prtest.second<<endl;
	cout<<ti2.get_start_time_interval()<<endl;
	cout<<ti2.get_end_time_interval()<<endl;
	cout<<ti2.is_nonempty()<<endl;
	return 0;
}