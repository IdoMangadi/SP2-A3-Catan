

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

    Road::Road(Player& owner, int edge) : Piece(ROAD, owner.getColor(), owner), edge(edge){}
    int Road::getEdge(){
        return this->edge;
    }
    ostream& operator<<(ostream& os, Road& road){
        os << road.getVisualDisplay();
        return os;
    }

    Settlement::Settlement(Player& owner, int vertex) : Piece(SETTLEMENT, "", owner), vertex(vertex){
        if(owner.getColor() == "red") this->setVisualDisplay(RED_SETTLEMENT);
        else if(owner.getColor() == "green") this->setVisualDisplay(GREEN_SETTLEMENT);
        else if(owner.getColor() == "yellow") this->setVisualDisplay(YELLOW_SETTLEMENT);
    }
    int Settlement::getVertex(){
        return this->vertex;
    }
    void Settlement::upgrade(){
        // if settlement, upgrade to city according to color
        this->setType(CITY);
        if(this->getVisualDisplay() == RED_SETTLEMENT) this->setVisualDisplay(RED_CITY);
        else if(this->getVisualDisplay() == GREEN_SETTLEMENT) this->setVisualDisplay(GREEN_CITY);
        else if(this->getVisualDisplay() == YELLOW_SETTLEMENT) this->setVisualDisplay(YELLOW_CITY);
    }
    ostream& operator<<(ostream& os, Settlement& settlement){
        os << settlement.getVisualDisplay();
        return os;
    }

}