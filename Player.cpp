
#include <algorithm>

#include "Player.hpp"
#include "Pieces.hpp"
#include "Card.hpp"

using namespace std;

namespace ariel{

    // Constructor:
    Player::Player(string name, size_t id, string color, int points) : name(name), id(id), color(color), points(points){
        this->resources = vector<int>(5, 0);  // initialize resources vector with 0
    }

    // Cardentials:
    size_t Player::getId(){
        return this->id;
    }
    string Player::getName(){
        return this->name;
    }
    string Player::getColor(){
        return this->color;
    }

    // Points:
    int Player::getPoints(){
        return this->points;
    }
    void Player::addPoints(int points){
        this->points += points;
    }

    // Resources:
    const vector<int>& Player::getResources() const{
        return this->resources;
    }
    void Player::addResource(int resource, int amount){
        if(resource >= 0 && resource < 5) this->resources[(size_t)resource] += amount;
    }
    bool Player::canAfford(int buildingType){
        if(buildingType == ROAD){
            return this->resources[WOOD] >= 1 && this->resources[BRICK] >= 1;
        }
        else if(buildingType == SETTLEMENT){
            return this->resources[WOOD] >= 1 && this->resources[BRICK] >= 1 && this->resources[WHEAT] >= 1 && this->resources[WOOL] >= 1;
        }
        else if(buildingType == CITY){
            return this->resources[WHEAT] >= 2 && this->resources[ORE] >= 3;
        }
        return false;
    }
    bool Player::buy(Piece* item, int itemType, int opCode){
        if((opCode != FREE && opCode != PAID) || (itemType != ROAD && itemType != SETTLEMENT && itemType != CITY)){  // invalid input
            return false;
        }
        // handling roads:
        if(itemType == ROAD){
            if(opCode == PAID){
                this->resources[WOOD]--;
                this->resources[BRICK]--;
            }
            this->roads.push_back((Road*)item);
        }
        // handling settlements:
        else if(itemType == SETTLEMENT){
            if(opCode == PAID){
                this->resources[WOOD]--;
                this->resources[BRICK]--;
                this->resources[WHEAT]--;
                this->resources[WOOL]--;
            }
            this->settlements.push_back((Settlement*)item);
            this->points++;
        }
        // handling cities:
        else if(itemType == CITY){
            this->resources[WHEAT] -= 2;
            this->resources[ORE] -= 3;
            this->settlements.erase(remove(this->settlements.begin(), this->settlements.end(), (Settlement*)item), this->settlements.end());  // remove the settlement
            this->cities.push_back((Settlement*)item);  // add the settlement as a city
            this->points++;
        }
        else if  (itemType == CARD){
            this->resources[WHEAT]--;
            this->resources[ORE]--;
            this->resources[WOOL]--;
            this->cards.push_back((Card*)item);
        }
        return true;
    }
    
    // Roads:
    const vector<Road*>& Player::getRoads() const{
        return this->roads;
    }

    // Buildings:
    const vector<Settlement*>& Player::getSettlements() const{
        return this->settlements;
    }
    const vector<Settlement*>& Player::getCities() const{
        return this->cities;
    }

    // Cards:
    const vector<Card*>& Player::getCards() const{
        return this->cards;
    }
    bool Player::hasCard(int type){
        for(size_t i = 0; i < this->cards.size(); i++){
            if(this->cards[i]->getType() == type && this->cards[i]->isUsed() == false){
                return true;
            }
        }
        return false;
    }

    ostream& operator<<(ostream& os, Player& player){
        os << BOLD << player.getColor() << player.getName() << RESET_COLOR << BOLD << ": Points: " << RESET_COLOR << player.getPoints() << BOLD <<" Resources: " << RESET_COLOR << WOOD_EMOJI << ": " << player.getResources()[0] << " " << BRICK_EMOJI << ": " << player.getResources()[1] << " " << WHEAT_EMOJI << ": " << player.getResources()[2] << " " << WOOL_EMOJI << ": " << player.getResources()[3] << " " << STONE_EMOJI << ": " << player.getResources()[4] << " ";
        return os;
    }

}