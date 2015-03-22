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

class Vertex
{
private:
	string jobName;
	int vertexNum;
	int predecessors;
	int successors;
	int finalNode;
	AdjacencyList* adjlist;
	AdjacencyList* invAdjList;
public:
	Vertex();
	Vertex(int v, int projectTime);
	Vertex(int v, int projectTime, string name);
	~Vertex() {}
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
	void printInvAdjacencyList() const;
	AdjacencyList * getAdjList() const { return adjlist; }
	AdjacencyList * getInvAdjList() const { return invAdjList; }
};

class TaskManager
{
private:
	int numProjects;
	int numActivities;
	int critPath;
	vector<Vertex> projectArr;
	vector<int> EE;
	vector<int> LE;
	vector<bool> critical;
	struct edge{
		int predecess;
		int success;
		int duration;
	};
	vector<edge> activityList;
public:
	TaskManager(int p);
	~TaskManager() {}
	void print();
	void addVertex(int vNum, int projTime, string name); //should not have two of the same vertex numbers
	void connect(Vertex& predecessor, Vertex& successor, int jobtime); //'connects' both vertices by adding the successor into the predecessors adjacency list, and the predecessor into the sucessors inverse adjacency list
	void disconnect(Vertex& predecessor, Vertex& successor); //removes what happens in the connect() function
	void getInput(int numTimes);
	void getEE();
	void getLE();
	void findCritical();
};



#endif /* defined(__Scheduler__TaskManager__) */
