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

#include "Sender.h"
#include <bitset>
#include <vector>
#include <cstdlib>

Define_Module(Sender);

void Sender::initialize()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const int WORD_LENGTH = 8;
    std::string originalMsg;
    std::vector<std::bitset<WORD_LENGTH>> binaryFrame;
    int characterCount;

    std::cout << "Input: ";
    std::cin >> originalMsg;

    characterCount = originalMsg.size() + 2;
    std::bitset<WORD_LENGTH> charCountBset(characterCount);
    std::bitset<WORD_LENGTH> evenParity = charCountBset;

    binaryFrame.push_back(charCountBset);
    for (char c : originalMsg) {
        std::bitset<WORD_LENGTH> bset(c);
        evenParity ^= bset;
        binaryFrame.push_back(bset);
    }
    binaryFrame.push_back(evenParity);

    std::cout << "message \"" << originalMsg << "\":" << std::endl;
    std::string transmittedString = "";
    for (auto word : binaryFrame) {
        transmittedString += word.to_string();
        std::cout << "\t" << word << std::endl;
    }
    int modify = std::rand() % 2;
    std::cout << "50% Chance [0/1]: " << modify << std::endl;
    if (modify == 1) {
        int errorBit = std::rand() % (WORD_LENGTH * characterCount);
        std::cout << "Modified Bit: " << errorBit << std::endl;
        transmittedString[errorBit] = (char)((int)transmittedString[errorBit] ^ 1);
    } else {
        std::cout << "No Error" << std::endl;
    }
    std::cout << "Final Transmitted Message: " << transmittedString << std::endl;
    cMessage* msg = new cMessage(transmittedString.c_str());
    send(msg, "out");
}

void Sender::handleMessage(cMessage *msg)
{

}
