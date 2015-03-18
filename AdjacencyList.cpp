//
//  LinkedAdjacencyList.cpp
//  Ass7
//
//  Created by Brad Lasecke on 11/28/14.
//  Copyright (c) 2014 Brad Lasecke. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
#include "AdjacencyList.h"

AdjacencyList::AdjacencyList()
{
    vertex = *new Vertex();
    top_ = 0;
}

AdjacencyList::AdjacencyList(Vertex v)
{
    vertex = v;
    top_ = 0;
}

AdjacencyList::~AdjacencyList()
{
    Node* temp = top_;
    while(temp != 0)
    {
        top_ = top_->next_; //advance pointer
        delete temp;
        temp = top_;
    }
    delete top_;
}

void AdjacencyList::add(Vertex v)
{
    Node* temp1 = top_;
    Node* temp2 = temp1;
    
    if(temp1 == 0) //if there are no other items in the list
    {
        top_ = new Node(v, top_);
    }
    else
    {
        while(temp1 != 0)
        {
            temp2 = temp1;
            temp1 = temp1->next_; //advance pointer to end of list
        }
        temp2->next_ = new Node(v, 0);
    }
}

Vertex AdjacencyList::pop()
{
    Vertex vTemp;
    if(top_ != 0)
    {
        Node* temp = top_;
        top_ = top_->next_; //advances pointer
        vTemp =  temp->vertex;
        delete temp;
    }
    return vertex;
}

Vertex AdjacencyList::top() const
{
    return top_->vertex;
}

void AdjacencyList::print()
{
    Node* temp = top_;
    
    cout << "Vertex " << vertex.getVertexNum() << "'s Adjacency List; predecessor count = " << vertex.getPredecessorsCount() << endl;
    
    if(temp == 0)
        cout << "No vertices in the AdjacencyList\n";
    else
    {
        cout << "\nVertex " << setw(10) << right << "Project Time\n";
        while(temp != 0)
        {
            cout << setw(3) << left << temp->vertex.getVertexNum();
            cout << setw(7) << right << temp->vertex.edge.getTime() << endl;
            temp = temp->next_; //advance
        }
        cout << endl;
    }
}

bool AdjacencyList::remove(Vertex v)
{
    Node* nodeToRemove = find(v);
    if(nodeToRemove != 0)
    {
        Node* nodeInFront = top_;
        
        if(top_->vertex.getVertexNum() == v.getVertexNum())
        {
            top_=top_->next_;
            delete nodeInFront;
            return true;
        }
        
        while(nodeInFront != 0)
        {
            if(nodeInFront->next_->vertex.getVertexNum() != nodeToRemove->vertex.getVertexNum())
                nodeInFront = nodeInFront->next_; //advance pointer if vertexNum are not equal
            else
                break;
        }
        
        nodeInFront->next_=nodeToRemove->next_;
        delete nodeToRemove;
        return true;
    }
    else
    {
        cerr << "vertex: " << v.getVertexNum() << " is not in the AdjacencyList\n";
        return false;
    }
}

Node* AdjacencyList::find(Vertex v)
{
    Node* temp = top_;
    while(temp != 0)
    {
        if(temp->vertex.getVertexNum() == v.getVertexNum())
            break;
        else
            temp=temp->next_;
    }
    
    return temp;
}

bool AdjacencyList::removeLast()
{
    Node* nodeInFront = top_;
    Node* nodeToRemove = top_;
    
    while(nodeToRemove->next_ != 0)
    {
        nodeInFront = nodeToRemove;
        nodeToRemove = nodeToRemove->next_;
    }
    
    nodeInFront->next_ = 0;
    delete nodeToRemove;
    return true;
}
