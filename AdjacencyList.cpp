//
//  LinkedAdjacencyList.cpp
//  Ass7
//
//  Created by Brad Lasecke on 11/28/14.
//  Copyright (c) 2014 Brad Lasecke. All rights reserved.
//


#include "AdjacencyList.h"

AdjacencyList::AdjacencyList()
{
	top_ = nullptr;
}

AdjacencyList::~AdjacencyList()
{
	Node* temp = top_;
	while (temp != nullptr)
	{
		top_ = top_->next_; //advance pointer
		delete temp;
		temp = top_;
	}
	delete top_;
}

void AdjacencyList::add(Vertex& v, int jobtime)
{
	Node* temp1 = top_;
	Node* temp2 = temp1;

	if (temp1 == nullptr) //if there are no other items in the list
	{
		top_ = new Node(v, top_, jobtime);
	}
	else
	{
		while (temp1 != nullptr)
		{
			temp2 = temp1;
			temp1 = temp1->next_; //advance pointer to end of list
		}
		temp2->next_ = new Node(v, nullptr, jobtime);
	}
}

Vertex AdjacencyList::pop()
{
	Vertex vTemp;
	if (top_ != nullptr)
	{
		Node* temp = top_;
		top_ = top_->next_; //advances pointer
		vTemp = *temp->vertex;
		delete temp;
	}
	return vTemp;
}

Vertex AdjacencyList::top() const
{
	return *top_->vertex;
}

void AdjacencyList::print()
{
	Node* temp = top_;

	if (top_ == nullptr)
		cout << "No vertices in the AdjacencyList\n";
	else
	{
		cout << "Vertex " << setw(10) << right << "Project Time\n";
		while (temp != nullptr)
		{
			cout << setw(3) << left << temp->vertex->getVertexNum();
			cout << setw(7) << right << temp->getDuration() << endl;
			temp = temp->next_; //advance
		}
		cout << endl;
	}
}

bool AdjacencyList::remove(Vertex &v)
{
	Node* nodeToRemove = find(v);
	if (nodeToRemove != nullptr)
	{
		Node* nodeInFront = top_;

		if (top_->vertex->getVertexNum() == v.getVertexNum())
		{
			top_ = top_->next_;
			delete nodeInFront;
			return true;
		}

		while (nodeInFront != nullptr)
		{
			if (nodeInFront->next_->vertex->getVertexNum() != nodeToRemove->vertex->getVertexNum())
				nodeInFront = nodeInFront->next_; //advance pointer if vertexNum are not equal
			else
				break;
		}

		nodeInFront->next_ = nodeToRemove->next_;
		delete nodeToRemove;
		return true;
	}
	else
	{
		cerr << "vertex: " << v.getVertexNum() << " is not in the AdjacencyList\n";
		return false;
	}
}

Node* AdjacencyList::find(Vertex &v)
{
	Node* temp = top_;
	while (temp != nullptr)
	{
		if (temp->vertex->getVertexNum() == v.getVertexNum())
			break;
		else
			temp = temp->next_;
	}

	return temp;
}

bool AdjacencyList::removeLast()
{
	Node* nodeInFront = top_;
	Node* nodeToRemove = top_;

	while (nodeToRemove->next_ != nullptr)
	{
		nodeInFront = nodeToRemove;
		nodeToRemove = nodeToRemove->next_;
	}

	nodeInFront->next_ = nullptr;
	delete nodeToRemove;
	return true;
}
