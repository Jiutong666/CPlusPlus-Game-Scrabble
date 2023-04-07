
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class LinkedList {
public:

	LinkedList();
	~LinkedList();

	LinkedList(const LinkedList& other); //  copy Constructors
	LinkedList& operator = (const LinkedList&); //   Assignment operator overloading 

	void append(Node* data); // add end 
	Value remove(Letter letter); 
	//Deletes a letter by its value, returns the value of the letter if the deletion succeeds, and -1 if it fails.
	Node* popFront();
	void display() const; // print Title
	bool empty() const; // check emply
	int getSize() const;  //return size
	
	 
	 //Overloading Output Operators
	friend std::ostream& operator<<(std::ostream& os, const LinkedList& link) {
		if (link.head != nullptr) {
			Node* temp = link.head->next;
			while (temp) {
				os << temp->tile->letter << "-" << temp->tile->value;
				if (temp->next) os << ", ";
				temp = temp->next;
			}
		}
		return os;
	}


	//Overloading intput Operators
	friend std::istream& operator>>(std::istream& os, LinkedList& link) {
		if (link.head != NULL) {
			while (link.head) {
				Node* temp = link.head;
				link.head = link.head->next;
				delete temp;
			}
		}
		link.size = 0;
		link.head = new Node;		
		Node* temp = link.head;
		std::string line;
		while (line.empty()) {
			getline(os, line);
		}
		std::stringstream iss(line);
		while (getline(iss, line, ','))	// with split as separator
		{
			Letter letter;
			Value val;
			if (line[0] == ' ') {
				letter = line[1];
				val = line[3]-'0';
				if (line.length() == 5) {
					val = val * 10 + line[4] - '0';
				}
			}
			else {
				letter = line[0];
				val = line[2]-'0';
				if (line.length() == 4) {
					val = val * 10 + line[3] - '0';
				}
			}

			Tile* tile = new Tile(letter, val);
			Node* node = new Node(tile);
			temp->next = node;
			temp = temp->next;
			link.size++;
		}
		return os;
	}

private:
	Node* head;
	int size;
};

#endif // ASSIGN2_LINKEDLIST_H
