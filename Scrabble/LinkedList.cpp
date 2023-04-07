#include "LinkedList.h"
#include <iostream>

// Chain table for hands: chain table of two players' hands
// Nested vectors for maps, which are actually two-dimensional arrays vector<vector<c>>
// Use a class to encapsulate player information, including hands, scores, etc.

LinkedList::LinkedList() {
	head = nullptr;
	size = 0;
}

LinkedList::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

LinkedList::LinkedList(const LinkedList& other) {

    this->head = new Node;
    this->size = 0;


    // firstly, determine if other is an empty linkedlist. if it is an empty linkedlist just ignore it
    if (other.size != 0 && other.head != nullptr) {
        this->size = other.size;
        Node* otherTemp = other.head->next;
        Node* thisTemp = head;

        //deep copy, each node is created with a new node, which is then inserted into the back of the current linkedlist 
        while (otherTemp) {
            Tile* newTile = new Tile(otherTemp->tile->letter, otherTemp->tile->value);
            Node* temp = new Node(newTile);
            thisTemp->next = temp;
            thisTemp = thisTemp->next;
            otherTemp = otherTemp->next;
        }
    }
}

LinkedList& LinkedList::operator=(const LinkedList& other)
{
     // Free up your space first
    if (this->head) {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    this->head = new Node;
    this->size = 0;
    // first determine if other is an empty linked table, if it is, just ignore it
    if (other.size != 0 && other.head != nullptr) {
        this->size = other.size;
        Node* otherTemp = other.head->next;
        Node* thisTemp = head;

       // deep copy, where each node is new and inserted into the back of the current chain
        while (otherTemp) {
            Tile* newTile = new Tile(otherTemp->tile->letter, otherTemp->tile->value);
            Node* temp = new Node(newTile);
            thisTemp->next = temp;
            thisTemp = thisTemp->next;
            otherTemp = otherTemp->next;
        }
    }
    return *this;
}

void LinkedList::append(Node* data){
    if (head == nullptr) {
        head = new Node;
        head->next = data;
        size++;
    }
    else {
        Node* temp = head->next;
        Node* pre = head;
        while (temp) {
            pre = temp;
            temp = temp->next;
        }
        pre->next = data;
        
        size++;
    }
}

Value LinkedList::remove(Letter letter){
    if (head == nullptr) return -1;
    Node* temp = head->next;
    Node* pre = head;
    Value val=-1;
    while (temp) {
        if (temp->tile->letter == letter) {
            pre->next = temp->next;
            val = temp->tile->value;
            size--;
            delete temp->tile;
            delete temp;
            if (pre == head && pre->next == nullptr) {
                //linked list empty
                delete head;
                head = nullptr;
            }
            break;
        }
        pre = temp;
        temp = temp->next;
    }
    return val;
}

Node* LinkedList::popFront(){
    if (head == nullptr) return nullptr;
    Node* res = this->head->next;
    this->head->next = res->next;
    size--;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    res->next = nullptr;
    return res;
}


void LinkedList::display() const{
    if (head != nullptr) {
        Node* temp = head->next;
        while (temp) {
            std::cout << temp->tile->letter << "-" << temp->tile->value << " ";
            temp = temp->next;
        }
    }
    else {
        std::cout << "No tile" << std::endl;
    }
}

bool LinkedList::empty() const{
    return head==nullptr;
}

int LinkedList::getSize() const{
    return size;
}
