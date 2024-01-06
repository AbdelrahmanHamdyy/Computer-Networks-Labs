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

#include "sender.h"
#include "customizedMessage_m.h"
#include <bitset>
#include <vector>
#include <cstdlib>

Define_Module(Sender);

void Sender::initialize()
{
    // TODO - Generated method body
}

void Sender::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    // Firstly we need to convert the type of cMessage to our customized one
    CustomizedMessage_Base * receivedMsg = check_and_cast<CustomizedMessage_Base*>(msg);
    //Now We can access its data
    if( receivedMsg->getM_Type() != 2){
        cancelAndDelete(receivedMsg);
        //Setting RAndom settings
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        //Defining size of char count and parity bits
        const int WORD_LENGTH = 8;
        //Getting The Desired Message
        std::string originalMsg;
        EV << "*****************************************"<<std::endl;
        EV << "Sender"<<std::endl;
        std::cout << "Input: ";
        std::cin >> originalMsg;
        //Setting CharCount
        int characterCount = originalMsg.size() + 2;
        //Getting Binary Representation of char count to print it
        std::bitset<WORD_LENGTH> charCountBset(characterCount);
        //Getting Even Parity bits and starting to calculate it as even parity
        std::bitset<WORD_LENGTH> evenParityBset = charCountBset;
        //Getting The Real Value of Parity Bits
        for (char c : originalMsg) {
            std::bitset<WORD_LENGTH> bset(c);
            evenParityBset ^= bset;
        }

        int modify = std::rand() % 2;
        //EV << "50% Chance [0/1]: " << modify << std::endl;

        if (modify == 1) {
            int totalLength = WORD_LENGTH * characterCount;
            int errorBit = std::rand() % (totalLength);

            //EV << "Modified Bit: " << errorBit << std::endl;

            if (errorBit < 8){
                //Then Char Count needs to be changed
                charCountBset.flip(WORD_LENGTH-errorBit-1);
                EV << "adding error in character count"<< std::endl;
            }


            else if(WORD_LENGTH <= errorBit and errorBit< totalLength-WORD_LENGTH){
                //Then Message itself needs to be changed
                int errorCharacter = (errorBit /WORD_LENGTH) - 1 ;
                int specificBit = WORD_LENGTH - (errorBit%WORD_LENGTH)-1;
                std::bitset<WORD_LENGTH> characterToBeChanged(originalMsg[errorCharacter]);
                characterToBeChanged.flip(specificBit);
                originalMsg[errorCharacter] = (char)(characterToBeChanged.to_ulong());
                EV << "adding error in Message itself"<< std::endl;
            }


            else{
                //Then Parity Bits themselves need to be changed
                int specificBit = WORD_LENGTH - (errorBit %WORD_LENGTH)-1;
                evenParityBset.flip(specificBit);
                EV << "adding error in parity bits"<< std::endl;
            }

        } else {
            std::cout << "No Error" << std::endl;
        }

        char characterCountFrame = (char)(charCountBset.to_ulong());
        char evenParity = (char)(evenParityBset.to_ulong());
        std::string message=originalMsg;

        EV << charCountBset.to_string() <<" ";
        for (int i=0;i<originalMsg.length();i++){
            std::bitset<WORD_LENGTH> charRepresentation(originalMsg[i]);
            EV << charRepresentation.to_string()<<" ";
        }
        EV << evenParityBset.to_string() <<" "<< std::endl;

        EV << "Message: "<< message.c_str() << std::endl;

        CustomizedMessage_Base * newMessage = new CustomizedMessage_Base("new Message");
        newMessage->setM_Header(characterCountFrame);
        newMessage->setM_Trailer(evenParity);
        newMessage->setM_Payload(message.c_str());
        newMessage->setM_Type(2);

        send(newMessage, "out");
    }

}
