#include <string>

#define VICTORYPOINT 011
#define KNIGHT 012
#define ROADBUILDING 013
#define MONOPOLY 014
#define YEAROFPLENTY 015

namespace ariel{

    class Card{
        private:
            int id;
            int type;
        public:
            Card(int id, int type);
            int getType();
            int getId();
    };
}