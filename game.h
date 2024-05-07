#ifndef __GAME_H__
#define __GAME_H__

#include <fstream>
#include "upc.h"

struct Cell {
	int glyph;
	int fcolor;
	int bcolor;
};

struct Map {
	int rows;
	int cols;
	Cell** cells;
};

/*
 * codedCell: 0xABCD
 *		-> D: foreground color, hex values from 0 to f (0..15) 4 bits
 *		-> C: background color, hex values from 0 to f (0..15) 4 bits
 *		-> AB: and the rest, represent a glyph code, hex value from 0 to ffffff.
 * */
inline void decodeCell(Cell& cell, int codedCell) {
	cell.fcolor = codedCell & 0x0f;
	cell.bcolor = (codedCell >> 4) & 0x0f;
	cell.glyph = codedCell >> 8;
}

inline Map* loadMap(std::string filename) {
	Map* map = new Map;
	std::ifstream f(filename);
	if (!f.is_open()) return nullptr;

	f >> map->rows >> map->cols;
	map->cells = new Cell*[map->rows];
	for (int i = 0; i < map->rows; ++i) {
		map->cells[i] = new Cell[map->cols];
		for (int j = 0; j < map->cols; ++j) {
			int cell;
			f >> std::hex >> cell;
			decodeCell(map->cells[i][j], cell);
		}
	}

	return map;
}

inline void destroyMap(Map*& map) {
	for (int i = 0; i < map->rows; ++i) {
		delete[] map->cells[i];
	}
	map = nullptr;
}

#endif
