#include <vector>
#include <iostream>
#include "Cord.hpp"

using namespace std;

class Rule {

public:
    vector<Cord> vars;
    Rule(){};
    Rule(vector<Cord> v){
        vars = v;
    };
    vector<Cord> get_moves(Cord cord) {
        vector<Cord> res;
        for (Cord v : vars) {
            Cord t;
            t.x = cord.x + v.x;
            if (t.x > 7 || t.x < 0) continue;
            t.x = cord.y + v.y;
            if (t.y > 7 || t.y < 0) continue;
            res.push_back(t);
        }
        return res;
    }

};
