
#include "Pieces.hpp"

namespace ariel{

    Piece::Piece(int type, Player& owner) : type(type), owner(owner){}

    Player& Piece::getOwner(){
        return this->owner;
    }
    int Piece::getType(){
        return this->type;
    }
    void Piece::setType(int type){
        this->type = type;
    }

    Road::Road(Player& owner, int edge) : Piece(ROAD, owner), edge(edge){}
    int Road::getEdge(){
        return this->edge;
    }

    Settlement::Settlement(int type, Player& owner, int vertex) : Piece(type, owner), vertex(vertex){}
    
    int Settlement::getVertex(){
        return this->vertex;
    }
    void Settlement::upgrade(){
        this->setType(CITY);
    }

}