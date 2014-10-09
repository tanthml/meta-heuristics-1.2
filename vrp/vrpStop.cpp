/* 
 * File:   vrpStop.cpp
 * Author: Administrator
 * 
 * Created on June 7, 2012, 4:21 PM
 */

#include <strings.h>
#include "vrpStop.h"

vrpStop::vrpStop() {}

vrpStop::vrpStop(const vrpStop& stop) {
    ID = stop.ID;
    X = stop.X;
    Y = stop.Y;
    Load = stop.Load;
    EarlyTime = stop.EarlyTime;
    LateTime = stop.LateTime;
    ServiceTime = stop.ServiceTime;
    Type = stop.Type;
    Group = stop.Group;
}

vrpStop *vrpStop::clone() const {
    return new vrpStop(*this);
}

vrpStop::~vrpStop() {}

void vrpStop::printOn(ostream& os) const {
  os << (int)ID;
}
void vrpStop::debug(ostream& os) const {
  os << (int)ID << "\t";
  os << X << "\t";
  os << Y << "\t";
  os << (int)EarlyTime<< "\t";
  os << (int)LateTime << "\t";
  os << (int)ServiceTime << "\t";
  os << (int)Load << "\t";
  os << (int)Type << "\t";
  os << (int)Group << "\t";
  os << endl;
} 
void vrpStop::Serialize(edaBuffer &buf, bool pack) 
{
    if ( pack ){
        buf.Pack( &ID );
        buf.Pack( &X );
        buf.Pack( &Y );
        buf.Pack( &Load );
        buf.Pack( &EarlyTime );
        buf.Pack( &LateTime );
        buf.Pack( &ServiceTime );
        buf.Pack( &Type );
        buf.Pack( &Group );
    } 
    else {
        buf.UnPack( &ID );
        buf.UnPack( &X );
        buf.UnPack( &Y );
        buf.UnPack( &Load );
        buf.UnPack( &EarlyTime );
        buf.UnPack( &LateTime );
        buf.UnPack( &ServiceTime );
        buf.UnPack( &Type );
        buf.UnPack( &Group );
    }
}

vrpStop& vrpStop::operator = (const vrpStop &stop) {
    ID = stop.ID;
    EarlyTime = stop.EarlyTime;
    Group = stop.Group;
    LateTime = stop.LateTime;
    Load = stop.Load;
    ServiceTime = stop.ServiceTime;
    Type = stop.Type;
    X = stop.X;
    Y = stop.Y;
    return *this;
}

bool vrpStop::operator == (const vrpStop &stop) const {
    if(ID != stop.ID)
        return false;
    if(EarlyTime != stop.EarlyTime)
        return false;
    if(Group != stop.Group)
        return false;
    if(LateTime != stop.LateTime)
        return false;
    if(Load != stop.Load)
        return false;
    if(ServiceTime != stop.ServiceTime)
        return false;
    if(Type != stop.Type)
        return false;
    if(X != stop.X)
        return false;
    if(Y != stop.Y)
        return false;
    return true;
}
ostream& operator << (ostream &os, const vrpStop &stop) {
    stop.printOn(os);
    return os;
}
