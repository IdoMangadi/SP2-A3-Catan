
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include <vector>

#define INVALID_POSITION 100

using namespace std;

namespace ariel{

    // forward declarations:
    class Player;
    class Hexagon;
    class Vertex;
    class Edge;
    class Road;
    class Settlement;
    class Card;

    class Board{
        private:
            vector<Player*> players;

            // the concrete board elements (rest of the classes hold pointers to these elements):
            vector<Hexagon> hexagons;
            vector<Vertex> vertices;
            vector<Edge> edges;

            vector<size_t> diceNums;
            vector<Card> cards;
            size_t cardsIndex;

            vector<vector<Road>> playersRoads; // to store the concrete roads of each player
            vector<vector<Settlement>> playersSettlements; // to store the concrete settlements of each player

            int longestRoad;
            int largestArmy;

        public:
            Board(Player* player1, Player* player2, Player* player3);  // constructor

            Player* hasWinner();  // return the player with the most points, or nullptr if no winner
            vector<Player*>* getPlayers();  // return the players

            bool buy(Player* player, int itemType, size_t position, int opCode);  // buy a building or a road or a card

            void distributeResources(size_t diceNum);  // distribute resources to players by the settlement class

            void stageOneResourcesDistribution(); // distribute resources to players after the first stage of the game

            vector<size_t>* rollDice();  // roll the dice and return the numbers, distribute resources to players by the board and not by the settlement class.



            void displayStats();  // display the stats of the players
            void display();  // display the board

    };
}






#endif  // BOARD_HPP
