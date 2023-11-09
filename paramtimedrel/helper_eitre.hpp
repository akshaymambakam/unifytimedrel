using namespace std;

using namespace paramtimedrel;

#ifndef HELPER_EITRE_HPP
#define HELPER_EITRE_HPP 1

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

void read_label_file(char *fName, vector<pair<int,int>> &labellingList){
    ifstream infile(fName);
    string line;
    int lineNum=0;
    while(std::getline(infile,line)){
        string s=line;
        if(s.find(",")==string::npos){
            continue;
        }
        int pos = s.find(",");
        int listart = atoi(s.substr(0,pos).c_str());
        int liend   = atoi(s.substr(s.find(",")+1).c_str());
        labellingList.push_back(pair<int,int>(listart,liend));
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
        cout<<*(dynamic_pointer_cast<interval_parambox<int,int>>(civ[i]))<<endl;
    }
}

void create_param_identification_map(vector<pair<int,int>> &all_labels,
    map<pair<int,int>,vector<parambox<int>>> &pi_map,
    vector<shared_ptr<compound_interval>> &civ){

    // Initialize pi_map
    vector<parambox<int>> empty_pbv;
    for(int i=0; i<all_labels.size(); i++){
        pi_map.insert({all_labels[i], empty_pbv});
    }
    if(all_labels.size()==0){
        return;
    }
    // Populate the map
    for(int i=0; i<civ.size(); i++){
        shared_ptr<interval_parambox<int,int>> ipb_ptr = 
            dynamic_pointer_cast<interval_parambox<int,int>>(civ[i]);
        pair<int,int> ipb_ti_pair = (ipb_ptr->get_sub_timed_interval()).get_time_interval_as_pair();
        parambox<int> ipb_pb      = ipb_ptr->get_sub_parambox();
        auto search_res = pi_map.find(ipb_ti_pair);
        if(search_res != pi_map.end()){
            (search_res->second).push_back(ipb_pb);
        }
    }
}

// Returns success status
int parambox_vec_to_powerset(vector<parambox<int>> &vpb,
    Pointset_Powerset<ppl_intbox> &power_res){

    if(vpb.empty())
        return 0;

    Pointset_Powerset<ppl_intbox> power_temp;
    for(int i=0; i<vpb.size(); i++){
        Constraint_System cst;
        for(int j=0; j<vpb[i].num_of_params(); j++){
            Variable cr(j);
            int lbt = vpb[i].get_lower_by_index(j).value;
            int ubt = vpb[i].get_upper_by_index(j).value;
            cst.insert(lbt<=cr);
            cst.insert(cr<=ubt);
        }
        if(i==0){
            power_temp = Pointset_Powerset<ppl_intbox>(ppl_intbox(cst));
        }else{
            power_temp.add_disjunct(ppl_intbox(cst));
        }
    }
    
    power_res = power_temp;
    return 1;
}

// Returns success status
int positive_example_param_identification(
    map<pair<int,int>,vector<parambox<int>>> &pi_map,
    Pointset_Powerset<ppl_intbox> &power_res){

    Pointset_Powerset<ppl_intbox> power_temp;
    int suc_res = 0;
    for(auto elem : pi_map){
        Pointset_Powerset<ppl_intbox> inner_power_temp;
        int suc_temp = parambox_vec_to_powerset(elem.second, inner_power_temp);
        if(suc_temp){
            if(suc_res == 0){
                suc_res = 1;
                power_temp = inner_power_temp;    
            }else{
                power_temp.intersection_assign(inner_power_temp);
            }
        }else{
            return 0;
        }
    }

    power_res = power_temp;
    return suc_res;
}

// Returns success status
int negative_example_param_identification(
    map<pair<int,int>,vector<parambox<int>>> &pi_map,
    Pointset_Powerset<ppl_intbox> &power_res){

    int suc_res = 0;

    for(auto elem : pi_map){
        for(auto pb_elem : elem.second){
            Constraint_System cst;
            for(int i=0; i<pb_elem.num_of_params(); i++){
                Variable cr(i);
                int lbt = pb_elem.get_lower_by_index(i).value;
                int ubt = pb_elem.get_upper_by_index(i).value;
                cst.insert(lbt<=cr);
                cst.insert(cr<=ubt);
            }
            if(suc_res == 0){
                power_res = Pointset_Powerset<ppl_intbox>(ppl_intbox(cst));
                suc_res = 1;
            }else{
                power_res.add_disjunct(ppl_intbox(cst));
            }
        }
    }
    return suc_res;
}

#endif // HELPER_EITRE_HPP