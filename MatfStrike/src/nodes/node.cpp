#include "nodes/node.h"
#include <algorithm>
#include <thread>

namespace mfe{


//static
std::mutex Node::globalNodeMutex;

Node::Node(const std::string & name, Node * parent)
	: mName(name), mParent(nullptr)
{
	setParent(parent);
//TODO  --> NOT REALLY
		//for (int i = 0; i < pNode->GetNodeAttributeCount(); i++){
		//	FbxNodeAttribute * attr = pNode->GetNodeAttributeByIndex(i);
		//	std::string typeName = GetAttributeTypeName(attr->GetAttributeType());
		//	if (typeName == "mesh"){
		//		FbxGeometryBase * mesh = (FbxMesh *)attr;
		//	}
		//}
}

void Node::deleteMe() { }

void Node::deleteMyChildren() { }

void Node::deleteMeAndMyChildren() { }

Node & Node::addChild(Node * child)
{
	child->setParent(this);
	return *this;
}

std::ostream & operator<<(std::ostream & o, const mfe::Node & node)
{
	o << "Node name: " << node.mName << " parent: " << node.mParent;
	o << " children: {";
	if (!node.mChildren.empty()){
		o << node.mChildren.front();
		for_each(++node.mChildren.cbegin(), node.mChildren.cend(),
			[&o](Node * n) {o << ", " << n->mName; });
	}
	return o << "}";
}

Node & Node::removeChild(Node * child)
{
	Node::NodesLock lock{this, child}; // first we lock them all

	if (child != this){
		child->mParent = 0;
		mChildren.erase(
			std::remove(mChildren.begin(), mChildren.end(), child), 
			mChildren.end() );
	}
	return *this;
}

Node & Node::setParent(Node * newParent)
{
	// Check if there is a loop and throw error
	// TODO: Wont work with recursive makeing of a node tree
	for(Node * n = this; n->mParent != nullptr; n = n->mParent)
		if (n == newParent)
			throw NodeCycleErr(this, this);

	Node::NodesLock lock{newParent, mParent, this}; // first we lock them all

	if (newParent != mParent) {
		try{ // add child to the Parent's vector of children
			if (newParent != 0)
				newParent->mChildren.push_back(this); 
		} catch (std::exception & ) { throw; }

		if (mParent != 0) { // then we remove the child from the old parent
			// cant just call removeChild() because we would need recursive mutex
			mParent->mChildren.erase( 
				std::remove( mParent->mChildren.begin(), mParent->mChildren.end(), this),
				mParent->mChildren.end() );
		}
		mParent = newParent; // finaly it's now safe to set the new parrent
	}

	return * this;
}

// friend funtions


// subclass functions


Node::NodesLock::~NodesLock()
{
	std::for_each(mNodeList.begin(), mNodeList.end(), [](Node * x) {x->mNodeMutex.unlock(); }); 
}

void Node::NodesLock::lock()
{
	// remove nullptrs from array since we need to dereference pointers
	mNodeList.erase(std::remove(mNodeList.begin(), mNodeList.end(), nullptr), mNodeList.end());

	while (true) {
		globalNodeMutex.lock(); //  global lock, then we lock all or nothing, this is to avoid dealock
		auto p = std::find_if_not(mNodeList.begin(), mNodeList.end(),
			[](Node * x) {return x->mNodeMutex.try_lock(); });
		if (p == mNodeList.end())
			break;

		std::for_each(mNodeList.begin(), p, [](Node * x) {x->mNodeMutex.unlock(); });
		globalNodeMutex.unlock();
		// we transfer the control to other threads in hopes they free the Nodes we want to lock
		std::this_thread::yield();
	}
	globalNodeMutex.unlock();
}

}
