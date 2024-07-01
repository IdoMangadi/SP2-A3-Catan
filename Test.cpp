
#include <stdio.h>
#include <cstdio>
#include <thread>

#include "doctest.h"
#include "Board.hpp"
#include "BoardElements.hpp"
#include "Player.hpp"
#include "Pieces.hpp"
#include "Card.hpp"

using namespace std;
using namespace ariel;


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

    SUBCASE("stageOneResourcesDistribution"){
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