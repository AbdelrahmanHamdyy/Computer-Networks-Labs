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

#include "RingNode.h"
#include <string>

Define_Module(RingNode);

void RingNode::initialize()
{
    EV << "Starting Node " << getIndex() << endl;
    if(getIndex()==0){
        send((new cMessage("0")),"ports$o",0);
    }
}

void RingNode::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(getIndex()==0){
      int value = atoi(msg->getName())+1;
      EV << "Number of Nodes is " <<  std::to_string(value) << endl;
      cancelAndDelete(msg);
      return;
    }
    int nextIdx = atoi(msg->getName())+1;
    msg->setName((std::to_string(nextIdx)).c_str());
    send(msg,"ports$o",1);
}
