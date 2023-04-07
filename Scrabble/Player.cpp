#include "Player.h"

Player::Player()
{
	name = "";
	score = 0;
}

Player::Player(int score_, std::string name_)
	:score(score_), name(name_){}

Player::Player(const Player& oth)
{
	name = oth.name;
	score = oth.score;
	TileList = oth.TileList;
}

Player& Player::operator=(const Player& oth)
{
	name = oth.name;
	score = oth.score;
	TileList = oth.TileList;
	return *this;
}

void Player::getHandTile(LinkedList& TileBaglist)
{
	
	//hand title less than 7
	while (TileList.getSize() < 7) {
		if (TileBaglist.empty()) return;
		TileList.append(TileBaglist.popFront());
	}
}

bool Player::place(Letter letter)
{
	Value val = TileList.remove(letter);
	if (val!=-1) {
		score += val;
		return true;
	}
	return false;
}

void Player::display()
{
	TileList.display();
}

Value Player::remove(Letter letter)
{
	return TileList.remove(letter);
}

void Player::AddTile(Node* data)
{
	TileList.append(data);
}
