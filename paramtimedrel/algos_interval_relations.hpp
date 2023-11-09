#include <vector>
#include <algorithm>

// For debug:
#include <iostream>
#include <utility>
#include <memory>
// end debug:

#include "gen_interval.hpp"
#include "compound_interval.hpp"

#ifndef ALGOS_INTERVAL_RELATIONS_HPP
#define ALGOS_INTERVAL_RELATIONS_HPP 1

namespace paramtimedrel {

struct {
    bool operator()(std::shared_ptr<compound_interval> &a,
        std::shared_ptr<compound_interval> &b) const
    {
        return a->compare_less_compound_interval(b);
    }
}compare_interval;

struct {
    bool operator()(std::shared_ptr<compound_interval> &a,
        std::shared_ptr<compound_interval> &b) const
    {   
        return a->compare_less_begin_compound_interval(b);
    }  
}compare_interval_begin;


std::vector<std::shared_ptr<compound_interval>> union_interval_relations(
    std::vector<std::shared_ptr<compound_interval>> civ1,
    std::vector<std::shared_ptr<compound_interval>> civ2){

    civ1.insert(civ1.end(), civ2.begin(), civ2.end());

    return civ1;
}


// TODO: Comparison cases can be simplified if compare_less_compound_interval is used
int find_interval_match(std::vector<std::shared_ptr<compound_interval>> &civ, int start, int finish,
    std::shared_ptr<gen_interval> c){
    while(start<=finish){
        int mid = (start+finish)/2;
        if(civ[mid]->matches_gen_interval(c)){
            return mid;
        }else if(civ[mid]->begin_less_gen_interval(c)){
            start = mid+1;
        }else if(civ[mid]->begin_same_as_gen_interval(c)){
            if(civ[mid]->end_less_gen_interval(c)){
                start = mid+1;
            }else{
                finish = mid-1;
            }
        }else{
            finish = mid-1;
        }
    }
    return -1;
}

std::vector<std::shared_ptr<compound_interval>> intersection_interval_relations(
    std::vector<std::shared_ptr<compound_interval>> &civ1,
    std::vector<std::shared_ptr<compound_interval>> &civ2){

    std::sort(civ2.begin(), civ2.end(), compare_interval);
    std::vector<std::shared_ptr<compound_interval>> civres;
    for(int i=0;i<civ1.size();i++){
        std::shared_ptr<gen_interval> gitemp = civ1[i]->get_sub_interval_ptr();
        int i2 = find_interval_match(civ2, 0, civ2.size()-1, gitemp);
        if(i2!=-1){
            int j=i2;
            while( (j < civ2.size()) and civ2[j]->matches_gen_interval(gitemp)){
                std::shared_ptr<compound_interval> citemp = civ1[i]->intersection(civ2[j]);
                if(citemp->is_nonempty()){
                    civres.push_back(citemp);
                }
                j++;
            }
            j = i2-1;
            while( (j>=0) and civ2[j]->matches_gen_interval(gitemp)){
                std::shared_ptr<compound_interval> citemp = civ1[i]->intersection(civ2[j]);
                if(citemp->is_nonempty()){
                    civres.push_back(citemp);
                }
                j--;
            }
        }
    }
    return civres;
}

int find_interval_concatenation_match(std::vector<std::shared_ptr<compound_interval>> &civ, 
    int start, int finish, std::shared_ptr<gen_interval> c){
    
    while(start<=finish){
        int mid = (start+finish)/2;
        if(civ[mid]->begin_same_as_end_gen_interval(c)){
            return mid;
        }else if(civ[mid]->begin_less_than_end_gen_interval(c)){
            start = mid+1;
        }else{
            finish = mid-1;
        }
    }
    return -1;
}

std::vector<std::shared_ptr<compound_interval>> concatenation_interval_relations(
    std::vector<std::shared_ptr<compound_interval>> &civ1, 
    std::vector<std::shared_ptr<compound_interval>> &civ2){
    
    std::sort(civ2.begin(), civ2.end(), compare_interval_begin);
    
    std::vector<std::shared_ptr<compound_interval>> civres;
    for(int i=0;i<civ1.size();i++){
        std::shared_ptr<gen_interval> gitemp = civ1[i]->get_sub_interval_ptr();
        int i2 = find_interval_concatenation_match(civ2, 0, civ2.size()-1, gitemp);
        if(i2!=-1){
            int j = i2;
            while( (j < civ2.size()) and civ2[j]->begin_same_as_end_gen_interval(gitemp)){
                std::shared_ptr<compound_interval> citemp = civ1[i]->concatenation(civ2[j]);
                if(citemp->is_nonempty()){
                    civres.push_back(citemp);
                }
                j++;
            }
            j = i2-1;
            while( (j>=0) && civ2[j]->begin_same_as_end_gen_interval(gitemp)){
                std::shared_ptr<compound_interval> citemp = civ1[i]->concatenation(civ2[j]);
                if(citemp->is_nonempty()){
                    civres.push_back(citemp);
                }
                j--;
            }
        }
    }
    return civres;
}

int contained_interval_relations(std::vector<std::shared_ptr<compound_interval>> &civnew,
    std::vector<std::shared_ptr<compound_interval>> &civold){
    
    int all_contained = 1;
    for(int i=0;i<civnew.size();i++){
        int contained = 0;  
        for(int j=0;j<civold.size();j++){
            contained = (contained || civold[j]->includes(civnew[i]));
        }
        all_contained = (all_contained && contained);
    }
    return all_contained;
}

std::vector<std::shared_ptr<compound_interval>> kleene_plus_interval_relations(
    std::vector<std::shared_ptr<compound_interval>> &civr){
    
    std::vector<std::shared_ptr<compound_interval>> civq,civp;
    civq = civr;
    civp = concatenation_interval_relations(civr, civr);
    int count = 0;
    while(not contained_interval_relations(civp, civq)){
        civq = union_interval_relations(
            union_interval_relations(civp,civq),
            concatenation_interval_relations(civp,civq));
        civp = concatenation_interval_relations(civp,civp);
        std::cout<<"1,2:"<<civp.size()<<","<<civq.size()<<std::endl;
        count++;
    }
    std::cout<<"Kleene count:"<<count<<std::endl;
    return civq;
}


} // namespace paramtimedrel

#endif // PARAMTIMEDREL_ALGOS_INTERVAL_RELATIONS_HPP