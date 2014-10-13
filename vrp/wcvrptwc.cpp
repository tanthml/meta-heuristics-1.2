/* 
 * File:   VRPMain.cpp
 * Author: Tieu Minh
 *
 * Created on November 21, 2012, 3:18 PM
 */

#include <iostream>
#include "../vrp/vrpLibrary.h"

using namespace std;

int main(int argc, char** argv) {
  EDAMetasearchStart (argc, argv);  
  if (argc != 2)
  {
    std::cerr << "Usage : ./" <<  __progname
              << " [heuristic] [instance] [parameters]" << std::endl;
  }
  else
  {
    vrpProblem *vrpPro = new vrpProblem(argv[1]);
    if( strcmp(argv[2],'HC') == 0 ) {
        edaSolutionList list;
        for(unsigned int i = 0; i < 1; i++) {
          vrpSolution *vrpSol = new vrpSolution (vrpPro); 
          vrpSol->init();
          list.push_back(vrpSol);
        }	

        vrpInterchangeMove optMove;
        vrpInterchangeNext optNext(vrpPro);
        if(strcmp(argv[3],'Best') == 0) {
            edaBestImprSelect moveSelect;
        }
        else {
            edaFirstImprSelect moveSelect;
        }
        unsigned int numloop = atoi(argv[4])
        edaGenContinue cont; 
        edaHC hcSearch(&optMove, &optNext, &moveSelect, &cont);  

        edaSeqWrapperControl sfControl; 
        sfControl.insertVertex (&hcSearch);   

        if (!sfControl.search (list))
        {
            cout << "Error: Cannot execute search" << std::endl;
        }
        else
        {
            vrpSolution* vrpSol = (vrpSolution*) list.getBest();
            cout << "[To Fitness] " << vrpSol->evaluate () << endl;
            cout << "[To Total Dist] " << vrpSol->getTotalDist () << endl;
            cout << "[To Total Wait] " << vrpSol->getTotalWaitTime () << endl;
            cout << "[Vehicles] " << vrpSol->size() << endl;
            cout << "[Route] " << *vrpSol << endl;
            cout << "------------------------------------------------------------------------------------------" << endl;
            vrpSol->debug(cout);
        }
    }
  }
  EDAMetasearchStop ();
  return 0;
}

edaSerialize *
userClassGenerate (int clsid)
{
  switch (clsid)
  {
    case _USERCLASSID_ + _CLSID_VRP_PROBLEM_:
      return new vrpProblem;

    case _USERCLASSID_ + _CLSID_VRP_STOP_:
      return new vrpStop;

    case _USERCLASSID_ + _CLSID_VRP_GROUP_CONFLICT_:
      return new vrpGroupConflict;

    case _USERCLASSID_ + _CLSID_VRP_SOLUTION_:
      return new vrpSolution;

    case _USERCLASSID_ + _CLSID_VRP_ROUTE_:
      return new vrpRoute;

    case _USERCLASSID_ + _CLSID_VRP_SUBROUTE_:
      return new vrpSubRoute;
    
    case _USERCLASSID_ + _CLSID_VRP_CONST_:
      return new vrpConst; 

    case _USERCLASSID_ + _CLSID_VRP_SUBROUTE_MOVE_:
      return new vrpSubRouteMove;
      
    case _USERCLASSID_ + _CLSID_VRP_SUBROUTE_NEXT_:
      return new vrpSubRouteNext;
      
    case _USERCLASSID_ + _CLSID_VRP_ROUTE_MOVE_:
      return new vrpRouteMove;
      
    case _USERCLASSID_ + _CLSID_VRP_ROUTE_NEXT_:
      return new vrpRouteNext;
      
    case _USERCLASSID_ + _CLSID_VRP_INTERCHANGE_MOVE_:
      return new vrpInterchangeMove;
      
    case _USERCLASSID_ + _CLSID_VRP_INTERCHANGE_NEXT_:
      return new vrpInterchangeNext;
    
    case _USERCLASSID_ + _CLSID_VRP_CYCLIC_MOVE_:
      return new vrpCyclicMove;
      
    case _USERCLASSID_ + _CLSID_VRP_CYCLIC_NEXT_:
      return new vrpCyclicNext;  
      
    case _USERCLASSID_ + _CLSID_VRP_INTERCHANGE_RAND_:
      return new vrpInterchangeRand;      
      
    case _USERCLASSID_ + _CLSID_VRP_REPRESENTATION_:
      return new vrpRepresentation;
      
    default:
      cerr << "Unknown classId " << clsid 
              << " for object generation!!!" << endl;
      exit (-1);
  }
}