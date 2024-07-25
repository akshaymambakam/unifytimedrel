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
#include "./paramtimedrel/parametric_interval.hpp"
#include "./paramtimedrel/utils.hpp"
#include "./paramtimedrel/helper_pebtre.hpp"

using namespace std::chrono;

using namespace std;

using namespace paramtimedrel;

extern int yylex();
extern int yyparse();
extern FILE* yyin;

vector<int> time_vec;
vector<int> event_vec;
vector<pair<int,int>> label_intervals;

vector<Constraint> paramS;

vector<Linear_Expression> lestack;

vector<vector<shared_ptr<compound_interval>>> pebtre_stack;

void yyerror(const char* s);
%}

%union {
	int ival;
	float fval;
}

%token<ival> T_INT
%token<ival> P_STRING Y_STRING
%token<ival> LEQ GEQ
%token K_PLUS T_LEFT T_RIGHT T_PLUS T_MINUS T_MULTIPLY
%token T_SLEFT T_SRIGHT
%token T_EPS
%token T_AND T_OR T_SEQCOMP

%type<ival> expression

%start full_form;

%%

full_form: constraints ptre;

constraints: constraints constraint
      | T_LEFT constraint T_RIGHT
      | constraint
      ;

constraint: expression GEQ expression {
        Linear_Expression le2=lestack.back();
        lestack.pop_back();
        Linear_Expression le1=lestack.back();
        lestack.pop_back();
        paramS.push_back(le1>=le2);
      } 
      | expression LEQ expression{
        Linear_Expression le2=lestack.back();
        lestack.pop_back();
        Linear_Expression le1=lestack.back();
        lestack.pop_back();
        paramS.push_back(le1<=le2);
      }
      ;

expression: 
      T_INT             
      {
            lestack.push_back(Linear_Expression($1));
            $$=0;
      }
      | expression T_PLUS expression
      {
            $$ = $1 || $3;
            Linear_Expression le1=lestack.back();
            lestack.pop_back();
            Linear_Expression le2=lestack.back();
            lestack.pop_back();
            lestack.push_back(le1+le2);
      }
      | expression T_MINUS expression   
      {
            $$ = $1 || $3;
            Linear_Expression le1=lestack.back(); 
            lestack.pop_back();
            Linear_Expression le2=lestack.back();
            lestack.pop_back();
            lestack.push_back(le2-le1);
      }
      | T_INT T_MULTIPLY expression 
      {     
            $$ = 1;
            Linear_Expression le1=lestack.back(); 
            lestack.pop_back(); 
            lestack.push_back($1*le1);
      }
      | T_LEFT expression T_RIGHT
      {
            $$ = $2;
      }
      | P_STRING 
      {
            $$ = 1;
            lestack.push_back(Linear_Expression(Variable($1+3)));
      }
;

ptre: T_EPS {
            Variable t0(0), t1(1);
            vector<shared_ptr<compound_interval>> iz_res;
            vector<timed_interval<int>> ti_temp = eps_to_timed_intervals(time_vec, event_vec);
            
            Constraint_System zoneTemp;
            for(int i=0;i<paramS.size();i++){
                zoneTemp.insert(paramS[i]);
            }

            for(int i=0; i<ti_temp.size(); i++){
                Constraint_System zoneTemp2 = zoneTemp;
                pair<int,int> tp = ti_temp[i].get_time_interval_as_pair();
                zoneTemp2.insert(t0==tp.first);
                zoneTemp2.insert(t1==tp.second);

                iz_res.push_back(make_shared<parametric_interval<int>>(ti_temp[i],
                    C_Polyhedron(zoneTemp2)));
            }

            pebtre_stack.push_back(iz_res);
      }
      | Y_STRING {
            Variable t0(0), t1(1);
            vector<shared_ptr<compound_interval>> itre_ret;
            vector<timed_interval<int>> ti_temp = event_to_timed_intervals(time_vec, event_vec, $1);

            Constraint_System zoneTemp;
            for(int i=0;i<paramS.size();i++){
                zoneTemp.insert(paramS[i]);
            }

            for(int i=0; i<ti_temp.size(); i++){
                Constraint_System zoneTemp2 = zoneTemp;
                pair<int,int> tp = ti_temp[i].get_time_interval_as_pair();
                zoneTemp2.insert(t0<=tp.second);
                zoneTemp2.insert(t0>=tp.first);
                zoneTemp2.insert(t1==tp.second);

                itre_ret.push_back(make_shared<parametric_interval<int>>(ti_temp[i],
                    C_Polyhedron(zoneTemp2)));
            }
            pebtre_stack.push_back(itre_ret);
      }
      | ptre K_PLUS {
            vector<shared_ptr<compound_interval>> iz;
            iz = pebtre_stack.back();
            pebtre_stack.pop_back();
            
            vector<shared_ptr<compound_interval>> iz_res = 
                kleene_plus_interval_relations(iz);
            pebtre_stack.push_back(iz_res);
      }
      | T_LEFT ptre T_RIGHT {

      }
      | ptre T_SEQCOMP ptre{
            vector<shared_ptr<compound_interval>> iz1, iz2;
            
            iz2 = pebtre_stack.back();
            pebtre_stack.pop_back();
            iz1 = pebtre_stack.back();
            pebtre_stack.pop_back();
            
            vector<shared_ptr<compound_interval>> iz_res = 
                concatenation_interval_relations(iz1, iz2);
            pebtre_stack.push_back(iz_res);
            
      }
      | ptre T_AND ptre{
            vector<shared_ptr<compound_interval>> iz1, iz2;
            
            iz2 = pebtre_stack.back();
            pebtre_stack.pop_back();
            iz1 = pebtre_stack.back();
            pebtre_stack.pop_back();

            vector<shared_ptr<compound_interval>> iz_res = 
                intersection_interval_relations(iz1, iz2);
            pebtre_stack.push_back(iz_res);
      }
      | ptre T_OR ptre{
            vector<shared_ptr<compound_interval>> iz1, iz2;
            
            iz2 = pebtre_stack.back();
            pebtre_stack.pop_back();
            iz1 = pebtre_stack.back();
            pebtre_stack.pop_back();

            vector<shared_ptr<compound_interval>> iz_res = 
                union_interval_relations(iz1, iz2);
            pebtre_stack.push_back(iz_res);
      }
      | ptre T_SLEFT expression expression T_SRIGHT{
            Variable t1(0),t2(1);
            vector<shared_ptr<compound_interval>> iz;
            iz = pebtre_stack.back();
            pebtre_stack.pop_back();

            Linear_Expression le2 = lestack.back();
            lestack.pop_back();
            Linear_Expression le1 = lestack.back();
            lestack.pop_back();

            Constraint A(le1<=t2-t1);
            Constraint B(t2-t1<=le2);


            vector<shared_ptr<compound_interval>> iz_res;
            for(int i=0; i<iz.size(); i++){
                shared_ptr<parametric_interval<int>> pitemp = 
                    dynamic_pointer_cast<parametric_interval<int>>(iz[i]);
                shared_ptr<parametric_interval<int>> pires = 
                    pitemp->add_duration_constraints(A,B);
                iz_res.push_back(pires);
            }

            pebtre_stack.push_back(iz_res);
      }
;

%%

int main(int argc, char** argv) {
    // User passes number of parameters and we init parambox_global
    int num_params = atoi(argv[3]);

    auto start = high_resolution_clock::now();

    read_event_file(argv[2], time_vec, event_vec);
    
    yyin = fopen(argv[1],"r");
	do {
		yyparse();
	} while(!feof(yyin));

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    cout<<"time: "<<duration.count()<<" ms"<<endl;

    // Print the results here.
    print_interval_relations(pebtre_stack.back());

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}