#include <vector>
#include <algorithm>

#include "gen_zone.hpp"

#ifndef ALGOS_TIMED_RELATIONS_HPP
#define ALGOS_TIMED_RELATIONS_HPP 1

namespace paramtimedrel {

struct earlier_bmin {
    inline bool operator() (std::shared_ptr<gen_zone> &z1, std::shared_ptr<gen_zone> &z2){
        return z1->compare_less_bmin(z2);
    }
};

struct earlier_emin {
    inline bool operator() (std::shared_ptr<gen_zone> &z1, std::shared_ptr<gen_zone> &z2){
        return z1->compare_less_emin(z2);
    }
};

static std::vector<std::shared_ptr<gen_zone>> gen_filter(const std::vector<std::shared_ptr<gen_zone>> &zs){

    std::vector<std::shared_ptr<gen_zone>> active, active_temp;
    std::vector<std::shared_ptr<gen_zone>> result;

    for(auto z1it = zs.cbegin(); z1it != zs.cend(); z1it++){

        bool already_included = std::any_of(active.begin(), active.end(), 
            [z1it](std::shared_ptr<gen_zone> &z2){return z2->includes(*z1it);});

        if(!already_included){

            active.erase( std::remove_if(active.begin(), active.end(), 
                [z1it](std::shared_ptr<gen_zone> &z2){return (*z1it)->includes(z2);}), active.end());
            active.push_back(*z1it);

            active_temp.clear();
            for(const auto& z2 : active){
                if(z2->compare_less_bmax_bmin(*z1it)){
                    result.push_back(z2->clone());
                } else {
                    active_temp.push_back(z2);
                }
            }
            active = active_temp;
        }
    }
    for(const auto& z2 : active){
        result.push_back(z2->clone());
    }

    std::sort(result.begin(), result.end(), earlier_bmin());

    return result;
}


static bool gen_includes(const std::vector<std::shared_ptr<gen_zone>> &zs1, const std::vector<std::shared_ptr<gen_zone>> &zs2){

    // std::sort(zs1.begin(), zs1.end(), earlier_bmin<value_type>());
    // std::sort(zs2.begin(), zs2.end(), earlier_bmin<value_type>());

    if(zs2.empty()){
        return true;
    } else if(zs1.empty()){
        return false;
    }

    std::vector<std::shared_ptr<gen_zone>> act_1;

    auto it1 = zs1.cbegin();
    auto it2 = zs2.cbegin();

    while(it1 != zs1.cend() and it2 != zs2.cend()) {

        if ((*it1)->compare_less_bmin_bmax(*it2)){ //  z1.bmin < z2.bmax
            act_1.push_back(*it1);
            it1++;
        } else {
            act_1.erase( std::remove_if(act_1.begin(), act_1.end(), 
            [&](std::shared_ptr<gen_zone> z1){return z1->compare_less_bmax_bmin(*it2);}), act_1.end()); // remove if z1.bmax < z2.bmin
            bool z2_incd = std::any_of(act_1.begin(), act_1.end(), 
                [&](std::shared_ptr<gen_zone> z1){return z1->includes(*it2);});
            if(!z2_incd){
                return false;
            }
            it2++;
        }
    }
    while (it2 != zs2.cend() and not act_1.empty()) {
        act_1.erase( std::remove_if(act_1.begin(), act_1.end(), 
        [&](std::shared_ptr<gen_zone> z1){return z1->compare_less_bmax_bmin(*it2);}), act_1.end()); // remove if z1.bmax < z2.bmin
        bool z2_incd = std::any_of(act_1.begin(), act_1.end(), 
            [&](std::shared_ptr<gen_zone> z1){return z1->includes(*it2);});
        if(!z2_incd){
            return false;
        }
        it2++;
    }
    return true;
}


static std::vector<std::shared_ptr<gen_zone>> gen_intersection(const std::vector<std::shared_ptr<gen_zone>> &zs1,
    const std::vector<std::shared_ptr<gen_zone>> &zs2){

    std::vector<std::shared_ptr<gen_zone>> result;

    std::vector<std::shared_ptr<gen_zone>> act_1, act_2, act_r, act_r_temp;

    // std::sort(zs1.begin(), zs1.end(), earlier_bmin<value_type>());
    // std::sort(zs2.begin(), zs2.end(), earlier_bmin<value_type>());

    auto it1 = zs1.cbegin();
    auto it2 = zs2.cbegin();

    while(it1 != zs1.cend() and it2 != zs2.cend()) {


        if ((*it1)->compare_less_bmin(*it2)){
            act_1.push_back(*it1);
            act_2.erase(std::remove_if(act_2.begin(), act_2.end(), 
                [&](std::shared_ptr<gen_zone> z2){return z2->compare_less_bmax_bmin(*it1);}), act_2.end());

            for(const auto& z2 : act_2){
                // result.add( zone_type::intersection(*it1, z2));

                auto kid = (*it1)->intersection(z2);

                if( kid->is_nonempty() and 
                    !std::any_of(act_r.begin(), act_r.end(), 
                        [&kid](std::shared_ptr<gen_zone> &zr){return zr->includes(kid);} ))
                {
                    act_r.erase( std::remove_if(act_r.begin(), act_r.end(), 
                        [&kid](std::shared_ptr<gen_zone> &zr){return kid->includes(zr);}), act_r.end());
                    act_r.push_back(kid);

                    act_r_temp.clear();
                    for(auto zr : act_r){
                        if(zr->compare_less_bmax_bmin(*it1)){
                            result.push_back(zr->clone());
                        }
                        else {
                            act_r_temp.push_back(zr);
                        }
                    }
                    act_r = act_r_temp;
                }
            }

            it1++;

        } else {

            act_2.push_back(*it2);
            act_1.erase(std::remove_if(act_1.begin(), act_1.end(), 
                [&](std::shared_ptr<gen_zone> z1){return z1->compare_less_bmax_bmin(*it2);}), act_1.end()); // remove if z1.emax < z2.bmin

            for(const auto& z1 : act_1){
                // result.add( zone_type::intersection(z1, *it2));

                auto kid = z1->intersection(*it2);

                if( kid->is_nonempty() and 
                    !std::any_of(act_r.begin(), act_r.end(), 
                        [&kid](std::shared_ptr<gen_zone> &zr){return zr->includes(kid);}))
                {
                    act_r.erase( std::remove_if(act_r.begin(), act_r.end(), 
                        [&kid](std::shared_ptr<gen_zone> &zr){return kid->includes(zr);}), act_r.end());
                    act_r.push_back(kid);

                    act_r_temp.clear();
                    for(auto zr : act_r){
                        if(zr->compare_less_bmax_bmin(*it2)){
                            result.push_back(zr->clone());
                        }
                        else {
                            act_r_temp.push_back(zr);
                        }
                    }
                    act_r = act_r_temp;
                }
            }

            it2++;
        }
    }

    /// Processing left-overs (if zs1 remains)
    while(it1 != zs1.cend()){
        act_2.erase(std::remove_if(act_2.begin(), act_2.end(), 
            [&](std::shared_ptr<gen_zone> z2){return z2->compare_less_bmax_bmin(*it1);}), act_2.end());

        for(const auto& z2 : act_2){
            auto kid = (*it1)->intersection(z2);

            if( kid->is_nonempty() and 
                !std::any_of(act_r.begin(), act_r.end(), 
                    [&kid](std::shared_ptr<gen_zone> &zr){return zr->includes(kid);}))
            {
                act_r.erase( std::remove_if(act_r.begin(), act_r.end(), 
                    [&kid](std::shared_ptr<gen_zone> &zr){return kid->includes(zr);}), act_r.end());
                act_r.push_back(kid);

                act_r_temp.clear();
                for(const auto& zr : act_r){
                    if( zr->compare_less_bmax_bmin(*it1)){
                        result.push_back(zr->clone());
                    }
                    else {
                        act_r_temp.push_back(zr);
                    }
                }
                // std::cout << result.size() << std::endl;

                act_r = act_r_temp;
            }
        }
        it1++;
    }



    /// Processing left-overs (if zs2 remains)
    while(it2 != zs2.cend()){
        act_1.erase(std::remove_if(act_1.begin(), act_1.end(), 
            [&](std::shared_ptr<gen_zone> z1){return z1->compare_less_bmax_bmin(*it2);}), act_1.end()); // remove if z1.emax < z2.bmin

        for(const auto& z1 : act_1){
            auto kid = z1->intersection(*it2);

            if( kid->is_nonempty() and 
                !std::any_of(act_r.begin(), act_r.end(), 
                    [&kid](std::shared_ptr<gen_zone> &zr){return zr->includes(kid);}))
            {
                act_r.erase( std::remove_if(act_r.begin(), act_r.end(), 
                    [&kid](std::shared_ptr<gen_zone> &zr){return kid->includes(zr);}), act_r.end());
                act_r.push_back(kid);

                act_r_temp.clear();
                for(const auto& zr : act_r){
                    if(zr->compare_less_bmax_bmin(*it2)){
                        result.push_back(zr->clone());
                    }
                    else {
                        act_r_temp.push_back(zr);
                    }
                }
                act_r = act_r_temp;
            }
        }
        it2++;
    }
    for(const auto& zr : act_r){
        result.push_back(zr->clone());
    }

    std::sort(result.begin(), result.end(), earlier_bmin());
    return result;
}


static std::vector<std::shared_ptr<gen_zone>> gen_concatenation(const std::vector<std::shared_ptr<gen_zone>> &_zs1, 
    const std::vector<std::shared_ptr<gen_zone>> &zs2){

    std::vector<std::shared_ptr<gen_zone>> result;

    std::vector<std::shared_ptr<gen_zone>> act_1, act_2, act_r, act_r_temp;

    // Could be better?
    std::vector<std::shared_ptr<gen_zone>> zs1;
    for(auto zs1t : _zs1){
        zs1.push_back(zs1t->clone());
    }    

    std::sort(zs1.begin(), zs1.end(), earlier_emin());
    // std::sort(zs2.begin(), zs2.end(), earlier_bmin<value_type>());

    auto it1 = zs1.cbegin();
    auto it2 = zs2.cbegin();

    while(it1 != zs1.cend() and it2 != zs2.cend()) {

        if ((*it1)->compare_less_emin_bmin(*it2)){
            act_1.push_back(*it1);
            act_2.erase(std::remove_if(act_2.begin(), act_2.end(), 
                [&](std::shared_ptr<gen_zone> z2){return z2->compare_less_bmax_emin(*it1);}), act_2.end());

            for(const auto& z2 : act_2){
                // result.add( zone_type::concatenation(*it1, z2));

                auto kid = (*it1)->concatenation(z2);

                if( kid->is_nonempty() and 
                    !std::any_of(act_r.begin(), act_r.end(), 
                        [&kid](std::shared_ptr<gen_zone> &zr){return zr->includes(kid);}))
                {
                    act_r.erase( std::remove_if(act_r.begin(), act_r.end(), 
                        [&kid](std::shared_ptr<gen_zone> &zr){return kid->includes(zr);}), act_r.end());
                    act_r.push_back(kid);

                    act_r_temp.clear();
                    for(auto zr : act_r){
                        if(zr->compare_less_bmax_bmin(*it1)){
                            result.push_back(zr->clone());
                        }
                        else {
                            act_r_temp.push_back(zr);
                        }
                    }
                    act_r = act_r_temp;
                }
            }

            it1++;

        } else {

            act_2.push_back(*it2);
            act_1.erase(std::remove_if(act_1.begin(), act_1.end(), 
                [&](std::shared_ptr<gen_zone> z1){return z1->compare_less_emax_bmin(*it2);}), act_1.end()); // remove if z1.emax < z2.bmin

            for(const auto& z1 : act_1){
                // result.add( zone_type::concatenation(z1, *it2));

                auto kid = z1->concatenation(*it2);

                if( kid->is_nonempty() and 
                    !std::any_of(act_r.begin(), act_r.end(), 
                        [&kid](std::shared_ptr<gen_zone> &zr){return zr->includes(kid);}))
                {
                    act_r.erase( std::remove_if(act_r.begin(), act_r.end(), 
                        [&kid](std::shared_ptr<gen_zone> &zr){return kid->includes(zr);}), act_r.end());
                    act_r.push_back(kid);

                    act_r_temp.clear();
                    for(auto zr : act_r){
                        if(zr->compare_less_bmax_bmin(*it2)){
                            result.push_back(zr->clone());
                        }
                        else {
                            act_r_temp.push_back(zr);
                        }
                    }
                    act_r = act_r_temp;
                }
            }

            it2++;
        }
    }

    /// Processing left-overs (if zs1 remains)
    while(it1 != zs1.cend()){
        act_2.erase(std::remove_if(act_2.begin(), act_2.end(), 
            [&](std::shared_ptr<gen_zone> z2){return z2->compare_less_bmax_bmin(*it1);}), act_2.end());

        for(const auto& z2 : act_2){
            auto kid = (*it1)->concatenation(z2);

            if( kid->is_nonempty() and 
                !std::any_of(act_r.begin(), act_r.end(), 
                    [&kid](std::shared_ptr<gen_zone> &zr){return zr->includes(kid);}))
            {
                act_r.erase( std::remove_if(act_r.begin(), act_r.end(), 
                    [&kid](std::shared_ptr<gen_zone> &zr){return kid->includes(zr);}), act_r.end());
                act_r.push_back(kid);

                act_r_temp.clear();
                for(const auto& zr : act_r){
                    if(zr->compare_less_bmax_bmin(*it1)){
                        result.push_back(zr->clone());
                    }
                    else {
                        act_r_temp.push_back(zr);
                    }
                }
                act_r = act_r_temp;
            }
        }
        it1++;
    }

    /// Processing left-overs (if zs2 remains)
    while(it2 != zs2.cend()){
        act_1.erase(std::remove_if(act_1.begin(), act_1.end(), 
        [&](std::shared_ptr<gen_zone> z1){return z1->compare_less_emax_bmin(*it2);}), act_1.end()); // remove if z1.emax < z2.bmin

        for(const auto& z1 : act_1){
            auto kid = z1->concatenation(*it2);

            if( kid->is_nonempty() and 
                !std::any_of(act_r.begin(), act_r.end(), 
                    [&kid](std::shared_ptr<gen_zone> &zr){return zr->includes(kid);}))
            {
                act_r.erase( std::remove_if(act_r.begin(), act_r.end(), 
                    [&kid](std::shared_ptr<gen_zone> &zr){return kid->includes(zr);}), act_r.end());
                act_r.push_back(kid);

                act_r_temp.clear();
                for(const auto& zr : act_r){
                    if(zr->compare_less_bmax_bmin(*it2)){
                        result.push_back(zr->clone());
                    }
                    else {
                        act_r_temp.push_back(zr);
                    }
                }
                act_r = act_r_temp;
            }
        }
        it2++;
    }
    for(const auto& zr : act_r){
        result.push_back(zr->clone());
    }

    std::sort(result.begin(), result.end(), earlier_bmin());
    return result;
}

// TODO: Might be wrong. We are only copying pointers not new zones.
// TODO: Clone copying needed?
// Might be correct if used in transitive closure

static std::vector<std::shared_ptr<gen_zone>> gen_union(const std::vector<std::shared_ptr<gen_zone>> &zs1, 
    const std::vector<std::shared_ptr<gen_zone>> &zs2){
    std::vector<std::shared_ptr<gen_zone>> result;

    result.insert( result.end(), zs1.cbegin(), zs1.cend());
    result.insert( result.end(), zs2.cbegin(), zs2.cend());

    return gen_filter(result);
}

static std::vector<std::shared_ptr<gen_zone>> gen_transitive_closure(const std::vector<std::shared_ptr<gen_zone>> &zs){
    std::vector<std::shared_ptr<gen_zone>> result;

    std::vector<std::shared_ptr<gen_zone>> zplus = zs;
    std::vector<std::shared_ptr<gen_zone>> zlast = zs;

    std::vector<std::shared_ptr<gen_zone>> znext;

    while(true){

        znext = gen_concatenation(zlast, zs);
        // std::cout << znext << zplus << includes(zplus, znext) << std::endl;

        if(not gen_includes(zplus, znext)) {
            zlast = znext;
            zplus = gen_union(zplus, znext);
            znext.clear();

        } else {
            break;
        }
        
    }
    return zplus;
}


} // namespace paramtimedrel

#endif // PARAMTIMEDREL_ALGOS_TIMED_RELATIONS_HPP