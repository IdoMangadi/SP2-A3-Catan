#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <string>
#include <vector>

#define FREE 0
#define PAID 1

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

#define EMPTY_VERTEX "⚪"
#define RED_SETTLEMENT "🔴"
#define GREEN_SETTLEMENT "🟢"
#define YELLOW_SETTLEMENT "🟡"
#define RED_CITY "🟥"
#define GREEN_CITY "🟩"
#define YELLOW_CITY "🟨"

// colors:
#define WHITE "\033[37m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

using namespace std;

namespace ariel{

    // forward declaration:
    class Player;

    /**
     * @brief A class representing a piece on the board.
    */
    class Piece{
        private:
            int type;
            string visualDisplay;
            Player& owner;
        public:
            /**
             * @brief Construct a new Piece object.
             * param id The id of the piece.
             * param owner The owner of the piece (reference to the player object)
             */       
            Piece(int type, string visualDisplay, Player& owner);
            void setType(int type);
            int getType();
            Player& getOwner();
            string getVisualDisplay();
            void setVisualDisplay(string type);
    };

    /**
     * @brief A class representing a road on the board.
    */
    class Road : public Piece{
        private:
            int edge;
        public:
            Road(Player& owner, int edge);
            int getEdge();
            friend ostream& operator<<(ostream& os, const Road& road);
    };

    /**
     * @brief A class representing a settlement on the board.
    */
    class Settlement : public Piece{
        private:
            int vertex;
        public:
            Settlement(Player& owner, int vertex);
            int getVertex();
            void upgrade();
            friend ostream& operator<<(ostream& os, Settlement& settlement);
    };
}

#endif  // PIECES_HPP