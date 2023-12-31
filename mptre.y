%{
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <chrono>
#include <map>
#include <ppl.hh>
#include <gmpxx.h>


using namespace Parma_Polyhedra_Library;
using namespace Parma_Polyhedra_Library::IO_Operators;

typedef Box<Interval<int,Integer_Interval_Info>> ppl_intbox;

#include "./paramtimedrel/algos_timed_relations.hpp"
#include "./paramtimedrel/zone_parambox.hpp"
#include "./paramtimedrel/utils.hpp"
#include "./paramtimedrel/helper_mptre.hpp"

using namespace std::chrono;

using namespace std;

using namespace paramtimedrel;

extern int yylex();
extern int yyparse();
extern FILE* yyin;

int max_dot=0;
vector<int> time_vec;
vector<vector<string>> value_vec;
vector<pair<double,double>> label_intervals;
double mfv = 1316134912; // TODO: fix this add maximum value of double
int miv = 1316134912; // TODO: fix this add maximum value of int
parambox<double> parambox_global = parambox<double>::make({0,0,0},{mfv,mfv,mfv});

vector<vector<shared_ptr<gen_zone>>> mptre_stack;

void yyerror(const char* s);
%}

%union {
	int ival;
	double fval;
    char* fstr;
}

%token<ival> T_INT
%token<ival> P_STRING X_STRING
%token<fstr> T_FLOAT
%token<ival> GEQ GE LEQ LE
%token K_PLUS T_MINUS T_NOT T_LEFT T_RIGHT
%token T_SLEFT T_SRIGHT
%token T_EPS
%token<ival> T_RISE T_FALL
%token T_AND T_OR T_SEQCOMP
%left T_PLUS T_MINUS

%type<ival> compop edgeop

%start full_form;

%%

full_form: constraints ptre;

constraints: constraints constraint
      | T_LEFT constraint T_RIGHT
      | constraint
      ;

constraint: T_FLOAT LEQ P_STRING LEQ T_FLOAT {
            double d1 = atof($1);
            double d5 = atof($5);
            parambox_global = parambox<double>::add_lower_bound_on_parameter(parambox_global, 
            d1, 1, $3);
            parambox_global = parambox<double>::add_upper_bound_on_parameter(parambox_global, 
            d5, 1, $3);

            free($1);
            free($5);
      };

ptre: T_EPS {
            vector<shared_ptr<gen_zone>> zp_res;
            zone<int> ztemp = 
                    zone<int>::make_from({0, miv, 0, miv, 0, 0},
                        {1,1,1,1,1,1});
            zp_res.push_back(make_shared<zone_parambox<int,double>>(ztemp,
            parambox_global));
            mptre_stack.push_back(zp_res);
      }
      | edgeop X_STRING{
            vector<shared_ptr<gen_zone>> zp_res;
            vector<zone<int>> leaf_zones = bool_to_edge_zone(time_vec, value_vec[$2], $1);
            for(int i=0; i<leaf_zones.size(); i++){
                zp_res.push_back(make_shared<zone_parambox<int,double>>(leaf_zones[i], 
                    parambox_global));
            }
            mptre_stack.push_back(zp_res);
      }
      | X_STRING{
            vector<shared_ptr<gen_zone>> zp_res;
            vector<zone<int>> leaf_zones = bool_to_zone(time_vec, value_vec[$1], 1);
            for(int i=0; i<leaf_zones.size(); i++){
                zp_res.push_back(make_shared<zone_parambox<int,double>>(leaf_zones[i], 
                    parambox_global));
            }
            mptre_stack.push_back(zp_res);
      }
      | T_NOT X_STRING{
            vector<shared_ptr<gen_zone>> zp_res;
            vector<zone<int>> leaf_zones = bool_to_zone(time_vec, value_vec[$2], 0);
            for(int i=0; i<leaf_zones.size(); i++){
                zp_res.push_back(make_shared<zone_parambox<int,double>>(leaf_zones[i], 
                    parambox_global));
            }
            mptre_stack.push_back(zp_res);
      }
      | porv
      | ptre K_PLUS {
            vector<shared_ptr<gen_zone>> imp;
            imp = mptre_stack.back();
            mptre_stack.pop_back();

            vector<shared_ptr<gen_zone>> zp_res = 
                gen_transitive_closure(imp);
            mptre_stack.push_back(zp_res);
      }
      | T_LEFT ptre T_RIGHT {

      }
      | ptre T_SEQCOMP ptre{
            vector<shared_ptr<gen_zone>> imp1, imp2;
            
            imp2 = mptre_stack.back();
            mptre_stack.pop_back();
            imp1 = mptre_stack.back();
            mptre_stack.pop_back();
            
            vector<shared_ptr<gen_zone>> zp_res = 
                gen_concatenation(imp1, imp2);
            mptre_stack.push_back(zp_res);
      }
      | ptre T_AND ptre{
            vector<shared_ptr<gen_zone>> imp1, imp2;
            
            imp2 = mptre_stack.back();
            mptre_stack.pop_back();
            imp1 = mptre_stack.back();
            mptre_stack.pop_back();
            
            vector<shared_ptr<gen_zone>> zp_res = 
                gen_intersection(imp1, imp2);
            mptre_stack.push_back(zp_res);
      }
      | ptre T_OR ptre{
            vector<shared_ptr<gen_zone>> imp1, imp2;
            
            imp2 = mptre_stack.back();
            mptre_stack.pop_back();
            imp1 = mptre_stack.back();
            mptre_stack.pop_back();
            
            vector<shared_ptr<gen_zone>> zp_res = 
                gen_union(imp1, imp2);
            mptre_stack.push_back(zp_res);
      }
      | ptre T_SLEFT T_INT T_INT T_SRIGHT{
            vector<shared_ptr<gen_zone>> imp;
            imp = mptre_stack.back();
            mptre_stack.pop_back();

            int dmin1 = $3;
            int dmax1 = $4;

            vector<shared_ptr<gen_zone>> zp_res;

            for(int i=0; i<imp.size(); i++){
                shared_ptr<zone_parambox<int,double>> zpptemp = 
                    dynamic_pointer_cast<zone_parambox<int,double>>(imp[i]);

                zone<int> ztemp = zpptemp->get_sub_zone();
                ztemp = zone<int>::duration_restriction(ztemp, 
                    timedrel::lower_bound<int>::closed(dmin1), 
                    timedrel::upper_bound<int>::closed(dmax1)
                );
                parambox<double> pbtemp = zpptemp->get_sub_parambox();

                zp_res.push_back(make_shared<zone_parambox<int,double>>(ztemp, pbtemp));
                mptre_stack.push_back(zp_res);
            }

            mptre_stack.push_back(zp_res);
      }
;

compop: GEQ| LEQ;
edgeop: T_RISE | T_FALL;

porv: X_STRING compop T_FLOAT{
            vector<string> tfvec = value_vec[$1];
            vector<string> tfbool;

            tfbool = get_bool_from_porv(tfvec, $2, string($3));

            vector<shared_ptr<gen_zone>> zp_res;
            vector<zone<int>> leaf_zones = bool_to_zone(time_vec, tfbool, 1);
            for(int i=0; i<leaf_zones.size(); i++){
                zp_res.push_back(make_shared<zone_parambox<int,double>>(leaf_zones[i], 
                    parambox_global));
            }
            mptre_stack.push_back(zp_res);

            free($3);
      }
      | edgeop X_STRING compop T_FLOAT {
            vector<string> tfvec = value_vec[$2];
            vector<string> tfbool;

            tfbool = get_bool_from_porv(tfvec, $3, string($4));

            vector<shared_ptr<gen_zone>> zp_res;
            vector<zone<int>> leaf_zones = bool_to_edge_zone(time_vec, tfbool, $1);
            for(int i=0; i<leaf_zones.size(); i++){
                zp_res.push_back(make_shared<zone_parambox<int,double>>(leaf_zones[i], 
                    parambox_global));
            }
            mptre_stack.push_back(zp_res);

            free($4);
      }
      | X_STRING compop P_STRING {
            vector<string> fvec = value_vec[$1];
            vector<pair<zone<int>, double>> zd_res;
            vector<shared_ptr<gen_zone>> zp_res;

            if(label_intervals.size()==1){
                vector<int> ntv;
                vector<string> nfv;
                compute_sub_signal(label_intervals[0], time_vec, fvec, ntv, nfv);
                zd_res = param_porv_to_zone(ntv, nfv, 0, ntv.size()-2, $2);
            }else{
                zd_res = param_porv_to_zone(time_vec, fvec, 0, time_vec.size()-2, $2);    
            }

            for(int i=0; i<zd_res.size(); i++){
                parambox<double> pbtemp = parambox_global;
                int mxflag = $2;
                if(mxflag == 3){
                    pbtemp = parambox<double>::add_upper_bound_on_parameter(pbtemp,
                        zd_res[i].second, 1, $3);
                }else if(mxflag == 1){
                    pbtemp = parambox<double>::add_lower_bound_on_parameter(pbtemp,
                        zd_res[i].second, 1, $3);
                }else{
                    // TODO: "<" and ">" not yet added.
                    cout<<"Comparison operator not yet supported!"<<endl;
                    exit(0);
                }

                zp_res.push_back(make_shared<zone_parambox<int,double>>(zd_res[i].first, 
                    pbtemp));
            }

            mptre_stack.push_back(zp_res);
      }
      | edgeop X_STRING compop P_STRING {
            vector<string> fvec = value_vec[$1];
            vector<shared_ptr<gen_zone>> zp_res;
            int time_scope_begin, time_scope_end;
            double prev_fv;

            if(time_vec.size()!=0){
                time_scope_begin = time_vec[0];
                time_scope_end   = time_vec[time_vec.size()-1];

                if(label_intervals.size()==1){
                    time_scope_begin = label_intervals[0].first;
                    time_scope_end   = label_intervals[0].second;
                }

                prev_fv = atof(fvec[0].c_str());
            }



            for(int i=0; i<time_vec.size(); i++){
                if(i==0){
                    continue;
                }

                double current_fv = atof(fvec[i].c_str());

                if ( (time_scope_begin <= time_vec[i]) &&  (time_vec[i] <= time_scope_end) ){
                    zone<int> ztemp = zone<int>::make_from_period_both_anchor(time_vec[i],
                            time_vec[i]);
                    parambox<double> pbtemp = parambox_global;

                    int edge_index = $1;
                    int comp_index = $3;

                    if(edge_index == 1){
                        if(comp_index == 1){
                            pbtemp = parambox<double>::add_upper_bound_on_parameter(pbtemp,
                            prev_fv, 0, $4);
                            pbtemp = parambox<double>::add_lower_bound_on_parameter(pbtemp,
                            current_fv, 1, $4);
                        }else if(comp_index == 3){
                            pbtemp = parambox<double>::add_upper_bound_on_parameter(pbtemp,
                            current_fv, 1, $4);
                            pbtemp = parambox<double>::add_lower_bound_on_parameter(pbtemp,
                            prev_fv, 0, $4);
                        }
                    }else if(edge_index == 0){
                        if(comp_index == 1){
                            pbtemp = parambox<double>::add_upper_bound_on_parameter(pbtemp,
                            current_fv, 0, $4);
                            pbtemp = parambox<double>::add_lower_bound_on_parameter(pbtemp,
                            prev_fv, 1, $4);
                        }else if(comp_index == 3){
                            pbtemp = parambox<double>::add_upper_bound_on_parameter(pbtemp,
                            prev_fv, 1, $4);
                            pbtemp = parambox<double>::add_lower_bound_on_parameter(pbtemp,
                            current_fv, 0, $4);
                        }
                    }

                    zp_res.push_back(make_shared<zone_parambox<int,double>>(ztemp,
                        pbtemp));
                }  

                prev_fv = current_fv;
            }

            mptre_stack.push_back(zp_res);
      }
;

%%

int main(int argc, char** argv) {
    // User passes number of parameters and we init parambox_global
    int num_params = atoi(argv[3]);
    vector<double> lb_vec_init(num_params, 0);
    vector<double> ub_vec_init(num_params, mfv);
    parambox_global = parambox<double>::make(lb_vec_init, ub_vec_init);

    auto start = high_resolution_clock::now();

    read_signal_file(argv[2], time_vec, value_vec);
    cout<<"time_vec size:"<<time_vec.size()<<endl;
    cout<<"value_vec size:"<<value_vec.size()<<endl;

    yyin = fopen(argv[1],"r");
    do {
        yyparse();
    } while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}