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

#include "./paramtimedrel/algos_interval_relations.hpp"
#include "./paramtimedrel/interval_parambox.hpp"
#include "./paramtimedrel/utils.hpp"
#include "./paramtimedrel/helper_eitre.hpp"

using namespace std::chrono;

using namespace std;

using namespace paramtimedrel;

extern int yylex();
extern int yyparse();
extern FILE* yyin;

vector<int> time_vec;
vector<int> event_vec;
vector<pair<int,int>> label_intervals;
int miv = 1316134912; // TODO: fix this add maximum value of integer
parambox<int> parambox_global = parambox<int>::make({0,0,0},{miv,miv,miv});

vector<vector<shared_ptr<compound_interval>>> eitre_stack;

void yyerror(const char* s);
%}

%union {
	int ival;
	float fval;
}

%token<ival> T_INT
%token<ival> P_STRING Y_STRING
%token<ival> LEQ
%token K_PLUS T_LEFT T_RIGHT
%token T_SLEFT T_SRIGHT
%token T_EPS
%token T_AND T_OR T_SEQCOMP

%type<ival> duration_limit

%start full_form;

%%

full_form: constraints ptre;

constraints: constraints constraint
      | T_LEFT constraint T_RIGHT
      | constraint
      ;

constraint: T_INT LEQ P_STRING LEQ T_INT {
            parambox_global = parambox<int>::add_lower_bound_on_parameter(parambox_global, 
            $1, 1, $3);
            parambox_global = parambox<int>::add_upper_bound_on_parameter(parambox_global, 
            $5, 1, $3);
      };

ptre: T_EPS {
            vector<shared_ptr<compound_interval>> iz_res;
            vector<timed_interval<int>> ti_temp = eps_to_timed_intervals(time_vec, event_vec);
            
            for(int i=0; i<ti_temp.size(); i++){
                iz_res.push_back(make_shared<interval_parambox<int,int>>(ti_temp[i],
                    parambox_global));
            }

            eitre_stack.push_back(iz_res);
      }
      | Y_STRING {
            vector<shared_ptr<compound_interval>> itre_ret;
            vector<timed_interval<int>> ti_temp = event_to_timed_intervals(time_vec, event_vec, $1);
            for(int i=0; i<ti_temp.size(); i++){
                itre_ret.push_back(make_shared<interval_parambox<int,int>>(ti_temp[i],
                    parambox_global));
            }
            eitre_stack.push_back(itre_ret);
      }
      | ptre K_PLUS {
            vector<shared_ptr<compound_interval>> iz;
            iz = eitre_stack.back();
            eitre_stack.pop_back();
            
            vector<shared_ptr<compound_interval>> iz_res = 
                kleene_plus_interval_relations(iz);
            eitre_stack.push_back(iz_res);
      }
      | T_LEFT ptre T_RIGHT {

      }
      | ptre T_SEQCOMP ptre{
            vector<shared_ptr<compound_interval>> iz1, iz2;
            
            iz2 = eitre_stack.back();
            eitre_stack.pop_back();
            iz1 = eitre_stack.back();
            eitre_stack.pop_back();
            
            vector<shared_ptr<compound_interval>> iz_res = 
                concatenation_interval_relations(iz1, iz2);
            eitre_stack.push_back(iz_res);
            
      }
      | ptre T_AND ptre{
            vector<shared_ptr<compound_interval>> iz1, iz2;
            
            iz2 = eitre_stack.back();
            eitre_stack.pop_back();
            iz1 = eitre_stack.back();
            eitre_stack.pop_back();

            vector<shared_ptr<compound_interval>> iz_res = 
                intersection_interval_relations(iz1, iz2);
            eitre_stack.push_back(iz_res);
      }
      | ptre T_OR ptre{
            vector<shared_ptr<compound_interval>> iz1, iz2;
            
            iz2 = eitre_stack.back();
            eitre_stack.pop_back();
            iz1 = eitre_stack.back();
            eitre_stack.pop_back();

            vector<shared_ptr<compound_interval>> iz_res = 
                union_interval_relations(iz1, iz2);
            eitre_stack.push_back(iz_res);
      }
      | ptre T_SLEFT duration_limit duration_limit T_SRIGHT{
            vector<shared_ptr<compound_interval>> iz;
            iz = eitre_stack.back();
            eitre_stack.pop_back();

            vector<shared_ptr<compound_interval>> iz_res;
            for(int i=0; i<iz.size(); i++){
                shared_ptr<interval_parambox<int,int>> ipbtemp = 
                    dynamic_pointer_cast<interval_parambox<int,int>>(iz[i]);
                pair<int,int> ptemp = (ipbtemp->get_sub_timed_interval()).get_time_interval_as_pair();
                int tival_duration = ptemp.second - ptemp.first;
                int lb_indicator = $3;
                int ub_indicator = $4;

                if( ((lb_indicator>=0) and (lb_indicator > tival_duration)) or
                    ((ub_indicator>=0) and (ub_indicator < tival_duration)) ){
                    // This means we have a violated constant duration bound.
                    // Therefore. There is no match. No need to add anything.
                }else{
                    if(lb_indicator<0){
                        int lb_param_id = (-lb_indicator)-1;
                        ipbtemp = 
                            ipbtemp->add_upper_bound_on_parameter(tival_duration, 1, lb_param_id);
                    }
                    if(ub_indicator<0){
                        int ub_param_id = (-ub_indicator)-1;
                        ipbtemp = 
                            ipbtemp->add_lower_bound_on_parameter(tival_duration, 1, ub_param_id);
                    }
                    if(ipbtemp->is_nonempty()){
                        iz_res.push_back(ipbtemp);
                    }
                }
                
            }

            eitre_stack.push_back(iz_res);
      }
      ;

duration_limit: 
      T_INT				
      {
            $$=$1;
      }
	  | P_STRING 
      {
            $$ = -(1+$1);
      }
;
%%

int main(int argc, char** argv) {
    // User passes number of parameters and we init parambox_global
    int num_params = atoi(argv[3]);
    vector<int> lb_vec_init(num_params, 0);
    vector<int> ub_vec_init(num_params, miv);
    parambox_global = parambox<int>::make(lb_vec_init, ub_vec_init);

    auto start = high_resolution_clock::now();

    read_event_file(argv[2], time_vec, event_vec);

    // Read label lists to do parametric identification
    vector<pair<int,int>> pos_labels;
    vector<pair<int,int>> neg_labels;
    if(argc > 4){
        read_label_file(argv[4], pos_labels);
        read_label_file(argv[5], neg_labels);
    }
    
    yyin = fopen(argv[1],"r");
	do {
		yyparse();
	} while(!feof(yyin));

    // Do parametric identification here
    int pos_success, neg_success;
    Pointset_Powerset<ppl_intbox> pos_param_set, neg_param_set;
    if(argc > 4){
        map<pair<int,int>, vector<parambox<int>>> pos_pi_map, neg_pi_map;
        create_param_identification_map(pos_labels, pos_pi_map, eitre_stack.back());
        create_param_identification_map(neg_labels, neg_pi_map, eitre_stack.back());
        pos_success = positive_example_param_identification(pos_pi_map, pos_param_set);
        neg_success = negative_example_param_identification(neg_pi_map, neg_param_set);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    cout<<"time: "<<duration.count()<<" ms"<<endl;

    // Print the results here.
    print_interval_relations(eitre_stack.back());

    if(argc > 4){
        if(pos_success == 1){
            cout<<"positive param set is:"<<endl;
            cout<<pos_param_set<<endl;
        }else{
            cout<<"positive param set is empty."<<endl;
        }
        if(neg_success == 1){
            cout<<"negative param set is:"<<endl;
            cout<<neg_param_set<<endl;
        }else{
            cout<<"negative param set is empty."<<endl;
        }
        if(pos_success and neg_success){
            cout<<"solution set is:"<<endl;
            Pointset_Powerset<ppl_intbox> solution_set = pos_param_set;
            solution_set.difference_assign(neg_param_set);
            cout<<solution_set<<endl;
        }
    }

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}