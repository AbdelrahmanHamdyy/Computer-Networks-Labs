//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Hub.h"
using namespace std;

Define_Module(Hub);

void Hub::initialize()
{
    int m = int(uniform(0, getParentModule()->par("N").intValue()));
    string s = "To Node " + to_string(m) + ": Hello from Hub";
    EV << s << endl;
    cMessage* msg = new cMessage(s.c_str());
    send(msg, "port$o", m);
}

void Hub::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        int m = int(uniform(0, getParentModule()->par("N").intValue()));
        string s = "To Node " + to_string(m) + ": Hello from Hub";
        EV << s << endl;
        msg->setName(s.c_str());
        send(msg, "port$o", m);
    } else {
        double interval = exponential(2.0);
        EV << "Sending after " << interval << endl;
        msg->setName("");
        scheduleAt(simTime() + interval, msg);
    }
}
