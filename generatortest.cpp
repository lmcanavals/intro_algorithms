#include "game.h"

using namespace std;

string glyphs[] = { " ", "░", "░", "░" };

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
			if (map->cells[i][j].glyph == 0) {
				cout << " ";
			} else {
				color(map->cells[i][j].fcolor, map->cells[i][j].bcolor);
				cout << glyphs[map->cells[i][j].glyph];
				clearColor();
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
	drawMap(map, ci);
	cin.get();
	clear();

	delete ci;
	destroyMap(map);
}


