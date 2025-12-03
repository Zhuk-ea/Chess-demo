#include <iostream>
#include <vector>

using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define WHITE   "\033[97m"
#define BG_LIGHT_GRAY "\033[48;5;250m"
#define BG_DARK_GRAY  "\033[48;5;240m"

void printSimpleWideChessboard() {
    cout << 
    "  ▄ ▄▄ ▄     ▄ ▄        ■■                  ▄▄        ■■                        \n" <<
    "  ▀████▀    ■█▀███▌    ████      ████      ▀██▀    ▐█ ██ █▌                     \n" <<
    "   ████     █████      ▐██▌      ▀██▀     ▐████▌    ██████                      \n" <<
    "  ▄████▄    ▄████▄     ████      ▄██▄      ████     ▄████▄                      \n" <<
    "  ▀▀▀▀▀▀    ▀▀▀▀▀▀    ▀▀▀▀▀▀    ▀▀▀▀▀▀    ▀▀▀▀▀▀    ▀▀▀▀▀▀                      \n";
}

int main() {
    printSimpleWideChessboard();
    return 0;
}