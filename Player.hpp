#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Pieces.hpp"
#include "Card.hpp"

#define WOOD 0  // dark green
#define BRICK 1  // red
#define WHEAT 2  // yellow
#define WOOL 3  // light green
#define ORE 4  // gray

namespace ariel{
    class Player{
        private:
            string name;
            int id;
            string color;
            int points;
            vector<int> resources;
            vector<Road*> roads;
            vector<Settlement*> buildings;
            vector<Card*> cards;
        
        public:
            Player(string name, int id, string color, int points);
            string getName();
            int getId();
            string getColor();

            int getPoints();
            void addPoints(int points);

            const vector<int>& getResources() const;
            void addResource(int resource, int amount);
            bool canAfford(int buildingType);

            /**
             * @brief Buy a building. Assuming controller checked if player can afford and board checked if position is valid.
             * @param piece The piece to buy.
             * @param pieceType The type of the piece (ROAD, SETTLEMENT, CITY).
             * @param opCode The operation code (FREE or PAID).
            */
            bool buy(Piece* piece, int itemType, int opCode);

            const vector<Road*>& getRoads() const;

            const vector<Settlement*>& getBuildings() const;

            const vector<Card*>& getCards() const;
            bool hasCard(int type);
            void useCard(Card* card);
    };
}

#endif  // PLAYER_HPP
