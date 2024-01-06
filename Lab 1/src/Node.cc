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

#include "Node.h"
using namespace std;

Define_Module(Node);
int count = 0;
bool on = true;

cMessage* generateMessage(const char* name) {
    string text;
    text = (strcmp(name, "Tic") == 0) ? "Tic_" : "Toc_";
    cMessage* msg = new cMessage((text + to_string(count)).c_str());
    count++;
    return msg;
}

void Node::initialize()
{
    // TODO - Generated method body
    if (strcmp(getName(), "Tic") == 0) {
        cMessage* msg = generateMessage(getName());
        send(msg, "out");
    }
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if (count == 10) {
        on = false;
    }
    if (on) {
        msg = generateMessage(getName());
        send(msg, "out");
    }
}
