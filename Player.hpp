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
            int points;
            vector<int> resources;
            vector<Settlement&> buildings;
            vector<Road&> roads;
            vector<Card&> cards;
            int roads;
            int settlements;
            int cities;
            int knights;
            int longestPath;
        
        public:
            Player(string name, int id, int points);
            string getName();
            int getId();

            int getPoints();
            void addPoints(int points);

            const vector<int>& getResources() const;
            void addResource(int resource);
            void removeResource(int resource);
            bool canAfford(int buildingType);
            Piece& buy(int buildingType);

            const vector<Road&>& getRoads() const;
            void addRoad(Road& road);  // TODO: add road to player and check if longest path is updated
            void removeRoad(Road& road);

            const vector<Settlement&>& getBuildings() const;
            void addBuilding(Settlement& building);
            void removeBuilding(Settlement& building);

            const vector<Card&>& getCards() const;
            void addCard(Card& card);
            void removeCard(Card& card);
            void useCard(Card& card);
    };
}

#endif  // PLAYER_HPP
