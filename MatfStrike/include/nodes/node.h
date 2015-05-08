#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <mutex>
#include <initializer_list>
#include <algorithm>

namespace mfe {


	//#include <cstdint>
	//typedef uint32_t nodeid;

	class Node
	{
	public:
		Node(const std::string & name, Node * parent = 0);

		//TODO
			void deleteMe();
			void deleteMyChildren();
			void deleteMeAndMyChildren();

		const std::vector<Node *> & children() const { return mChildren; };
		Node & addChild(Node * child);
		Node & removeChild(Node * child);
		const Node * parent() const { return mParent; }
		Node & setParent(Node * parent);
		const std::string & name() const { return mName; } ;
		Node & setName(const std::string & newName) { mName = newName; return *this; };

		friend std::ostream & operator<<(std::ostream & o, const Node & node);

	protected:
		std::string mName;
		Node * mParent;
		std::vector<Node *> mChildren;

	private:
		static std::mutex globalNodeMutex;
		std::mutex mNodeMutex;

		// SUBCLASSES

		struct NodesLock
		{
			NodesLock(std::initializer_list<Node *> nodeList) : mNodeList(nodeList) { lock(); }
			NodesLock(std::vector<Node *> nodeList) : mNodeList(nodeList) { lock(); }
			~NodesLock();
			void lock();
		private:
			std::vector<Node *> mNodeList;
		};

	};


	// errors
	struct NodeCycleErr  // Parent -> children hichery of Nodes can't make a loop  
	{
		NodeCycleErr(Node * parent, Node * child) 
			: mParent(parent), mChild(child) {} // ne znam zasto sam morao eksplicitno da pravim konstruktor
		Node * mParent;
		Node * mChild;
	};
}