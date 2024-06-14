
#include "Player.hpp"

using namespace std;

namespace ariel{
    // Constructor:
    Player::Player(string name, int id, int points) : name(name), id(id), points(points){
        this->resources = vector<int>(5, 0);
    }

    // Cardentials:
    int Player::getId(){
        return this->id;
    }
    string Player::getName(){
        return this->name;
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
        this->resources[resource] += amount;
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
    }
    bool Player::buy(Piece* item, int itemType, int opCode){
        if((opCode != FREE && opCode != PAID) || (itemType != ROAD && itemType != SETTLEMENT && itemType != CITY)){
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
            this->buildings.push_back((Settlement*)item);
        }
        // handling cities:
        else if(itemType == CITY){
            this->resources[WHEAT] -= 2;
            this->resources[ORE] -= 3;
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
    const vector<Settlement*>& Player::getBuildings() const{
        return this->buildings;
    }

    // Cards:
    const vector<Card*>& Player::getCards() const{
        return this->cards;
    }
    bool Player::hasCard(int type){
        for(int i = 0; i < this->cards.size(); i++){
            if(this->cards[i]->getType() == type && this->cards[i]->isUsed() == false){
                return true;
            }
        }
        return false;
    }

    // bool Player::operator==(const Player& player){
    //     return this->id == player.id;
    // }

    // bool Player::operator!=(const Player& player){
    //     return this->id != player.id;
    // }

    // bool Player::operator<(const Player& player){
    //     return this->id < player.id;
    // }

    // bool Player::operator>(const Player& player){
    //     return this->id > player.id;
    // }

    // bool Player::operator<=(const Player& player){
    //     return this->id <= player.id;
    // }

    // bool Player::operator>=(const Player& player){
    //     return this->id >= player.id;
    // }

    // ostream& operator<<(ostream& os, const Player& player){
    //     os << "Player " << player.id << " - " << player.name << " - " << player.points << " points";
    //     return os;
    // }

    // istream& operator>>(istream& is, Player& player){
    //     is >> player.id >> player.name >> player.points;
    //     return is;
    // }

}