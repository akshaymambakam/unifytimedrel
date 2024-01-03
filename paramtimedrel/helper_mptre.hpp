using namespace std;

using namespace paramtimedrel;

#ifndef HELPER_MPTRE_HPP
#define HELPER_MPTRE_HPP 1

#include <fstream>

void read_signal_file(char *fName, vector<int> &timeVec, vector<vector<string>> &valueVec){
    ifstream infile(fName);
    string delimiter = ",";
    string line;
    int lineNum=0;
    while (std::getline(infile, line))
    {
        size_t pos = 0;
        std::string token;
        int num=0;
        string s=line;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            if(num==0){
                timeVec.push_back(atoi(s.c_str()));
            }else{
                if(lineNum==0){
                    vector<string> tcVec;
                    tcVec.push_back(token);
                    valueVec.push_back(tcVec);
                }else{
                    valueVec[num-1].push_back(token);
                }
                
            }
            s.erase(0, pos + delimiter.length());
            num++;
        }
        if(lineNum==0){
            vector<string> tcVec;
            tcVec.push_back(s);
            valueVec.push_back(tcVec);
        }else{
            valueVec[num-1].push_back(s);
        }
        lineNum++;
    }
    infile.close();
}

int placesAfterDot(string sf){
    int count=0;
    int i=0;
    int dotFlag=0;
    while(sf[i]!=0){
        if(sf[i]=='.'){
            count = 0;
            dotFlag = 1;
        }
        count++;
        i++;
    }
    if(dotFlag){
        return count-1;
    }else{
        return 0;
    }
}

int exponentOf10(int expo){
    int exp10=1;
    for(int i=0;i<expo;i++){
        exp10*=10;
    }
    return exp10;
}

int removeDot(string fnum){
    char dup[100];
    int i=0,j=0;
    while(fnum[i]!=0){
        if(fnum[i]!='.'){
            dup[j]=fnum[i];
            j++;
        }
        i++;
    }
    dup[i]=0;
    return atoi(dup);
}

void compute_sub_signal(pair<int,int> interval, vector<int> orig_tvec, vector<string> orig_fvec, 
    vector<int> &new_tvec, vector<string> &new_fvec){
    for(int i=0;i<orig_tvec.size();i++){
        int l = interval.first;
        int u = interval.second;
        if((i-2>0) && (i+1)<orig_tvec.size() && (orig_tvec[i+1]>=l) && (orig_tvec[i-2]<=u)){
            new_tvec.push_back(orig_tvec[i]);
            new_fvec.push_back(orig_fvec[i]);
        }
    }
}

vector<string> get_bool_from_porv(vector<string> fvec, int compop, string compval){
    vector<string> tfbool;

    mpq_class ftrat, fvrat;
    int ftexp10 = exponentOf10(placesAfterDot(compval));
    int fndot = removeDot(compval);
    ftrat = mpq_class(fndot, ftexp10);

    for(int i=0; i<fvec.size(); i++){
        ftexp10 = exponentOf10(placesAfterDot(fvec[i]));
        fndot = removeDot(fvec[i]);
        fvrat = mpq_class(fndot, ftexp10);

        if(compop == 1){ // <=
            if(fvrat <= ftrat){
                tfbool.push_back("1");
            }else{
                tfbool.push_back("0");
            }
            
        }else if(compop == 3){ // >=
            if(fvrat >= ftrat){
                tfbool.push_back("1");
            }else{
                tfbool.push_back("0");
            }
        }else{
            cout<<"Comparison operator not supported!"<<endl;
        }
    }

    return tfbool;
}

vector<zone<int>> bool_to_edge_zone(vector<int> timeVec,
    vector<string> fvec, int prevOneIn){
    vector<zone<int>> zlr;

    int prevOne = 0;

    for(int i=0;i<timeVec.size()-1;i++){
        int exp10 = exponentOf10(placesAfterDot(fvec[i]));
        int fvectemp = removeDot(fvec[i]);
        if(i==0){
            prevOne = fvectemp;
        }else{
            if(fvectemp != prevOne){
                if( (prevOneIn == 1 && fvectemp > prevOne) || 
                    (prevOneIn == 0 && fvectemp < prevOne) ){
                    zone<int> ztemp = zone<int>::make_from_period_both_anchor(timeVec[i], 
                        timeVec[i]);
                    zlr.push_back(ztemp);
                }
                prevOne = fvectemp;
            }
        }
    }
    return zlr;
}

vector<zone<int>> bool_to_zone(vector<int> timeVec, 
    vector<string> fvec, int prevOneIn){
    vector<zone<int>> zlr;

    int ztstart = 0, ztend = 0;
    int prevOne = 1-prevOneIn;
    
    for(int i=0;i<timeVec.size()-1;i++){
        int exp10 = exponentOf10(placesAfterDot(fvec[i]));
        int fvectemp = removeDot(fvec[i]);
        if(fvectemp==1-prevOneIn){
            if(prevOne == prevOneIn){
                zone<int> ztemp = 
                    zone<int>::make_from({ztstart, ztend, ztstart, ztend, 0, ztend-ztstart},
                        {1,1,1,1,1,1});
                zlr.push_back(ztemp);
            }
            prevOne = 1-prevOneIn;
        }else if(fvectemp==prevOneIn){
            if(prevOne == prevOneIn){
                ztend = timeVec[i+1];
            }else{
                prevOne = prevOneIn;
                ztstart = timeVec[i];
                ztend   = timeVec[i+1];
            }
        }else{
            cerr<<"Error:Non-Boolean predicate"<<endl;
            exit(0);
        }
    }
    if(prevOne == prevOneIn){
        zone<int> ztemp = 
                    zone<int>::make_from({ztstart, ztend, ztstart, ztend, 0, ztend-ztstart},
                        {1,1,1,1,1,1});
                zlr.push_back(ztemp);
    }
    return zlr;
}


/* x <> p */
vector<pair<zone<int>,double>> param_porv_to_zone(vector<int> timeVec, vector<string> fvec,
    int begin, int end, int mxFlag){

    // Find the extremum
    vector<pair<zone<int>, double>> res;
    int mxIndex;
    double mxValue;
    for(int i=begin;i<=end;i++){
        if(i==begin){
            mxIndex = begin;
            mxValue = atof(fvec[i].c_str());
        }else{
            double currValue = atof(fvec[i].c_str());
            if(mxFlag == 3){
                if(currValue < mxValue){
                    mxValue = currValue;
                    mxIndex = i;
                }
            }else if(mxFlag == 1){
                if(currValue > mxValue){
                    mxValue = currValue;
                    mxIndex = i;
                }
            }
            
        }
    }

    zone<int> ztemp = zone<int>::make_from({timeVec[begin], timeVec[mxIndex+1], 
                        timeVec[mxIndex], timeVec[end+1], 0, timeVec[end+1]-timeVec[begin]},
                        {1,1,1,1,1,1});
    double ftemp = atof(fvec[mxIndex].c_str());

    vector<pair<zone<int>, double>> subRes1, subRes2;

    if(mxIndex > begin)
        subRes1 = param_porv_to_zone(timeVec, fvec, begin, mxIndex-1, mxFlag);
    
    res.insert(res.end(), subRes1.begin(), subRes1.end());
    res.push_back(pair<zone<int>, double>(ztemp, ftemp));
    
    if(mxIndex < end)
        subRes2 = param_porv_to_zone(timeVec, fvec, mxIndex+1, end, mxFlag);
    
    res.insert(res.end(), subRes2.begin(), subRes2.end());

    return res;
}

#endif // HELPER_MPTRE_HPP