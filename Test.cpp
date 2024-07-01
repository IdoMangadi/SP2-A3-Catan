/**
 * @file Test.cpp
 * in this file we run the CatanDemo file (in this file there is the demoMain() function) and we test this function.
 * to test outputs we will redirect the output to a file and then we will compare the file with the expected output.
 * the function demoMain will run in a seperate thread and the test will communicate with the thread.
 * the test will give the thread the input that it needs throgh the console.
 * after each operation, we will check the output file and compare it with the expected output.
 */

#include <stdio.h>
#include <cstdio>
#include <thread>

#include "doctest.h"
#include "Board.hpp"
#include "BoardElements.hpp"
#include "CatanDemo.hpp"
#include "Player.hpp"
#include "Pieces.hpp"

using namespace std;

// TEST_CASE("Test"){

//     // redirecting output to a file so that every output will overwrite the file
//     freopen("output.txt", "w", stdout);

//     // running the demoMain() functionin a seperate thread (the output will be redirected to the file output.txt)
//     int argc = 4;
//     char* arg0 = "CatanDemo";
//     char* arg1 = "player0";
//     char* arg2 = "player1";
//     char* arg3 = "player2";
//     char* argv[4] = {arg0, arg1, arg2, arg3};
//     thread t1(demoMain, argc, argv);

//     // the first thing that happend is that the thread is waiting for input from the user (stageOne() function), we will give it the input "0 0" "1 2" "2 4" "7 10" "8 12" "9 14":
//     // this idea is to run the demo in thread and give it a file as input, and then check the output file with the expected output file.
//     // this inputs will check for special situations in the game.
//     // maybe this part should be last
    
// }

TEST_CASE("TestBoardBuy"){
    // initialized the board:
    Player player0 = Player("player0", 0, RED, 0);  // name, id, color, points
    Player player1 = Player("player1", 1, GREEN, 0);
    Player player2 = Player("player2", 2, YELLOW, 0);
    Board board = Board(&player0, &player1, &player2);
    bool result;

    // testing the buy function:
    SUBCASE("Invalid arguments"){
        result = board.buy(&player0, CITY, 0, 2);  // invalid opcode
        CHECK_FALSE(result);

        result = board.buy(&player0, 89, 0, FREE);  // invalid item type
        CHECK_FALSE(result);

        result = board.buy(nullptr, CITY, 0, 0);  // null player
        CHECK_FALSE(result);
    }

    SUBCASE("cantAfford"){
    result = board.buy(&player0, CITY, 0, PAID);  // player cant afford
    CHECK_FALSE(result);
    }

    for(size_t i=0; i<5; i++){  // appending each player 10 resources of each type:
        player0.addResource(i, 100);
        player1.addResource(i, 100);
        player2.addResource(i, 100);
    }

    SUBCASE("invalid positions"){
        result = board.buy(&player0, SETTLEMENT, 0, STAGE_ONE);  // should be successful
        CHECK(result);
        result = board.buy(&player0, ROAD, 0, STAGE_ONE);  // should be successful
        CHECK(result);
        result = board.buy(&player1, ROAD, 0, STAGE_ONE);  // should be unsuccessful because the position is taken
        CHECK_FALSE(result);

        result = board.buy(&player1, SETTLEMENT, 1, STAGE_ONE);  // should be successful
        CHECK(result);
        result = board.buy(&player2, SETTLEMENT, 1, PAID);  // should be unsuccessful because the position is taken
        CHECK_FALSE(result);

        result = board.buy(&player2, CITY, 1, PAID);  // should be unsuccessful because the position is empty
        CHECK_FALSE(result);
    }

    SUBCASE("cards"){
        // buying more then 25 cards:
        for(size_t i=0; i<26; i++) board.buy(&player0, CARD, 0, PAID);
        result = board.buy(&player0, CARD, 0, PAID);  // should be unsuccessful because there is only 25 cards
        CHECK_FALSE(result);
    }
}

TEST_CASE("TestCatanDemo"){
    
}