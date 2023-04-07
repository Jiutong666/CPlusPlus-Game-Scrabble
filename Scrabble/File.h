#ifndef ASSIGN2_FILE_H
#define ASSIGN2_FILE_H

#include <fstream>
#include "LinkedList.h"
#include "Player.h"
#include <vector>
//using namespace std;


//read Tile
void readTile(LinkedList& TileBaglist, std::string path);


//save game
bool saveGame(std::string path, Player* players, int nums, int turn, std::vector<std::vector<char>>& board, LinkedList& TileBaglist, bool enhance);


//read game,returning which person's turn it is
int readGame(std::string path, Player* players,int &nums, LinkedList& TileBaglist, std::vector<std::vector<char>>& board, bool enhance);

// Read word lexicon
bool readWords(std::string path,std::vector<std::vector<std::string>>& words);
#endif