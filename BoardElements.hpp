#include <string>
#include "Pieces.hpp"

using namespace std;

namespace ariel{

    class Hexagon{
        private:
            string type;
            int id;
            bool hasRobber;
        public:
            Hexagon(string type, int number, bool hasRobber);
            string getType();
            int getNumber();
            bool getHasRobber();
            void setHasRobber(bool hasRobber);
    };

    class Edge{
        private:
            int id;
            Vertex vertex1;
            Vertex vertex2;
            bool hasRoad;
            Road road;
        public:
            Edge(int id, Vertex vertex1, Vertex vertex2, bool hasRoad);
            int getId();
            Vertex getVertex1();
            Vertex getVertex2();
            bool getHasRoad();
            void setHasRoad(bool hasRoad);
    };

    class Vertex{
        private:
            int id;
            bool hasSettlement;
            Settlement settlement;
            vector<Edge> edges;

        public:
            Vertex(int id, bool hasSettlement, bool hasCity);
            int getId();
            bool getHasSettlement();
            bool getHasCity();
            void setHasSettlement(bool hasSettlement);
            void setHasCity(bool hasCity);
    };
}