// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#define WOOD 0  // dark green
#define BRICK 1  // red
#define WHEAT 2  // yellow
#define WOOL 3  // light green
#define ORE 4  // gray

using namespace std;

namespace ariel{

    // Forward declarations:
    class Piece;
    class Road;
    class Settlement;
    class Card;

    class Player{
        private:
            string name;
            size_t id;
            string color;
            int points;
            vector<int> resources;
            vector<Road*> roads;
            vector<Settlement*> settlements;
            vector<Settlement*> cities;
            vector<Card*> cards;
            size_t knightsCounter;
        
        public:
            /**
             * @brief Construct a new Player object.
             */
            Player(string name, size_t id, string color, int points);
            /**
             * @brief Get the name of the player.
             */
            string getName();
            /**
             * @brief Get the id of the player.
             */
            size_t getId();
            /**
             * @brief Get the color of the player.
             */
            string getColor();
            /**
             * @brief Get the points of the player.
             */
            int getPoints();
            /**
             * @brief Add points to the player.
             */
            void addPoints(int points);
            /**
             * @brief Get the resources of the player.
             */
            vector<int>& getResources();
            /**
             * @brief Add a resource to the player.
             */
            void addResource(int resource, int amount);
            /**
             * @brief Check if the player can afford a building.
             */
            bool canAfford(int buildingType);
            /**
             * @brief Check if the player can afford a building.
             */
            bool canAfford(vector<int> costs);


            /**
             * @brief Buy a building. Assuming controller checked if player can afford and board checked if position is valid.
             * @param piece The piece to buy.
             * @param pieceType The type of the piece (ROAD, SETTLEMENT, CITY).
             * @param opCode The operation code (FREE or PAID).
            */
            bool buy(void* piece, int itemType, int opCode);
            /**
             * @brief Get the roads of the player.
             */
            const vector<Road*>& getRoads() const;
            /**
             * @brief Get the settlements of the player.
             */
            vector<Settlement*>& getSettlements();
            /**
             * @brief Get the cities of the player.
             */
            vector<Settlement*>& getCities();
            /**
             * @brief Get the cards of the player.
             */
            const vector<Card*>& getCards() const;
            /**
             * @brief Check if the player has a card.
             */
            bool hasCard(int type);
            /**
             * @brief Use a card.
             */
            bool useCard(int type);
            /**
             * @brief Get the visual display of the cards.
             */
            string getCardsVisual();
            /**
             * @brief Get the knights counter of the player.
             */
            size_t getKnightsCounter();
            /**
             * @brief Add a knight to the player (when actually using a knight card).
             */
            void addKnight();
            /**
             * @brief Overloading the << operator to print the player object.
             */
            friend ostream& operator<<(ostream& os, Player& player);  // printing player stats (name, points, resources)
    };
}

#endif  // PLAYER_HPP
