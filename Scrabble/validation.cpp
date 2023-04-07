#include "validation.h"

bool nameValid(std::string name) {
	if (name.empty()) return false;
	for (unsigned int i = 0; i < name.size(); i++) {
		if (!isalpha(name[i])) return false;  ///judge whether it is a letter or not
		if (!isupper(name[i])) return false; 	//judge if it is uppercase
		
	}
	return true;
}

// Check if the command is right
bool commandValid(std::string tile, std::string at, std::string pos) {
	if (at.compare("at") != 0) {
		return false;
	}
	if (tile.length() > 1) return false;

	if (tile[0] < 'A' || tile[0]>'Z') {
		return false;
	}
	char line = pos[0];
	if (line < 'A' || line>'O') {
		return false;
	}
	if (pos.length() == 2) {
		// column number of one digit
		char col = pos[1];
		if (col < '0' || col>'9') {
			return false;
		}
		return true;
	}
	else if (pos.length() == 3) {
		// Two-digit column number
		std::string col = pos.substr(1,2);
		if (col[0] != '1' || col[1] > '5' || col[1] < '0') {
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}


//Detecting the presence of titles in the vicinity of the placement
bool checkAji(std::string pos, std::vector<std::vector<char>> board)
{
	char line = pos[0];
	int l = line - 'A';
	int c;
	int size = board.size();
	if (pos.length() == 2) {
		char col = pos[1];
		c = col - '0';
	}
	else{
		std::string col = pos.substr(1, 2);
		c = col[1] - '0';
		c += 10;
	}
	//up
	if (l+ 1 < size && board[l + 1][c] != ' ') {
		return true;
	}
	//down
	if (l - 1 >= 0 && board[l - 1][c] != ' ') {
		return true;
	}
	//left
	if (c - 1 >= 0 && board[l][c - 1] != ' ') {
		return true;
	}
	//right
	if (c + 1 < size && board[l][c + 1] != ' ') {
		return true;
	}
	return false;
}

