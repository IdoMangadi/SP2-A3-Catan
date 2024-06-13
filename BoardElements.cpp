
#include "BoardElements.hpp"

namespace ariel{

    Hexagon::Hexagon(int id, int type, int diceNum, bool hasRobber) : id(id), type(type), diceNum(diceNum), hasRobber(hasRobber){}

    int Hexagon::getType(){
        return this->type;
    }
    int Hexagon::getId(){
        return this->id;
    }
    int Hexagon::getDiceNum(){
        return this->diceNum;
    }
    bool Hexagon::getHasRobber(){
        return this->hasRobber;
    }
    void Hexagon::setHasRobber(bool hasRobber){
        this->hasRobber = hasRobber;
    }
    void Hexagon::addVertex(Vertex* vertex){
        this->vertices.push_back(vertex);
    }

    Edge::Edge(int id, Vertex* vertex1, Vertex* vertex2) : id(id), vertex1(vertex1), vertex2(vertex2){
        this->road = nullptr;
    }
    int Edge::getId(){
        return this->id;
    }
    Vertex* Edge::getVertex1(){
        return this->vertex1;
    }
    Vertex* Edge::getVertex2(){
        return this->vertex2;
    }
    bool Edge::hasRoad(){
        return this->road != nullptr;
    }
    Road* Edge::getRoad(){
        return this->road;
    }
    void Edge::setRoad(Road* road){
        this->road = road;
    }

    Vertex::Vertex(int id) : id(id){
        this->settlement = nullptr;
    }
    void Vertex::addEdge(Edge* edge){
        this->edges.push_back(edge);
    }
    void Vertex::setSettlement(Settlement* settlement){
        this->settlement = settlement;
    }
    int Vertex::getId(){
        return this->id;
    }
    vector<Edge*> Vertex::getEdges(){
        return this->edges;
    }
    bool Vertex::hasSettlement(){
        return this->settlement != nullptr;
    }
    Settlement* Vertex::getSettlement(){
        return this->settlement;
    }
}