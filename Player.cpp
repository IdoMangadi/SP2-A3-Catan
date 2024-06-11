
#include "Player.hpp"
#include <stdexcept>

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
    void Player::addResource(int resource){
        this->resources[resource]++;
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
    bool Player::buy(Piece* piece, int pieceType, int opCode){
        if((opCode != FREE && opCode != PAID) || (pieceType != ROAD && pieceType != SETTLEMENT && pieceType != CITY)){
            return false;
        }
        // handling roads:
        if(pieceType == ROAD){
            if(opCode == PAID){
                this->resources[WOOD]--;
                this->resources[BRICK]--;
            }
            this->roads.push_back((Road*)piece);
        }
        // handling settlements:
        else if(pieceType == SETTLEMENT){
            this->resources[WOOD]--;
            this->resources[BRICK]--;
            this->resources[WHEAT]--;
            this->resources[WOOL]--;
            this->buildings.push_back((Settlement*)piece);
        }
        // handling cities:
        else if(pieceType == CITY){
            this->resources[WHEAT] -= 2;
            this->resources[ORE] -= 3;
            for(int i = 0; i < this->buildings.size(); i++){  // find the settlement to upgrade
                if(this->buildings[i]->getVertex() == ((Settlement*)piece)->getVertex()){ // if the settlement is found
                    this->buildings[i].upgrade();  // upgrade the settlement to a city
                    break;
                }
            }
        }
        return true;
    }
    
    // Roads:
    const vector<Road>& Player::getRoads() const{
        return this->roads;
    }

    // Buildings:
    const vector<Settlement>& Player::getBuildings() const{
        return this->buildings;
    }

    // Cards:
    const vector<Card>& Player::getCards() const{
        return this->cards;
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