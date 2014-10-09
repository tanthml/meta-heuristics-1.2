/* 
 * File:   vrpProblem.h
 * Author: Administrator
 *
 * Created on June 7, 2012, 4:42 PM
 */

#ifndef VRPPROBLEM_H
#define	VRPPROBLEM_H

#include "vrpStop.h"
#include "vrpGroupConflict.h"


class vrpProblem: public edaProblem {
public:
    vrpProblem();
    vrpProblem(const vrpProblem &problem);
    vrpProblem(const char *filename);
    virtual ~vrpProblem();
    vrpProblem* clone() const;
    void load(const char* filename);    
    vrpProblem& operator = (const edaProblem &pro);
    vector<vrpStop*> getLandfill() const;
    vector<vrpStop*> getRegularStop() const;
    vrpStop* getDepot() const;
    vrpStop* getStop(const unsigned int id) const;
    unsigned int getNumStops() const;
    unsigned int getMaxCapacity() const;
    unsigned int getMaxTotalDist() const; 
    unsigned int getDist(const unsigned int id_1, const unsigned int id_2) const;
    unsigned int getTime(const unsigned int id_1, const unsigned int id_2) const;
    bool isConflict(const unsigned int group, const vector<unsigned int>& groups) const;  
    bool isConflict(const vector<unsigned int>& groups) const;
    void printOn(ostream& os) const;
    void printTable(const char* file_name);
    void Serialize(edaBuffer &buf, bool pack);
    setClassID(_USERCLASSID_ + _CLSID_VRP_PROBLEM_);

    const char* className() const {
        return "vrpProblem";
    }

private:    
    unsigned int _num_stops;
    unsigned int _speed;
    unsigned int _capacity_veh; //the capacity of the vehicle
    unsigned int _max_total_dist;
    unsigned int *_dist; //the distance between 2 stops
    vrpGroupConflict *_conflict_group; // the conflict group in problem
    vrpStop *_list_stops; //list stops have num_stops 
    unsigned int getMinutes(const unsigned int hour_minute) const;
    void easer();

};
ostream& operator<<(ostream &os, const vrpProblem &pro);
#endif	/* VRPPROBLEM_H */

