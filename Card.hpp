#include <string>

#define CARD 010

#define VICTORYPOINT 011
#define KNIGHT 012
#define ROADBUILDING 013
#define MONOPOLY 014
#define YEAROFPLENTY 015

namespace ariel{

    /**
     * @brief Card class represents a card in the game.
    */
    class Card{
        private:
            int id;
            int type;
            bool bought;
            bool used;
        public:
            /**
             * @brief Construct a new Card object.
            */
            Card(int id, int type);
            int getType();
            int getId();
            bool isUsed();
            void use();
    };
}