#include "scrabble.h"
#include <time.h>
#define EXIT_SUCCESS    0


int main(void) {
	LinkedList TileBaglist;
	readTile(TileBaglist, "ScrabbleTiles.txt");  //read bag
	std::vector<std::vector<char>> board;
	initBoard(board); //  Initializing the board
	std::cout << "Welcome to Scrabble!" << std::endl;
	std::cout << "--------------------" << std::endl;
	bool enhance = false;
	std::vector<std::vector<std::string>> words;// word
	while (1) {
		MainMenu(TileBaglist, board, enhance, words);
	}


	return EXIT_SUCCESS;
}



//  print board
void displayBoard(std::vector<std::vector<char>>& board) {
	printf("\n   ");
	for (int i = 0; i < 10; i++) {
		printf(" %d  ", i);
	}
	for (int i = 10; i < 15; i++) {
		printf(" %d ", i);
	}
	printf("\n  -------------------------------------------------------------\n");
	for (int i = 0; i < 15; i++) {
		char c = 'A' + i;
		printf("%c |", c);
		for (int j = 0; j < 15; j++) {
			printf(" %c |", board[i][j]);
		}
		printf("\n");
	}
}

bool checkWord(std::vector<std::vector<char>>& board, std::vector<std::string> posBuffer, std::vector<std::vector<std::string>>& words)
{
	for (unsigned int i = 0; i < posBuffer.size(); i++) {
		std::string pos = posBuffer[i];
		if (pos.length() == 2) {
			char line = pos[0];
			char col = pos[1];
			// Judging words that are connected horizontally
			unsigned int colIndex = col - '0';
			unsigned int lineIndex = line - 'A';
			std::string strLine = "";
			// Connect the left ones first
			while (board[lineIndex][colIndex] != ' ') {
				strLine = board[lineIndex][colIndex] + strLine;
				if (colIndex == 0) break;
				colIndex--;
			}
			// Connect the right ones again
			colIndex = col - '0' + 1;
			while (colIndex < board.size() && board[lineIndex][colIndex] != ' ') {
				strLine = strLine + board[lineIndex][colIndex];
				colIndex++;
			}
			// Check if the horizontal word is in the lexicon
			int lineFlag = 0; // Flag, if in the lexicon, lineFlag is flagged 1
			for (unsigned int i = 0; i < words[strLine[0] - 'A'].size(); i++) {
				if (strLine.compare(words[strLine[0] - 'A'][i]) == 0) {
					lineFlag = 1;
					break;
				}
			}
			if (lineFlag == 0) return false; // If there is a word that is not in the lexicon, return false directly
			
			// Check if the vertical word is in the lexicon
			colIndex = col - '0';
			lineIndex = line - 'A';
			std::string strCol = "";
			// Add up the above characters first
			while (board[lineIndex][colIndex] != ' ') {
				strCol = board[lineIndex][colIndex] + strCol;
				if (lineIndex == 0) break;
				lineIndex--;
			}
			// Add up the below characters
			lineIndex = line - 'A' + 1;
			while (lineIndex < board.size() && board[lineIndex][colIndex] != ' ') {
				strCol = strCol + board[lineIndex][colIndex];
				lineIndex++;
			}
			// Check if the vertical word is in the lexicon
			int ColFlag = 0; // Flag, if within the lexicon, ColFlag is flagged 1
			for (unsigned int i = 0; i < words[strCol[0] - 'A'].size(); i++) {
				if (strCol.compare(words[strCol[0] - 'A'][i]) == 0) {
					ColFlag = 1;
					break;
				}
			}
			if (ColFlag == 0) return false; // If there is a word that is not in the lexicon, return false directly

		}
		else if (pos.length() == 3) {
			char line = pos[0];
			char col = pos[2];
			// Judging words that are connected horizontally
			unsigned int colIndex = col - '0';
			colIndex += 10;
			unsigned int lineIndex = line - 'A';
			std::string strLine = "";
			// Connect the left ones first
			while (board[lineIndex][colIndex] != ' ') {
				strLine = board[lineIndex][colIndex] + strLine;
				if (colIndex == 0) break;
				colIndex--;
			}
			// Connect the right ones again
			colIndex = col - '0';
			colIndex += 11;
			while (colIndex < board.size() && board[lineIndex][colIndex] != ' ') {
				strLine = strLine + board[lineIndex][colIndex];
				colIndex++;
			}
			// Check if the horizontal word is in the lexicon
			int lineFlag = 0; // Flag, if in the lexicon, lineFlag is flagged 1
			for (unsigned int i = 0; i < words[strLine[0] - 'A'].size(); i++) {
				if (strLine.compare(words[strLine[0] - 'A'][i]) == 0) {
					lineFlag = 1;
					break;
				}
			}
			if (lineFlag == 0) return false; // If there is a word that is not in the lexicon, return false directly

			// Check if the vertical word is in the lexicon
			colIndex = col - '0';
			colIndex += 10;
			lineIndex = line - 'A';
			std::string strCol = "";
			// Add up the above characters first
			while (board[lineIndex][colIndex] != ' ') {
				strCol = board[lineIndex][colIndex] + strCol;
				if (lineIndex == 0) break;
				lineIndex--;
			}
			// Add up the below characters
			lineIndex = line - 'A';
			lineIndex+=1;
			while (lineIndex < board.size() && board[lineIndex][colIndex] != ' ') {
				strCol = strCol + board[lineIndex][colIndex];
				lineIndex++;
			}
			// Check if the vertical word is in the lexicon
			int ColFlag = 0; // Flag, if within the lexicon, ColFlag is flagged 1
			for (unsigned int i = 0; i < words[strCol[0] - 'A'].size(); i++) {
				if (strCol.compare(words[strCol[0] - 'A'][i]) == 0) {
					ColFlag = 1;
					break;
				}
			}
			if (ColFlag == 0) return false; // If there is a word that is not in the lexicon, return false directly
		}
	}

	return true;
}

bool Action(std::string tiles, std::string pos, Player* player, int pler, std::vector<std::vector<char>>& board) {
	if (pos.length() == 2) {
		char tile = tiles[0];
		char line = pos[0];
		char col = pos[1];
	
		//First determine if the board will fit

		if (board[line - 'A'][col - '0'] == ' ') {
			
			// check title 
			if (player[pler].place(tile)) {
				board[line - 'A'][col - '0'] = tile;
				return true;
			}
			else {
				std::cout << "Warning: You don't have this tile." << std::endl;
				return false;
			}
		}
		else {
			std::cout << "Warning: the placement of tile is illegal." << std::endl;
			return false;
		}
	}
	else if (pos.length() == 3) {
		char tile = tiles[0];
		char line = pos[0];
		char col = pos[2];
		// First determine if the board will place
		if (board[line - 'A'][(col - '0')+10] == ' ') {
			// can be placed depending on the hand tile
			if (player[pler].place(tile)) {
				board[line - 'A'][(col - '0') + 10] = tile;
				return true;
			}
			else {
				std::cout << "Warning: You don't have this tile." << std::endl;
				return false;
			}
		}
		else {
			std::cout << "Warning: the placement of tile is illegal." <<std:: endl;
			return false;
		}
	}
	else return false;
	
}

//Shuffle
void shuffle(LinkedList& TileBaglist) {
	srand((unsigned)time(NULL));
	LinkedList first;
	LinkedList second;
	int N = rand() % 3;
	int times = 0;
	while (TileBaglist.getSize() > N) {
		if (times % 2 == 0) {
			while (N--) {
				first.append(TileBaglist.popFront());
			}
		}
		else {
			while (N--) {
				second.append(TileBaglist.popFront());
			}
		}
		N = rand() % 10;
		times++;
	}

	std::cout << std::endl;

	while (second.getSize()) {
		TileBaglist.append(second.popFront());
	}
	
	while (first.getSize()) {
		TileBaglist.append(first.popFront());
	}
}


void exitGame() {
	std::cout << "\n\nGoodbye\n";
	exit(EXIT_SUCCESS);
}

void GameOver(Player* player) {
	std::cout << "Game over" << std::endl;
	std::cout << "Score for " << player[0].getName() << ": " << player[0].getScore() << std::endl;
	std::cout << "Score for " << player[1].getName() << ": " << player[1].getScore() << std::endl;
	if (player[0].getScore() > player[1].getScore()) {
		//player1 win
		std::cout << "Player " << player[0].getName() << " won!";

	}else if( player[0].getScore() == player[1].getScore()){	
		//draw
		std::cout << "Player " << player[0].getName()<<" and "<< player[1].getName()<<" are Draw";
	}
	else {
		//player2 win
		std::cout << "Player " << player[1].getName() << " won!";
	}
	exitGame();
}

void gamePlay(Player* player, int nums, LinkedList& TileBaglist, std::vector<std::vector<char>>& board, int pler, bool isLoad, bool enhance, std::vector<std::vector<std::string>>& words) {
	if (!isLoad) {
		// Determine if it is loaded
		
		//shuffle 
		shuffle(TileBaglist);
		
		//get hand tile
		for (int i = 0; i < nums; i++) {
			player[i].getHandTile(TileBaglist);
		}
		pler = -1;// mark player 

	}
	
	int fisrt_flag = 0; // Record if it is the first time a tile has been released  
	int pass[4]; // recording pass,if twice
	for (int i = 0; i < 4; i++) {
		pass[i] = 0;
	}
	while (1) {

	
		//Judgement logic, the bag is empty and one player has no cards in hand
		if (TileBaglist.empty() && (player[0].handEmpty() || player[1].handEmpty())) {
		
			//end game
			GameOver(player);
			break;
		}

	
		//change player
		if(!isLoad)pler++;
		else{
			isLoad =false;
		}
		if (pler == nums) {
			pler = 0;
		}
	
		//print player information
		std::cout <<"\n" << player[pler].getName() << ", it's your turn" << std::endl;
		for (int i = 0; i < nums; i++) {
			std::cout << "Score for " << player[i].getName() << ": " << player[i].getScore() << std::endl;
		}
		
	
		//print board
		displayBoard(board);
		std::cout << std::endl;
		std::cout << "Your hand is" << std::endl;
		player[pler].display();
		std::cout << std::endl;
		std::cout << std::endl;
		
		int passflag = 0; //  Mark this time with or without a pass 
		
		// Save the current player's hand, board and library for easy retrieval
		std::vector<std::vector<char>> saveBorad(board);
		Player savePlayer(player[pler]);
		LinkedList saveTileBag(TileBaglist);
		int save_fisrt_flag = fisrt_flag;

		std::vector<std::string> posBuffer; // Record the coordinates of each successful placement for later checking
		
		while (1) {

			passflag = 0;
			std::cout << "> ";
			std::string cmd;
			
			if (!getline(std::cin, cmd)) {
				exitGame();
			}

			std::stringstream ss(cmd);
			ss >> cmd;
			if (cmd.compare("place") == 0) {
				std::string tile;
				std::string at;
				std::string pos;
				ss >> tile >> at >> pos;
				std::string a;
				if (tile.compare("Done") == 0) {
					if (enhance) {
						// Enhanced version to detect correct word placement
						if (checkWord(board, posBuffer,words)) {
							// All in the lexicon, proceed to next round
							break;
						}
						else {
							// Prompt for errors and backtrack
							std::cout << "Warning: Some words on the chessboard are not in the thesaurus. Please reposition your hand." << std::endl;
							board = saveBorad;
							player[pler] = savePlayer;
							TileBaglist = saveTileBag;
							fisrt_flag = save_fisrt_flag;
							posBuffer.clear();
						}
					}
					else {
						// Non-enhanced version direct next person
						break;
					}
				}
				else if (player[pler].handEmpty()) {
					std::cout << "Warning: you do not have any tile." << std::endl;
				}
				else {
					if (commandValid(tile, at, pos)) {
						if (fisrt_flag == 0) {
							
							// If it is the first time you place a tile,
							// you do not need to check if there is an adjacent piece in the position
							if (Action(tile, pos, player, pler, board)) {
								posBuffer.push_back(pos);
								
								fisrt_flag = 1;
								if (player[pler].handEmpty()) {
								
									// place 7 title bingo

									player[pler].Bingo();
									std::cout << "BINGO!!!" << std::endl;
								}
							}
						}
						else {
							
							//Check the location for adjacency
							if (checkAji(pos,board)) {
								if (Action(tile, pos, player, pler, board)) {
									posBuffer.push_back(pos);
								
									// Complete the placement operation
									
									if (player[pler].handEmpty()) {
										
										//bingo
										player[pler].Bingo();
										std::cout << "BINGO!!!" << std::endl;
									}
								}
							}
							else {
								std::cout << "Warning: the placement of tile is illegal." << std::endl;
							}
						}
					}
					else {
						std::cout << "Warning: the command is not correctly formatted." << std::endl;
					}
				}
			}
			else if (cmd.compare("replace") == 0) {
				Letter ti;
				ss >> ti;
				if (ti < 'A' || ti>'Z') {
					std::cout << "Warning: the command is not correctly formatted." << std::endl;
				}
				else {
					Value val = player[pler].remove(ti);
					if (val==-1) {
						
						//do not have this tile 
						std::cout << "Warning: the tile is not in the player's hand." << std::endl;
					}
					else {
						Tile* tile = new Tile(ti, val);
						Node* node = new Node(tile);
						TileBaglist.append(node);
						player[pler].AddTile(TileBaglist.popFront()); // draw a card from the bag 
						break; // after replace to change another palyer
					}
				}
			}
			else if (cmd.compare("pass") == 0) {
				passflag = 1;
				
				if (TileBaglist.empty()&&(pass[pler] == 1)) {
					GameOver(player);
				}
				else {
					pass[pler] = 1;
				}
				board = saveBorad;
				player[pler] = savePlayer;
				TileBaglist = saveTileBag;
				fisrt_flag = save_fisrt_flag;
				posBuffer.clear();
				break;
			}
			else if (cmd.compare("save") == 0) {
				std::string path;
				ss >> path;

				// Save the game to a file
				// Contents saved: 1. two players' information and hands and the first player's turn 2. bag 3 board
				// Take the hand first if it is not full when reading

				if (saveGame(path, player, nums, pler, board, TileBaglist, enhance)) {
					std::cout << "Game succesffully saved." << std::endl;
				}
				else {
					std::cout << "Game failed saved. Please check the path of save." << std::endl;
				}
			}
			else if (cmd.compare("help") == 0 && enhance) {
				std::cout << "place <tile> at <position>" << std::endl
					<< "\tplace the tile(s) in your hand onto the board to form a word" << std::endl
					<< std::endl;
				std::cout << "place Done" << std::endl
					<< "\tdone placing tiles for the current turn" << std::endl
					<< std::endl;
				std::cout << "pass" << std::endl
					<< "\t pass your turn" << std::endl
					<< std::endl;
				std::cout << "replace <tile>" << std::endl
					<< "\treplace one tile in your hand then continue with the other player's turn" << std::endl
					<< std::endl;
				std::cout << "save" << std::endl
					<< "\t save the game to a file" << std::endl
					<< std::endl;
				std::cout << "^Z" << std::endl
					<< "\tquit the game" << std::endl
					<< std::endl;
			}
			else {
				std::cout << "Invalid Input" << std::endl;
			}

		}
		if (passflag == 0 ) {
			pass[pler] = 0;
		}
		
		player[pler].getHandTile(TileBaglist); //get title
	}
}


void NewGame(LinkedList& TileBaglist, std::vector<std::vector<char>>& board, bool enhance, std::vector<std::vector<std::string>>& words) {
	Player player[4];   //create player 
	std::cout << std::endl;
	std::cout << "Starting a New Game" << std::endl;
	std::cout << std::endl;
	
	int nums = 2; // Number of players, default is 2
	if (enhance) {
		// If it is an enhanced version, enter the number of players
		std::string opstring;
		std::cout << "Please enter the number of players(between 2 and 4)" << std::endl;
		std::cout << "> ";
		getline(std::cin, opstring);
		while (opstring.size() > 2 || opstring[0] - '0' < 2 || opstring[0] - '0' > 4) {
			std::cout << "Please enter a number between 2 and 4." << std::endl;
			std::cout << "> ";
			if (!getline(std::cin, opstring)) {
				exitGame();
			}
		}
		nums = opstring[0] - '0';
	}
	//Play 1
	std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
	std::string player1;
	std::cout << "> ";

	if (!getline(std::cin, player1)) {
		exitGame();
	}

	while (!nameValid(player1)) {
		std::cout << "Warning: name should be uppercase characters only" << std::endl;
		std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
		std::cout << "> ";
		if (!getline(std::cin, player1)) {
			exitGame();
		}
	}
	//score,playname
	Player first(0,player1);
	player[0] = first;


	//Play 2
	std::cout << std::endl;
	std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
	std::string player2;
	std::cout << "> ";
	if (!getline(std::cin, player2)) {
		exitGame();
	}

	while (!nameValid(player2) || player1.compare(player2) == 0) {
		
		if(player1.compare(player2) == 0){
			std::cout<<"Warning: You have same name, Please ENTER name again !"<< std::endl;			
		}
		if(!nameValid(player2)){
			std::cout << "Warning: name should be uppercase characters only" << std::endl;
		}

		std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
	
		std::cout << "> ";
		if (!getline(std::cin, player2)) {
			exitGame();
		}
	}
	//score,playname
	Player second(0,player2);

	//score,playname
	player[1] = second;
	
	if (enhance && nums > 2) {
		//Play 3
		std::cout << std::endl;
		std::cout << "Enter a name for player 3 (uppercase characters only)" << std::endl;
		std::string player3;
		std::cout << "> ";
		if (!getline(std::cin, player3)) {
			exitGame();
		}

		while (!nameValid(player3) || player1.compare(player3) == 0 || player2.compare(player3)==0) {

			if (player1.compare(player3) == 0 || player2.compare(player3) == 0) {
				std::cout << "Warning: You have same name, Please ENTER name again !" << std::endl;
			}
			if (!nameValid(player3)) {
				std::cout << "Warning: name should be uppercase characters only" << std::endl;

			}

			std::cout << "Enter a name for player 3 (uppercase characters only)" << std::endl;

			std::cout << "> ";
			if (!getline(std::cin, player3)) {
				exitGame();
			}
		}
		//score,playname
		Player third(0, player3);
		//score,playname
		player[2] = third;

		if (nums == 4) {
			//Play 4
			std::cout << std::endl;
			std::cout << "Enter a name for player 4 (uppercase characters only)" << std::endl;
			std::string player4;
			std::cout << "> ";
			if (!getline(std::cin, player4)) {
				exitGame();
			}

			while (!nameValid(player4) || player1.compare(player4) == 0 || player2.compare(player4) == 0 || player3.compare(player4) == 0) {

				if (player1.compare(player4) == 0 || player2.compare(player4) == 0 || player3.compare(player4) == 0) {
					std::cout << "Warning: You have same name, Please ENTER name again !" << std::endl;
				}
				if (!nameValid(player4)) {
					std::cout << "Warning: name should be uppercase characters only" << std::endl;

				}

				std::cout << "Enter a name for player 4 (uppercase characters only)" << std::endl;

				std::cout << "> ";
				if (!getline(std::cin, player4)) {
					exitGame();
				}
			}
			//score,playname
			Player fourth(0, player4);
			//score,playname
			player[3] = fourth;
		}
	}

	std::cout << std::endl;
	std::cout << "Let's Play!" << std::endl;

	// <normal gameplay continues from here>
	gamePlay(player, nums, TileBaglist, board, 1, false, enhance, words);

}

void LoadGame(bool enhance, std::vector<std::vector<std::string>>& words) {
	std::string path;
	std::cout << "\nEnter the filename from which load a game." << std::endl;
	std::cout << "> ";
	getline(std::cin,path); 

	Player player[4];
	LinkedList TileBaglist;
	std::vector<std::vector<char>> board;
	int nums = 2;
	if (enhance) {
		if (!readWords("web2", words)) {
			std::cout << "Warning: Failed open words file. Please check the file path." << std::endl;
			return;
		}
	}
	int pler = readGame(path, player,nums, TileBaglist, board,enhance);
	if (pler == -1) {
		// The non-enhanced version reads the enhanced version of the file
		return;
	}
	std::cout << "\nScrabble game successfully loaded" << std::endl;
	gamePlay(player, nums, TileBaglist, board, pler, true, enhance, words);

}




void MainMenu(LinkedList& TileBaglist, std::vector<std::vector<char>>& board, bool& enhance, std::vector<std::vector<std::string>>& words) {
	std::cout << "Menu" << std::endl;
	std::cout << "----" << std::endl;
	std::cout << "1. New Game" <<std::endl;
	std::cout << "2. Load Game" << std::endl;
	std::cout << "3. Credits (Show student information)" << std::endl;
	std::cout << "4. game settings" << std::endl;
	std::cout << "5. Quit" << std::endl;
	std::cout << std::endl;
	std::cout << "> ";
	int op;
	std::string opstring;
	if (!getline(std::cin, opstring)) {
		exitGame();
	}

	while (opstring.size() > 2 || opstring[0] - '0' < 1 || opstring[0] - '0'>5) {
		std::cout << "Please enter a number between 1 and 5." << std::endl;
		std::cout << "> ";
		if (!getline(std::cin, opstring)) {
			exitGame();
		}
	}
	op = opstring[0] - '0';

	switch (op)
	{
	case 1:
		NewGame(TileBaglist,board,enhance,words);
		break;
	case 2:
		LoadGame(enhance,words);
		break;
	case 3:
		Credits();
		break;
	case 4:
		// game setting
		std::cout << "The status of opening the enhanced version is: ";
		if (enhance) {
			std::cout << "true" << std::endl;
		}
		else {
			std::cout << "false" << std::endl;
		}
		std::cout << "Enter 1 to open the enhanced version\nEnter 0 to close the enhanced version." << std::endl;
		while (opstring.size() > 2 || opstring[0] - '0' > 1 || opstring[0] - '0' < 0) {
			std::cout << "Please enter a number between 0 and 1." << std::endl;
			std::cout << "> ";
			if (!getline(std::cin, opstring)) {
				exitGame();
			}
		}
		if (opstring[0] - '0' == 1) {
			std::cout << "Successfully opened the enhanced version\nNow reading word thesaurus, please wait a moment..." << std::endl;

			if (readWords("web2", words)) {
				enhance = true;
				std::cout << "Word thesaurus reading completed.\n" << std::endl;
			}
			else {
				std::cout << "Warning: Failed open words file. Please check the file path." << std::endl;
				std::cout << "Failed open enhance version." << std::endl;
			}
		}
		else {
			enhance = false;
		}
		break;
	case 5:
		exitGame();
		break;
	default:
		break;
	}

}

//initBoard
void initBoard(std::vector<std::vector<char>>& board) {
	for (int i = 0; i < 15; i++) {
		std::vector<char> b;
		for (int j = 0; j < 15; j++) {
			b.push_back(' ');
		}
		board.push_back(b);
	}
}

void Credits(){
	std::cout << "\n\n------------------------------------------------" << std::endl;
	std::cout << " Individual work" << std::endl;
	std::cout << "Name: Yuncong JI" << std::endl;
	std::cout << "Student ID: s3752061" << std::endl;
	std::cout << "Email: s3752061@student.rmit.edu.au" << std::endl;
	std::cout <<std:: endl;


}


