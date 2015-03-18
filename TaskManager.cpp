//
//  TaskManager.cpp
//  Scheduler
//
//  Created by Brad Lasecke on 3/13/15.
//  Copyright (c) 2015 Lasecke. All rights reserved.
//

#include "TaskManager.h"
#include "AdjacencyList.h"


Vertex::Vertex()
{
    vertexNum = 0;
    predecessors = 0;
    successors = 0;
    eeTime = 0;
    leTime = std::numeric_limits<int>::max(); //largest possible value
    edge = *new Edge();
    list = new AdjacencyList();
}

Vertex::Vertex(int v, int projectTime)
{
    vertexNum = v;
    predecessors = 0;
    successors = 0;
    eeTime = 0;
    leTime = std::numeric_limits<int>::max(); //largest possible value
    edge = *new Edge(projectTime);
    list = new AdjacencyList();
}

Vertex::~Vertex()
{
    list->~AdjacencyList();
}

void Vertex::addToAdjList(Vertex& v)
{
    this->incSuccessorsCount();
    v.incPredecessorsCount();
    this->list->add(v);
}

void Vertex::printAdjacencyList() const
{
    cout << "Vertex " << vertexNum << "'s adjacency list\nPredecessor count = " <<  predecessors << "\nSuccessor count = " << successors << endl;
    list->print();
}
