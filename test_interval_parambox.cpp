#include <iostream>

#include "./paramtimedrel/interval_parambox.hpp"
#include "./paramtimedrel/utils.hpp"

using namespace std;

using namespace paramtimedrel;

int main(){
	timed_interval<int> ti0({0,1});
	timed_interval<int> ti1({1,2});
	cout<<ti1<<endl;
	pair<int,int> p0(1,2);
	pair<int,int> p1(0,1);
	parambox<int> pb0 = parambox<int>::make({0,0,0},{2,3,4});
	parambox<int> pb1 = parambox<int>::make({0,0,0},{1,2,3});
	interval_parambox<int,int> ipb0(ti0,pb0);
	cout<<ipb0<<endl;
	cout<<ipb0.get_sub_timed_interval()<<endl;
	cout<<ipb0.get_sub_parambox()<<endl;
	shared_ptr<compound_interval> ipbp0 = make_shared<interval_parambox<int,int>>(ti0,pb0);
	shared_ptr<compound_interval> ipbp1 = make_shared<interval_parambox<int,int>>(ti1,pb1);
	shared_ptr<compound_interval> ipbp2 = make_shared<interval_parambox<int,int>>(ti0,pb1);
	shared_ptr<gen_interval> tip0 = make_shared<timed_interval<int>>(p0);
	shared_ptr<gen_interval> tip1 = make_shared<timed_interval<int>>(p1);
	shared_ptr<gen_interval> tip3 = ipbp0->get_sub_interval_ptr();
	cout<<ipbp0->compare_less_compound_interval(ipbp1)<<endl;
	cout<<ipbp0->compare_less_begin_compound_interval(ipbp1)<<endl;
	cout<<ipbp1->begin_same_as_gen_interval(tip0)<<endl;
	cout<<ipbp1->end_same_as_gen_interval(tip0)<<endl;
	cout<<ipbp0->begin_less_gen_interval(tip0)<<endl;
	cout<<ipbp0->end_less_gen_interval(tip0)<<endl;
	cout<<ipbp1->begin_same_as_end_gen_interval(tip1)<<endl;
	cout<<ipbp0->begin_less_than_end_gen_interval(tip1)<<endl;
	cout<<ipbp1->matches_gen_interval(tip0)<<endl;
	cout<<*dynamic_pointer_cast<timed_interval<int>>(tip3)<<endl;
	cout<<ipbp0->includes(ipbp2)<<endl;
	cout<<*dynamic_pointer_cast<interval_parambox<int,int>>(ipbp2->clone())<<endl;
	cout<<*dynamic_pointer_cast<interval_parambox<int,int>>(ipbp0->intersection(ipbp2))<<endl;
	cout<<*dynamic_pointer_cast<interval_parambox<int,int>>(ipbp0->concatenation(ipbp1))<<endl;
	cout<<ipbp0->is_nonempty()<<endl;
	return 0;
}