
#ifndef BOARD_HPP
#define BOARD_HPP

#include "BoardElements.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "Pieces.hpp"

namespace ariel{

    class Board{
        private:
            vector<Player*> players;

            // the concrete board elements (rest of the classes hold pointers to these elements):
            vector<Hexagon> hexagons;
            vector<Vertex> vertices;
            vector<Edge> edges;

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
            Board(Player* player1, Player* player2, Player* player3);

            Player* hasWinner();

    };
}






#endif  // BOARD_HPP
