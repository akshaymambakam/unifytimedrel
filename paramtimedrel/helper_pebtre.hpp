using namespace std;

using namespace paramtimedrel;

#ifndef HELPER_PEBTRE_HPP
#define HELPER_PEBTRE_HPP 1

void read_event_file(char *fName, vector<int> &timeVec, vector<int> &eventNumVec){
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

vector<timed_interval<int>> event_to_timed_intervals(vector<int> timeVec,
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

vector<timed_interval<int>> eps_to_timed_intervals(vector<int> timeVec,
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
        shared_ptr<parametric_interval<int>> pit = 
            dynamic_pointer_cast<parametric_interval<int>>(civ[i]);
        cout<<pit->get_sub_timed_interval()<<"; "<<pit->get_sub_poly()<<endl;
    }
}


#endif // HELPER_PEBTRE_HPP