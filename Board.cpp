

#include "Board.hpp"
#include "../../../../usr/include/c++/11/bits/algorithmfwd.h"

namespace ariel{

    Board::Board(Player* player1, Player* player2, Player* player3) : players({player1, player2, player3}){
        this->longestRoad = 0;
        this->largestArmy = 0;

        // Create the hexagons:
        this->hexagons.push_back(Hexagon(0, MOUNTAINS, 10, false));
        this->hexagons.push_back(Hexagon(1, PASTURE, 2, false));
        this->hexagons.push_back(Hexagon(2, FOREST, 9, false));

        this->hexagons.push_back(Hexagon(3, AGRICULTURAL, 12, false));
        this->hexagons.push_back(Hexagon(4, HILLS, 6, false));
        this->hexagons.push_back(Hexagon(5, PASTURE, 4, false));
        this->hexagons.push_back(Hexagon(6, HILLS, 10, false));

        this->hexagons.push_back(Hexagon(7, AGRICULTURAL, 9, false));
        this->hexagons.push_back(Hexagon(8, FOREST, 11, false));
        this->hexagons.push_back(Hexagon(9, DESERT, 0, true));
        this->hexagons.push_back(Hexagon(10, FOREST, 3, false));
        this->hexagons.push_back(Hexagon(11, MOUNTAINS, 8, false));

        this->hexagons.push_back(Hexagon(12, FOREST, 8, false));
        this->hexagons.push_back(Hexagon(13, MOUNTAINS, 3, false));
        this->hexagons.push_back(Hexagon(14, AGRICULTURAL, 4, false));
        this->hexagons.push_back(Hexagon(15, PASTURE, 5, false));

        this->hexagons.push_back(Hexagon(16, HILLS, 5, false));
        this->hexagons.push_back(Hexagon(17, AGRICULTURAL, 6, false));
        this->hexagons.push_back(Hexagon(18, PASTURE, 11, false));

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
        this->edges.push_back(Edge(0, &this->vertices[0], &this->vertices[3]));
        this->edges.push_back(Edge(1, &this->vertices[0], &this->vertices[4]));
        this->edges.push_back(Edge(2, &this->vertices[1], &this->vertices[4]));
        this->edges.push_back(Edge(3, &this->vertices[1], &this->vertices[5]));
        this->edges.push_back(Edge(4, &this->vertices[2], &this->vertices[5]));
        this->edges.push_back(Edge(5, &this->vertices[2], &this->vertices[6]));

        this->edges.push_back(Edge(6, &this->vertices[3], &this->vertices[7]));
        this->edges.push_back(Edge(7, &this->vertices[4], &this->vertices[8]));
        this->edges.push_back(Edge(8, &this->vertices[5], &this->vertices[9]));
        this->edges.push_back(Edge(9, &this->vertices[6], &this->vertices[10]));

        this->edges.push_back(Edge(10, &this->vertices[7], &this->vertices[11]));
        this->edges.push_back(Edge(11, &this->vertices[7], &this->vertices[12]));
        this->edges.push_back(Edge(12, &this->vertices[8], &this->vertices[12]));
        this->edges.push_back(Edge(13, &this->vertices[8], &this->vertices[13]));
        this->edges.push_back(Edge(14, &this->vertices[9], &this->vertices[13]));
        this->edges.push_back(Edge(15, &this->vertices[9], &this->vertices[14]));
        this->edges.push_back(Edge(16, &this->vertices[10], &this->vertices[14]));
        this->edges.push_back(Edge(17, &this->vertices[10], &this->vertices[15]));

        this->edges.push_back(Edge(18, &this->vertices[11], &this->vertices[16]));
        this->edges.push_back(Edge(19, &this->vertices[12], &this->vertices[17]));
        this->edges.push_back(Edge(20, &this->vertices[13], &this->vertices[18]));
        this->edges.push_back(Edge(21, &this->vertices[14], &this->vertices[19]));
        this->edges.push_back(Edge(22, &this->vertices[15], &this->vertices[20]));

        this->edges.push_back(Edge(23, &this->vertices[16], &this->vertices[21]));
        this->edges.push_back(Edge(24, &this->vertices[16], &this->vertices[22]));
        this->edges.push_back(Edge(25, &this->vertices[17], &this->vertices[22]));
        this->edges.push_back(Edge(26, &this->vertices[17], &this->vertices[23]));
        this->edges.push_back(Edge(27, &this->vertices[18], &this->vertices[23]));
        this->edges.push_back(Edge(28, &this->vertices[18], &this->vertices[24]));
        this->edges.push_back(Edge(29, &this->vertices[19], &this->vertices[24]));
        this->edges.push_back(Edge(30, &this->vertices[19], &this->vertices[25]));
        this->edges.push_back(Edge(31, &this->vertices[20], &this->vertices[25]));
        this->edges.push_back(Edge(32, &this->vertices[20], &this->vertices[26]));

        this->edges.push_back(Edge(33, &this->vertices[21], &this->vertices[27]));
        this->edges.push_back(Edge(34, &this->vertices[22], &this->vertices[28]));
        this->edges.push_back(Edge(35, &this->vertices[23], &this->vertices[29]));
        this->edges.push_back(Edge(36, &this->vertices[24], &this->vertices[30]));
        this->edges.push_back(Edge(37, &this->vertices[25], &this->vertices[31]));
        this->edges.push_back(Edge(38, &this->vertices[26], &this->vertices[32]));

        this->edges.push_back(Edge(39, &this->vertices[27], &this->vertices[33]));
        this->edges.push_back(Edge(40, &this->vertices[28], &this->vertices[33]));
        this->edges.push_back(Edge(41, &this->vertices[28], &this->vertices[34]));
        this->edges.push_back(Edge(42, &this->vertices[29], &this->vertices[34]));
        this->edges.push_back(Edge(43, &this->vertices[29], &this->vertices[35]));
        this->edges.push_back(Edge(44, &this->vertices[30], &this->vertices[35]));
        this->edges.push_back(Edge(45, &this->vertices[30], &this->vertices[36]));
        this->edges.push_back(Edge(46, &this->vertices[31], &this->vertices[36]));
        this->edges.push_back(Edge(47, &this->vertices[31], &this->vertices[37]));
        this->edges.push_back(Edge(48, &this->vertices[32], &this->vertices[37]));

        this->edges.push_back(Edge(49, &this->vertices[33], &this->vertices[38]));
        this->edges.push_back(Edge(50, &this->vertices[34], &this->vertices[39]));
        this->edges.push_back(Edge(51, &this->vertices[35], &this->vertices[40]));
        this->edges.push_back(Edge(52, &this->vertices[36], &this->vertices[41]));
        this->edges.push_back(Edge(53, &this->vertices[37], &this->vertices[42]));

        this->edges.push_back(Edge(54, &this->vertices[38], &this->vertices[43]));
        this->edges.push_back(Edge(55, &this->vertices[39], &this->vertices[43]));
        this->edges.push_back(Edge(56, &this->vertices[39], &this->vertices[44]));
        this->edges.push_back(Edge(57, &this->vertices[40], &this->vertices[44]));
        this->edges.push_back(Edge(58, &this->vertices[40], &this->vertices[45]));
        this->edges.push_back(Edge(59, &this->vertices[41], &this->vertices[45]));
        this->edges.push_back(Edge(60, &this->vertices[41], &this->vertices[46]));
        this->edges.push_back(Edge(61, &this->vertices[42], &this->vertices[46]));

        this->edges.push_back(Edge(62, &this->vertices[43], &this->vertices[47]));
        this->edges.push_back(Edge(63, &this->vertices[44], &this->vertices[48]));
        this->edges.push_back(Edge(64, &this->vertices[45], &this->vertices[49]));
        this->edges.push_back(Edge(65, &this->vertices[46], &this->vertices[50]));

        this->edges.push_back(Edge(66, &this->vertices[47], &this->vertices[51]));
        this->edges.push_back(Edge(67, &this->vertices[48], &this->vertices[51]));
        this->edges.push_back(Edge(68, &this->vertices[48], &this->vertices[52]));
        this->edges.push_back(Edge(69, &this->vertices[49], &this->vertices[52]));
        this->edges.push_back(Edge(70, &this->vertices[49], &this->vertices[53]));
        this->edges.push_back(Edge(71, &this->vertices[50], &this->vertices[53]));

        // connect the edges to the vertices:
        for(int i=0; i<72; i++){
            this->edges[i].getVertex1()->addEdge(&this->edges[i]);
            this->edges[i].getVertex2()->addEdge(&this->edges[i]);
        }

        // Create the cards:
        for(int i=0; i<14; i++){  // 14 KNIGHT cards:
            this->cards.push_back(Card(0, KNIGHT));
        }
        for(int i=14; i<19; i++){  // 5 VICTORY_POINT cards:
            this->cards.push_back(Card(1, VICTORYPOINT));
        }
        for(int i=19; i<21; i++){  // 2 MONOPOLY cards:
            this->cards.push_back(Card(2, MONOPOLY));
        }
        for(int i=21; i<23; i++){  // 2 ROAD_BUILDING cards:
            this->cards.push_back(Card(3, ROADBUILDING));
        }
        for(int i=23; i<25; i++){  // 2 YEAR_OF_PLENTY cards:
            this->cards.push_back(Card(4, YEAROFPLENTY));
        }
        // shuffle the cards:
        random_shuffle(this->cards.begin(), this->cards.end());
    }

    Player* Board::hasWinner(){
        for(int i=0; i<3; i++){
            if(this->players[i]->getPoints() >= 10){
                return this->players[i];
            }
        }
        return nullptr;
    }





    
} // namespace ariel