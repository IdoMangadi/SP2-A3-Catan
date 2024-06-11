
#include "Card.hpp"

namespace ariel{
    Card::Card(int id, int type) : id(id), type(type), used(false){
    }

    int Card::getType(){
        return this->type;
    }

    int Card::getId(){
        return this->id;
    }

    void Card::use(){
        this->used = true;
    }
}