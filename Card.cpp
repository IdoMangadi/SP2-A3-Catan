
#include "Card.hpp"

namespace ariel{
    Card::Card(int id, int type) : id(id), type(type), bought(false), used(false){
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
}