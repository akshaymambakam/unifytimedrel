#include <iostream>
#include <gmp.h>
#include <gmpxx.h>


using namespace std;

int compare_func(mpq_class a, mpq_class b){
	return a < b;
}

int main(){
	cout<<compare_func(1,2)<<endl;
	return 0;
}