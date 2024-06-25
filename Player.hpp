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
            Player(string name, size_t id, string color, int points);
            string getName();
            size_t getId();
            string getColor();

            int getPoints();
            void addPoints(int points);

            vector<int>& getResources();
            void addResource(int resource, int amount);
            bool canAfford(int buildingType);
            bool canAfford(vector<int> costs);

            /**
             * @brief Buy a building. Assuming controller checked if player can afford and board checked if position is valid.
             * @param piece The piece to buy.
             * @param pieceType The type of the piece (ROAD, SETTLEMENT, CITY).
             * @param opCode The operation code (FREE or PAID).
            */
            bool buy(void* piece, int itemType, int opCode);

            const vector<Road*>& getRoads() const;

            vector<Settlement*>& getSettlements();
            vector<Settlement*>& getCities();

            const vector<Card*>& getCards() const;
            bool hasCard(int type);
            bool useCard(int type);
            string getCardsVisual();

            size_t getKnightsCounter();
            void addKnight();

            friend ostream& operator<<(ostream& os, Player& player);  // printing player stats (name, points, resources)
    };
}

#endif  // PLAYER_HPP
