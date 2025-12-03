#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

class Figure {
    
public:
    vector<string> vec;
    Figure() {
        vec = vector<string> (5, "          ");
    }
    Figure(string s0, string s1, string s2, string s3, string s4) {
        vec.push_back(s0);
        vec.push_back(s1);
        vec.push_back(s2);
        vec.push_back(s3);
        vec.push_back(s4);
    }
};

class Figures {
public:
    vector<Figure> mas;
    Figures() {
        mas.push_back(Figure());
        mas.push_back(Figure("          ",
                             "   ▐██▌   ",
                             "   ▀██▀   ",
                             "   ▄██▄   ",
                             "  ▀▀▀▀▀▀  "));
        mas.push_back(Figure("  ▄ ▄▄ ▄  ",
                             "  ▀████▀  ",
                             "   ████   ",
                             "  ▄████▄  ",
                             "  ▀▀▀▀▀▀  "));

        
        mas.push_back(Figure("   ▄ ▄    ",
                             "  ■█▀███▌ ",
                             "  █████   ",
                             "  ▄████▄  ",
                             "  ▀▀▀▀▀▀  "));

        /*
        mas.push_back(Figure("   ▄ ▄    ",
                             "  ▄█▀███  ",
                             " ▀▀████▄  ",
                             "   ████   ",
                             "  ▀▀▀▀▀▀  "));
        */
        




        mas.push_back(Figure("    ▄▄    ",
                             "   ▐██▌   ",
                             "   ████   ",
                             "   ▄██▄   ",
                             "  ▀▀▀▀▀▀  "));
        mas.push_back(Figure("    ▄▄    ",
                             " ▐█ ██ █▌ ",
                             "  ██████  ",
                             "  ▄████▄  ",
                             "  ▀▀▀▀▀▀  "));
        mas.push_back(Figure("    ▄▄    ",
                             "   ▀██▀   ",
                             "  ▐████▌  ",
                             "   ████   ",
                             "  ▀▀▀▀▀▀  "));       
    }
    Figures(int x) {
        mas.push_back(Figure("          ",
                             "   ▄▀▀▄   ",
                             "   █■■█   ",
                             "   ▀▄▄▀   ",
                             "          "));
        mas.push_back(Figure("          ",
                             "   █▀▀█   ",
                             "     █    ",
                             "    █     ",
                             "          "));
        mas.push_back(Figure("          ",
                             "   ▄▀▀▀   ",
                             "   █▀▀▄   ",
                             "   ▀▄▄▀   ",
                             "          "));
        mas.push_back(Figure("          ",
                             "   █▀▀▀   ",
                             "   ▀▀▀▄   ",
                             "   ▀▄▄▀   ",
                             "          "));
        mas.push_back(Figure("          ",
                             "   █  █   ",
                             "   █▄▄█   ",
                             "      █   ",
                             "          "));
        mas.push_back(Figure("          ",
                             "   ▄▀▀▄   ",
                             "    ■■█   ",
                             "   ▀▄▄▀   ",
                             "          "));
        mas.push_back(Figure("          ",
                             "   ▄▀▀▄   ",
                             "   ▀ ▄▀   ",
                             "   ▄█▄▄   ",
                             "          "));
        mas.push_back(Figure("          ",
                             "    ▄█    ",
                             "   ▀ █    ",
                             "   ▄▄█▄   ",
                             "          "));
    }

    Figures(string str) {
        mas.push_back(Figure("          ",
                             "  ▄▀▀▀▀▄  ",
                             "  █▄▄▄▄█  ",
                             "  █    █  ",
                             "          "));
        mas.push_back(Figure("          ",
                             "  █▀▀▀█   ",
                             "  █▀▀▀▀█  ",
                             "  █▄▄▄▄█  ",
                             "          "));
        mas.push_back(Figure("          ",
                             "  ▄▀▀▀▀▄  ",
                             "  █       ",
                             "  ▀▄▄▄▄▀  ",
                             "          "));
        mas.push_back(Figure("          ",
                             "  █▀▀▀█▄  ",
                             "  █    █  ",
                             "  █▄▄▄█▀  ",
                             "          "));
        mas.push_back(Figure("          ",
                             "  █▀▀▀▀   ",
                             "  █■■■■   ",
                             "  █▄▄▄▄   ",
                             "          "));
        mas.push_back(Figure("          ",
                             "  █▀▀▀▀   ",
                             "  █■■■■   ",
                             "  █       ",
                             "          "));
        mas.push_back(Figure("          ",
                             "  ▄▀▀▀▀▄  ",
                             "  █   ▄▄  ",
                             "  ▀▄▄▄▄▀  ",
                             "          "));
        mas.push_back(Figure("          ",
                             "  █    █  ",
                             "  █■■■■█  ",
                             "  █    █  ",
                             "          "));
    }
};


