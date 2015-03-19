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
    Node* next_;
public:
    Node() {vertex = 0; next_ = 0;}
    Node(Vertex& v, Node* n) {vertex = &v; next_ = n;}
    friend class AdjacencyList;
    friend class Vertex;
};


#endif
