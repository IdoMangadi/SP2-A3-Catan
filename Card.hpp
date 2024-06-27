#include <string>

#define CARD 010

#define VICTORYPOINT 011
#define KNIGHT 012
#define ROADBUILDING 013
#define MONOPOLY 014
#define YEAROFPLENTY 015

using namespace std;

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
            string visualDisplay;
        public:
            /**
             * @brief Construct a new Card object.
            */
            Card(int id, int type);
            /**
             * @brief Get the type of the card.
             */
            int getType();
            /**
             * @brief Get the id of the card.
             */
            int getId();
            /**
             * @brief set the card as bought.
             */
            void setBought();
            /**
             * @brief Check if the card is used.
             */
            bool isUsed();
            /**
             * @brief Use the card.
             */
            void use();
            /**
             * @brief Get the visual display of the card.
             */
            string getVisualDisplay();
    };
}