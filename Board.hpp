
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
            vector<Player*> players;  // the players

            // the concrete board elements (rest of the classes hold pointers to these elements):
            vector<Hexagon> hexagons;
            vector<Vertex> vertices;
            vector<Edge> edges;

            vector<size_t> diceNums;
            vector<Card> cards;
            size_t cardsIndex;  // the index of the next card to draw

            vector<vector<Road>> playersRoads; // to store the concrete roads of each player
            vector<vector<Settlement>> playersSettlements; // to store the concrete settlements of each player

            // the stats:
            size_t longestRoad;
            Player* longestRoadPlayer;
            size_t largestArmy;
            Player* largestArmyPlayer;

        public:
            /**
             * @brief Construct a new Board object. 
             * creates the concrete board elements (hexagons, vertices, edges) and the pieces (roads, settlements, cards).
            */
            Board(Player* player1, Player* player2, Player* player3);

            /**
             * return the player with the most points, or nullptr if no winner
            */
            Player* hasWinner();

            /**
             * return the players
            */
            vector<Player*>* getPlayers();

            /**
             * buy a building or a road or a card.
             * NOTE: position validation is not done here. make sure to validate the position before calling this function.
            */
            bool buy(Player* player, int itemType, size_t position, int opCode);

            /**
             * distribute resources to players.
            */
            void distributeResources(size_t diceNum);

            /**
             * distribute resources to players after the first stage of the game
            */
            void stageOneResourcesDistribution();

            /**
             * updating the largest army player
            */
            bool knightUsed(Player* player);

            /**
             * updating the longest road player
            */
            bool longestRoadCheck(Player* player);

            /**
             * roll the dice and return the numbers, distribute resources to players by the board and not by the settlement class
            */
            vector<size_t>* rollDice();

            /**
             * // display the stats of the players
            */
            void displayStats();
            /**
             * // display the board
            */
            void display();

    };
}






#endif  // BOARD_HPP
