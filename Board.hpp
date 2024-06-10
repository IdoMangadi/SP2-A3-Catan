
#include <iostream>
#include <string>

#include "BoardElements.hpp"
#include "Player.hpp"
#include "Card.hpp"


namespace ariel{
    class Board{
        private:
            vector<Hexagon> hexagons;
            vector<Edge> edges;
            vector<Vertex> vertices;
            vector<Player> players;
            vector<Card> deck;
            int robber;
            int turn;
            int dice;
            int longestRoad;
            int largestArmy;
            int winner;
        public:
            Board();
            void addHexagon(Hexagon hexagon);
            void addEdge(Edge edge);
            void addVertex(Vertex vertex);
            void addPlayer(Player player);
            void addCard(Card card);
            void setRobber(int robber);
            void setTurn(int turn);
            void setDice(int dice);
            void setLongestRoad(int longestRoad);
            void setLargestArmy(int largestArmy);
            void setWinner(int winner);
            vector<Hexagon> getHexagons();
            vector<Edge> getEdges();
            vector<Vertex> getVertices();
            vector<Player> getPlayers();
            vector<Card> getDeck();
            int getRobber();
            int getTurn();
            int getDice();
            int getLongestRoad();
            int getLargestArmy();
            int getWinner();
    };
}