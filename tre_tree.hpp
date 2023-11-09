#ifndef TRE_TREE_HPP
#define TRE_TREE_HPP 1

#include "ided_zone.hpp"

// TODO: ided_zone has a template T
class tre_tree{
	public:
		vector<ided_zone> zlist;
		shared_ptr<tre_tree> ch1 = nullptr;
		shared_ptr<tre_tree> ch2 = nullptr;
		tre_tree(){}
        tre_tree(const vector<ided_zone> &izlist, 
			const shared_ptr<tre_tree> &ich1, const shared_ptr<tre_tree> &ich2){
            this->zlist = izlist;
            this->ch1   = ich1;
            this->ch2   = ich2;
		}
};

#endif