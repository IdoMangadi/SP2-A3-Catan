
#include "BoardElements.hpp"

namespace ariel{

    Hexagon::Hexagon(int id, int type, int diceNum, bool hasRobber) : id(id), type(type), diceNum(diceNum), hasRobber(hasRobber){}

    int Hexagon::getType(){
        return this->type;
    }
    int Hexagon::getId(){
        return this->id;
    }
    bool Hexagon::getHasRobber(){
        return this->hasRobber;
    }
    void Hexagon::setHasRobber(bool hasRobber){
        this->hasRobber = hasRobber;
    }

    Edge::Edge(int id, Vertex& vertex1, Vertex& vertex2) : id(id), vertex1(vertex1), vertex2(vertex2){
        this->road = nullptr;
    }
    int Edge::getId(){
        return this->id;
    }
    Vertex& Edge::getVertex1(){
        return this->vertex1;
    }
    Vertex& Edge::getVertex2(){
        return this->vertex2;
    }
    bool Edge::hasRoad(){
        return this->road != nullptr;
    }
    Road& Edge::getRoad(){
        return *(this->road);
    }

    Vertex::Vertex(int id, vector<Edge&> edges) : id(id), edges(edges){
        this->settlement = nullptr;
    }
    int Vertex::getId(){
        return this->id;
    }
    vector<Edge&> Vertex::getEdges(){
        return this->edges;
    }
    bool Vertex::hasSettlement(){
        return this->settlement != nullptr;
    }
    Settlement& Vertex::getSettlement(){
        return *(this->settlement);
    }
}