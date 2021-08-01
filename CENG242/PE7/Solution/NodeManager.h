#ifndef __NODEMANAGER_H__
#define __NODEMANAGER_H__

#include "Node.h"
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////
// // // // // DO NOT CHANGE "PUBLIC PARTS" FILE! // // // // //
///////////////////////////////////////////////////////////////
class NodeManager {

private:
    vector<Node*> tree;     //every node
    vector<int> father;     //id of the father
    vector<int> index;      //where is the node

	// DO NOT MODIFY BELOW
public:
	// Contsructor : You can initialize your variables depending on your implementation
	NodeManager();

	// Destructor  : totally depends on your implementation
	// Note that it is responsible of destroying any tree (node) it contains
	~NodeManager();

	// It takes 2 integer such that
	//    - the first one is parent node id
	//    - the second one is child node id
	// If there does not exist any node with the given id(s), you should construct it (them) first in the type of Node.
	// Later, you should attach the given <parent-child> to the correct position in your collection
	// Note that the given nodes may already exist, yet their parent-child relationship is not constructed yet.
	// It is ensured that you are not given an existing relationship.
	void addRelation(int, int);

	// This converts the Node object whose id is given in the first argument into DataNode
	// Node whose id is given may not exist among the current trees!
	// However, if the node whose id is given exists, then it is ensured that its type is Node, not DataNode.
	// Whatever the case is, you are expected to create a new DataNode object.
	// It assigns the given char value in the second argument to the constructed DataNode object.
	// If there was a corresponding Node object previously, you are expected to destroy only that Node.
	// Apply the destruction carefully since there has been replaced a DataNode object at that position.
	// Do not forget to attach the new DataNode object into the position of the destroyed Node object!
	void setDataToNode(int, char);

	// It returns the reference for the node whose id is given in the argument
	// It should search the stated node among all the current trees
	// It is ensured that the node whose id is given exists.
	const Node& getNode(int);
};

#endif