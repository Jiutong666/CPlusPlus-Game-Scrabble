
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// Define a Letter type
typedef char Letter;

// Define a Value type
typedef int Value;

class Tile {
public:
	Tile(Letter le, Value val):letter(le),value(val){}
	Letter letter;
	Value  value;
};

#endif // ASSIGN2_TILE_H
