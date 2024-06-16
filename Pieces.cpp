
#include "Pieces.hpp"

namespace ariel{

    Piece::Piece(string type, Player& owner) : type(type), owner(owner){}

    Player& Piece::getOwner(){
        return this->owner;
    }
    string Piece::getType(){
        return this->type;
    }
    void Piece::setType(string type){
        this->type = type;
    }

    Road::Road(Player& owner, int edge) : Piece("ROAD", owner), edge(edge){
    }
    int Road::getEdge(){
        return this->edge;
    }

    Settlement::Settlement(string type, Player& owner, int vertex) : Piece(type, owner), vertex(vertex){}
    
    int Settlement::getVertex(){
        return this->vertex;
    }
    void Settlement::upgrade(){
        this->setType(CITY);
    }
    ostream& operator<<(ostream& os, const Settlement& settlement){
        if(this->getType() == SETTLEMENT){
        }
        return os;
            
    }

}