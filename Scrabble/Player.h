
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include <string>
#include <fstream>

class Player {
public:
	Player();
	Player(int score_, std::string name_); //  Constructors 
	Player(const Player&); //   copy Constructors 
	Player& operator=(const Player&);
	
	void getHandTile(LinkedList& TileBaglist); //  get title
	bool place(Letter letter); //  place 
	void display(); //  print 
	Value remove(Letter letter); // delete
	void AddTile(Node* data); //  add a new title
	bool handEmpty() { return TileList.empty(); }
	void Bingo() { score += 50; }

	int getScore() { return score; }
	std::string getName() { return name; }


	//Overloading Output Operators
	friend std::ostream& operator<<(std::ostream& os, const Player& player) {
		os << player.name << std::endl;
		os << player.score << std::endl;
		os << player.TileList; 
		return os;
	}


	//Overloading Input Operators
	friend std::istream& operator>>(std::istream& os, Player& player) {
		os >> player.name;
		os >> player.score;
		os >> player.TileList;
		return os;
	}

private:
	int score;
	std::string name;
	LinkedList TileList;
};



#endif