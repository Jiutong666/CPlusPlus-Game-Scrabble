#ifndef SCRABBLE_H
#define SCRABBLE_H

#include "File.h"
#include "validation.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


//print board
void displayBoard(std::vector<std::vector<char>>& board);

//place Title action
bool Action(std::string tiles, std::string pos, Player* player, int pler, std::vector<std::vector<char>>& board);
//shuffle
void shuffle(LinkedList& TileBaglist);
//return game
void exitGame();
//end game
void GameOver(Player* player);
//play game 
void gamePlay(Player* player, int nums, LinkedList& TileBaglist, std::vector<std::vector<char>>& board, int pler, bool isLoad, bool enhance, std::vector<std::vector<std::string>>& words);

//play a new game
void NewGame(LinkedList& TileBaglist, std::vector<std::vector<char>>& board, bool enhance, std::vector<std::vector<std::string>>& words);
//main menu
void MainMenu(LinkedList& TileBaglist, std::vector<std::vector<char>>& board, bool& enhance, std::vector<std::vector<std::string>>& words);
//initboard
void initBoard(std::vector<std::vector<char>>& board);
//show information
void Credits();
//load game
void LoadGame(bool enhance, std::vector<std::vector<std::string>>& words);
// check word
bool checkWord(std::vector<std::vector<char>>& board, std::vector<std::string> posBuffer, std::vector<std::vector<std::string>>& words);

#endif