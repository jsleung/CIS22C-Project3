//
//  TaskManager.h
//  Scheduler
//
//  Created by Brad Lasecke on 3/13/15.
//  Copyright (c) 2015 Lasecke. All rights reserved.
//

#ifndef __Scheduler__TaskManager__
#define __Scheduler__TaskManager__

#include <limits>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

class AdjacencyList;

class Edge
{
private:
	int projectTime;
public:
	Edge() { projectTime = 0; }
	Edge(int p) { projectTime = p; }
	int getTime() const { return projectTime; }
	void setTime(int p) { projectTime = p; }
};


class Vertex
{
private:
	string jobName;
	int vertexNum;
	int predecessors;
	int successors;
	int finalNode;
	int eeTime; //earliest event time
	int leTime; //latest event time
	AdjacencyList* adjlist;
	AdjacencyList* invAdjList;
public:
	Edge edge; //public in order to access data values inside Edge class
	Vertex();
	Vertex(int v, int projectTime);
	Vertex(int v, int projectTime, string name);
	Vertex(const Vertex& copy);
	~Vertex() {}

	void seteeTime(int e) { eeTime = e; }
	void setleTime(int e) { leTime = e; }
	int getEarliestTime() const { return eeTime; }
	int getLatestTime() const { return leTime; }
	void incSuccessorsCount() { successors++; }
	void decSuccessorsCount() { successors--; }
	int getSuccessorsCount() const { return successors; }
	void incPredecessorsCount() { predecessors++; }
	void decPredecessorsCount() { predecessors--; }
	int getPredecessorsCount() const { return predecessors; }
	int getVertexNum() const { return vertexNum; }
	void setVertexNum(int v) { vertexNum = v; }
	void setName(string n) { jobName = n; }
	void addToAdjList(Vertex& v, int jobtime);
	void addToInvAdjList(Vertex& v, int jobtime);
	void printAdjacencyList() const;
	AdjacencyList * getAdjList() const { return adjlist; }
	AdjacencyList * getInvAdjList() const { return invAdjList; }
};

class TaskManager
{
private:
	int numProjects;
	vector<Vertex> projectArr;
public:
	TaskManager(int p);
	~TaskManager() {}
	void print();
	void addVertex(int vNum, int projTime, string name); //should not have two of the same vertex numbers
	void connect(Vertex& predecessor, Vertex& successor, int jobtime); //'connects' both vertices by adding the successor into the predecessors adjacency list, and the predecessor into the sucessors inverse adjacency list
	void disconnect(Vertex& predecessor, Vertex& successor); //removes what happens in the connect() function
	void getInput(int numTimes);
	vector<int> getEE();
	vector<int> getLE();
};



#endif /* defined(__Scheduler__TaskManager__) */
