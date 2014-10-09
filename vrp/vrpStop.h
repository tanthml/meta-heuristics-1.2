/* 
 * File:   vrpStop.h
 * Author: Administrator
 *
 * Created on June 7, 2012, 4:21 PM
 */

#ifndef VRPSTOP_H
#define	VRPSTOP_H
#include "vrpDefine.h"

class vrpStop : public edaSerialize {
public:
  vrpStop();
  vrpStop(const vrpStop& stop);
  vrpStop *clone() const;
  virtual ~vrpStop();

  void printOn(ostream& os) const;
  void debug(ostream& os) const;

  vrpStop& operator =(const vrpStop &stop);
  bool operator ==(const vrpStop &stop) const;

  void Serialize(edaBuffer &buf, bool pack);
  setClassID(_USERCLASSID_ + _CLSID_VRP_STOP_);


  const char* className() const {
      return "vrpStop";
  }

public:
  unsigned int ID; //index in original stop
  double X; // X coordinate
  double Y; // Y coordinate
  unsigned int Load; // amount waste at stop
  unsigned int EarlyTime; // early time window
  unsigned int LateTime; // late time window
  unsigned int ServiceTime; //time for unload and load waste 
  unsigned int Type; //type of stop ( regular_stop , landfill, depot)
  unsigned int Group; //group of regular stop
};
ostream& operator<<(ostream &os, const vrpStop &stop);
#endif	/* VRPSTOP_H */

