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

#include "Player2.h"
using namespace std;

Define_Module(Player2);

void Player2::initialize()
{
    EV << "Target: " << par("target").intValue() << endl;
}

void Player2::handleMessage(cMessage *msg)
{
    int n = par("target").intValue();
    if (atoi(msg->getFullName()) == n) {
        msg->setName("Correct");
        send(msg, "out");
    } else {
        msg->setName("Wrong");
        send(msg, "out");
    }
}
