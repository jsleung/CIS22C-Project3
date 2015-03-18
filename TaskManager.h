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

using namespace std;

class AdjacencyList;

class Edge
{
private:
    int projectTime;
public:
    Edge() {projectTime = 0;}
    Edge(int p) {projectTime = p;}
    int getTime() {return projectTime;}
    void setTime(int p) {projectTime = p;}
};


class Vertex
{
private:
    int vertexNum;
    int predecessors;
    int successors;
    int eeTime; //earliest event time
    int leTime; //latest event time
    AdjacencyList* list;
public:
    Edge edge; //public in order to access data values inside Edge class
    Vertex();
    Vertex(int v, int projectTime);
    ~Vertex();
    
    void seteeTime(int e) {eeTime = e;}
    void setleTime(int e) {leTime = e;}
    int getEarliestTime() {return eeTime;}
    int getLatestTime() {return leTime;}
    void incSuccessorsCount() {successors++;}
    void decSuccessorsCount() {successors--;}
    int getSuccessorsCount() {return successors;}
    void incPredecessorsCount() {predecessors++;}
    void decPredecessorsCount() {predecessors--;}
    int getPredecessorsCount() {return predecessors;}
    int getVertexNum() {return vertexNum;}
    void setVertexNum(int v) {vertexNum = v;}
    void addToAdjList(Vertex& v);
    void printAdjacencyList() const;
};

class TaskManager
{
private:
    int numProjects;
    Vertex* projectArr;
public:
    TaskManager(int p) {numProjects = p; projectArr = new Vertex[numProjects];}
    
};



#endif /* defined(__Scheduler__TaskManager__) */
