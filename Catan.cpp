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
 * @brief Get a vertex number between 0 and 53 from the user.
*/
size_t getVertexFromUser(){
    string vertex;
    do{
        cin >> vertex;
        // check if the input is a one or two digits number between 0 and 53 and return it:
        if(vertex.length() == 1 && vertex[0] >= '0' && vertex[0] <= '9'){
            return (size_t)(vertex[0] - '0');
        }
        else if(vertex.length() == 2 && vertex[0] >= '0' && vertex[0] <= '5' && vertex[1] >= '0' && vertex[1] <= '9'){
            if(stoi(vertex) <= 53) return (size_t)stoi(vertex);  // check if the number is between 0 and 53
        }
        else{
            cout << "Invalid vertex, please enter a number between 0 and 53" << endl;
        }
    } while(true);
    return 100;
}
/**
 * @brief Get a edge number between 0 and 71 from the user.
*/
size_t getEdgeFromUser(){
    string edge;
    do{
        cin >> edge;
        // check if the input is a one or two digits number between 0 and 71 and return it:
        if(edge.length() == 1 && edge[0] >= '0' && edge[0] <= '9'){
            return (size_t)(edge[0] - '0');
        }
        else if(edge.length() == 2 && edge[0] >= '0' && edge[0] <= '7' && edge[1] >= '0' && edge[1] <= '9'){
            if(stoi(edge) <= 71) return (size_t)stoi(edge);  // check if the number is between 0 and 71
        }
        else{
            cout << "Invalid edge, please enter a number between 0 and 71" << endl;
        }
    } while(true);
    return 100;
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
        size_t vertexId = 100, edgeId = 100;
        do{
            cout << playerName << ", choose vertex to place settelement. Enter a vertex number between 0 and 53: " << endl;
            vertexId = getVertexFromUser();
        } while(board->buy(currPlayer, SETTLEMENT, vertexId, STAGE_ONE) == false);
        do{
            cout << playerName << ", choose edge to place road. Enter an edge number between 0 and 71: " << endl;
            edgeId = getEdgeFromUser();
        } while(board->buy(currPlayer, ROAD, edgeId, STAGE_ONE) == false);
    }
}

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
    Player player1(player1Name, 0, RED, 0);
    Player player2(player2Name, 1, GREEN, 0); 
    Player player3(player3Name, 2, YELLOW, 0);

    Board board(&player1, &player2, &player3); 
    size_t turn = 0;
    board.display();

    // first stage: each player places 2 settlements and 2 roads:
    stageOne(&board);

    // second stage: game loop:
    while(true){
        cout << "Turn: " << board.getPlayers()->at(turn)->getName() << endl;
        string action;
        cout << "Choose action:\n<roll>\n<buy> <item> <position>\n<trade> <offer> <seek>\n<status>\n<end>" << endl;
        cin >> action;
        vector<string> actionTokens;
        splitAction(&action, &actionTokens);

        if(actionTokens.at(0) == "roll"){  // roll the dice, resources are distributed to players by the Board class.
            vector<int>* diceNums = board.rollDice();
            cout << "Dice numbers: " << diceNums->at(0) << " " << diceNums->at(1) << endl;
        }

    }
        
    //     // --------TODO: completet this part from here---------:
    //     else if(actionTokens.at(0) == "buy"){
    //         int itemType = -1, position = -1;
    //         if(actionTokens.at(1) == "road"){
    //             itemType = ROAD;
    //         }
    //         else if(actionTokens.at(1) == "settlement"){
    //             itemType = SETTLEMENT;
    //         }
    //         else if(actionTokens.at(1) == "city"){
    //             itemType = CITY;
    //         }
    //         else{
    //             cout << "Invalid item type" << endl;
    //             continue;
    //         }
    //         position = stoi(actionTokens.at(2));
    //         if(board.buy(board.getPlayers()->at(0), itemType, position, PAID) == false){
    //             cout << "Failed to buy item" << endl;
    //         }
    //     }
    //     else if(actionTokens.at(0) == "trade"){
    //         int offer = -1, seek = -1;
    //         offer = stoi(actionTokens.at(1));
    //         seek = stoi(actionTokens.at(2));
    //         if(board.trade(board.getPlayers()->at(0), offer, seek) == false){
    //             cout << "Failed to trade" << endl;
    //         }
    //     }
    //     else if(actionTokens.at(0) == "status"){
    //         board.printStatus();
    //     }
    //     else if(actionTokens.at(0) == "end"){
    //         break;
    //     }
    //     else{
    //         cout << "Invalid action" << endl;
    //     }
    //     // --------------------up-to-here-------------------------------:

    //     turn = (turn + 1) % 3;
    // }

    return 0;
    
}









#endif  // CATAN_HPP