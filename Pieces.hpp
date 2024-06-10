

namespace ariel{

    class Piece{
        private:
            int id;
            Player owner;
        public:
            Piece(int id, Player owner);
            Player getOwner();
            int getId();
    };

    class Road : public Piece{
        private:
            Edge edge;
        public:
            Road(int id, Player owner, Edge edge);
    };

    class Settlement : public Piece{
        private:
            Vertex vertex;
        public:
            Settlement(int id, Player owner, Vertex vertex);
    };

    class City : public Settlement{
        public:
            City(int id, Player owner, Vertex vertex);
    };
}