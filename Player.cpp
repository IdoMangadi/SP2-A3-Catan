
#include "Player.hpp"

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
    void Player::addResource(int resource){
        this->resources[resource]++;
    }
    void Player::removeResource(int resource){
        this->resources[resource]--;
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
    bool Player::buy(int buildingType){
        if(buildingType == ROAD && this->canAfford(ROAD)){
            this->resources[WOOD]--;
            this->resources[BRICK]--;
            return true;
        }
        else if(buildingType == SETTLEMENT && this->canAfford(SETTLEMENT)){
            this->resources[WOOD]--;
            this->resources[BRICK]--;
            this->resources[WHEAT]--;
            this->resources[WOOL]--;
            return true;
        }
        else if(buildingType == CITY && this->canAfford(CITY)){
            this->resources[WHEAT] -= 2;
            this->resources[ORE] -= 3;
            return true;
        }
        return false;
    }

    // Roads:
    const vector<Road&>& Player::getRoads() const{
        return this->roads;
    }




    void Player::addPiece(Piece piece){
        this->pieces.push_back(piece);
    }

    void Player::removePiece(Piece piece){
        for(int i = 0; i < this->pieces.size(); i++){
            if(this->pieces[i].getId() == piece.getId()){
                this->pieces.erase(this->pieces.begin() + i);
                break;
            }
        }
    }

    void Player::addPoints(int points){
        this->points += points;
    }

    void Player::removePoints(int points){
        this->points -= points;
    }

    int Player::getId(){
        return this->id;
    }

    string Player::getName(){
        return this->name;
    }

    int Player::getPoints(){
        return this->points;
    }

    vector<Piece> Player::getPieces(){
        return this->pieces;
    }

    bool Player::hasPiece(Piece piece){
        for(int i = 0; i < this->pieces.size(); i++){
            if(this->pieces[i].getId() == piece.getId()){
                return true;
            }
        }
        return false;
    }

    bool Player::operator==(const Player& player){
        return this->id == player.id;
    }

    bool Player::operator!=(const Player& player){
        return this->id != player.id;
    }

    bool Player::operator<(const Player& player){
        return this->id < player.id;
    }

    bool Player::operator>(const Player& player){
        return this->id > player.id;
    }

    bool Player::operator<=(const Player& player){
        return this->id <= player.id;
    }

    bool Player::operator>=(const Player& player){
        return this->id >= player.id;
    }

    ostream& operator<<(ostream& os, const Player& player){
        os << "Player " << player.id << " - " << player.name << " - " << player.points << " points";
        return os;
    }

    istream& operator>>(istream& is, Player& player){
        is >> player.id >> player.name >> player.points;
        return is;
    }








}