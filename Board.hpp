
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include <vector>

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

            vector<int> diceNums;
            vector<Card> cards;

            vector<Road> roadsPlayer1;
            vector<Road> roadsPlayer2;
            vector<Road> roadsPlayer3;

            vector<Settlement> settlementsPlayer1;
            vector<Settlement> settlementsPlayer2;
            vector<Settlement> settlementsPlayer3;

            int longestRoad;
            int largestArmy;

        public:
            Board(Player* player1, Player* player2, Player* player3);  // constructor

            Player* hasWinner();  // return the player with the most points, or nullptr if no winner
            vector<Player*>* getPlayers();  // return the players

            vector<int>* rollDice();  // roll the dice and return the numbers, distribute resources to players



            void display();  // display the board

    };
}






#endif  // BOARD_HPP
