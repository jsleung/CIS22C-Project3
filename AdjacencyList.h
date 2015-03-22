//
//  LinkedList.h
//  Ass7
//
//  Created by Brad Lasecke on 11/28/14.
//  Copyright (c) 2014 Brad Lasecke. All rights reserved.
//

#ifndef Ass7_LinkedList_h
#define Ass7_LinkedList_h
#include <cstdlib>
#include <iomanip>
#include "TaskManager.h"
#include "Node.h"

class Vertex;

class AdjacencyList
{
private:
	Node* top_;
public:
	AdjacencyList();
	~AdjacencyList();
	void add(Vertex& v, int jobtime); //puts a new Vertex at the end of the linked list
	Vertex pop(); //deletes top Node and returns its vertex
	Vertex top() const; //returns what vertex is at the top of the list;
	void print();
	bool remove(Vertex &v); //finds node equal to item and removes it
	Node* find(Vertex &v); //returns the node equal to item
	bool removeLast(); //removes the last node in the list
	Node * getTop()  { return top_; }

};


#endif
