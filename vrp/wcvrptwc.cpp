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
    remove( "log" );
    EDAMetasearchStart (argc, argv);  
    if (argc < 5)
    {
      std::cerr << "Usage : ./" <<  __progname
              << " [instance] [HC] [Best/First] [NumLoop]\n" 
              << " Or : ./" <<  __progname
              << " [instance] [SA] [Linear/Exponent] [NumLoop] [InitTemp] [Threshold] [Quantity/Ratio]\n" 
              << " Or : ./" <<  __progname
              << " [instance] [TS] [Best/No] [NumLoop] [NumTabuList]\n" 
              << " Or : ./" <<  __progname
              << " [instance] [GA] [Rank/Weight] [NumLoop] [NumPop] [SelectRate] [CrossRate] [MuteRate]\n";
    }
    else
    {
      vrpProblem *vrpPro = new vrpProblem(argv[1]);
      //cout << *vrpPro << endl;
      vrpConst *vrpCon = new vrpConst();
      edaSolutionList list;
      for(unsigned int i = 0; i < 1; i++) {
          vrpSolution *vrpSol = new vrpSolution (vrpPro); 
          vrpSol->init();
          list.push_back(vrpSol);
      }
      edaSearch* search = NULL;

      if( strcmp(argv[2],"HC") == 0 ) {  
          vrpInterchangeMove optMove;
          vrpInterchangeNext optNext(vrpPro);
          edaMoveSelect* moveSelect = NULL;
          if(strcmp(argv[3],"Best") == 0) {
              moveSelect = new edaBestImprSelect();
          }
          else if(strcmp(argv[3],"First") == 0) {
              moveSelect = new edaFirstImprSelect();
          }        
          unsigned int numloop = atoi(argv[4]);
          edaGenContinue cont(numloop); 
          search = new edaHC(&optMove, &optNext, moveSelect, &cont);          
      }
      else if(strcmp(argv[2],"SA") == 0 ) {
          vrpInterchangeMove optMove;
          vrpInterchangeNext optNextRan(vrpPro);
          edaCoolingSchedule* coolingSchedule = NULL;               
          if(strcmp(argv[3],"Linear") == 0) {
              float threshold = atof(argv[6]); 
              float quantity = atof(argv[7]);
              coolingSchedule = new edaLinearCoolingSchedule(threshold, quantity);
          }
          else if (strcmp(argv[3],"Exponent") == 0) {
              float threshold = atof(argv[6]); 
              float ratio = atof(argv[7]);
              coolingSchedule = new edaExpCoolingSchedule(threshold, ratio);
          }   
          unsigned int numloop = atoi(argv[4]);
          edaGenContinue cont(numloop); 
          float initTemp = atof(argv[5]);
          search = new edaSA(&optMove, &optNextRan, &cont,  initTemp, coolingSchedule);  
      }
      else if(strcmp(argv[2],"TS") == 0 ) {
          vrpInterchangeMove optMove;
          vrpInterchangeNext optNext(vrpPro);

          edaAspirCrit* aspirCrit;       
          if(strcmp(argv[3],"Best") == 0) {
              aspirCrit = new edaImprBestFitAspirCrit();
          }
          else if(strcmp(argv[3],"No") == 0) {
              aspirCrit = new edaNoAspirCrit();
          }
          unsigned int numloop = atoi(argv[4]);
          edaGenContinue cont(numloop); 
          unsigned int numlist = atoi(argv[5]);
          edaSimpleMoveTabuList tabuList(numlist);        
          search = new edaTS(&optMove, &optNext, &tabuList, aspirCrit, &cont);  
      }
      else if(strcmp(argv[2],"GA") == 0 ) {
          vrpRepresentation repre(*vrpPro, *vrpCon);
          edaNaturalSelection* slect = NULL;
          if(strcmp(argv[3],"Rank") == 0) {
              float nRate = atof(argv[6]);
              slect = new edaRankSelection(nRate);
          }
          else if(strcmp(argv[3],"Weight") == 0) {
              float nRate = atof(argv[6]);
              slect = new edaRouletteWheelSelection(nRate);
          }
          unsigned int numloop = atoi(argv[4]);
          edaGenContinue cont(numloop);
          unsigned int numpop = atoi(argv[5]);
          for(unsigned int i = 1; i < numpop; i++) {
              vrpSolution *vrpSol = new vrpSolution (vrpPro); 
              vrpSol->init();
              list.push_back(vrpSol);
          }	        

          float cRate = atof(argv[7]);
          edaPartiallyMatchedCrossover cross(cRate);

          float mRate = atof(argv[8]);
          edaRandSwapMutation mute(mRate);   

          search = new edaGA(&cont, &repre, slect, &cross, &mute);
      }
      edaSeqWrapperControl sfControl; 
      sfControl.insertVertex(search);   

      if (!sfControl.search(list))
      {
          cout << "{\"Status\":\"Error\",\"Info\":\"Cannot execute search\"}";
      }
      else
      {
          vrpSolution* vrpSol = (vrpSolution*) list.getBest();
          cout << "{\"Status\":\"Success\",";
          cout << "\"Fitness\":" << -vrpSol->evaluate () << ",";
          cout << "\"Dist\":" << vrpSol->getTotalDist()/1000 << ",";
          cout << "\"Move\":" << vrpSol->getTotalMoveTime() << ",";
          cout << "\"Wait\":" << vrpSol->getTotalWaitTime() << ",";
          cout << "\"Vehicle\":" << vrpSol->size() << "}";
          //cout << "[Route] " << *vrpSol << endl;       
          vrpSol->writeCSVFile("log");
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