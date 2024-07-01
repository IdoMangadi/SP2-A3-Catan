

#include "Board.hpp"
#include "BoardElements.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "Pieces.hpp"
#include "../../../../usr/include/c++/11/bits/algorithmfwd.h"
#include <queue>

using namespace std;

namespace ariel{
    
    Board::Board(Player* player1, Player* player2, Player* player3) : players({player1, player2, player3}){

        this->playersRoads = vector<vector<Road>>(3, vector<Road>()); // initialize the players' roads
        this->playersSettlements = vector<vector<Settlement>>(3, vector<Settlement>());  // initialize the players' settlements

        this->longestRoad = 0;  // initialize the longest road
        this->longestRoadPlayer = nullptr;  // initialize the longest road
        this->largestArmy = 0;  // initialize the largest army
        this->largestArmyPlayer = nullptr;  // initialize the largest army

        // Create the hexagons:
        this->hexagons.push_back(Hexagon(0, MOUNTAINS_EMOJI, 10, false));
        this->hexagons.push_back(Hexagon(1, PASTURE_EMOJI, 2, false));
        this->hexagons.push_back(Hexagon(2, FOREST_EMOJI, 9, false));

        this->hexagons.push_back(Hexagon(3, AGRICULTURAL_EMOJI, 12, false));
        this->hexagons.push_back(Hexagon(4, HILLS_EMOJI, 6, false));
        this->hexagons.push_back(Hexagon(5, PASTURE_EMOJI, 4, false));
        this->hexagons.push_back(Hexagon(6, HILLS_EMOJI, 10, false));

        this->hexagons.push_back(Hexagon(7, AGRICULTURAL_EMOJI, 9, false));
        this->hexagons.push_back(Hexagon(8, FOREST_EMOJI, 11, false));
        this->hexagons.push_back(Hexagon(9, DESERT_EMOJI, 0, true));
        this->hexagons.push_back(Hexagon(10, FOREST_EMOJI, 3, false));
        this->hexagons.push_back(Hexagon(11, MOUNTAINS_EMOJI, 8, false));

        this->hexagons.push_back(Hexagon(12, FOREST_EMOJI, 8, false));
        this->hexagons.push_back(Hexagon(13, MOUNTAINS_EMOJI, 3, false));
        this->hexagons.push_back(Hexagon(14, AGRICULTURAL_EMOJI, 4, false));
        this->hexagons.push_back(Hexagon(15, PASTURE_EMOJI, 5, false));

        this->hexagons.push_back(Hexagon(16, HILLS_EMOJI, 5, false));
        this->hexagons.push_back(Hexagon(17, AGRICULTURAL_EMOJI, 6, false));
        this->hexagons.push_back(Hexagon(18, PASTURE_EMOJI, 11, false));

        // Create the vertices:
        for(int i=0; i<54; i++){
            this->vertices.push_back(Vertex(i));
        }
        // Add the vertices to the hexagons:
        this->hexagons[0].addVertex(&this->vertices[0]);
        this->hexagons[0].addVertex(&this->vertices[3]);
        this->hexagons[0].addVertex(&this->vertices[4]);
        this->hexagons[0].addVertex(&this->vertices[7]);
        this->hexagons[0].addVertex(&this->vertices[8]);
        this->hexagons[0].addVertex(&this->vertices[12]);

        this->hexagons[1].addVertex(&this->vertices[1]);
        this->hexagons[1].addVertex(&this->vertices[4]);
        this->hexagons[1].addVertex(&this->vertices[5]);
        this->hexagons[1].addVertex(&this->vertices[8]);
        this->hexagons[1].addVertex(&this->vertices[9]);
        this->hexagons[1].addVertex(&this->vertices[13]);

        this->hexagons[2].addVertex(&this->vertices[2]);
        this->hexagons[2].addVertex(&this->vertices[5]);
        this->hexagons[2].addVertex(&this->vertices[6]);
        this->hexagons[2].addVertex(&this->vertices[9]);
        this->hexagons[2].addVertex(&this->vertices[10]);
        this->hexagons[2].addVertex(&this->vertices[14]);

        this->hexagons[3].addVertex(&this->vertices[7]);
        this->hexagons[3].addVertex(&this->vertices[11]);
        this->hexagons[3].addVertex(&this->vertices[12]);
        this->hexagons[3].addVertex(&this->vertices[16]);
        this->hexagons[3].addVertex(&this->vertices[17]);
        this->hexagons[3].addVertex(&this->vertices[22]);

        this->hexagons[4].addVertex(&this->vertices[8]);
        this->hexagons[4].addVertex(&this->vertices[12]);
        this->hexagons[4].addVertex(&this->vertices[13]);
        this->hexagons[4].addVertex(&this->vertices[17]);
        this->hexagons[4].addVertex(&this->vertices[18]);
        this->hexagons[4].addVertex(&this->vertices[23]);

        this->hexagons[5].addVertex(&this->vertices[9]);
        this->hexagons[5].addVertex(&this->vertices[13]);
        this->hexagons[5].addVertex(&this->vertices[14]);
        this->hexagons[5].addVertex(&this->vertices[18]);
        this->hexagons[5].addVertex(&this->vertices[19]);
        this->hexagons[5].addVertex(&this->vertices[24]);

        this->hexagons[6].addVertex(&this->vertices[10]);
        this->hexagons[6].addVertex(&this->vertices[14]);
        this->hexagons[6].addVertex(&this->vertices[15]);
        this->hexagons[6].addVertex(&this->vertices[19]);
        this->hexagons[6].addVertex(&this->vertices[20]);
        this->hexagons[6].addVertex(&this->vertices[25]);

        this->hexagons[7].addVertex(&this->vertices[16]);
        this->hexagons[7].addVertex(&this->vertices[21]);
        this->hexagons[7].addVertex(&this->vertices[22]);
        this->hexagons[7].addVertex(&this->vertices[27]);
        this->hexagons[7].addVertex(&this->vertices[28]);
        this->hexagons[7].addVertex(&this->vertices[33]);

        this->hexagons[8].addVertex(&this->vertices[17]);
        this->hexagons[8].addVertex(&this->vertices[22]);
        this->hexagons[8].addVertex(&this->vertices[23]);
        this->hexagons[8].addVertex(&this->vertices[28]);
        this->hexagons[8].addVertex(&this->vertices[29]);
        this->hexagons[8].addVertex(&this->vertices[34]);

        this->hexagons[9].addVertex(&this->vertices[18]);
        this->hexagons[9].addVertex(&this->vertices[23]);
        this->hexagons[9].addVertex(&this->vertices[24]);
        this->hexagons[9].addVertex(&this->vertices[29]);
        this->hexagons[9].addVertex(&this->vertices[30]);
        this->hexagons[9].addVertex(&this->vertices[35]);

        this->hexagons[10].addVertex(&this->vertices[19]);
        this->hexagons[10].addVertex(&this->vertices[24]);
        this->hexagons[10].addVertex(&this->vertices[25]);
        this->hexagons[10].addVertex(&this->vertices[30]);
        this->hexagons[10].addVertex(&this->vertices[31]);
        this->hexagons[10].addVertex(&this->vertices[36]);

        this->hexagons[11].addVertex(&this->vertices[20]);
        this->hexagons[11].addVertex(&this->vertices[25]);
        this->hexagons[11].addVertex(&this->vertices[26]);
        this->hexagons[11].addVertex(&this->vertices[31]);
        this->hexagons[11].addVertex(&this->vertices[32]);
        this->hexagons[11].addVertex(&this->vertices[37]);

        this->hexagons[12].addVertex(&this->vertices[28]);
        this->hexagons[12].addVertex(&this->vertices[33]);
        this->hexagons[12].addVertex(&this->vertices[34]);
        this->hexagons[12].addVertex(&this->vertices[38]);
        this->hexagons[12].addVertex(&this->vertices[39]);
        this->hexagons[12].addVertex(&this->vertices[43]);

        this->hexagons[13].addVertex(&this->vertices[29]);
        this->hexagons[13].addVertex(&this->vertices[34]);
        this->hexagons[13].addVertex(&this->vertices[35]);
        this->hexagons[13].addVertex(&this->vertices[39]);
        this->hexagons[13].addVertex(&this->vertices[40]);
        this->hexagons[13].addVertex(&this->vertices[44]);

        this->hexagons[14].addVertex(&this->vertices[30]);
        this->hexagons[14].addVertex(&this->vertices[35]);
        this->hexagons[14].addVertex(&this->vertices[36]);
        this->hexagons[14].addVertex(&this->vertices[40]);
        this->hexagons[14].addVertex(&this->vertices[41]);
        this->hexagons[14].addVertex(&this->vertices[45]);

        this->hexagons[15].addVertex(&this->vertices[31]);
        this->hexagons[15].addVertex(&this->vertices[36]);
        this->hexagons[15].addVertex(&this->vertices[37]);
        this->hexagons[15].addVertex(&this->vertices[41]);
        this->hexagons[15].addVertex(&this->vertices[42]);
        this->hexagons[15].addVertex(&this->vertices[46]);

        this->hexagons[16].addVertex(&this->vertices[39]);
        this->hexagons[16].addVertex(&this->vertices[43]);
        this->hexagons[16].addVertex(&this->vertices[44]);
        this->hexagons[16].addVertex(&this->vertices[47]);
        this->hexagons[16].addVertex(&this->vertices[48]);
        this->hexagons[16].addVertex(&this->vertices[51]);

        this->hexagons[17].addVertex(&this->vertices[40]);
        this->hexagons[17].addVertex(&this->vertices[44]);
        this->hexagons[17].addVertex(&this->vertices[45]);
        this->hexagons[17].addVertex(&this->vertices[48]);
        this->hexagons[17].addVertex(&this->vertices[49]);
        this->hexagons[17].addVertex(&this->vertices[52]);

        this->hexagons[18].addVertex(&this->vertices[41]);
        this->hexagons[18].addVertex(&this->vertices[45]);
        this->hexagons[18].addVertex(&this->vertices[46]);
        this->hexagons[18].addVertex(&this->vertices[49]);
        this->hexagons[18].addVertex(&this->vertices[50]);
        this->hexagons[18].addVertex(&this->vertices[53]);

        // Create the edges (connected to the vertices):
        this->edges.push_back(Edge(0, 1, &this->vertices[0], &this->vertices[3]));
        this->edges.push_back(Edge(1, 2, &this->vertices[0], &this->vertices[4]));
        this->edges.push_back(Edge(2, 1, &this->vertices[1], &this->vertices[4]));
        this->edges.push_back(Edge(3, 2, &this->vertices[1], &this->vertices[5]));
        this->edges.push_back(Edge(4, 1, &this->vertices[2], &this->vertices[5]));
        this->edges.push_back(Edge(5, 2, &this->vertices[2], &this->vertices[6]));

        this->edges.push_back(Edge(6, 0, &this->vertices[3], &this->vertices[7]));
        this->edges.push_back(Edge(7, 0, &this->vertices[4], &this->vertices[8]));
        this->edges.push_back(Edge(8, 0, &this->vertices[5], &this->vertices[9]));
        this->edges.push_back(Edge(9, 0, &this->vertices[6], &this->vertices[10]));

        this->edges.push_back(Edge(10,1, &this->vertices[7], &this->vertices[11]));
        this->edges.push_back(Edge(11,2, &this->vertices[7], &this->vertices[12]));
        this->edges.push_back(Edge(12,1, &this->vertices[8], &this->vertices[12]));
        this->edges.push_back(Edge(13,2, &this->vertices[8], &this->vertices[13]));
        this->edges.push_back(Edge(14,1, &this->vertices[9], &this->vertices[13]));
        this->edges.push_back(Edge(15,2, &this->vertices[9], &this->vertices[14]));
        this->edges.push_back(Edge(16,1, &this->vertices[10], &this->vertices[14]));
        this->edges.push_back(Edge(17,2, &this->vertices[10], &this->vertices[15]));

        this->edges.push_back(Edge(18,0, &this->vertices[11], &this->vertices[16]));
        this->edges.push_back(Edge(19,0, &this->vertices[12], &this->vertices[17]));
        this->edges.push_back(Edge(20,0, &this->vertices[13], &this->vertices[18]));
        this->edges.push_back(Edge(21,0, &this->vertices[14], &this->vertices[19]));
        this->edges.push_back(Edge(22,0, &this->vertices[15], &this->vertices[20]));

        this->edges.push_back(Edge(23,1, &this->vertices[16], &this->vertices[21]));
        this->edges.push_back(Edge(24,2, &this->vertices[16], &this->vertices[22]));
        this->edges.push_back(Edge(25,1, &this->vertices[17], &this->vertices[22]));
        this->edges.push_back(Edge(26,2, &this->vertices[17], &this->vertices[23]));
        this->edges.push_back(Edge(27,1, &this->vertices[18], &this->vertices[23]));
        this->edges.push_back(Edge(28,2, &this->vertices[18], &this->vertices[24]));
        this->edges.push_back(Edge(29,1, &this->vertices[19], &this->vertices[24]));
        this->edges.push_back(Edge(30,2, &this->vertices[19], &this->vertices[25]));
        this->edges.push_back(Edge(31,1, &this->vertices[20], &this->vertices[25]));
        this->edges.push_back(Edge(32,2, &this->vertices[20], &this->vertices[26]));

        this->edges.push_back(Edge(33,0, &this->vertices[21], &this->vertices[27]));
        this->edges.push_back(Edge(34,0, &this->vertices[22], &this->vertices[28]));
        this->edges.push_back(Edge(35,0, &this->vertices[23], &this->vertices[29]));
        this->edges.push_back(Edge(36,0, &this->vertices[24], &this->vertices[30]));
        this->edges.push_back(Edge(37,0, &this->vertices[25], &this->vertices[31]));
        this->edges.push_back(Edge(38,0, &this->vertices[26], &this->vertices[32]));

        this->edges.push_back(Edge(39,2, &this->vertices[27], &this->vertices[33]));
        this->edges.push_back(Edge(40,1, &this->vertices[28], &this->vertices[33]));
        this->edges.push_back(Edge(41,2, &this->vertices[28], &this->vertices[34]));
        this->edges.push_back(Edge(42,1, &this->vertices[29], &this->vertices[34]));
        this->edges.push_back(Edge(43,2, &this->vertices[29], &this->vertices[35]));
        this->edges.push_back(Edge(44,1, &this->vertices[30], &this->vertices[35]));
        this->edges.push_back(Edge(45,2, &this->vertices[30], &this->vertices[36]));
        this->edges.push_back(Edge(46,1, &this->vertices[31], &this->vertices[36]));
        this->edges.push_back(Edge(47,2, &this->vertices[31], &this->vertices[37]));
        this->edges.push_back(Edge(48,1, &this->vertices[32], &this->vertices[37]));

        this->edges.push_back(Edge(49,0, &this->vertices[33], &this->vertices[38]));
        this->edges.push_back(Edge(50,0, &this->vertices[34], &this->vertices[39]));
        this->edges.push_back(Edge(51,0, &this->vertices[35], &this->vertices[40]));
        this->edges.push_back(Edge(52,0, &this->vertices[36], &this->vertices[41]));
        this->edges.push_back(Edge(53,0, &this->vertices[37], &this->vertices[42]));

        this->edges.push_back(Edge(54,2, &this->vertices[38], &this->vertices[43]));
        this->edges.push_back(Edge(55,1, &this->vertices[39], &this->vertices[43]));
        this->edges.push_back(Edge(56,2, &this->vertices[39], &this->vertices[44]));
        this->edges.push_back(Edge(57,1, &this->vertices[40], &this->vertices[44]));
        this->edges.push_back(Edge(58,2, &this->vertices[40], &this->vertices[45]));
        this->edges.push_back(Edge(59,1, &this->vertices[41], &this->vertices[45]));
        this->edges.push_back(Edge(60,2, &this->vertices[41], &this->vertices[46]));
        this->edges.push_back(Edge(61,1, &this->vertices[42], &this->vertices[46]));

        this->edges.push_back(Edge(62,0, &this->vertices[43], &this->vertices[47]));
        this->edges.push_back(Edge(63,0, &this->vertices[44], &this->vertices[48]));
        this->edges.push_back(Edge(64,0, &this->vertices[45], &this->vertices[49]));
        this->edges.push_back(Edge(65,0, &this->vertices[46], &this->vertices[50]));

        this->edges.push_back(Edge(66,2, &this->vertices[47], &this->vertices[51]));
        this->edges.push_back(Edge(67,1, &this->vertices[48], &this->vertices[51]));
        this->edges.push_back(Edge(68,2, &this->vertices[48], &this->vertices[52]));
        this->edges.push_back(Edge(69,1, &this->vertices[49], &this->vertices[52]));
        this->edges.push_back(Edge(70,2, &this->vertices[49], &this->vertices[53]));
        this->edges.push_back(Edge(71,1, &this->vertices[50], &this->vertices[53]));

        // connect the edges to the vertices:
        for(size_t i=0; i<72; i++){
            this->edges[i].getVertex1()->addEdge(&this->edges[i]);
            this->edges[i].getVertex2()->addEdge(&this->edges[i]);
        }

        // Create the cards:
        for(size_t i=0; i<14; i++){  // 14 KNIGHT cards:
            this->cards.push_back(Card(i, KNIGHT));
        }
        for(size_t i=14; i<19; i++){  // 5 VICTORY_POINT cards:
            this->cards.push_back(Card(i, VICTORYPOINT));
        }
        for(size_t i=19; i<21; i++){  // 2 MONOPOLY cards:
            this->cards.push_back(Card(i, MONOPOLY));
        }
        for(size_t i=21; i<23; i++){  // 2 ROAD_BUILDING cards:
            this->cards.push_back(Card(i, ROADBUILDING));
        }
        for(size_t i=23; i<25; i++){  // 2 YEAR_OF_PLENTY cards:
            this->cards.push_back(Card(i, YEAROFPLENTY));
        }
        // shuffle the cards:
        srand(time(0));  // Seed the random number generator
        for (size_t i = cards.size() - 1; i > 0; --i) {
            size_t j = (size_t)rand() % (i + 1);  // Get a random index from 0 to i

            // Swap cards[i] with the element at random index
            Card temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }
        cardsIndex = 0;  // initialize the cards index

        // creating 15 roads for each player:
        for(size_t i=0; i<3; i++){
            for(size_t j=0; j<15; j++){
                this->playersRoads[i].push_back(Road(*this->players[i], INVALID_POSITION));
            }
        }

        // creating 9 settlements for each player:
        for(size_t i=0; i<3; i++){
            for(size_t j=0; j<9; j++){
                this->playersSettlements[i].push_back(Settlement(*this->players[i], INVALID_POSITION));
            }
        }
    }

    Player* Board::hasWinner(){
        for(size_t i=0; i<3; i++){
            if(this->players[i]->getPoints() >= 10){
                return this->players[i];
            }
        }
        return nullptr;
    }
    vector<Player*>* Board::getPlayers(){
        return &this->players;
    }

    bool Board::buy(Player* player, int itemType, size_t position, int opCode){

        if((opCode != FREE && opCode != PAID && opCode != STAGE_ONE) || (player == nullptr)) return false;  // invalid input

        if(opCode == PAID && player->canAfford(itemType) == false) return false;  // if the player can't afford the item

        if(itemType == SETTLEMENT){  // handling settlements:

            if(player->getSettlements().size() >= 5) return false;  // if the player already has 5 settlements

            for(size_t i=0; i<this->vertices[position].getEdges().size(); i++){  // iterate over the vertex's adjacents and check if there is a settlement on one of them
                if(this->vertices[position].getEdges()[i]->getVertex1()->hasSettlement() || this->vertices[position].getEdges()[i]->getVertex2()->hasSettlement()){
                    return false;
                }
            }
            bool hasRoad = false;
            if(opCode != STAGE_ONE){  // if its not the first stage make sure there is a road of the current player that connected to the vertex
                for(size_t i=0; i<this->vertices[position].getEdges().size(); i++){  // iterate over the vertex's edges and check if there is a road of the current player
                    if(this->vertices[position].getEdges()[i]->hasRoad() && this->vertices[position].getEdges()[i]->getRoad()->getOwner().getId() == player->getId()){
                        hasRoad = true;
                        break;
                    }
                }
            }
            // buying and setting the settlement:
            if(opCode == STAGE_ONE || (hasRoad && player->canAfford(itemType))){  // if the player can afford the settlement
                size_t playerBuildings = player->getSettlements().size() + player->getCities().size();  // get the number of buildings the player has
                Settlement* currSettlement = &(this->playersSettlements[player->getId()][playerBuildings]);
                this->vertices[position].setSettlement(currSettlement);  // set the settlement on the vertex
                currSettlement->setVertex(position);  // set the vertex of the settlement
                opCode = (opCode == STAGE_ONE) ? FREE : PAID;  // if its the first stage the settlement is free 
                return player->buy(currSettlement, itemType, opCode);  // buy the settlement
            }
        }

        if(itemType == CITY){ // handling cities:

            if(player->getCities().size() >= 4) return false;  // if the player already has 4 cities

            // check if there is a settlement of the player on this vertex:
            if(this->vertices[position].hasSettlement() && this->vertices[position].getSettlement()->getType() == SETTLEMENT && this->vertices[position].getSettlement()->getOwner().getId() == player->getId()){
                this->vertices[position].getSettlement()->upgrade();  // upgrade the settlement to a city (will also handle buildings ordering in the player object)
                return player->buy(this->vertices[position].getSettlement(), itemType, opCode);
            }
        }

        if(itemType == ROAD){  // handling roads:

            if(this->edges[position].hasRoad()) return false;  // if there is already a road on the edge
            if(player->getRoads().size() >= 15) return false;  // if the player already has 15 roads

            bool hasConnection = false;
            Edge* currEdge = &(this->edges[position]);
            if(opCode != STAGE_ONE){  // if its not the first stage make sure there is a road of the current player that connected to the edge

                if(currEdge->getVertex1()->hasSettlement() == false){  // if the first vertex of the edge doesn't have a settlement check if there is a road connected to it that belongs to the current player
                    for(size_t i=0; i<currEdge->getVertex1()->getEdges().size(); i++){  // iterate over the vertex's edges
                        if(currEdge->getVertex1()->getEdges()[i]->hasRoad() == true && currEdge->getVertex1()->getEdges()[i]->getRoad()->getOwner().getId() == player->getId()){
                            hasConnection = true;
                            break;
                        }
                    }
                }
                else if(currEdge->getVertex1()->getSettlement()->getOwner().getId() == player->getId()) hasConnection = true;  // if the first vertex of the edge has a settlement check if it belongs to the current player

                if(currEdge->getVertex2()->hasSettlement() == false){  // if the second vertex of the edge doesn't have a settlement check if there is a road connected to it
                    for(size_t i=0; i<currEdge->getVertex2()->getEdges().size(); i++){
                        if(currEdge->getVertex2()->getEdges()[i]->hasRoad() == true && currEdge->getVertex2()->getEdges()[i]->getRoad()->getOwner().getId() == player->getId()){
                            hasConnection = true;
                            break;
                        }
                    }
                }
                else if(currEdge->getVertex2()->getSettlement()->getOwner().getId() == player->getId()) hasConnection = true;  // if the second vertex of the edge has a settlement check if it belongs to the current player
            }
            else{  // if its the first stage
                // if(there is a settlement on the vertex1 && the settlement belongs to the current player && the settlement is the last settlement the player built)
                if(currEdge->getVertex1()->hasSettlement() && currEdge->getVertex1()->getSettlement()->getOwner().getId() == player->getId() && currEdge->getVertex1()->getSettlement() == player->getSettlements()[player->getSettlements().size()-1]){
                    hasConnection = true;
                }
                // if(there is a settlement on the vertex2 && the settlement belongs to the current player && the settlement is the last settlement the player built)
                else if(currEdge->getVertex2()->hasSettlement() && currEdge->getVertex2()->getSettlement()->getOwner().getId() == player->getId() && currEdge->getVertex2()->getSettlement() == player->getSettlements()[player->getSettlements().size()-1]){
                    hasConnection = true;
                }
            }
            if(hasConnection){  // if there is a road of the current player that connected to the edge
                Road* road = &(this->playersRoads[player->getId()][player->getRoads().size()]);  // get the first available road of the player
                this->edges[position].setRoad(road);  // set the road on the edge
                road->setEdge(position);  // set the edge of the road
                opCode = (opCode == STAGE_ONE) ? FREE : PAID;  // if its the first stage the road is free
                this->longestRoadCheck(player);  // check if the player has the longest road
                return player->buy(road, itemType, opCode);  // buy the road
            }
        }
        if(itemType == CARD && this->cards.size() > cardsIndex){  // handling cards:
            this->cards[cardsIndex].setBought();  // set the card as bought
            return player->buy(&this->cards[cardsIndex++], itemType, PAID);  // buy the card
        }
        return false;
    }

    void Board::distributeResources(size_t diceSum){
        
        if(diceSum < 2 || diceSum > 12) return;  // invalid input

        for(size_t i=0; i<19; i++){  // iterate over the hexagons
            if(this->hexagons[i].getDiceNum() == diceSum && !this->hexagons[i].getHasRobber()){  // if the dice number matches the hexagon's dice number
                for(size_t j=0; j<6; j++){  // iterate over the hexagon's vertices
                    if(this->hexagons[i].getVertices()->at(j)->hasSettlement()){  // if the vertex has a settlement
                        
                        int settelemtType = this->hexagons[i].getVertices()->at(j)->getSettlement()->getType();
                        // distribute resources to the player:
                        if(settelemtType == CITY){
                            this->players[this->hexagons[i].getVertices()->at(j)->getSettlement()->getOwner().getId()]->addResource(this->hexagons[i].getResourceType(), 2);
                        }
                        else{
                            this->players[this->hexagons[i].getVertices()->at(j)->getSettlement()->getOwner().getId()]->addResource(this->hexagons[i].getResourceType(), 1);
                        }
                    }
                }
            }
        }
    }

    void Board::stageOneResourcesDistribution(){
        for(size_t i =0; i<19; i++){  // iterate over the hexagons
            for(size_t j=0; j<6; j++){ // iterate over the hexagon's vertices
                Settlement* settlement = this->hexagons[i].getVertices()->at(j)->getSettlement();
                if(settlement != nullptr){  // if the vertex has a settlement
                    Player& owner = settlement->getOwner();
                    if(settlement == owner.getSettlements()[owner.getSettlements().size()-1]){  // if the settlement is the last settlement the player built
                        owner.addResource(this->hexagons[i].getResourceType(), 1);
                    }
                }
            }

        }
    }

    bool Board::knightUsed(Player* player){
        player->addKnight();
        size_t currPlayerKnights = player->getKnightsCounter();
        if(currPlayerKnights >= 3){  // if the player has more than 3 knights
            // check if the player has the largest army:
            if(currPlayerKnights > this->largestArmy){
                if(this->largestArmy != 0){  // means there is a player that has the largest army
                    this->largestArmyPlayer->addPoints(-2);  // remove the points from the previous largest army owner
                }
                this->largestArmy = currPlayerKnights;  // update the largest army
                this->largestArmyPlayer = player;  // update the largest army owner
                player->addPoints(2);  // add 2 points to the player
            }
        }
        return true;
    }

    /**
     * this function checks what is the length of the longest road of the player.
     * if the player has the longest road it updates the longest road length and the longest road owner and returns true. 
     * NOTE: the player dosent have access to the edges objects. only to the roads objects.
     *       the roads objects have access to the edges id only.
     *       this function check by itself the length of the longest road of the player.
     * The function longestRoadCheck is designed to check if the player has the longest road in the game. 
     * It does this by iterating over all the roads owned by the player 
     * and performing a breadth-first search (BFS) from each road to find the longest connected path of roads
     * 
     * NOTE: the edges are object that hold pointers to the vertices objects and to the road objects (if there is a road on the edge).
     *       the roads are objects that hold refference to the player object.
     *       the player object has a vector of pointers to the roads objects that he already bought.
     *       the roads objects have access to the edges id only (not the edges objects).
     *       the board has vector of the edges objects, vertices objects and players objects.
     *       the board has a vector of the roads objects for each player.
     *       there is no direct access from the road object to the edges objects. it can be done only through the board object. it has a vector of the edges objects that each road holds the id of the edges that it is on.
     * 
    */
   
    bool Board::longestRoadCheck(Player* player){
        size_t longestRoad = 0;  // initialize the longest road length
        vector<Road*> playerRoads = player->getRoads();  // get the player's roads
        vector<bool> visitedEdges(72, false);  // initialize the visited edges vector
        for(size_t i=0; i<playerRoads.size(); i++){  // iterate over the player's roads
            size_t currRoad = playerRoads[i]->getEdge();  // get the current road
            vector<bool> visitedEdges(72, false);  // initialize the visited edges vector
            size_t currLength = 1;  // initialize the current length
            queue<size_t> q;  // initialize the queue
            q.push(currRoad);  // push the current road to the queue
            visitedEdges[currRoad] = true;  // mark the current road as visited
            while(!q.empty()){  // while the queue is not empty
                size_t currEdge = q.front();  // get the current edge
                q.pop();  // pop the current edge
                for(size_t j=0; j<2; j++){  // iterate over the edge's vertices
                    size_t currVertex = (j == 0) ? (size_t)this->edges[currEdge].getVertex1()->getId() : (size_t)this->edges[currEdge].getVertex2()->getId();  // get the current vertex
                    for(size_t k=0; k<this->vertices[currVertex].getEdges().size(); k++){  // iterate over the vertex's edges
                        size_t nextEdge = (size_t)this->vertices[currVertex].getEdges()[k]->getId();  // get the next edge
                        if(this->edges[nextEdge].hasRoad() && this->edges[nextEdge].getRoad()->getOwner().getId() == player->getId() && visitedEdges[nextEdge] == false){  // if the next edge has a road of the current player and it wasn't visited
                            q.push(nextEdge);  // push the next edge to the queue
                            visitedEdges[nextEdge] = true;  // mark the next edge as visited
                            currLength++;  // increment the current length
                        }
                    }
                }
            }
            longestRoad = max(longestRoad, currLength);  // update the longest road length
        }
        if(longestRoad >= 5 && longestRoad > this->longestRoad){
            if(this->longestRoad != 0){  // means there is a player that has the longest road
                this->longestRoadPlayer->addPoints(-2);  // remove the points from the previous longest road owner
            }
            this->longestRoad = longestRoad;  // update the longest road
            this->longestRoadPlayer = player;  // update the longest road owner
            player->addPoints(2);  // add 2 points to the player
            return true;
        }
        return false;
    }

    vector<size_t>* Board::rollDice(){

        this->diceNums.clear();  // clear the previous dice numbers
        this->diceNums.push_back((size_t)rand() % 6 + 1);  // roll the dice twice
        this->diceNums.push_back((size_t)rand() % 6 + 1);
        size_t diceSum = this->diceNums[0] + this->diceNums[1];  // get the sum of the dice numbers

        distributeResources(diceSum);  // distribute the resources
        return &this->diceNums;  // return the dice numbers

        // TODO: handle the case of rolling a 7
    }

    void Board::displayStats(){
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        // display players stats:
        for(size_t i=0; i<3; i++){
            // printing player stats:
            cout << *(this->players[i]) << this->players[i]->getCardsVisual() << endl;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }
 
    void Board::display(){
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        // display players stats:
        for(size_t i=0; i<3; i++){
            // printing player stats:
            cout << *(this->players[i]) << endl;
        }

        // display the board:
        cout<<"                                                               "<<this->vertices[0]<<"       "<<this->vertices[1]<<"       "<<this->vertices[2]<<endl;
        cout<<"                                                             "<<this->edges[0]<<"   "<<this->edges[1]<<"   "<<this->edges[2]<<"   "<<this->edges[3]<<"   "<<this->edges[4]<<"   "<<this->edges[5]<<endl;
        cout<<"                                                           "<<this->vertices[3]<<"       "<<this->vertices[4]<<"       "<<this->vertices[5]<<"       "<<this->vertices[6]<<endl;
        cout<<"                                                           "<<this->edges[6]<<" "<<this->hexagons[0]<<"  "<<this->edges[7]<<" "<<this->hexagons[1]<<"  "<<this->edges[8]<<"  "<<this->hexagons[2]<<" "<<this->edges[9]<<endl;
        cout<<"                                                           "<<this->vertices[7]<<"       "<<this->vertices[8]<<"       "<<this->vertices[9]<<"       "<<this->vertices[10]<<endl;
        cout<<"                                                         "<<this->edges[10]<<"   "<<this->edges[11]<<"   "<<this->edges[12]<<"   "<<this->edges[13]<<"   "<<this->edges[14]<<"   "<<this->edges[15]<<"   "<<this->edges[16]<<"   "<<this->edges[17]<<endl;
        cout<<"                                                       "<<this->vertices[11]<<"       "<<this->vertices[12]<<"       "<<this->vertices[13]<<"       "<<this->vertices[14]<<"       "<<this->vertices[15]<<endl;
        cout<<"                                                       "<<this->edges[18]<<" "<<this->hexagons[3]<<" "<<this->edges[19]<<" "<<this->hexagons[4]<<"  "<<this->edges[20]<<" "<<this->hexagons[5]<<"  "<<this->edges[21]<<" "<<this->hexagons[6]<<" "<<this->edges[22]<<endl;
        cout<<"                                                       "<<this->vertices[16]<<"       "<<this->vertices[17]<<"       "<<this->vertices[18]<<"       "<<this->vertices[19]<<"       "<<this->vertices[20]<<endl;
        cout<<"                                                     "<<this->edges[23]<<"   "<<this->edges[24]<<"   "<<this->edges[25]<<"   "<<this->edges[26]<<"   "<<this->edges[27]<<"   "<<this->edges[28]<<"   "<<this->edges[29]<<"   "<<this->edges[30]<<"   "<<this->edges[31]<<"   "<<this->edges[32]<<endl;
        cout<<"                                                   "<<this->vertices[21]<<"       "<<this->vertices[22]<<"       "<<this->vertices[23]<<"       "<<this->vertices[24]<<"       "<<this->vertices[25]<<"       "<<this->vertices[26]<<endl;
        cout<<"                                                   "<<this->edges[33]<<" "<<this->hexagons[7]<<"  "<<this->edges[34]<<" "<<this->hexagons[8]<<" "<<this->edges[35]<<"  "<<this->hexagons[9]<<"  "<<this->edges[36]<<" "<<this->hexagons[10]<<"  "<<this->edges[37]<<"  "<<this->hexagons[11]<<"  "<<this->edges[38]<<endl;
        cout<<"                                                   "<<this->vertices[27]<<"       "<<this->vertices[28]<<"       "<<this->vertices[29]<<"       "<<this->vertices[30]<<"       "<<this->vertices[31]<<"       "<<this->vertices[32]<<endl;
        cout<<"                                                     "<<this->edges[39]<<"   "<<this->edges[40]<<"   "<<this->edges[41]<<"   "<<this->edges[42]<<"   "<<this->edges[43]<<"   "<<this->edges[44]<<"   "<<this->edges[45]<<"   "<<this->edges[46]<<"   "<<this->edges[47]<<"   "<<this->edges[48]<<endl;
        cout<<"                                                       "<<this->vertices[33]<<"       "<<this->vertices[34]<<"       "<<this->vertices[35]<<"       "<<this->vertices[36]<<"       "<<this->vertices[37]<<endl;
        cout<<"                                                       "<<this->edges[49]<<" "<<this->hexagons[12]<<"  "<<this->edges[50]<<"  "<<this->hexagons[13]<<"  "<<this->edges[51]<<"  "<<this->hexagons[14]<<" "<<this->edges[52]<<"  "<<this->hexagons[15]<<" "<<this->edges[53]<<endl;
        cout<<"                                                       "<<this->vertices[38]<<"       "<<this->vertices[39]<<"       "<<this->vertices[40]<<"       "<<this->vertices[41]<<"       "<<this->vertices[42]<<endl;
        cout<<"                                                         "<<this->edges[54]<<"   "<<this->edges[55]<<"   "<<this->edges[56]<<"   "<<this->edges[57]<<"   "<<this->edges[58]<<"   "<<this->edges[59]<<"   "<<this->edges[60]<<"   "<<this->edges[61]<<endl;
        cout<<"                                                           "<<this->vertices[43]<<"       "<<this->vertices[44]<<"       "<<this->vertices[45]<<"       "<<this->vertices[46]<<endl;
        cout<<"                                                           "<<this->edges[62]<<" "<<this->hexagons[16]<<"  "<<this->edges[63]<<" "<<this->hexagons[17]<<"  "<<this->edges[64]<<" "<<this->hexagons[18]<<" "<<this->edges[65]<<endl;
        cout<<"                                                           "<<this->vertices[47]<<"       "<<this->vertices[48]<<"       "<<this->vertices[49]<<"       "<<this->vertices[50]<<endl;
        cout<<"                                                             "<<this->edges[66]<<"   "<<this->edges[67]<<"   "<<this->edges[68]<<"   "<<this->edges[69]<<"   "<<this->edges[70]<<"   "<<this->edges[71]<<endl;
        cout<<"                                                               "<<this->vertices[51]<<"       "<<this->vertices[52]<<"       "<<this->vertices[53]<<endl;

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }
    
} // namespace ariel
