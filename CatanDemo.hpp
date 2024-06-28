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
 * this function display the jpg "boardPositions.jpg" that contains the positions of the vertices and edges.
 * the file is in the same directory as the code.
 */
void displayPositions();

/**
 * @brief Parse a string to a size_t.
 * @param str The string to parse.
 * @param result The result of the parsing.
 * @return True if the parsing was successful, false otherwise.
 * the function checks if the string is a nubmer and if so it converts it to a size_t and return true, otherwise it returns false.
*/
bool parseStringToSize_t(string str, size_t& result);

/**
 * function to check if a string is a number between 0 and 53
*/
size_t vertexValidation(string vertex);

/**
 * @brief Get a vertex number between 0 and 53 from the user.
*/
size_t getVertexFromUser();

/**
 * function to check if a string is a number between 0 and 71
*/
size_t edgeValidation(string edge);

/**
 * @brief Get a edge number between 0 and 71 from the user.
*/
size_t getEdgeFromUser();

/**
 * stagr one is used as the first stage of the game when every player placing two settlements and two roads.
 */
void stageOne(Board* board);

/**
 * @brief Split a string into tokens by spaces.
*/
void splitAction(string* action, vector<string>* actionTokens);

/**
 * @brief Handle the buy action.
*/
bool mainBuy(Board* board, Player* player, vector<string>* actionTokens);

void printInvalidTrade();
/**
 * check if the trade input is valid.
 * trade format: trade offer <amount> <resource> <amount> <resource>... seek <amount> <resource> <amount> <resource>... 
 * example: trade offer 1 ORE 1 WHEAT seek 2 WOOD
 * example2: trade offer 1 ORE 1 WHEAT 1 WOOL seek 2 WOOD 1 BRICK
 * the function validate that: the input contains the words 'trade', 'OFFER' and 'SEEK', the resources are valid and the amounts are numbers.
*/
bool tradeValidation(vector<string>* actionTokens);
/**
 * parse the trade input to 2 vectors of resources (5 cells long) representing the offer and the seek.
 * action tokens format : trade OFFER <amount> <resource> <amount> <resource>... SEEK <amount> <resource> <amount> <resource>...
*/
bool parseActionToVectors(vector<string>* actionTokens, vector<int>* offer, vector<int>* seek);
/**
 * check if some player want to accept the proposal.
 * print the proposal to the terminal and ask for y/n answer from the other players (in turns each player enter his answer).
 * in case a player accept the offer it check if the player can afford the trade.
*/
Player* playerAccept(Board* board, vector<int>* offer, vector<int>* seek, Player* offerer);

/**
 * this function handles user input in format: trade offer 1ORE 1WHEAT seek 2WOOD
 * it parse the 'offer' and 'seek' to vector of resources 5 cells long (representing all the resources) (include validation check).
 * then it print the offer to the terminal and ask for y/n answer from the other players (in turns each player enter his answer).
 * in case there is player that accept the offer (the first one) it make the trade appending and reducing the relevant resources from each of the players.
 * the function uses:  function of validation check for input named: "tradeValidation", function to parse the actionTokens to 2 vectors of resources named: "parseActionToVectors",
 *                     function to check if some player want to accept the proposal named: "playerAccept" (includes print the proposal and get input from users).
*/
bool mainTrade(Board *board, Player* player, vector<string>* actionTokens);

bool mainCard(Board* board, Player* player, vector<string>* actionTokens);

/**
 * @brief Get the amount of resources a player has.
*/
size_t resourcesAmount(Player* player);

/**
 * this function validates that a given strings vector is from the type: <amount> <RESOURCE> <amount> <RESOURCE>... (amount is a number and resource is a string representing a resource).
*/
bool validateResourcesToDiscardFormat(const vector<string>* actionTokens);

/**
 * this function validates that the player has enough resources to discard according to the input.
 * the input format is: <amount> <RESOURCE> <amount> <RESOURCE>...
 * arguments: resources - the player resources vector, actionTokens - the input vector, amountToDiscard - the amount of resources the player need to discard.
 * the function also check if the player entered the correct amount of resources to discard (make sure he didnt enter more or less resources than needed).
*/
bool validateResourcesToDiscard(const vector<int>& resources, vector<string>* actionTokens, size_t amountToDiscard);

/**
 * this function activated when the dice roll is 7.
 * its iterate over the players by their order and:
 * if a player has more then 7 cards he need to discard half of his resources (the user inputs which resources to discard).
 * the function interact with the user and check if the input is valid.
 * the function does not handle the robber move.
*/
bool sevenScenario(Board* board);


int demoMain(int argc , char* argv[]);

#endif  // CATAN_HPP
