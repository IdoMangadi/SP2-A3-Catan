#ifndef BOARD_ELEMENTS_HPP
#define BOARD_ELEMENTS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Pieces.hpp"

using namespace std;

namespace ariel{

    class Edge;
    class Vertex;

    /**
     * @brief A class representing a hexagon on the board.
    */
    class Hexagon{
        private:
            int id;
            string type;
            int diceNum;
            bool hasRobber;
            vector<Vertex*> vertices;
        public:
            Hexagon(int id, string type, int diceNum, bool hasRobber);
            int getId();
            int getDiceNum();
            string getType();
            int getResourceType();
            bool getHasRobber();
            void setRobber(bool hasRobber);
            void addVertex(Vertex* vertex);
            vector<Vertex*>* getVertices(); 

            friend ostream& operator<<(ostream& os, const Hexagon& hexagon);
    };

    /**
     * @brief A class representing an edge on the board.
    */
    class Edge{
        private:
            int id;
            int pose; // 0 = '|' , 1 = '/' , 2 = '\'
            string color;
            Vertex* vertex1;
            Vertex* vertex2;
            Road* road;

        public:
            Edge(int id, int pose, Vertex* vertex1, Vertex* vertex2);
            int getId();

            void setColor(string color);

            Vertex* getVertex1();
            Vertex* getVertex2();

            bool hasRoad();
            Road* getRoad();
            void setRoad(Road* road);

            friend ostream& operator<<(ostream& os, const Edge& edge);
    };

    /**
     * @brief A class representing a vertex on the board.
    */
    class Vertex{
        private:
            int id;
            string shape;
            vector<Edge*> edges;
            Settlement* settlement;

        public:
            Vertex(int id);
            int getId();

            void addEdge(Edge* edge);
            vector<Edge*> getEdges();
            
            void setSettlement(Settlement* settlement);
            bool hasSettlement();
            Settlement* getSettlement();

            friend ostream& operator<<(ostream& os, const Vertex& vertex);
    };
}

#endif  // BOARD_ELEMENTS_HPP
