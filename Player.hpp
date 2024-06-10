

#define WOOD 1  // dark green
#define BRICK 2  // red
#define WHEAT 3  // yellow
#define WOOL 4  // light green
#define ORE 5  // gray

namespace ariel{
    class Player{
        private:
            string name;
            int id;
            vector<int> resources;
            vector<Settlement> buildings;
            vector<Road> roads;
            vector<Card> cards;
            bool isTurn;
        
        public:
            Player(string name);
            void placeSettelemnt(vector<string> places, vector<int> placesNum, Board board);
            void placeRoad(vector<string> places, vector<int> placesNum, Board board);
            void rollDice();
            void endTurn();
    }
}