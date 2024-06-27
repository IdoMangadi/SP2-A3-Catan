#ifndef BOARD_ELEMENTS_HPP
#define BOARD_ELEMENTS_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ariel{
    
    // forward declarations:
    class Edge;
    class Vertex;
    class Road;
    class Settlement;


    /**
     * @brief A class representing a hexagon on the board.
    */
    class Hexagon{
        private:
            int id;
            string type;
            size_t diceNum;
            bool hasRobber;  // not used. here for future implementation
            vector<Vertex*> vertices;  // the vertices of the hexagon (6 vertices for each hexagon)
        public:
            /**
             * @brief Construct a new Hexagon object.
             */
            Hexagon(int id, string type, size_t diceNum, bool hasRobber);
            /**
             * @brief Get the id of the hexagon.
             */
            int getId();
            /**
             * @brief Get the dice number of the hexagon.
             */
            size_t getDiceNum();
            /**
             * @brief Get the type of the hexagon (can be "DESERT", "FOREST", "HILLS", "AGRICULTURAL", "PASTURE", "MOUNTAINS")
             */
            string getType();
            /**
             * @brief Get the resource type of the hexagon (can be WOOD, BRICK, WHEAT, WOOL, ORE, DESERT)
             */
            int getResourceType();
            /**
             * @brief Get if the hexagon has the robber on it.
             */
            bool getHasRobber();
            /**
             * @brief Set the robber on the hexagon.
             */
            void setRobber(bool hasRobber);
            /**
             * @brief Add a vertex to the hexagon.
             */
            void addVertex(Vertex* vertex);
            /**
             * @brief Get the vertices of the hexagon.
             */
            vector<Vertex*>* getVertices(); 
            /**
             * @brief Overload the << operator for the hexagon.
             */
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
            /**
             * @brief Construct a new Edge object.
             */
            Edge(int id, int pose, Vertex* vertex1, Vertex* vertex2);
            /**
             * @brief Get the id of the edge.
             */
            int getId();
            /**
             * @brief Set the color of the edge.
             */
            void setColor(string color);
            /**
             * @brief Get the first vertex of the edge.
             */
            Vertex* getVertex1();
            /**
             * @brief Get the second vertex of the edge.
             */
            Vertex* getVertex2();
            /**
             * @brief Check if the edge has a road.
             */
            bool hasRoad();
            /**
             * @brief Get the road of the edge.
             */
            Road* getRoad();
            /**
             * @brief Set the road of the edge.
             */
            void setRoad(Road* road);
            /**
             * @brief Overload the << operator for the edge.
             */
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
            /**
             * @brief Construct a new Vertex object.
             */
            Vertex(int id);
            /**
             * @brief Get the id of the vertex.
             */
            int getId();
            /**
             * @brief Add an edge to the vertex.
             */
            void addEdge(Edge* edge);
            /**
             * @brief Get the edges of the vertex.
             */
            vector<Edge*> getEdges();
            /**
             * @brief Set the settlement on the vertex.
             */
            void setSettlement(Settlement* settlement);
            /**
             * @brief Check if the vertex has a settlement.
             */
            bool hasSettlement();
            /**
             * @brief Get the settlement of the vertex.
             */
            Settlement* getSettlement();
            /**
             * @brief Overload the << operator for the vertex.
             */
            friend ostream& operator<<(ostream& os, const Vertex& vertex);
    };
}

#endif  // BOARD_ELEMENTS_HPP
