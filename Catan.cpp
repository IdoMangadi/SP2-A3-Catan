#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <string>
#include <sstream> 

#include "Board.hpp"
#include "Player.hpp"
#include "Pieces.hpp"
#include "Card.hpp"
#include "BoardElements.hpp"

using namespace std;
using namespace ariel;

/**
 * @brief Parse a string to a size_t.
 * @param str The string to parse.
 * @param result The result of the parsing.
 * @return True if the parsing was successful, false otherwise.
 * the function checks if the string is a nubmer and if so it converts it to a size_t and return true, otherwise it returns false.
*/
bool parseStringToSize_t(string str, size_t& result){
    for(size_t i=0; i<str.length(); i++){
        if(str[i] < '0' || str[i] > '9') return false;
    }
    result = (size_t)stoi(str);
    return true;
}
/**
 * function to check if a string is a number between 0 and 53
*/
size_t vertexValidation(string vertex){
    size_t result = INVALID_POSITION;
    if(parseStringToSize_t(vertex, result) == false) return INVALID_POSITION;  // check if the input is a number
    if(result >= 0 && result <= 53) return result;  // check if the number is between 0 and 53
    return INVALID_POSITION;
}

/**
 * @brief Get a vertex number between 0 and 53 from the user.
*/
size_t getVertexFromUser(){
    string vertex;
    do{
        cin >> vertex;
        cin.ignore();  // insuring the next input will be correct
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
    size_t result = INVALID_POSITION;
    if(parseStringToSize_t(edge, result) == false) return INVALID_POSITION;  // check if the input is a number
    if(result >= 0 && result <= 71) return result;  // check if the number is between 0 and 71
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
  
    // Creating an input string stream from the input string 
    istringstream stream(*(action)); 
  
    // Temporary string to store each token 
    string token; 
  
    // Read tokens from the string stream separated by the 
    // delimiter 
    while (getline(stream, token, ' ')) { 
        // Add the token to the vector of tokens 
        actionTokens->push_back(token); 
    }
} 
/**
 * @brief Handle the buy action.
*/
bool mainBuy(Board* board, Player* player, vector<string>* actionTokens){
    if(actionTokens->at(0) != "CARD" && actionTokens->size() != 3){  // invalid input
        cout << "Invalid action, please try again (NOT ENOUGH ARGUMENTS)" << endl;
        return false;
    }
    
    if(actionTokens->at(0) == "CARD"){
        if(board->buy(player, CARD, INVALID_POSITION, PAID) == true)
            cout << BOLD << "bought successfully" << RESET_COLOR << endl;
    }

    size_t position = INVALID_POSITION, itemType;  // position will be changed only if the item is a road or a building
    if(actionTokens->at(1) == "ROAD"){ 
        position = edgeValidation(actionTokens->at(2));
        itemType = ROAD;
    }
    if(actionTokens->at(1) == "SETTLEMENT" || actionTokens->at(1) == "CITY"){ 
        position = vertexValidation(actionTokens->at(2));
        if(actionTokens->at(1) == "SETTLEMENT") itemType = SETTLEMENT;
        else itemType = CITY;
    }
    if(position != INVALID_POSITION)
        if(board->buy(player, itemType, position, PAID) == true)
            cout << BOLD << "bought successfully" << RESET_COLOR << endl;
        else cout << BOLD << "failed to buy" << RESET_COLOR << endl;
    else{
        cout << "Invalid action, please try again (INVALID POSITION/ITEM)" << endl;
        return false;
    }
    return false;
}
void printInvalidTrade(){
    cout << "Invalid trade. usage: trade OFFER <amount> <resource> <amount> <resource>... SEEK <amount> <resource> <amount> <resource>..." << endl;
}
/**
 * check if the trade input is valid.
 * trade format: trade offer <amount> <resource> <amount> <resource>... seek <amount> <resource> <amount> <resource>... 
 * example: trade offer 1 ORE 1 WHEAT seek 2 WOOD
 * example2: trade offer 1 ORE 1 WHEAT 1 WOOL seek 2 WOOD 1 BRICK
 * the function validate that: the input contains the words 'trade', 'OFFER' and 'SEEK', the resources are valid and the amounts are numbers.
*/
bool tradeValidation(vector<string>* actionTokens){
    bool offer = false, seek = false;
    if (actionTokens->size() < 4 || actionTokens->at(0) != "trade"){ 
        printInvalidTrade();
        return false;  // the input is too short or the first word is not 'trade'
    }  
    for(size_t i=1; i<actionTokens->size(); i++){
        if(actionTokens->at(i) == "OFFER") offer = true;
        else if(actionTokens->at(i) == "SEEK") seek = true;
        else if(offer == true && seek == false){  // the OFFER part
            if(i % 2 == 1){  // odd index means the resource
                if(actionTokens->at(i) != "ORE" && actionTokens->at(i) != "WOOD" && actionTokens->at(i) != "BRICK" && actionTokens->at(i) != "WOOL" && actionTokens->at(i) != "WHEAT"){
                    printInvalidTrade();  // means that the resource is invalid
                    return false;
                }
            }
            else{  // even index means the amount
                for(size_t j=0; j<actionTokens->at(i).length(); j++){  // check if the amount is a number
                    if(actionTokens->at(i)[j] < '0' || actionTokens->at(i)[j] > '9'){
                        printInvalidTrade();
                        return false;
                    }
                }
            }
        }
        else if(offer == true && seek == true){  // the SEEK part
            if(i % 2 == 0){  // even index means the resource
                if(actionTokens->at(i) != "ORE" && actionTokens->at(i) != "WOOD" && actionTokens->at(i) != "BRICK" && actionTokens->at(i) != "WOOL" && actionTokens->at(i) != "WHEAT"){
                    printInvalidTrade();
                    return false;
                }
            }
            else{  // even index means the amount
                for(size_t j=0; j<actionTokens->at(i).length(); j++){
                    if(actionTokens->at(i)[j] < '0' || actionTokens->at(i)[j] > '9'){
                        printInvalidTrade();
                        return false;
                    }
                }
            }
        }
    }
    if(offer == true && seek == true) return true;
    return false;
}
/**
 * parse the trade input to 2 vectors of resources (5 cells long) representing the offer and the seek.
 * action tokens format : trade OFFER <amount> <resource> <amount> <resource>... SEEK <amount> <resource> <amount> <resource>...
*/
bool parseActionToVectors(vector<string>* actionTokens, vector<int>* offer, vector<int>* seek){
    bool offerB = false, seekB = false;
    for(size_t i=1; i<actionTokens->size(); i++){
        if(actionTokens->at(i) == "OFFER") offerB = true;
        else if(actionTokens->at(i) == "SEEK") seekB = true;
        else if(offerB == true && seekB == false){  // the OFFER part
            if(i % 2 == 1){  // odd index means the resource
                if (actionTokens->at(i) == "WOOD") offer->at(0) = stoi(actionTokens->at(i-1));
                else if(actionTokens->at(i) == "BRICK") offer->at(1) = stoi(actionTokens->at(i-1));
                else if(actionTokens->at(i) == "WHEAT") offer->at(2) = stoi(actionTokens->at(i-1));
                else if(actionTokens->at(i) == "WOOL") offer->at(3) = stoi(actionTokens->at(i-1));
                else if(actionTokens->at(i) == "ORE") offer->at(4) = stoi(actionTokens->at(i-1));
            }
        }
        else if(offerB == true && seekB == true){  // the SEEK part
            if(i % 2 == 0){  // even index means the resource
                if(actionTokens->at(i) == "WOOD") seek->at(0) = stoi(actionTokens->at(i-1));
                else if(actionTokens->at(i) == "BRICK") seek->at(1) = stoi(actionTokens->at(i-1));
                else if(actionTokens->at(i) == "WHEAT") seek->at(2) = stoi(actionTokens->at(i-1));
                else if(actionTokens->at(i) == "WOOL") seek->at(3) = stoi(actionTokens->at(i-1));
                else if(actionTokens->at(i) == "ORE") seek->at(4) = stoi(actionTokens->at(i-1));
                
            }
        }
    }
    return true;
}
/**
 * check if some player want to accept the proposal.
 * print the proposal to the terminal and ask for y/n answer from the other players (in turns each player enter his answer).
 * in case a player accept the offer it check if the player can afford the trade.
*/
Player* playerAccept(Board* board, vector<int>* offer, vector<int>* seek, Player* offerer){

    cout << BOLD << offerer->getColor() << "Trade proposal from " << offerer->getName() << RESET_COLOR << ": OFFER ";
    if(offer->at(0) > 0) cout << offer->at(0) << " WOOD";
    if(offer->at(1) > 0) cout << offer->at(1) << " BRICK";
    if(offer->at(2) > 0) cout << offer->at(2) << " WHEAT";
    if(offer->at(3) > 0) cout << offer->at(3) << " WOOL";
    if(offer->at(4) > 0) cout << offer->at(4) << " ORE";
    cout << ", SEEK ";
    if(seek->at(0) > 0) cout << seek->at(0) << " WOOD ";
    if(seek->at(1) > 0) cout << seek->at(1) << " BRICK ";
    if(seek->at(2) > 0) cout << seek->at(2) << " WHEAT ";
    if(seek->at(3) > 0) cout << seek->at(3) << " WOOL ";
    if(seek->at(4) > 0) cout << seek->at(4) << " ORE ";
    cout << endl;

    string answer;
    for(size_t i=0; i<3; i++){ // iterate over the players (not including the player that made the offer)
        if(board->getPlayers()->at(i) == offerer) continue;
        cout << BOLD << board->getPlayers()->at(i)->getColor() << board->getPlayers()->at(i)->getName() << RESET_COLOR << ", do you accept the trade? <y/n>" << endl;
        cin >> answer;
        cin.ignore();  // insuring the next input will be correct
        if(answer == "y" && board->getPlayers()->at(i)->canAfford(*seek) == true) return board->getPlayers()->at(i);
    }
    return nullptr;
}

/**
 * this function handles user input in format: trade offer 1ORE 1WHEAT seek 2WOOD
 * it parse the 'offer' and 'seek' to vector of resources 5 cells long (representing all the resources) (include validation check).
 * then it print the offer to the terminal and ask for y/n answer from the other players (in turns each player enter his answer).
 * in case there is player that accept the offer (the first one) it make the trade appending and reducing the relevant resources from each of the players.
 * the function uses:  function of validation check for input named: "tradeValidation", function to parse the actionTokens to 2 vectors of resources named: "parseActionToVectors",
 *                     function to check if some player want to accept the proposal named: "playerAccept" (includes print the proposal and get input from users).
*/
bool mainTrade(Board *board, Player* player, vector<string>* actionTokens){
    if(tradeValidation(actionTokens) == false){
        return false;
    }
    vector<int> offer = {0, 0, 0, 0, 0};  // 5 cells long vector representing the offer
    vector<int> seek = {0, 0, 0, 0, 0};  // 5 cells long vector representing the seek
    parseActionToVectors(actionTokens, &offer, &seek);
    if(player->canAfford(offer) == false){
        cout << "You can't afford the trade" << endl;
        return false;
    }

    Player* acceptedPlayer = playerAccept(board, &offer, &seek, player);
    if(acceptedPlayer == nullptr){
        cout << "No player accepted the trade" << endl;
        return false;
    }

    else{
        cout << BOLD << acceptedPlayer->getColor() << acceptedPlayer->getName() << RESET_COLOR << " accepted the trade" << endl;
        for(size_t i=0; i<5; i++){  // make the trade
            player->addResource(i, -offer.at(i));
            acceptedPlayer->addResource(i, offer.at(i));
            player->addResource(i, seek.at(i));
            acceptedPlayer->addResource(i, -seek.at(i));
        }
        return true;
    }
    return false;
}

bool mainCard(Board* board, Player* player, vector<string>* actionTokens){
    if(actionTokens->size() < 2 || actionTokens->size() > 4){  // invalid input
        cout << "Invalid action, please try again (NOT ENOUGH ARGUMENTS)" << endl;
        return false;
    }

    if(actionTokens->at(1) == "VICTORYPOINT"){
        player->addPoints(1);
        return true;
    }
    if(actionTokens->at(1) == "KNIGHT"){
        player->addKnight();
        // TODO: implement the knight action (when needed)
        return true;
    }
    if(actionTokens->at(1) == "ROADBUILDING"){
        
    }


    cout << "Invalid action, please try again (INVALID CARD TYPE)" << endl;
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
    // for tests:
    // appending each player 10 resources of each type:
    for(size_t i=0; i<3; i++){
        for(size_t j=0; j<5; j++){
            players[i].addResource(j, 10);
        }
    }
    size_t turn = 0;
    board.display();

    // first stage: each player places 2 settlements and 2 roads:
    stageOne(&board);
    Player* winner;

    // second stage: game loop:
    while(true){
        string action = "";
        // dice roll:
        do{
            cout << BOLD << players[turn].getColor() << "Turn " << players[turn].getName()<< ": " << RESET_COLOR << "Roll the dice! <roll>" << endl;
            cin >> action;
        } while(action != "roll");
        vector<size_t>* diceNums = board.rollDice();
        cout << BOLD << "Dice numbers: " << diceNums->at(0) << " , " << diceNums->at(1) << RESET_COLOR << endl;

        // player action loop:
        bool endTurn = false;
        cin.ignore();
        do{
            // player action:
            cout << "Choose action:  <buy> <ITEM> <position>\n                <trade> <OFFER> <SEEK>\n                <card> <TYPE> <option>\n                <status>\n                <end>" << endl;
            getline(cin, action);
            vector<string> actionTokens;
            splitAction(&action, &actionTokens);

            // buy action:
            if(actionTokens.at(0) == "buy"){  // TODO: make sure the user isnt stuck for bad input
                mainBuy(&board, &players[turn], &actionTokens);
                continue;
            }
            // trade action:
            else if(actionTokens.at(0) == "trade"){
                mainTrade(&board, &players[turn], &actionTokens);
                continue;
            }
            else if(actionTokens.at(0) == "card"){
                mainCard(&board, &players[turn], &actionTokens);
                continue;
            }
            // status:
            else if(actionTokens.at(0) == "status"){
                board.displayStats();
                continue;
            }
            // end turn:
            else if(actionTokens.at(0) == "end"){
                endTurn = true;
            }
            else{
                cout << "Invalid action, please try again" << endl;
            }
            winner = board.hasWinner();
            if(winner != nullptr) break;

        } while(endTurn == false);

        if(winner != nullptr) break;

        board.display();
        turn = (turn + 1) % 3;
    }

    cout << BOLD << winner->getColor() << winner->getName() << RESET_COLOR << " won the game!" << endl;
    board.display();
    return 0;
}

#endif  // CATAN_HPP
