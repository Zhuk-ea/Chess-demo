class Cord {
public:
    int x, y;
    Cord() {}
    Cord(int a, int b) {
        x = a;
        y = b;
    }
    Cord(Cord& t){
        x = t.x;
        y = t.y;
    }
    Cord(const Cord& t) : x(t.x), y(t.y) {}  // Добавь этот конструктор
    
    // Оператор сравнения для удобства
    bool operator==(const Cord& other) const {
        return x == other.x && y == other.y;
    }

};



struct CordPair {
    Cord c1;
    Cord c2;
    CordPair(Cord a, Cord b) {
        c1 = a;
        c2 = b;
    }
};
