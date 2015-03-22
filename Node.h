//
//  Node.h
//  Ass7
//
//  Created by Brad Lasecke on 11/28/14.
//  Copyright (c) 2014 Brad Lasecke. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include "TaskManager.h"

class AdjacencyList; //in order to make List a friend class
class Vertex;

class Node
{
private:
	Vertex* vertex;
	int duration;
	Node* next_;
public:
	Node() { vertex = nullptr; next_ = nullptr; }
	Node(Vertex& v, Node* n, int jobtime) { vertex = &v; next_ = n; duration = jobtime; }
	Vertex* getVertex(){ return vertex; }
	Node * getNext() { return next_; }
	int getDuration(){ return duration; }
	friend class AdjacencyList;
	friend class Vertex;
};


#endif
