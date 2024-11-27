class Tile {
    protected:
        bool revealed;
        bool flagged;
    public:
        Tile() : revealed(false), flagged(false) {}
        virtual ~Tile() {}
};