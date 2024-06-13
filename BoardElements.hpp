#ifndef BOARD_ELEMENTS_HPP
#define BOARD_ELEMENTS_HPP

#include <string>
#include <vector>
#include "Pieces.hpp"

#define DESERT 000  
#define FOREST 100  // dark green
#define HILLS 200  // red
#define AGRICULTURAL 300  // yellow
#define PASTURE 400  // light green
#define MOUNTAINS 500  // gray

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
            int type;
            int diceNum;
            bool hasRobber;
            vector<Vertex*> vertices;
        public:
            Hexagon(int id, int type, int diceNum, bool hasRobber);
            int getType();
            int getId();
            int getDiceNum();
            bool getHasRobber();
            void setHasRobber(bool hasRobber);
            void addVertex(Vertex* vertex);
    };

    /**
     * @brief A class representing an edge on the board.
    */
    class Edge{
        private:
            int id;
            Vertex* vertex1;
            Vertex* vertex2;
            Road* road;

        public:
            Edge(int id, Vertex* vertex1, Vertex* vertex2);
            int getId();

            Vertex* getVertex1();
            Vertex* getVertex2();

            bool hasRoad();
            Road* getRoad();
            void setRoad(Road* road);
    };

    /**
     * @brief A class representing a vertex on the board.
    */
    class Vertex{
        private:
            int id;
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
    };
}

#endif  // BOARD_ELEMENTS_HPP
