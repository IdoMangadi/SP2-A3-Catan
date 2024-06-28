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
#include "Card.hpp"
#include "CatanDemo.hpp"
#include "Player.hpp"
#include "Pieces.hpp"

using namespace std;

TEST_CASE("Test"){

    // redirecting output to a file so that every output will overwrite the file
    freopen("output.txt", "w", stdout);

    // running the demoMain() functionin a seperate thread (the output will be redirected to the file output.txt)
    int argc = 1;
    char* argv[] = {"player0", "player1", "player2"};
    thread t1(demoMain(argc, argv));

    // the first thing that happend is that the thread is waiting for input from the user (stageOne() function), we will give it the input "0 0" "1 2" "2 4" "7 10" "8 12" "9 14":
    // this idea is to run the demo in thread and give it a file as input, and then check the output file with the expected output file.
    // this inputs will check for special situations in the game.
    // maybe this part should be last
    
}

TEST_CASE("TestBoard"){
    // initialized the board:
    Player player0 = Player("player0", 0, RED, 0);  // name, id, color, points
    Player player1 = Player("player1", 1, GREEN, 0);
    Player player2 = Player("player2", 2, YELLOW, 0);
    Board board = Board(&player0, &player1, &player2);



}