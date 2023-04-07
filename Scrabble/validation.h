#ifndef ASSIGN2_VALIDATION_H
#define ASSIGN2_VALIDATION_H

#include "string"
#include <vector>



// check name
bool nameValid(std::string name);

//check command
bool commandValid(std::string tile, std::string at,std::string pos);

//Detecting the presence of titles in the vicinity of the placement
bool checkAji(std::string pos, std::vector<std::vector<char>> board);
#endif