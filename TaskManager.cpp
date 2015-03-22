//
//  TaskManager.cpp
//  Scheduler
//
//  Created by Brad Lasecke on 3/13/15.
//  Copyright (c) 2015 Lasecke. All rights reserved.
//

#include "AdjacencyList.h"
//#include "Stack.h"

using namespace std;

Vertex::Vertex()
{
	jobName = "null";
	vertexNum = -1;
	predecessors = 0;
	successors = 0;
	eeTime = 0;
	leTime = std::numeric_limits<int>::max(); //largest possible value
	edge = *new Edge();
	adjlist = new AdjacencyList();
	invAdjList = new AdjacencyList(); //inverse adjacency list
}

Vertex::Vertex(int v, int projectTime)
{
	Vertex();
	vertexNum = v;
}

Vertex::Vertex(int v, int projectTime, string name)
{
	Vertex(v, projectTime);
	jobName = name;
}

Vertex::Vertex(const Vertex& copy)
{
	Vertex(copy.vertexNum, copy.edge.getTime(), copy.jobName);
}

void Vertex::addToAdjList(Vertex& v, int jobtime)
{
	this->incSuccessorsCount();
	this->adjlist->add(v, jobtime);
}
//one of these functions is going to double the amount of preds. and succs.
void Vertex::addToInvAdjList(Vertex& v, int jobtime)
{
	this->incPredecessorsCount();
	this->invAdjList->add(v, jobtime);
}

void Vertex::printAdjacencyList() const
{
	cout << jobName << "'s adjacency list: Vertex Number [" << vertexNum << "]\nPredecessor count = " << predecessors << "\nSuccessor count = " << successors << endl;
	adjlist->print();
}

TaskManager::TaskManager(int p)
{
	numProjects = p;
	projectArr.resize(numProjects);
	//projectArr = new Vertex[numProjects];
}

void TaskManager::print()
{
	for (int i = 0; i < numProjects; i++)
	{
		//if there exists a vertex
		if (projectArr[i].getVertexNum() != -1)
			projectArr[i].printAdjacencyList();
	}
}

void TaskManager::addVertex(int vNum, int projTime, string name)
{
	if (vNum < numProjects)
	{
		projectArr[vNum].setVertexNum(vNum);
		projectArr[vNum].setName(name);
	}
	else
	{
		cerr << "\nThe vertex number is too high for the number of projects!\nTaskManager::addVertex()\n";
		exit(0);
	}
}

bool isValid(string s)
{
	if (s == "q" || s == "Q" || s == "quit" || s == "QUIT")
		return false;
	else
		return true;
}

void TaskManager::getInput(int numTimes)
{
	string input = "";
	string name = "";
	int vertexNum = 0;
	int jobTime = 0;
	string temp = "";
	int pred = 0; //predecessor
	int succes = 0; //successor

	while (isValid(input) && vertexNum < numTimes)
	{
		cout << "Enter a name for the next job: ";
		cin >> input;

		if (!isValid(input))
			break;

		name = input;
		addVertex(vertexNum, jobTime, name);
		vertexNum++;
	}

	while (true)
	{
		cout << "Would you like to connect any of the jobs together? (y/n) ";
		cin >> temp;
		if (temp == "n" || temp == "N")
			break;
		else
		{
			cout << "Which job would you like to start with?(0 -" << numTimes - 1 << ") ";
			cin >> pred;
			cout << "Which job would you like to connect it to?(0 -" << numTimes - 1 << ") ";
			cin >> succes;
			cout << "How many hours will this connection take? ";
			cin >> jobTime;
			if (pred < 0 || pred >= numTimes || succes < 0 || succes >= numTimes || pred == succes){
				cout << "Your jobs are not within bounds\n";
				continue;
			}
			if (projectArr[pred].getAdjList()->find(projectArr[succes]) == nullptr){
				connect(projectArr[pred], projectArr[succes], jobTime);
			}
			else{
				cout << "That connection was already created\n";
			}
		}
	}
}

void TaskManager::connect(Vertex& predecessor, Vertex& successor, int jobtime)
{
	predecessor.addToAdjList(successor, jobtime);
	successor.addToInvAdjList(predecessor, jobtime);
}
