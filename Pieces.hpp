#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <string>
#include <vector>

#define FREE 0
#define PAID 1
#define STAGE_ONE 100 

// building types:
#define ROAD 0
#define SETTLEMENT 1
#define CITY 2

// emojis:
#define DESERT_EMOJI "🏜️"
#define FOREST_EMOJI "🌲"
#define HILLS_EMOJI "🌋"
#define AGRICULTURAL_EMOJI "🌾"
#define PASTURE_EMOJI "🐑"
#define MOUNTAINS_EMOJI "🏔️"

#define WOOD_EMOJI "🪵"
#define BRICK_EMOJI "🧱"
#define WHEAT_EMOJI "🌾"
#define WOOL_EMOJI "🐑"
#define STONE_EMOJI "🪨"

#define EMPTY_VERTEX "△"
#define SETTLEMENT_EMOJI "▲"
#define CITY_EMOJI "●"

// colors:
#define RESET_COLOR "\033[0m"
#define BOLD "\033[1m"
#define WHITE "\033[37m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define STRIKE_THROUGH "\033[9m"

using namespace std;

namespace ariel{

    // forward declaration:
    class Player;

    /**
     * @brief An abstruct class representing a piece on the board.
    */
    class Piece{
        protected:
            int type;  // 0 - road, 1 - settlement, 2 - city
            string visualDisplay;  // the emoji that represents the piece
            Player& owner;  // reference to the player object
        public:
            virtual void pureVirtual() = 0;  // pure virtual function
            virtual ~Piece() = default;  // default destructor
            /**
             * @brief Construct a new Piece object.
             * param id The id of the piece.
             * param owner The owner of the piece (reference to the player object)
             */       
            Piece(int type, string visualDisplay, Player& owner);
            /**
             * @brief Set the type of the piece.
             */
            void setType(int type);
            /**
             * @brief Get the type of the piece.
             */
            int getType();
            /**
             * @brief Get the owner of the piece.
             */
            Player& getOwner();
            /**
             * @brief Get the visual display of the piece.
             */
            string getVisualDisplay();
            /**
             * @brief Set the visual display of the piece.
             */
            void setVisualDisplay(string type);
    };

    /**
     * @brief A class representing a road on the board.
    */
    class Road : public Piece{
        private:
            size_t edge;  // the edge id of the road according to the boardPosition.jpg
        public:
            void pureVirtual() override{}  // override the pure virtual function
            /**
             * @brief Construct a new Road object.
             */
            Road(Player& owner, size_t edge);
            /**
             * @brief Get the edge of the road.
             */
            size_t getEdge();
            /**
             * @brief Set the edge of the road.
             */
            void setEdge(size_t edge);
            /**
             * @brief Overloading the << operator to print the road object.
             */
            friend ostream& operator<<(ostream& os, const Road& road);
    };

    /**
     * @brief A class representing a settlement on the board.
    */
    class Settlement : public Piece{
        private:
            size_t vertex;  // the vertex id of the settlement according to the boardPosition.jpg
        public:
            void pureVirtual() override{}  // override the pure virtual function
            /**
             * @brief Construct a new Settlement object.
             */
            Settlement(Player& owner, size_t vertex);
            /**
             * @brief Get the vertex of the settlement.
             */
            size_t getVertex();
            /**
             * @brief Set the vertex of the settlement.
             */
            void setVertex(size_t vertex);
            /**
             * @brief Upgrade the settlement to a city.
             */
            void upgrade();
            /**
             * @brief Overloading the << operator to print the settlement object.
             */
            friend ostream& operator<<(ostream& os, Settlement& settlement);
    };
}

#endif  // PIECES_HPP