
#include "BoardElements.hpp"

using namespace std;

namespace ariel{

    Hexagon::Hexagon(int id, string type, int diceNum, bool hasRobber) : id(id), type(type), diceNum(diceNum), hasRobber(hasRobber){}

    int Hexagon::getDiceNum(){
        return this->diceNum;
    }
    int Hexagon::getId(){
        return this->id;
    }
    string Hexagon::getType(){
        return this->type;
    }
    int Hexagon::getResourceType(){  // the type of the resource the hexagon produces (hexagon type / 100 - 1)
        if (this->type == DESERT_EMOJI) return -1;
        if (this->type == FOREST_EMOJI) return WOOD;
        if (this->type == HILLS_EMOJI) return BRICK;
        if (this->type == AGRICULTURAL_EMOJI) return WHEAT;
        if (this->type == PASTURE_EMOJI) return WOOL;
        if (this->type == MOUNTAINS_EMOJI) return ORE;

    }
    bool Hexagon::getHasRobber(){
        return this->hasRobber;
    }
    void Hexagon::setRobber(bool hasRobber){
        this->hasRobber = hasRobber;
    }
    void Hexagon::addVertex(Vertex* vertex){
        this->vertices.push_back(vertex);
    }
    vector<Vertex*>* Hexagon::getVertices(){
        return &this->vertices;
    }
    ostream& operator<<(ostream& os, const Hexagon& hexagon){
        os << hexagon.type << hexagon.diceNum;
        return os;
    }

    Edge::Edge(int id, int pose, Vertex* vertex1, Vertex* vertex2) : id(id), pose(pose), vertex1(vertex1), vertex2(vertex2){
        this->color = WHITE;  // default color is white
        this->road = nullptr;
    }
    int Edge::getId(){
        return this->id;
    }
    void Edge::setColor(string color){
        this->color = color;
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
    ostream& operator<<(ostream& os, const Edge& edge){
        string pose;  
        if (edge.pose == 0) pose = "|";
        else if (edge.pose == 1) pose = "/";
        else pose = "\\";
        os << edge.color << pose;
        return os;
    }

    Vertex::Vertex(int id) : id(id){
        this->shape = EMPTY_VERTEX;
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
    ostream& operator<<(ostream& os, const Vertex& vertex){
        if(vertex.settlement != nullptr){  // if there is a settlement on the vertex
            os << vertex.settlement;
        }
        else{
            os << vertex.shape;
        }
        return os;
    }
}