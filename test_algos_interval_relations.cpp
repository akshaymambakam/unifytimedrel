#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <chrono>

#include "./paramtimedrel/algos_interval_relations.hpp"
#include "./paramtimedrel/interval_parambox.hpp"
#include "./paramtimedrel/utils.hpp"

using namespace std::chrono;

using namespace std;

using namespace paramtimedrel;

void readEventFile(char *fName, vector<int> &timeVec, vector<int> &eventNumVec){
    ifstream infile(fName);
    string line;
    int lineNum=0;
    while(std::getline(infile,line)){
        string s=line;
        int pos = s.find(",");
        int timeStamp = atoi(s.substr(0,pos).c_str());
        int eventNum = atoi(s.substr(s.find("y")+1).c_str());
        timeVec.push_back(timeStamp);
        eventNumVec.push_back(eventNum);
    }
    infile.close();
}

vector<timed_interval<int>> eventToTimedInterval(vector<int> timeVec,
    vector<int> eventVec, int eventNum){
    
    vector<timed_interval<int>> tivalvec;
    int prevts = 0;

    for(int i=0;i<timeVec.size();i++){
        if(eventVec[i]==eventNum){
            pair<int,int> tp(prevts, timeVec[i]);
            timed_interval<int> tival(tp);
            tivalvec.push_back(tival);
        }
        prevts = timeVec[i];
    }

    return tivalvec;
}

vector<timed_interval<int>> epsToTimedInterval(vector<int> timeVec,
    vector<int> eventVec){

    vector<timed_interval<int>> tivalvec;
    int prevts = 0;
    
    for(int i=0;i<timeVec.size();i++){
        if(prevts == timeVec[i]){
            pair<int,int> tp(prevts, timeVec[i]);
            timed_interval<int> tival(tp);
            tivalvec.push_back(tival);
        }
        prevts = timeVec[i];
    }

    return tivalvec;
}

void print_interval_relations(vector<shared_ptr<compound_interval>> &civ){
    cout<<"size:"<<civ.size()<<endl;
    for(int i=0; i<civ.size(); i++){
        cout<<*(dynamic_pointer_cast<interval_parambox<int,int>>(civ[i]))<<endl;
    }
}

int main(){

    auto start = high_resolution_clock::now();

    vector<int> timeVec;
    vector<int> eventVec;
    char fname[50] = "testBlowup.csv";
    readEventFile(fname, timeVec, eventVec);
    vector<timed_interval<int>> tia = eventToTimedInterval(timeVec, eventVec, 0);
    vector<timed_interval<int>> tib = eventToTimedInterval(timeVec, eventVec, 1);
    vector<timed_interval<int>> tie = epsToTimedInterval(timeVec, eventVec);
    parambox<int> pbglobal = parambox<int>::make({1,1,1},{10000,10000,10000});
    shared_ptr<interval_parambox<int,int>> ipbp0 = make_shared<interval_parambox<int,int>>(tia[0], pbglobal);
    

    // Start testing blowup example
    vector<shared_ptr<compound_interval>> mse;
    for(int i=0; i<tie.size(); i++){
        mse.push_back(make_shared<interval_parambox<int,int>>(tie[i], pbglobal));
    }
    vector<shared_ptr<compound_interval>> msa;
    for(int i=0; i<tia.size(); i++){
        msa.push_back(make_shared<interval_parambox<int,int>>(tia[i], pbglobal));
    }
    vector<shared_ptr<compound_interval>> msb;
    for(int i=0; i<tib.size(); i++){
        msb.push_back(make_shared<interval_parambox<int,int>>(tib[i], pbglobal));
    }
    
    // Concatenation
    vector<shared_ptr<compound_interval>> msba;
    msba = concatenation_interval_relations(msb, msa);
    
    // Duration restriction
    vector<shared_ptr<compound_interval>> msbadr;
    for(int i=0; i<msba.size(); i++){
        shared_ptr<interval_parambox<int,int>> ipbtemp = 
            dynamic_pointer_cast<interval_parambox<int,int>>(msba[i]);
        pair<int,int> ptemp = (ipbtemp->get_sub_timed_interval()).get_time_interval_as_pair();
        int tival_duration = ptemp.second - ptemp.first;
        ipbtemp = ipbtemp->add_upper_bound_on_parameter(tival_duration, 1, 1);
        ipbtemp = ipbtemp->add_lower_bound_on_parameter(tival_duration, 1, 2);
        msbadr.push_back(ipbtemp);
    }

    // Kleene plus
    vector<shared_ptr<compound_interval>> msbadrkp;
    msbadrkp = kleene_plus_interval_relations(msbadr);

    // Kleene plus to Kleene star
    vector<shared_ptr<compound_interval>> msbadrks;
    msbadrks = union_interval_relations(msbadrkp, mse);

    // a concat k*
    vector<shared_ptr<compound_interval>> msaCbadrks;
    msaCbadrks = concatenation_interval_relations(msa, msbadrks);

    // a concat k* concat b
    vector<shared_ptr<compound_interval>> msaCbadrksCb;
    msaCbadrksCb = concatenation_interval_relations(msaCbadrks, msb);

    // (a concat k* concat b) duration restriction
    vector<shared_ptr<compound_interval>> msaCbadrksCbdr;
    for(int i=0; i<msaCbadrksCb.size(); i++){
        shared_ptr<interval_parambox<int,int>> ipbtemp = 
            dynamic_pointer_cast<interval_parambox<int,int>>(msaCbadrksCb[i]);
        pair<int,int> ptemp = (ipbtemp->get_sub_timed_interval()).get_time_interval_as_pair();
        int tival_duration = ptemp.second - ptemp.first;
        ipbtemp = ipbtemp->add_upper_bound_on_parameter(tival_duration, 1, 0);
        ipbtemp = ipbtemp->add_lower_bound_on_parameter(tival_duration, 1, 0);
        msaCbadrksCbdr.push_back(ipbtemp);
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop-start);

    cout<<"time(ms):"<<duration.count()<<endl;

    print_interval_relations(msaCbadrksCbdr);
    return 0;
}