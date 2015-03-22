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

void Vertex::printInvAdjacencyList() const
{
	cout << jobName << "'s Inverse adjacency list: Vertex Number [" << vertexNum << "]\nPredecessor count = " << predecessors << "\nSuccessor count = " << successors << endl;
	invAdjList->print();
}

TaskManager::TaskManager(int p)
{
	numProjects = p;
	critPath = 0;
	numActivities = 0;
	projectArr.resize(numProjects);
	activityList.resize(numProjects); //Temporary resize to not require constant push_back calls
}

void TaskManager::print()
{
	for (int i = 0; i < numProjects; i++)
	{
		//if there exists a vertex
		if (projectArr[i].getVertexNum() != -1)
			projectArr[i].printInvAdjacencyList();
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
				if (numActivities >= activityList.size()){
					activityList.resize(activityList.size() * 2);
				}
				activityList[numActivities].predecess = pred;
				activityList[numActivities].success = succes;
				activityList[numActivities].duration = jobTime;
				numActivities++;
			}
			else{
				cout << "That connection was already created\n";
			}
		}
	}
	activityList.resize(numActivities);
}

void TaskManager::connect(Vertex& predecessor, Vertex& successor, int jobtime)
{
	predecessor.addToAdjList(successor, jobtime);
	successor.addToInvAdjList(predecessor, jobtime);
}

void TaskManager::getEE(){
	EE.resize(numProjects, 0);
	deque<int> EEstack; //stack as in example
	vector<int> predecessCopy; //copies the values of predecessors, so decreasing doesnt effect adjList
	predecessCopy.resize(numProjects);
	for (int i = 0; i < numProjects; i++){
		predecessCopy[i] = projectArr[i].getPredecessorsCount();
	}
	EEstack.push_front(0); // start at vertex 0
	while (!EEstack.empty()){
		int tempFront = EEstack.front();
		EEstack.pop_front();
		Node * firstNode = (projectArr[tempFront].getAdjList())->getTop(); // grab first node of adjacency list of vertex 0
		while (firstNode != nullptr){
			Vertex *chosen = firstNode->getVertex(); //look at first Node's vertex (a successor)
			predecessCopy[chosen->getVertexNum()]--; //decrease the successor's predecessor count
			if (EE[tempFront] + firstNode->getDuration() > EE[chosen->getVertexNum()]){ //do the math that is shown in lecture slide
				EE[chosen->getVertexNum()] = EE[tempFront] + firstNode->getDuration();
			}
			if (predecessCopy[chosen->getVertexNum()] == 0){
				EEstack.push_front(chosen->getVertexNum()); //only push the successor on the stack if all predecessors have been seen
			}
			firstNode = firstNode->getNext();
		}
		/*cout << "pushed off " << tempFront << "\t";
		for (int i = 0; i < numProjects; i++){
			cout << EE[i] << ' ';
		}
		cout << endl;*/
	}
	/*
	cout << "EE:\n";
	for (int i = 0; i < numProjects; i++){
		cout << EE[i] << ' ';
	}
	cout << endl;*/
	critPath = EE[numProjects - 1]; //critical path length, used in finding LE
}

//LE is very similar to EE except goes backwards from the last vertex and subtracts from the critical path length
void TaskManager::getLE(){
	LE.resize(numProjects, critPath);
	deque<int> LEstack;
	vector<int> succesCopy;
	succesCopy.resize(numProjects);
	for (int i = 0; i < numProjects; i++){
		succesCopy[i] = projectArr[i].getSuccessorsCount();
	}
	LEstack.push_front(numProjects - 1);
	while (!LEstack.empty()){
		int tempFront = LEstack.front();
		LEstack.pop_front();
		Node * firstNode = (projectArr[tempFront].getInvAdjList())->getTop();
		while (firstNode != nullptr){
			Vertex *chosen = firstNode->getVertex();
			succesCopy[chosen->getVertexNum()]--;
			if (LE[tempFront] - firstNode->getDuration() < LE[chosen->getVertexNum()]){
				LE[chosen->getVertexNum()] = LE[tempFront] - firstNode->getDuration();
			}
			if (succesCopy[chosen->getVertexNum()] == 0){
				LEstack.push_front(chosen->getVertexNum());
			}
			firstNode = firstNode->getNext();
		}
		/*cout << "pushed off " << tempFront << "\t";
		for (int i = 0; i < numProjects; i++){
		cout << LE[i] << ' ';
		}
		cout << endl;*/
	}
	/*
	cout <<"LE:\n";
	for (int i = 0; i < numProjects; i++){
	cout << LE[i] << ' ';
	}
	cout << endl;*/
}

//finds critical activities via the equation on slide 17 and 38
void TaskManager::findCritical(){
	getEE();
	getLE();
	vector<bool> isCritical(numActivities, false);
	for (int i = 0; i < numActivities; i++){
		if (LE[activityList[i].success] - activityList[i].duration - EE[activityList[i].predecess] == 0){
			isCritical[i] = true;
			int j = i + 1;
			cout << "Activity " << j << " is Critical" << endl; // activities go from 0 - n-1, off by one
		}
	}
}
