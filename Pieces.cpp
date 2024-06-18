

#include "Pieces.hpp"
#include "Player.hpp"

using namespace std;

namespace ariel{

    Piece::Piece(int type, string visualDisplay, Player& owner) : type(type), visualDisplay(visualDisplay), owner(owner){}
    Player& Piece::getOwner(){
        return this->owner;
    }
    int Piece::getType(){
        return this->type;
    }
    void Piece::setType(int type){ 
        this->type = type;
    }
    string Piece::getVisualDisplay(){
        return this->visualDisplay;
    }
    void Piece::setVisualDisplay(string visualDisplay){
        this->visualDisplay = visualDisplay;
    }

    Road::Road(Player& owner, size_t edge) : Piece(ROAD, owner.getColor(), owner), edge(edge){}
    size_t Road::getEdge(){
        return this->edge;
    }
    ostream& operator<<(ostream& os, Road& road){
        os << road.getVisualDisplay();
        return os;
    }

    Settlement::Settlement(Player& owner, size_t vertex) : Piece(SETTLEMENT, SETTLEMENT_EMOJI, owner), vertex(vertex){}
    size_t Settlement::getVertex(){
        return this->vertex;
    }
    void Settlement::upgrade(){
        // if settlement, upgrade to city according to color
        this->setType(CITY);
        this->visualDisplay = CITY_EMOJI;
    }
    ostream& operator<<(ostream& os, Settlement& settlement){
        os << settlement.owner.getColor() << settlement.getVisualDisplay() << RESET_COLOR;
        return os;
    }

}