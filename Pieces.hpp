#ifndef PIECES_HPP
#define PIECES_HPP

#include "Player.hpp"
#include "Pieces.hpp"
#include "BoardElements.hpp"

#define ROAD 0
#define SETTLEMENT 1
#define CITY 2

namespace ariel{

    /**
     * @brief A class representing a piece on the board.
    */
    class Piece{
        private:
            int type;
            Player& owner;
        public:
            /**
             * @brief Construct a new Piece object.
             * param id The id of the piece.
             * param owner The owner of the piece (reference to the player object)
             */       
            Piece(int type, Player& owner);
            Player& getOwner();
            int getType();
    };

    /**
     * @brief A class representing a road on the board.
    */
    class Road : public Piece{
        private:
            int edge;
        public:
            Road(Player& owner, int edge);
    };

    /**
     * @brief A class representing a settlement on the board.
    */
    class Settlement : public Piece{
        private:
            int vertex;
        public:
            Settlement(int type, Player& owner, int vertex);
    };
}

#endif  // PIECES_HPP