

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
    void Road::setEdge(size_t edge){
        this->edge = edge;
    }
    ostream& operator<<(ostream& os, Road& road){
        os << road.getVisualDisplay();
        return os;
    }

    Settlement::Settlement(Player& owner, size_t vertex) : Piece(SETTLEMENT, SETTLEMENT_EMOJI, owner), vertex(vertex){}
    size_t Settlement::getVertex(){
        return this->vertex;
    }
    void Settlement::setVertex(size_t vertex){
        this->vertex = vertex;
    }
    void Settlement::upgrade(){
        // upgrade to city according to color (board.cpp handles the validation check for the upgrade)
        this->setType(CITY);
        this->visualDisplay = CITY_EMOJI;

        // handling player ordering:
        Player& owner = this->getOwner();
        // removing the settlement from the player's settlements vector
        vector<Settlement*>& settlements = owner.getSettlements();
        for (int i = 0; i < settlements.size(); i++){
            if (settlements[(size_t)i] == this){
                settlements.erase(settlements.begin() + i);
                break;
            }
        }
        // adding the city to the player's cities vector
        owner.getCities().push_back(this);
    }
    ostream& operator<<(ostream& os, Settlement& settlement){
        os << settlement.owner.getColor() << settlement.getVisualDisplay() << RESET_COLOR;
        return os;
    }

}