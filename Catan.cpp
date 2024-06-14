#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include "Board.hpp"

using namespace std;
using namespace ariel;

void stageOne(Board* board){
    for(int i=0; i<6; i++){
        int vertexId = -1, edgeId = -1;
        // player 1:
        if(i == 0 || i == 5){
            do {
                cout << board->getPlayers()->at(0)->getName() << ", choose vertex to place settelement" << endl;
                cin >> vertexId;
            } while(board->buy(board->getPlayers()->at(0), SETTLEMENT, vertexId, FREE) == false);
            do {
                cout << board->getPlayers()->at(0)->getName() << ", choose edge to place road" << endl;
                cin >> edgeId;
            } while(board->buy(board->getPlayers()->at(0), ROAD, edgeId, FREE) == false);
        }
        // player 2:
        else if(i == 1 || i == 4){
            do {
                cout << board->getPlayers()->at(1)->getName() << ", choose vertex to place settelement" << endl;
                cin >> vertexId;
            } while(board->buy(board->getPlayers()->at(1), SETTLEMENT, vertexId, FREE) == false);
            do {
                cout << board->getPlayers()->at(1)->getName() << ", choose edge to place road" << endl;
                cin >> edgeId;
            } while(board->buy(board->getPlayers()->at(1), ROAD, edgeId, FREE) == false);
        }
        // player 3:
        else{
            do {
                cout << board->getPlayers()->at(2)->getName() << ", choose vertex to place settelement" << endl;
                cin >> vertexId;
            } while(board->buy(board->getPlayers()->at(2), SETTLEMENT, vertexId, FREE) == false);
            do {
                cout << board->getPlayers()->at(2)->getName() << ", choose edge to place road" << endl;
                cin >> edgeId;
            } while(board->buy(board->getPlayers()->at(2), ROAD, edgeId, FREE) == false);
        }
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
    Player player1(player1Name, 1, 0);
    Player player2(player2Name, 2, 0);
    Player player3(player3Name, 3, 0);

    Board board(&player1, &player2, &player3); 
    int turn = 0;

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
        
        // --------TODO: completet this part from here---------:
        else if(actionTokens.at(0) == "buy"){
            int itemType = -1, position = -1;
            if(actionTokens.at(1) == "road"){
                itemType = ROAD;
            }
            else if(actionTokens.at(1) == "settlement"){
                itemType = SETTLEMENT;
            }
            else if(actionTokens.at(1) == "city"){
                itemType = CITY;
            }
            else{
                cout << "Invalid item type" << endl;
                continue;
            }
            position = stoi(actionTokens.at(2));
            if(board.buy(board.getPlayers()->at(0), itemType, position, PAID) == false){
                cout << "Failed to buy item" << endl;
            }
        }
        else if(actionTokens.at(0) == "trade"){
            int offer = -1, seek = -1;
            offer = stoi(actionTokens.at(1));
            seek = stoi(actionTokens.at(2));
            if(board.trade(board.getPlayers()->at(0), offer, seek) == false){
                cout << "Failed to trade" << endl;
            }
        }
        else if(actionTokens.at(0) == "status"){
            board.printStatus();
        }
        else if(actionTokens.at(0) == "end"){
            break;
        }
        else{
            cout << "Invalid action" << endl;
        }
        // --------------------up-to-here-------------------------------:

        turn = (turn + 1) % 3;
    }

    return 0;
    
}









#endif  // CATAN_HPP