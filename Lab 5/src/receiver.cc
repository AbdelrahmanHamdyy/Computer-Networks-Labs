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

#include "receiver.h"
#include "customizedMessage_m.h"
#include <bitset>
#include <vector>
#include <cstdlib>

Define_Module(Receiver);

void Receiver::initialize()
{
    // TODO - Generated method body
    CustomizedMessage_Base * newMessage = new CustomizedMessage_Base("new Message");
    newMessage->setM_Type(1);
    send(newMessage, "out");
}

void Receiver::handleMessage(cMessage *msg)
{
    EV << "*****************************************"<<std::endl;
    EV << "Receiver"<<std::endl;
    // TODO - Generated method body
    CustomizedMessage_Base * receivedMsg = check_and_cast<CustomizedMessage_Base*>(msg);
    const int WORD_LENGTH = 8;

    std::string message = receivedMsg->getM_Payload();

    std::bitset<WORD_LENGTH> result(receivedMsg->getM_Header());
    for (int i = 0; i < message.length(); i++) {
        std::bitset<WORD_LENGTH> bset(message[i]);
        result ^= bset;
    }
    result ^= receivedMsg->getM_Trailer();

    cancelAndDelete(receivedMsg);
    CustomizedMessage_Base * newMessage = new CustomizedMessage_Base("new Message");
    if (result.to_ulong() == 0) {
        EV << "The Received message is \"" << message << "\"." << std::endl;
        newMessage->setM_Type(1);
    } else {
        EV << "Error" << std::endl;
        newMessage->setM_Type(0);
    }
    send(newMessage, "out");
}
