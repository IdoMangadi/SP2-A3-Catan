
#include "Pieces.hpp"

namespace ariel{

    Piece::Piece(int type, Player& owner) : type(type), owner(owner){}

    Player& Piece::getOwner(){
        return this->owner;
    }

    int Piece::getType(){
        return this->type;
    }

    Road::Road(Player& owner, int edge) : Piece(ROAD, owner), edge(edge){}

    Settlement::Settlement(int type, Player& owner, int vertex) : Piece(type, owner), vertex(vertex){}

}