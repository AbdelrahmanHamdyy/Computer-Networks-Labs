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

#include "Player1.h"
using namespace std;

Define_Module(Player1);

void Player1::initialize()
{
    int n = par("guess").intValue();
    cMessage* msg = new cMessage(to_string(n).c_str());
    send(msg, "out");
}

void Player1::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getFullName(), "Wrong") == 0) {
        msg->setName(to_string(par("guess").intValue()).c_str());
        send(msg, "out");
    } else {
        EV << "Congratulations! You've guessed the correct number!" << endl;
        cancelAndDelete(msg);
    }
}
