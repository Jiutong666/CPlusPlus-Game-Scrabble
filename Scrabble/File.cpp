#include "File.h"
#include <iostream>

void readTile(LinkedList& TileBaglist, std::string path) {
	std::ifstream infile(path);

	if (!infile.is_open()) {
		std::cout << "Failed open Tile bag file. Please check the file path." << std::endl;
		exit(1);
	}
	while (!infile.eof()) {
		Letter letter;
		Value val;
		infile >> letter;
		infile >> val;
		Tile* tile = new Tile(letter, val);
		Node* node = new Node(tile);
		TileBaglist.append(node);
	}
}

bool saveGame(std::string path, Player* players, int nums, int turn, std::vector<std::vector<char>>& board, LinkedList& TileBaglist, bool enhance) {
	std::ofstream outfile(path);

	if (!outfile.is_open()) return false;
	if (enhance) {
		outfile << "#myformat" << std::endl;
		outfile << nums << std::endl;
	}

	for (int i = 0; i < nums; i++) {
		outfile << players[i] << std::endl;
	}

	//write board
	std::string line = "   ";
	for (int i = 0; i < 10; i++) {
		line += " " + std::to_string(i) + "  ";
	}
	for (int i = 10; i < 15; i++) {
		line += " " + std::to_string(i) + " ";
	}
	outfile << line << std::endl;
	outfile << "  -------------------------------------------------------------" << std::endl;

	for (int i = 0; i < 15; i++) {
		line = "";
		char c = 'A' + i;
		line = line + c + " |";
		for (int j = 0; j < 15; j++) {
			char d = board[i][j];
			line = line + " " + d + " |";
		}
		outfile << line << std::endl;
	}

	outfile << TileBaglist << std::endl;
	outfile << players[turn].getName();
	return true;
}

int readGame(std::string path, Player* players, int& nums, LinkedList& TileBaglist, std::vector<std::vector<char>>& board,bool enhance)
{
	std::ifstream infile(path);
	if (!infile.is_open()) {
		std::cout << "Failed open Tile bag file. Please check the file path." << std::endl;
		return -1;
	}
	nums = 2;
	std::string str;
	if (enhance) {
		getline(infile, str);
		if (str[0] != '#') {
	// Enhanced version reads files saved by non-enhanced versions

	// Back up the file read pointer to the beginning
			infile.seekg(0, std::ios::beg);
		}
		else {
			// Enhanced version reads files saved by Enhanced version
			infile >> nums;
		}
	}
	else {
		getline(infile, str);
		if (str[0] != '#') {
	// Non-enhanced version reads files saved by non-enhanced version
	// Back up the file read pointer to the beginning
			infile.seekg(0, std::ios::beg);
		}
		else {
			// Non-enhanced version reads files saved by enhanced version
			// Report an error and return to the main menu
			std::cout << "You need to turn on the enhancement to read the enhanced version save file." << std::endl;
			std::cout << std::endl;
			return -1;
		}
	}

	for (int i = 0; i < nums; i++) {
		infile >> players[i];
	}
	


	//read board
	std::string line;
	// Remove the two useless lines
	getline(infile, line);
	getline(infile, line);

	for (int i = 0; i < 15; i++) {
		getline(infile, line);
		int fisrtIndex = 4; // Position of the first character
		std::vector<char> b1;
		for (int j = 0; j < 15; j++) {
			b1.push_back(line[fisrtIndex]);
			fisrtIndex += 4;
		}
		board.push_back(b1);
	}

	infile >> TileBaglist;
	std::string name;
	infile >> name;
	for (int i = 0; i < nums; i++) {
  		if (name.compare(players[i].getName()) == 0) return i;
 	}
	return -1;
	 
}

bool readWords(std::string path, std::vector<std::vector<std::string>>& words)
{
	std::ifstream infile(path);
	if (!infile.is_open()) {
		
		return false;
	}
	while (!infile.eof()) {
		words.resize(26);
		std::string str;
		infile >> str;
		for (unsigned int i = 0; i < str.size(); i++) {
			str[i] = toupper(str[i]);
		}

		if (str.empty()) continue;
		// Use a hash table data structure for easy retrieval, indexed by the first letter
		//e.g. App and apple both in the first group
		int index = str[0] - 'A';
		words[index].push_back(str); // Put the word in the last 

	}
	return true;
}

