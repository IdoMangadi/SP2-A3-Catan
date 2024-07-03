// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <condition_variable>

#include "doctest.h"
#include "Board.hpp"
#include "BoardElements.hpp"
#include "Player.hpp"
#include "Pieces.hpp"
#include "Card.hpp"
#include "../../../../usr/include/x86_64-linux-gnu/sys/wait.h"

#define EXPECTED_LINES_NUM 46

using namespace std;
using namespace ariel;

/** in this test case we will run the CatanDemo executable with execv when redirect its output to a file (output.txt).
 *  then we will read the file line by line and check if the output is as expected.
 *  in this test: invalid edge and vertex positions (out of range and not a number), invalid action, invalid trade. 
*/
TEST_CASE("TestCatanDemo"){

    int pid = fork(); 

    if (pid == 0) { // Child process
        // Redirect standard input from input.txt
        int fdIn = open("input.txt", O_RDONLY);
        if (fdIn < 0) {
            cerr << "Failed to open input.txt" << std::endl;
            exit(1);
        }
        dup2(fdIn, STDIN_FILENO);
        close(fdIn);

        // Redirect standard output to output.txt
        int fdOut = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fdOut < 0) {
            cerr << "Failed to open output.txt" << std::endl;
            exit(1);
        }
        dup2(fdOut, STDOUT_FILENO);
        close(fdOut);

        // Prepare arguments for execv
        char *args[] = {(char*)"./catan_demo", (char*)"player0", (char*)"player1", (char*)"player2", NULL};
        
        // Execute the command
        execv("./catan_demo", args);

        // If execv returns, it means it failed
        cerr << "execv failed" << std::endl;
        exit(1);

    } else if (pid > 0) { // Parent process
        wait(NULL); // Wait for child process to finish

        // comparing the output to the expected output:
        ifstream expected("expected.txt");
        ifstream output("output.txt");

        string expectedLine, outputLine;
        size_t lineNum = 0;

        while(getline(expected, expectedLine) && getline(output, outputLine)){
            lineNum++;
            CHECK(expectedLine == outputLine);  // check if the lines are equal
        }
        CHECK(lineNum == EXPECTED_LINES_NUM);  // check if the number of lines is correct
        expected.close();
        output.close();
    }

}


TEST_CASE("TestBoardBuy"){
    // initialized the board:
    Player player0 = Player("player0", 0, RED, 0);  // name, id, color, points
    Player player1 = Player("player1", 1, GREEN, 0);
    Player player2 = Player("player2", 2, YELLOW, 0);
    Board board = Board(&player0, &player1, &player2);
    bool result;

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

    for(size_t i=0; i<5; i++){  // appending each player 100 resources of each type:
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

TEST_CASE("BoardResourses"){
    // initialized the board:
    Player player0 = Player("player0", 0, RED, 0);  // name, id, color, points
    Player player1 = Player("player1", 1, GREEN, 0);
    Player player2 = Player("player2", 2, YELLOW, 0);
    Board board = Board(&player0, &player1, &player2);

    for(size_t i=0; i<5; i++){  // appending each player 10 resources of each type:
        player0.addResource(i, 10);
        player1.addResource(i, 10);
        player2.addResource(i, 10);
    }

    SUBCASE("stageOneResourcesDistribution"){  // checck for miss distribution 
        board.stageOneResourcesDistribution();
        CHECK(player0.getResources()[0] == 10);
        CHECK(player0.getResources()[1] == 10);
        CHECK(player0.getResources()[2] == 10);
        CHECK(player0.getResources()[3] == 10);
        CHECK(player0.getResources()[4] == 10);

        CHECK(player1.getResources()[0] == 10);
        CHECK(player1.getResources()[1] == 10);
        CHECK(player1.getResources()[2] == 10);
        CHECK(player1.getResources()[3] == 10);
        CHECK(player1.getResources()[4] == 10);

        CHECK(player2.getResources()[0] == 10);
        CHECK(player2.getResources()[1] == 10);
        CHECK(player2.getResources()[2] == 10);
        CHECK(player2.getResources()[3] == 10);
        CHECK(player2.getResources()[4] == 10);
    }

    SUBCASE("distributeResources"){
        board.distributeResources(0);
        board.distributeResources(7);
        board.distributeResources(15);
        CHECK(player0.getResources()[0] == 10);
        CHECK(player0.getResources()[1] == 10);
        CHECK(player0.getResources()[2] == 10);
        CHECK(player0.getResources()[3] == 10);
        CHECK(player0.getResources()[4] == 10);

        CHECK(player1.getResources()[0] == 10);
        CHECK(player1.getResources()[1] == 10);
        CHECK(player1.getResources()[2] == 10);
        CHECK(player1.getResources()[3] == 10);
        CHECK(player1.getResources()[4] == 10);

        CHECK(player2.getResources()[0] == 10);
        CHECK(player2.getResources()[1] == 10);
        CHECK(player2.getResources()[2] == 10);
        CHECK(player2.getResources()[3] == 10);
        CHECK(player2.getResources()[4] == 10);

    }
}