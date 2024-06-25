
#include "Card.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace ariel{
    Card::Card(int id, int type) : id(id), type(type), bought(false), used(false){
        if(type == VICTORYPOINT) this->visualDisplay = "VICTORYPOINT";
        else if(type == KNIGHT) this->visualDisplay = "KNIGHT";
        else if(type == ROADBUILDING) this->visualDisplay = "ROADBUILDING";
        else if(type == MONOPOLY) this->visualDisplay = "MONOPOLY";
        else if(type == YEAROFPLENTY) this->visualDisplay = "YEAROFPLENTY";
        else this->visualDisplay = "CARD";
    }

    int Card::getType(){
        return this->type;
    }

    int Card::getId(){
        return this->id;
    }
    bool Card::isUsed(){
        return this->used;
    }
    
    void Card::use(){
        this->used = true;
    }
    string Card::getVisualDisplay(){
        return this->visualDisplay;
    }
}