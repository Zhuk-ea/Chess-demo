#include <vector>
#include <iostream>
#include "Figures.hpp"
#include <string>
#include "Rules.hpp"

using namespace std;


// ANSI коды для цветов
        const string RESET = "\033[0m";
        const string BG_LIGHT = "\033[48;5;248m";     // светло-серый
        const string BG_DARK = "\033[48;5;238m";      // тёмно-серый
        const string BG_SELECTED = "\033[48;5;12m";   // синий для выбранной
        const string BG_POSSIBLE = "\033[48;5;10m";   // зелёный для возможных ходов
        const string WHITE_PIECE = "\033[97m";        // ярко-белый для фигур
        const string BLACK_PIECE = "\033[30m";        // чёрный для фигур
class Board {
public:
    vector<vector<int>> mtx;
    int turn; // 1 - белые, 2 - черные
    string message; // Сообщение для отображения
    
    Board() {
        mtx = vector<vector<int>>(8, vector<int>(8, 0));
        cell_states = vector<vector<int>>(8, vector<int>(8, 0));
        turn = 1; // Белые ходят первыми
        message = "Введите ход (например: e2 e4) или 'exit' для выхода";
        f = Figures();
        s = Figures("a");
        n = Figures(1);
    }

    void print() {
        


        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Верхние координаты (буквы)
        for (int i = 0; i < 5; ++i) {
            cout << "          ";
            for (int x = 0; x < 8; ++x) {
                int display_x = turn == 1 ? x : 7 - x;
                cout << s.mas[display_x].vec[i];
            }
            cout << "\n";
        }

        for (int y = 0; y < 8; ++y) {
            int display_y = turn == 1 ? y : 7 - y;
            
            for (int i = 0; i < 5; ++i) {
                cout << n.mas[display_y].vec[i];
                
                for (int x = 0; x < 8; ++x) {
                    int display_x = turn == 1 ? x : 7 - x;
                    
                    string bgColor;
                    int cellState = cell_states[display_y][display_x];
                    
                    if (cellState == 1) {
                        bgColor = BG_SELECTED;
                    } else if (cellState == 2) {
                        bgColor = BG_POSSIBLE;
                    } else {
                        bool isLight = (x + y) % 2 == 0;
                        bgColor = isLight ? BG_LIGHT : BG_DARK;
                    }
                    
                    int figureCode = mtx[display_y][display_x];
                    bool isWhiteFigure = figureCode < 20;
                    string figureColor = isWhiteFigure ? WHITE_PIECE : BLACK_PIECE;
                    cout << bgColor << figureColor << f.mas[figureCode % 10].vec[i];
                    cout << RESET;
                }
            
                cout << "\n";
            }
        }
        
        // Пустая строка
        cout << "\n";
        
        // Строка с сообщением
        cout << message << "\n";
        
        // Пустая строка для ввода
        cout << "\n";
        
        cout.flush();
    }

    void reset() {
        mtx[0] = {22, 23, 24, 25, 26, 24, 23, 22};
        mtx[1] = {21, 21, 21, 21, 21, 21, 21, 21};
        for (int i = 2; i < 6; ++i) {
            mtx[i] = {0, 0, 0, 0, 0, 0, 0, 0};
        }
        mtx[6] = {11, 11, 11, 11, 11, 11, 11, 11};
        mtx[7] = {12, 13, 14, 15, 16, 14, 13, 12};
        turn = 1; // Сбрасываем ход к белым
        message = "Введите ход (например: e2 e4)";
        reset_cell_states();
    }

    CordPair get_move() {
        string str;
        Cord c;
        Cord c2;
        
        // Выводим приглашение для ввода
        cout << "> ";
        cout.flush();
        
        
        getline(cin, str);

        // Проверяем команду выхода
        if (str == "exit" || str == "quit" || str == "x" || str == "X") {
            return CordPair(Cord(-2, -2), Cord(-2, -2)); // Специальный код для выхода
        }


        if (str.size() > 5) {
            return CordPair(Cord(-1, -1), Cord(-1, -1));
        }
        
        char t = str[0];
        if (t <= 'h' && t >= 'a') {
            c.x = t - 'a'; // Белые: a=0, h=7
        } else if (t <= 'H' && t >= 'A') {
            c.x = t - 'A'; // Белые: A=0, H=7
        } else {
            return CordPair(Cord(-1, -1), Cord(-1, -1));
        }

        t = str[1];
        if (t <= '8' && t >= '1') {
            c.y = 7 - (t - '1');
        } else {
            return CordPair(Cord(-1, -1), Cord(-1, -1));
        }
        
        if (str.size() == 2) {
            return CordPair(c, Cord(-1, -1));
        }

        if (str.size() < 5) {
            return CordPair(Cord(-1, -1), Cord(-1, -1));
        }
        
        t = str[3];
        if (t <= 'h' && t >= 'a') {
                c2.x = t - 'a';
        } else if (t <= 'H' && t >= 'A') {
                c2.x = t - 'A';
        } else {
            return CordPair(Cord(-1, -1), Cord(-1, -1));
        }

        t = str[4];
        if (t <= '8' && t >= '1') {
                c2.y = 7 - (t - '1');
        } else {
            return CordPair(Cord(-1, -1), Cord(-1, -1));
        }
        
        return CordPair(c, c2);
    }

    void highlight_options(Cord cord) {
        reset_cell_states();
        cell_states[cord.y][cord.x] = 1;
        
        vector<Cord> possible_moves = get_possible_moves(cord);
        for (Cord move : possible_moves) {
            cell_states[move.y][move.x] = 2;
        }
        
        message = "Выберите клетку для хода";
        validation_and_move();
    }

    void reset_cell_states() {
        for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 8; ++x) {
                cell_states[y][x] = 0;
            }
        }
    }

    vector<Cord> get_possible_moves(Cord cord) {
        vector<Cord> moves;
        int figure = mtx[cord.y][cord.x];
        if (figure == 0) return moves;
        
        int type = figure % 10;
        int color = figure / 10;
        
        // Проверяем, что игрок ходит своей фигурой
        if (color != turn) {
            return moves;
        }
        
        switch (type) {
            case 1: // Пешка
                get_pawn_moves(cord, color, moves);
                break;
            case 2: // Ладья
                get_rook_moves(cord, color, moves);
                break;
            case 3: // Конь
                get_knight_moves(cord, color, moves);
                break;
            case 4: // Слон
                get_bishop_moves(cord, color, moves);
                break;
            case 5: // Ферзь
                get_queen_moves(cord, color, moves);
                break;
            case 6: // Король
                get_king_moves(cord, color, moves);
                break;
        }
        
        return moves;
    }

    void get_pawn_moves(Cord cord, int color, vector<Cord>& moves) {
        int direction = (color == 1) ? -1 : 1; // Белые вверх, черные вниз
        int start_row = (color == 1) ? 6 : 1;
        
        // Ход вперед на 1 клетку
        Cord forward = Cord(cord.x, cord.y + direction);
        if (is_valid_position(forward) && mtx[forward.y][forward.x] == 0) {
            moves.push_back(forward);
            
            // Ход вперед на 2 клетки из начальной позиции
            if (cord.y == start_row) {
                Cord double_forward = Cord(cord.x, cord.y + 2 * direction);
                if (is_valid_position(double_forward) && mtx[double_forward.y][double_forward.x] == 0) {
                    moves.push_back(double_forward);
                }
            }
        }
        
        // Взятие по диагонали
        Cord diag_left = Cord(cord.x - 1, cord.y + direction);
        Cord diag_right = Cord(cord.x + 1, cord.y + direction);
        
        if (is_valid_position(diag_left) && mtx[diag_left.y][diag_left.x] != 0 && 
            mtx[diag_left.y][diag_left.x] / 10 != color) {
            moves.push_back(diag_left);
        }
        if (is_valid_position(diag_right) && mtx[diag_right.y][diag_right.x] != 0 && 
            mtx[diag_right.y][diag_right.x] / 10 != color) {
            moves.push_back(diag_right);
        }
    }

    void get_rook_moves(Cord cord, int color, vector<Cord>& moves) {
        // Направления: вверх, вниз, влево, вправо
        int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        
        for (auto dir : directions) {
            for (int step = 1; step < 8; step++) {
                Cord new_pos = Cord(cord.x + dir[0] * step, cord.y + dir[1] * step);
                if (!is_valid_position(new_pos)) break;
                
                if (mtx[new_pos.y][new_pos.x] == 0) {
                    moves.push_back(new_pos);
                } else {
                    if (mtx[new_pos.y][new_pos.x] / 10 != color) {
                        moves.push_back(new_pos);
                    }
                    break;
                }
            }
        }
    }

    void get_knight_moves(Cord cord, int color, vector<Cord>& moves) {
        // Все возможные ходы коня (L-образные)
        int moves_list[8][2] = {
            {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
            {1, -2}, {1, 2}, {2, -1}, {2, 1}
        };
        
        for (auto move : moves_list) {
            Cord new_pos = Cord(cord.x + move[0], cord.y + move[1]);
            if (is_valid_position(new_pos)) {
                if (mtx[new_pos.y][new_pos.x] == 0 || mtx[new_pos.y][new_pos.x] / 10 != color) {
                    moves.push_back(new_pos);
                }
            }
        }
    }

    void get_bishop_moves(Cord cord, int color, vector<Cord>& moves) {
        // Направления по диагоналям
        int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        
        for (auto dir : directions) {
            for (int step = 1; step < 8; step++) {
                Cord new_pos = Cord(cord.x + dir[0] * step, cord.y + dir[1] * step);
                if (!is_valid_position(new_pos)) break;
                
                if (mtx[new_pos.y][new_pos.x] == 0) {
                    moves.push_back(new_pos);
                } else {
                    if (mtx[new_pos.y][new_pos.x] / 10 != color) {
                        moves.push_back(new_pos);
                    }
                    break;
                }
            }
        }
    }

    void get_queen_moves(Cord cord, int color, vector<Cord>& moves) {
        // Ферзь = ладья + слон
        get_rook_moves(cord, color, moves);
        get_bishop_moves(cord, color, moves);
    }

    void get_king_moves(Cord cord, int color, vector<Cord>& moves) {
        // Все соседние клетки вокруг короля
        int moves_list[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
        for (auto move : moves_list) {
            Cord new_pos = Cord(cord.x + move[0], cord.y + move[1]);
            if (is_valid_position(new_pos)) {
                if (mtx[new_pos.y][new_pos.x] == 0 || mtx[new_pos.y][new_pos.x] / 10 != color) {
                    moves.push_back(new_pos);
                }
            }
        }
    }

    bool is_valid_position(Cord pos) {
        return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
    }

    void validation_and_move() {
        // Сначала рисуем доску с текущим сообщением
        print();
        
        // Затем получаем ход (внутри get_move() будет выводить "> ")
        CordPair cords = get_move();
        Cord c1 = cords.c1;
        Cord c2 = cords.c2;
        
            // Проверяем команду выхода
        if (c1.x == -2) { // Код для выхода
            message = "Выход из игры...";
            print();
            
            // Выходим из программы
            exit(0);
        }

        if (c1.x == -1) {
            message = "Некорректный ввод";
            validation_and_move();
            return;
        }

        if (mtx[c1.y][c1.x] == 0) {
            message = "На этой клетке нет фигуры";
            validation_and_move();
            return;
        }

        if (mtx[c1.y][c1.x] / 10 != turn) {
            message = "Нельзя ходить чужой фигурой!";
            validation_and_move();
            return;
        }

        if (c2.x == -1) {
            highlight_options(c1);
            return;
        }

        vector<Cord> possible_moves = get_possible_moves(c1);
        bool valid_move = false;
        for (Cord move : possible_moves) {
            if (move.x == c2.x && move.y == c2.y) {
                valid_move = true;
                break;
            }
        }
        
        if (valid_move) {
            reset_cell_states();
            move(c1, c2);
            turn = (turn == 1) ? 2 : 1;
            message = "Введите ход (например: e2 e4)";
            validation_and_move();
        } else {
            message = "Недопустимый ход!";
            validation_and_move();
        }
    }

    void move(Cord from, Cord to) {
        mtx[to.y][to.x] = mtx[from.y][from.x];
        mtx[from.y][from.x] = 0;
    }

private:
    Figures f;
    Figures s;
    Figures n;
    vector<vector<int>> cell_states; // 0 - обычная, 1 - выбрана, 2 - возможный ход
};