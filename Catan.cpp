#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <string>

#include "Board.hpp"
#include "Player.hpp"
#include "Pieces.hpp"
#include "Card.hpp"
#include "BoardElements.hpp"

using namespace std;
using namespace ariel;

/**
 * function to check if a string is a number between 0 and 53
*/
size_t vertexValidation(string vertex){
    // check if the input is a one or two digits number between 0 and 53 and return it:
    if(vertex.length() == 1 && vertex[0] >= '0' && vertex[0] <= '9'){ 
            return (size_t)(vertex[0] - '0');
    }
    else if(vertex.length() == 2 && vertex[0] >= '0' && vertex[0] <= '5' && vertex[1] >= '0' && vertex[1] <= '9'){
        if(stoi(vertex) <= 53) return (size_t)stoi(vertex);  // check if the number is between 0 and 53
    }
    return INVALID_POSITION;
}
/**
 * @brief Get a vertex number between 0 and 53 from the user.
*/
size_t getVertexFromUser(){
    string vertex;
    do{
        cin >> vertex;
        size_t result = vertexValidation(vertex);
        if(result != INVALID_POSITION) return result;
        else cout << "Invalid vertex, please enter a number between 0 and 53" << endl;
    } while(true);
    return INVALID_POSITION;
}
/**
 * function to check if a string is a number between 0 and 71
*/
size_t edgeValidation(string edge){
    // check if the input is a one or two digits number between 0 and 71 and return it:
    if(edge.length() == 1 && edge[0] >= '0' && edge[0] <= '9'){
        return (size_t)(edge[0] - '0');
    }
    else if(edge.length() == 2 && edge[0] >= '0' && edge[0] <= '7' && edge[1] >= '0' && edge[1] <= '9'){
        if(stoi(edge) <= 71) return (size_t)stoi(edge);  // check if the number is between 0 and 71
    }
    return INVALID_POSITION;
}
/**
 * @brief Get a edge number between 0 and 71 from the user.
*/
size_t getEdgeFromUser(){
    string edge;
    do{
        cin >> edge;
        size_t result = edgeValidation(edge);
        if(result != INVALID_POSITION) return result;
        else cout << "Invalid edge, please enter a number between 0 and 71" << endl;
    } while(true);
    return INVALID_POSITION;
}
void stageOne(Board* board){
    for(size_t i=0; i<6; i++){
        // get the player name:
        string playerName;
        Player* currPlayer;
        if (i == 0 || i == 5) currPlayer = board->getPlayers()->at(0);
        else if (i == 1 || i == 4) currPlayer = board->getPlayers()->at(1);
        else currPlayer = board->getPlayers()->at(2);
        playerName = currPlayer->getName();

        // buying a settlement and a road:
        size_t vertexId = INVALID_POSITION, edgeId = INVALID_POSITION;
        do{
            cout << playerName << ", choose vertex to place settelement. Enter a vertex number between 0 and 53: " << endl;
            vertexId = getVertexFromUser();
        } while(board->buy(currPlayer, SETTLEMENT, vertexId, STAGE_ONE) == false);
        do{
            cout << playerName << ", choose edge to place road. Enter an edge number between 0 and 71: " << endl;
            edgeId = getEdgeFromUser();
        } while(board->buy(currPlayer, ROAD, edgeId, STAGE_ONE) == false);
        if(i < 5) board->display();
    }
    board->stageOneResourcesDistribution();
    board->display();
}
/**
 * @brief Split a string into tokens by spaces.
*/
void splitAction(string* action, vector<string>* actionTokens){
    string token = "";
    for(size_t i=0; i<action->length(); i++){
        if(action->at(i) == ' '){
            actionTokens->push_back(token);
            token = "";
        }
        else{
            token += action->at(i);
        }
    }
    actionTokens->push_back(token);
}
/**
 * @brief Handle the buy action.
*/
bool mainBuy(Board* board, Player* player, vector<string>* actionTokens){
    if(actionTokens->size() != 3){  // invalid input
        cout << "Invalid action, please try again" << endl;
        return false;
    }
    size_t position = INVALID_POSITION, itemType;  // position will be changed only if the item is a road or a building
    if(actionTokens->at(1) == "ROAD"){ 
        position = edgeValidation(actionTokens->at(1));
        itemType = ROAD;
    }
    if(actionTokens->at(1) == "SETTLEMENT" || actionTokens->at(1) == "CITY"){ 
        position = vertexValidation(actionTokens->at(1));
        if(actionTokens->at(1) == "SETTLEMENT") itemType = SETTLEMENT;
        else itemType = CITY;
    }
    if(position != INVALID_POSITION) return board->buy(player, itemType, position, PAID);
    else{
        cout << "Invalid action, please try again" << endl;
        return false;
    }
    return false;
}


int main(int argc , char* argv[]){
    // check if the number of arguments is correct:
    if(argc != 4){
        cout << "Usage: Catan <player1_name> <player2_name> <player3_name>" << endl;
        return 1;
    }
    // extracting player names from command line arguments:
    string player1Name = argv[1];
    string player2Name = argv[2];
    string player3Name = argv[3];

    // initialize players and board:
    vector<Player> players = {Player(player1Name, 0, RED, 0), Player(player2Name, 1, GREEN, 0), Player(player3Name, 2, YELLOW, 0)};
    Board board(&players[0], &players[1], &players[2]); 
    size_t turn = 0;
    board.display();

    // first stage: each player places 2 settlements and 2 roads:
    stageOne(&board);

    // second stage: game loop:
    while(true){
        string action;
        // dice roll:
        do{
            cout << BOLD << players[turn].getColor() << "Turn " << players[turn].getName()<< ": " << RESET_COLOR << "Roll the dice! <roll>" << endl;
            cin >> action;
        } while(action != "roll");
        vector<size_t>* diceNums = board.rollDice();
        cout << BOLD << "Dice numbers: " << diceNums->at(0) << " , " << diceNums->at(1) << RESET_COLOR << endl;

        while(true){
            // player action:
            cout << "Choose action:  <buy> <ITEM> <position>\n                <trade> <offer> <seek>\n                <status>\n                <end>" << endl;
            cin >> action;
            vector<string> actionTokens;
            splitAction(&action, &actionTokens);

            // buy action:
            if(actionTokens.at(0) == "buy"){
                if(mainBuy(&board, &players[turn], &actionTokens) == false) continue;
            }

            // continue from here...

            break;
        }

        board.display();
        turn = (turn + 1) % 3;
    }

    return 0;
    
}









#endif  // CATAN_HPP