#include "game.h"

using namespace std;

// Caracteres!
char glyphs[] = { 0, 176, 2, 1, 3 };

// just in case
// string glyphs[] = { " ", "░", "☻", "☺", "♥" };

// Constantes de tipo de elemento!
#define EMPTY	0
#define WALL	1
#define HERO	2
#define ENEMY	3
#define LIFE	4

void loadStuff(string fname, Map*& map, ConsoleInfo*& ci) {
    ci = new ConsoleInfo;
    getConsoleInfo(ci);
    map = loadMap(fname);
    int marginv = ci->maxRows - map->rows;
    int marginh = ci->maxColumns - map->cols;
    if (marginv < 0 || marginh < 0) {
        map = nullptr; // console too small for labyrinth, try making it bigger
    } else {
        int top = marginv / 2;
        int left = marginh / 2;
        int bottom = marginv - top;
        int right = marginh - left;
        getConsoleInfo(ci, top, right, bottom, left);
    }
}

void drawMap(Map* map, ConsoleInfo* ci) {
    for (int i = 0; i < map->rows; ++i) {
        gotoxy(ci->left, ci->top + i);
        for (int j = 0; j < map->cols; ++j) {
            if (map->cells[i][j].glyph == EMPTY) {
                cout << " ";
            } else {
                color(map->cells[i][j].fcolor, map->cells[i][j].bcolor);
                cout << glyphs[map->cells[i][j].glyph];
                clearColor();
            }
        }
    }
}

enum Dir { UP, RIGHT, DOWN, LEFT };

void movehero(int& x, int& y, Dir dir, Map* map, ConsoleInfo* ci) {
    int px = x, py = y;
    switch (dir) {
    case UP: py = y - 1; break;
    case RIGHT: px = x + 1; break;
    case DOWN: py = y + 1; break;
    case LEFT: px = x - 1; break;
    }
    if ((px != x || py != y) && map->cells[py][px].glyph == EMPTY) {
        map->cells[y][x] = { EMPTY, 0, 0 };
        gotoxy(ci->left + x, ci->top + y);
        cout << " ";
        x = px;
        y = py;
        map->cells[y][x] = { HERO, BRIGHT_CYAN, BLACK };
        gotoxy(ci->left + x, ci->top + y);
        color(map->cells[y][x].fcolor, map->cells[y][x].bcolor);
        cout << glyphs[map->cells[y][x].glyph];
        clearColor();
    }
}

void moveenemy(int& ex, int& ey, int& edx, int& edy, int& esteps, int MAXSTEPS, Map* map, ConsoleInfo* ci) {
    esteps = (esteps + 1) % MAXSTEPS;
    if (esteps == 0) {
        int px = ex, py = ey;
        // TODO, chech x
        py += edy;
        if (map->cells[py][px].glyph != WALL) {
            map->cells[ey][ex] = { EMPTY, 0, 0 };
            gotoxy(ci->left + ex, ci->top + ey);
            cout << " ";
            ex = px;
            ey = py;
            map->cells[ey][ex] = { ENEMY, BRIGHT_YELLOW, BLACK };
            gotoxy(ci->left + ex, ci->top + ey);
            color(map->cells[ey][ex].fcolor, map->cells[ey][ex].bcolor);
            cout << glyphs[map->cells[ey][ex].glyph];
            clearColor();
        } else {
            edy *= -1;
        }
    }
}

void gameloop(Map* map, ConsoleInfo* ci) {
    int x = 0; int y = 1;
    int ex = 9; int ey = 4;
    int edx = 0;
    int edy = -1;
    int delay = 50;
    int MAXSTEPS = (1000 / delay) / 2; // fps = 1000 / delay; enemy moves every esteps frames; 
    int esteps = 0;

    int lives = 3;

    drawMap(map, ci);
    while (lives > 0) {
        sleep4(delay);
        moveenemy(ex, ey, edx, edy, esteps, MAXSTEPS, map, ci);
        if (_kbhit()) {
            switch (toupper(_getch())) {
            case 'W': movehero(x, y, UP, map, ci); break;
            case 'A': movehero(x, y, LEFT, map, ci); break;
            case 'S': movehero(x, y, DOWN, map, ci); break;
            case 'D': movehero(x, y, RIGHT, map, ci); break;
            }
        }
    }
}

int main() {
    ConsoleInfo* ci;
    Map* map;

    loadStuff("lab.awesome", map, ci);
    if (map == nullptr) {
        cout << "Terminal too small for this map\n";
        return -1;
    }

    clear();
    hideCursor();
    gameloop(map, ci);
    clear();

    delete ci;
    destroyMap(map);
}