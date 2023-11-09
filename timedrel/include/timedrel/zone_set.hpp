#ifndef ZONE_SET_HPP
#define ZONE_SET_HPP 1

#include <vector>
#include <deque>
#include <algorithm>
 
#include "zone.hpp"

namespace timedrel {

template <class T>
struct earlier_bmin {
    inline bool operator() (const zone<T>& z1, const zone<T>& z2){
        return (z1.get_bmin() < z2.get_bmin());
    }
};

template <class T>
struct earlier_emin {
    inline bool operator() (const zone<T>& z1, const zone<T>& z2){
        return (z1.get_emin() < z2.get_emin());
    }
};

template<
    typename T, 
    typename Container = std::vector< zone<T> > 
>
class zone_set {

template<typename T1, typename Container1>
friend bool operator==(
    const zone_set<T1, Container1>&, 
    const zone_set<T1, Container1>&);

template<typename T1, typename Container1>
friend bool operator!=(
    const zone_set<T1, Container1>&, 
    const zone_set<T1, Container1>&);

template<typename T1, typename Container1>
friend std::ostream& operator<<(
    std::ostream &os, 
    const zone_set<T1, Container1>&);

// template<typename T, typename Container>
// friend bool operator<(
//     const zone_set<T, Container>&, 
//     const zone_set<T, Container>&);

public:
    typedef T                                    value_type;
    typedef zone<value_type>                     zone_type;

    typedef typename zone_type::lower_bound_type lower_bound_type;
    typedef typename zone_type::upper_bound_type upper_bound_type;

    typedef typename Container::reference        reference;
    typedef typename Container::const_reference  const_reference;
    typedef typename Container::iterator         iterator;
    typedef typename Container::const_iterator   const_iterator;
    typedef typename Container::pointer          pointer;
    typedef typename Container::const_pointer    const_pointer;
    typedef typename Container::size_type        size_type;

    typedef Container                            container_type;

    typedef zone_set<T, Container>               type;
    typedef zone_set<T, Container>               zone_set_type;

protected:
    Container container;

public:
    // zone_set() : container() { }

    // zone_set(const zone_set_type& other) : container(other.container) { };

    // zone_set(zone_set_type&& c) : container(std::move(c.container)) { };

    // zone_set_type& operator=(const zone_set_type& other) noexcept {
    //     if (this != &other)
    //         container = other.container;
    //     return *this;
    // }

    // type& operator=(type&& other) noexcept {
    //     using std::swap;
    //     swap(*this, other);

    //     return *this;
    // }

    zone_set() = default;
    ~zone_set() = default;

    zone_set(const zone_set_type& other) = default;
    zone_set(zone_set_type&& c) = default;

    zone_set_type& operator=(const zone_set_type& other) = default;
    zone_set_type& operator=(zone_set_type&& other) = default;

    bool empty() const {
        return container.empty();
    }
    bool is_empty() const {
        return container.empty();
    }
    size_type size() const {
        return container.size();
    }
    iterator begin(){
        return container.begin();
    }
    iterator end(){
        return container.end();
    }
    const_iterator begin() const{
        return container.begin();
    }
    const_iterator end() const{
        return container.end();
    }
    const_iterator cbegin() const {
        return container.cbegin();
    }
    const_iterator cend() const {
        return container.cend();
    }

    reference front() {
        return container.front();
    }

    const_reference front() const {
        return container.front();
    }

    reference back() {
        return container.back();
    }

    const_reference back() const {
        return container.back();
    }

    void sort_by_bmin(){
        std::sort(begin(), end(), earlier_bmin<value_type>());
    }

    void sort_by_emin(){
        std::sort(begin(), end(), earlier_emin<value_type>());
    }

    void is_sorted_by_bmin(){
        std::is_sorted(begin(), end(), earlier_bmin<value_type>());
    }

    void is_sorted_by_emin(){
        std::is_sorted(begin(), end(), earlier_emin<value_type>());
    }

    iterator erase(iterator position){
        return container.erase(position);
    }

    iterator erase(iterator first, iterator last){
        return container.erase(first, last);   
    }
    void clear(){
        container.clear();
    }
    void push_back(const zone_type& z) {
        container.push_back(z);
    }
    void push_back(zone_type&& z) {
        container.push_back(std::move(z));
    }
    iterator insert(iterator pos, const zone_type& z) {
        return container.insert(pos, z);
    }
    iterator insert(const_iterator pos, const zone_type& z) {
        return container.insert(pos, z);
    }
    iterator insert(const_iterator pos, zone_type&& z ){
        return container.insert(pos, z);
    }
    template< class InputIt >
    void insert(iterator pos, InputIt first, InputIt last){
        container.insert(pos, first, last);
    }
    template< class InputIt >
    iterator insert(const_iterator pos, InputIt first, InputIt last){
        return container.insert(pos, first, last);
    }

    void add(const zone_type& z){
        if(!z.is_nonempty()){return;}
        container.push_back(z);
    }
    void add(zone_type&& z){
        if(!z.is_nonempty()){return;}
        container.push_back(std::move(z));
    }
    void add(const std::array<value_type,6>& values, 
             const std::array<bool,6>& signs){
        add(zone_type::make(values, signs));
    }

    void add(const std::array<value_type,6>& values){
       add(zone_type::make(values));
    }

    void add_from_period(value_type begin, value_type end){
        add(zone_type::make_from_period(begin, end));
    }
    void add_from_period_rise_anchor(value_type begin, value_type end){
        add(zone_type::make_from_period_rise_anchor(begin, end));
    }
    void add_from_period_fall_anchor(value_type begin, value_type end){
        add(zone_type::make_from_period_fall_anchor(begin, end));
    }
    void add_from_period_both_anchor(value_type begin, value_type end){
        add(zone_type::make_from_period_both_anchor(begin, end));
    }

    static zone_set_type filter(const zone_set_type &zs){
 
        zone_set_type active, active_temp;
        zone_set_type result = zone_set();
  
        // for(const auto& z1 : zs){
        for(auto z1it = zs.cbegin(); z1it != zs.cend(); z1it++){
 
            bool already_included = std::any_of(active.begin(), active.end(), [z1it](zone_type &z2){return zone_type::includes(z2, *z1it);});
 
            if(!already_included){
 
                active.erase( std::remove_if(active.begin(), active.end(), [z1it](zone_type &z2){return zone_type::includes(*z1it, z2);}), active.end());
                active.push_back(*z1it);
 
                active_temp.clear();
                for(const auto& z2 : active){
                    if( z2.get_bmax() < z1it->get_bmin()){
                        result.push_back(z2);
                    } else {
                        active_temp.push_back(z2);
                    }
                }
                active = active_temp;
            }
        }
        for(const auto& z2 : active){
            result.push_back(z2);
        }

        result.sort_by_bmin();
        return result;
    }

    static bool includes(const zone_set_type& zs1, const zone_set_type& zs2){

        // std::sort(zs1.begin(), zs1.end(), earlier_bmin<value_type>());
        // std::sort(zs2.begin(), zs2.end(), earlier_bmin<value_type>());

        if(zs2.empty()){
            return true;
        } else if(zs1.empty()){
            return false;
        }

        auto act_1 = zone_set();

        auto it1 = zs1.cbegin();
        auto it2 = zs2.cbegin();

        while(it1 != zs1.cend() and it2 != zs2.cend()) {

            if (it1->get_bmin() < it2->get_bmax()){ //  z1.bmin < z2.bmin
                act_1.push_back(*it1);
                it1++;
            } else {
                act_1.erase( std::remove_if(act_1.begin(), act_1.end(), [&](zone_type z1){return z1.get_bmax() < it2->get_bmin();}), act_1.end()); // remove if z1.bmax < z2.bmin
                bool z2_incd = std::any_of(act_1.begin(), act_1.end(), [&](zone_type z1){return zone_type::includes(z1, *it2);});
                if(!z2_incd){
                    return false;
                }
                it2++;
            }
        }
        while (it2 != zs2.cend() and not act_1.empty()) {
            act_1.erase( std::remove_if(act_1.begin(), act_1.end(), [&](zone_type z1){return z1.get_bmax() < it2->get_bmin();}), act_1.end()); // remove if z1.bmax < z2.bmin
            bool z2_incd = std::any_of(act_1.begin(), act_1.end(), [&](zone_type z1){return zone_type::includes(z1, *it2);});
            if(!z2_incd){
                return false;
            }
            it2++;
        }
        return true;
    }

    static zone_set_type intersection(zone_set_type&& zs1, zone_set_type&& zs2){
        return zone_set_type::intersection(std::move(zs1), std::move(zs2));
    }

    static zone_set_type intersection(const zone_set_type& zs1, zone_set_type&& zs2){
        return zone_set_type::intersection(zs1, std::move(zs2));
    }

    static zone_set_type intersection(zone_set_type&& zs1, const zone_set_type& zs2){
        return zone_set_type::intersection(std::move(zs1), zs2);
    }


    static zone_set_type intersection(const zone_set_type& zs1, const zone_set_type& zs2){

        zone_set_type result = zone_set();

        zone_set_type act_1, act_2, act_r, act_r_temp;

        // std::sort(zs1.begin(), zs1.end(), earlier_bmin<value_type>());
        // std::sort(zs2.begin(), zs2.end(), earlier_bmin<value_type>());

        auto it1 = zs1.cbegin();
        auto it2 = zs2.cbegin();

        while(it1 != zs1.cend() and it2 != zs2.cend()) {


            if (it1->get_bmin() < it2->get_bmin()){
                act_1.push_back(*it1);
                act_2.erase(std::remove_if(act_2.begin(), act_2.end(), [&](zone_type z2){return z2.get_bmax() < it1->get_bmin();}), act_2.end());

                for(const auto& z2 : act_2){
                    // result.add( zone_type::intersection(*it1, z2));

                    auto kid = zone_type::intersection(*it1, z2);

                    if( kid.is_nonempty() and 
                        !std::any_of(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(zr, kid);} ))
                    {
                        act_r.erase( std::remove_if(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(kid, zr);}), act_r.end());
                        act_r.push_back(kid);

                        act_r_temp.clear();
                        for(auto zr : act_r){
                            if( zr.get_bmax() < it1->get_bmin()){
                                result.push_back(zr);
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
                act_1.erase(std::remove_if(act_1.begin(), act_1.end(), [&](zone_type z1){return z1.get_bmax() < it2->get_bmin();}), act_1.end()); // remove if z1.emax < z2.bmin

                for(const auto& z1 : act_1){
                    // result.add( zone_type::intersection(z1, *it2));

                    auto kid = zone_type::intersection(z1, *it2);

                    if( kid.is_nonempty() and 
                        !std::any_of(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(zr, kid);}))
                    {
                        act_r.erase( std::remove_if(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(kid, zr);}), act_r.end());
                        act_r.push_back(kid);

                        act_r_temp.clear();
                        for(auto zr : act_r){
                            if( zr.get_bmax() < it2->get_bmin()){
                                result.push_back(zr);
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
            act_2.erase(std::remove_if(act_2.begin(), act_2.end(), [&](zone_type z2){return z2.get_bmax() < it1->get_bmin();}), act_2.end());

            for(const auto& z2 : act_2){
                auto kid = zone_type::intersection(*it1, z2);

                if( kid.is_nonempty() and 
                    !std::any_of(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(zr, kid);}))
                {
                    act_r.erase( std::remove_if(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(kid, zr);}), act_r.end());
                    act_r.push_back(kid);

                    act_r_temp.clear();
                    for(const auto& zr : act_r){
                        if( zr.get_bmax() < it1->get_bmin()){
                            result.push_back(zr);
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
            act_1.erase(std::remove_if(act_1.begin(), act_1.end(), [&](zone_type z1){return z1.get_bmax() < it2->get_bmin();}), act_1.end()); // remove if z1.emax < z2.bmin

            for(const auto& z1 : act_1){
                auto kid = zone_type::intersection(z1, *it2);

                if( kid.is_nonempty() and 
                    !std::any_of(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(zr, kid);}))
                {
                    act_r.erase( std::remove_if(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(kid, zr);}), act_r.end());
                    act_r.push_back(kid);

                    act_r_temp.clear();
                    for(const auto& zr : act_r){
                        if( zr.get_bmax() < it2->get_bmin()){
                            result.push_back(zr);
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
            result.push_back(zr);
        }

        result.sort_by_bmin();
        return result;
    }

    static zone_set_type concatenation(const zone_set_type& _zs1, const zone_set_type& zs2){

        zone_set_type result = zone_set();

        zone_set_type act_1, act_2, act_r, act_r_temp;

        // Could be better?
        auto zs1 = zone_set_type(_zs1);
        std::sort(zs1.begin(), zs1.end(), earlier_emin<value_type>());
        // std::sort(zs2.begin(), zs2.end(), earlier_bmin<value_type>());

        auto it1 = zs1.cbegin();
        auto it2 = zs2.cbegin();

        while(it1 != zs1.cend() and it2 != zs2.cend()) {

            if (it1->get_emin() < it2->get_bmin()){
                act_1.push_back(*it1);
                act_2.erase(std::remove_if(act_2.begin(), act_2.end(), [&](zone_type z2){return z2.get_bmax() < it1->get_emin();}), act_2.end());

                for(const auto& z2 : act_2){
                    // result.add( zone_type::concatenation(*it1, z2));

                    auto kid = zone_type::concatenation(*it1, z2);

                    if( kid.is_nonempty() and 
                        !std::any_of(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(zr, kid);}))
                    {
                        act_r.erase( std::remove_if(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(kid, zr);}), act_r.end());
                        act_r.push_back(kid);

                        act_r_temp.clear();
                        for(auto zr : act_r){
                            if( zr.get_bmax() < it1->get_bmin()){
                                result.push_back(zr);
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
                act_1.erase(std::remove_if(act_1.begin(), act_1.end(), [&](zone_type z1){return z1.get_emax() < it2->get_bmin();}), act_1.end()); // remove if z1.emax < z2.bmin

                for(const auto& z1 : act_1){
                    // result.add( zone_type::concatenation(z1, *it2));

                    auto kid = zone_type::concatenation(z1, *it2);

                    if( kid.is_nonempty() and 
                        !std::any_of(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(zr, kid);}))
                    {
                        act_r.erase( std::remove_if(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(kid, zr);}), act_r.end());
                        act_r.push_back(kid);

                        act_r_temp.clear();
                        for(auto zr : act_r){
                            if( zr.get_bmax() < it2->get_bmin()){
                                result.push_back(zr);
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
            act_2.erase(std::remove_if(act_2.begin(), act_2.end(), [&](zone_type z2){return z2.get_bmax() < it1->get_bmin();}), act_2.end());

            for(const auto& z2 : act_2){
                auto kid = zone_type::concatenation(*it1, z2);

                if( kid.is_nonempty() and 
                    !std::any_of(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(zr, kid);}))
                {
                    act_r.erase( std::remove_if(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(kid, zr);}), act_r.end());
                    act_r.push_back(kid);

                    act_r_temp.clear();
                    for(const auto& zr : act_r){
                        if( zr.get_bmax() < it1->get_bmin()){
                            result.push_back(zr);
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
            act_1.erase(std::remove_if(act_1.begin(), act_1.end(), [&](zone_type z1){return z1.get_emax() < it2->get_bmin();}), act_1.end()); // remove if z1.emax < z2.bmin

            for(const auto& z1 : act_1){
                auto kid = zone_type::concatenation(z1, *it2);

                if( kid.is_nonempty() and 
                    !std::any_of(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(zr, kid);}))
                {
                    act_r.erase( std::remove_if(act_r.begin(), act_r.end(), [&kid](zone_type &zr){return zone_type::includes(kid, zr);}), act_r.end());
                    act_r.push_back(kid);

                    act_r_temp.clear();
                    for(const auto& zr : act_r){
                        if( zr.get_bmax() < it2->get_bmin()){
                            result.push_back(zr);
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
            result.push_back(zr);
        }

        result.sort_by_bmin();
        return result;
    }

    static zone_set_type transitive_closure(const zone_set_type& zs){

        auto result = zone_set();

        zone_set_type zplus = zs;
        zone_set_type zlast = zs;

        zone_set_type znext;

        while(true){

            znext = concatenation(zlast, zs);
            // std::cout << znext << zplus << includes(zplus, znext) << std::endl;

            if(not includes(zplus, znext)) {
                zlast = znext;
                zplus = set_union(zplus, znext);
                znext.clear();

            } else {
                break;
            }
            
        }

    return zplus;
}

    static zone_set_type set_union(const zone_set_type& zs1, const zone_set_type& zs2){

        auto result = zone_set();

        result.insert( result.end(), zs1.cbegin(), zs1.cend());
        result.insert( result.end(), zs2.cbegin(), zs2.cend());

        return zone_set_type::filter(result);
    }

    static zone_set_type duration_restriction(
        const zone_set_type& zs,
        const lower_bound_type& dmin, 
        const upper_bound_type& dmax){

        auto result = zone_set();

        // for (const auto& z : zs){
        for(auto it = zs.cbegin(); it != zs.cend(); it++){
            result.add(zone_type::duration_restriction(*it, dmin, dmax));
        }

        result.sort_by_bmin();
        return zone_set_type::filter(result);

    }

    /**
     *  @brief  Duration restriction operation
     *  @param  arg  A %zone.
     *  @return Complement %zone_set
     *
     *  Returns a set of timed periods whose durations are in (dmin, dmax] and that are in the zone set given
     */
    static zone_set_type duration_restriction(
        const zone_set_type& zs, 
        const value_type dmin, 
        const value_type dmax){

        return duration_restriction(zs, lower_bound_type::open(dmin), upper_bound_type::closed(dmax));
    }

    /**
     *  @brief  Complementation operation for a single zone
     *  @param  z      A %zone
     *  @return result A %zone_set
     *
     *  Returns the complement of the zone z with respect to the universal zone set
     */
    static zone_set_type complementation(const zone_type& z){

        auto result = zone_set();

        result.add(zone_type::make(
            z.get_bmax().complement(), upper_bound_type::unbounded(), 
            lower_bound_type::unbounded(), upper_bound_type::unbounded(),
            lower_bound_type::unbounded(), upper_bound_type::unbounded()));

        result.add(zone_type::make(
            lower_bound_type::unbounded(), z.get_bmin().complement(), 
            lower_bound_type::unbounded(), upper_bound_type::unbounded(),
            lower_bound_type::unbounded(), upper_bound_type::unbounded()));

        result.add(zone_type::make(
            lower_bound_type::unbounded(), upper_bound_type::unbounded(), 
            z.get_emax().complement(), upper_bound_type::unbounded(),
            lower_bound_type::unbounded(), upper_bound_type::unbounded()));

        result.add(zone_type::make(
            lower_bound_type::unbounded(), upper_bound_type::unbounded(), 
            lower_bound_type::unbounded(), z.get_emin().complement(),
            lower_bound_type::unbounded(), upper_bound_type::unbounded()));

        result.add(zone_type::make(
            lower_bound_type::unbounded(), upper_bound_type::unbounded(), 
            lower_bound_type::unbounded(), upper_bound_type::unbounded(),
            z.get_dmax().complement(), upper_bound_type::unbounded()));

        result.add(zone_type::make(
            lower_bound_type::unbounded(), upper_bound_type::unbounded(), 
            lower_bound_type::unbounded(), upper_bound_type::unbounded(),
            lower_bound_type::unbounded(), z.get_dmin().complement()));

        return zone_set_type::filter(result);

    }

    /**
     *  @brief  Complementation operation for a zone set
     *
     *  @param  zs     A %zone_set.
     *  @return result A %zone_set
     *
     *  Returns the complement of the zone set zs with respect to the universal zone set
     */
    static zone_set_type complementation(const zone_set_type& zs){

        auto result = zone_set();

        result.add(zone_type::universal());

        for(auto z : zs){
            auto nzs = zone_set_type::complementation(z);
            result = zone_set_type::intersection(result, nzs);
        }

        return result;
    }

    /**
     *  @brief  Set difference operation between two zone sets
     *
     *  @param  zs1    A %zone_set.
     *  @param  zs2    A %zone_set.
     *  @return result A %zone_set.
     *
     *  Returns a zone set that contains time periods which are in the first zone set and not in the second.
     */
    static zone_set_type set_difference(const zone_set_type& zs1, const zone_set_type& zs2){

        auto result = zone_set(zs1);

        for(auto z : zs2){
            auto nzs = zone_set_type::complementation(z);
            result = zone_set_type::intersection(result, nzs);
        }

        return result;
    }

    /**
     *  @brief  Metric Compass Logic -- Meets Operator
     *  @param  %zone.
        @param  %a.

     *  @return %zone_set
     *
     *  Returns the result of operation <A>_(a, b) on the zone set given 
     */
    static zone_set_type diamond_meets(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){

        zone_set_type result = zone_set();

        for(auto z : zs){
            result.add(zone_type::make(
                z.get_emin(),
                z.get_emax(),
                lower_bound_type::unbounded(),
                upper_bound_type::unbounded(),
                lbound,
                ubound
            ));
        }

        return zone_set<T>::filter(result);
    }



    /**
     *  @brief  Metric Compass Logic -- MetBy Operator
     *  @param  %zone.
        @param  %a.

     *  @return %zone_set
     *
     *  Returns the result of operation <Ai>_(a, b] on the zone set given 
     */
    static zone_set_type diamond_met_by(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        
        zone_set_type result = zone_set();

        for(auto z : zs){
            result.add(zone_type::make(
                lower_bound_type::unbounded(),
                upper_bound_type::unbounded(),               
                z.get_bmin(),
                z.get_bmax(),
                lbound,
                ubound
            ));
        }

        return zone_set<T>::filter(result);
    }



    /**
     *  @brief  Metric Compass Logic -- MetBy Operator
     *  @param  %zone.
        @param  %a.

     *  @return %zone_set
     *
     *  Returns the result of operation <Ai>_(a, b) on the zone set given 
     */
    static zone_set_type diamond_started_by(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        
        zone_set_type result = zone_set();

        for(auto z : zs){
            result.add(zone_type::make(
                z.get_bmin(),
                z.get_bmax(),
                lower_bound_type::add(z.get_emin(), lbound),
                upper_bound_type::add(z.get_emax(), ubound),        
                lower_bound_type::add(z.get_dmin(), lbound),
                upper_bound_type::add(z.get_dmax(), ubound)
            ));
        }

        return zone_set<T>::filter(result);
    }


    /**
     *  @brief  Metric Compass Logic -- MetBy Operator
     *  @param  %zone.
        @param  %a.

     *  @return %zone_set
     *
     *  Returns the result of operation <Ai>_(a, b] on the zone set given 
     */
    static zone_set_type diamond_starts(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        
        zone_set_type result = zone_set();

        for(auto z : zs){
            result.add(zone_type::make(
                z.get_bmin(),
                z.get_bmax(),
                lower_bound_type::add(z.get_emin(), ubound),
                upper_bound_type::add(z.get_emax(), lbound),        
                lower_bound_type::add(z.get_dmin(), ubound),
                upper_bound_type::add(z.get_dmax(), lbound)
            ));
        }

        return zone_set<T>::filter(result);
    }



    /**
     *  @brief  Metric Compass Logic -- MetBy Operator
     *  @param  %zone.
        @param  %a.

     *  @return %zone_set
     *
     *  Returns the result of operation <Ai>_(a, b] on the zone set given 
     */
    static zone_set_type diamond_finished_by(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        
        zone_set_type result = zone_set();

        for(auto z : zs){
            result.add(zone_type::make(
                lower_bound_type::add(z.get_bmin(), ubound),
                upper_bound_type::add(z.get_bmax(), lbound),        
                z.get_emin(),
                z.get_emax(),
                lower_bound_type::add(z.get_dmin(), lbound),
                upper_bound_type::add(z.get_dmax(), ubound)
            ));
        }

        return zone_set<T>::filter(result);
    }



    /**
     *  @brief  Metric Compass Logic -- MetBy Operator
     *  @param  %zone.
        @param  %a.

     *  @return %zone_set
     *
     *  Returns the result of operation <Ai>_(a, b] on the zone set given 
     */
    static zone_set_type diamond_finishes(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        
        zone_set_type result = zone_set();

        for(auto z : zs){
            result.add(zone_type::make(
                lower_bound_type::add(z.get_bmin(), lbound), 
                upper_bound_type::add(z.get_bmax(), ubound),         
                z.get_emin(),
                z.get_emax(),
                lower_bound_type::intersection(
                    lower_bound_type::open(0),
                    lower_bound_type::add(z.get_dmin(), ubound)
                    ), 
                upper_bound_type::add(z.get_dmax(), lbound)
            ));
        }

        return zone_set<T>::filter(result);
    }

    static zone_set_type diamond_meets(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::diamond_meets(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type diamond_met_by(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::diamond_met_by(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type diamond_starts(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::diamond_starts(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type diamond_started_by(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::diamond_started_by(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type diamond_finishes(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::diamond_finishes(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type diamond_finished_by(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::diamond_finished_by(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }

    static zone_set_type box_meets(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        return zone_set_type::complementation(diamond_meets(zone_set_type::complementation(zs), lbound, ubound));
    }
    static zone_set_type box_met_by(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        return zone_set_type::complementation(diamond_met_by(zone_set_type::complementation(zs), lbound, ubound));
    }
    static zone_set_type box_starts(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        return zone_set_type::complementation(diamond_starts(zone_set_type::complementation(zs), lbound, ubound));
    }
    static zone_set_type box_started_by(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        return zone_set_type::complementation(diamond_started_by(zone_set_type::complementation(zs), lbound, ubound));
    }
    static zone_set_type box_finishes(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        return zone_set_type::complementation(diamond_finishes(zone_set_type::complementation(zs), lbound, ubound));
    }
    static zone_set_type box_finished_by(const zone_set_type& zs, const lower_bound_type lbound, const upper_bound_type ubound){
        return zone_set_type::complementation(diamond_finished_by(zone_set_type::complementation(zs), lbound, ubound));
    }

    static zone_set_type box_meets(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::box_meets(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type box_met_by(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::box_met_by(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type box_starts(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::box_starts(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type box_started_by(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::box_started_by(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type box_finishes(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::box_finishes(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }
    static zone_set_type box_finished_by(const zone_set_type& zs, const value_type a, const value_type b){
        return zone_set_type::box_finished_by(zs, lower_bound_type::open(a), upper_bound_type::closed(b));
    }

};




/**
 *  @brief  zone_set equality comparison.
 *  @param  lhs  A %zone_set.
 *  @param  rhs  A %zone_set of the same type as @a lhs.
 *  @return  True iff the size and elements of the sets are equal.
 *
 *  This is a syntactic equivalence relation.
 */
template<typename T, typename Container>
inline bool operator==(
    const zone_set<T, Container>& lhs, 
    const zone_set<T, Container>& rhs){ 

    return lhs.container == rhs.container; 
}

template<typename T, typename Container>
inline bool operator!=(
    const zone_set<T, Container>& lhs, 
    const zone_set<T, Container>& rhs){ 

    return !(lhs.container == rhs.container); 
}

} //namespace timedrel

#endif
