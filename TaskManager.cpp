//
//  TaskManager.cpp
//  Scheduler
//
//  Created by Brad Lasecke on 3/13/15.
//  Copyright (c) 2015 Lasecke. All rights reserved.
//

#include "TaskManager.h"
#include "AdjacencyList.h"
//#include "Stack.h"

using namespace std;

Vertex::Vertex()
{
	jobName = "null";
	vertexNum = 0;
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

void Vertex::addToAdjList(Vertex& v)
{
	this->incSuccessorsCount();
	this->adjlist->add(v);
}
//one of these functions is going to double the amount of preds. and succs.
void Vertex::addToInvAdjList(Vertex& v)
{
	this->incPredecessorsCount();
	this->invAdjList->add(v);
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
		if (projectArr[i].getVertexNum() != 0)
			projectArr[i].printAdjacencyList();
	}
}

void TaskManager::addVertex(int vNum, int projTime, string name)
{
	if (vNum < numProjects)
	{
		projectArr[vNum].setVertexNum(vNum);
		projectArr[vNum].edge.setTime(projTime);
		projectArr[vNum].setName(name);
	}
	else
	{
		cerr << "\nThe vertex number is too high for the number of projects!\nTaskManager::addVertex()\n";
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
	int vertexNum = 1;
	int jobTime = 0;
	string temp = "";
	int pred = 0; //predecessor
	int succes = 0; //successor

	while (isValid(input) || vertexNum < numTimes)
	{
		cout << "Enter a name for the next job: ";
		cin >> input;

		if (!isValid(input))
			break;

		name = input;
		cout << "How many hours will " << name << " take? ";
		cin >> jobTime;
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
			cout << "Which job would you like to start with?(1-" << numTimes - 1 << ") ";
			cin >> pred;
			cout << "Which job would you like to connect it to?(1-" << numTimes - 1 << ") ";
			cin >> succes;
			connect(projectArr[pred], projectArr[succes]);
		}
	}
}

void TaskManager::connect(Vertex& predecessor, Vertex& successor)
{
	predecessor.addToAdjList(successor);
	successor.addToInvAdjList(predecessor);
}
