#include "Node.h"

// // // THE FRIEND METHODS ARE ALREADY IMPLEMENTED. // // //
// // // // // // // DO NOT CHANGE THEM! // // // // // // //

Node::Node(int id):id(id) {
}

Node::~Node() {
    for(unsigned int i=0;i<children.size();i++)delete children[i];
}

bool check_node(Node* node){
    try{node->getData();}
    catch(...){
        return false;       //false means normal npde
    }
    return true;        //means datanode
}

Node::Node(const Node& node) {
	id=node.id;
	for(unsigned int i=0;i<node.children.size();i++){
	    if(check_node(node.children[i]))
	        children.push_back(new DataNode(*(DataNode*)node.children[i]));
	    else
	        children.push_back(new Node(*node.children[i]));
	}
}

int Node::getId() const {
	return id;
}

char Node::getData() const {
	throw InvalidRequest();
}

vector<Node*>& Node::getChildren() {
	return children;
}

void Node::operator+=(Node& childNode) {
	children.push_back(&childNode);
}

Node* Node::operator&(const Node& node) const {
	// TODO
	try{
	    getData();
	}
	catch(InvalidRequest a){
	    try{
	        node.getData();
	    }
	    catch(InvalidRequest a){
	        return new Node(this->id);
	    }
	    return new DataNode(node.id,node.getData());
	}
	return new DataNode(this->id,this->getData());
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const Node& node) {
	try {
		node.getData();
		os << *(DataNode*)&node;
	}
	catch (InvalidRequest e) {
		os << "[" << node.id;
		for (int i = 0; i < node.children.size(); i++)
			os << ", " << *node.children[i];
		os << "]";
	}
	return os;
}

/*************** DataNode *****************/

DataNode::DataNode(int id, char data):Node(id),data(data) {
}

DataNode::~DataNode() {
}

DataNode::DataNode(const DataNode& dataNode):Node(dataNode),data(dataNode.data) {
}

DataNode::DataNode(const Node& node, char data):Node(node),data(data) {
}

char DataNode::getData() const {
	return data;
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const DataNode& dataNode) {
	os << "[" << "(" << dataNode.id << ", \'" << dataNode.data << "\')";
	for (int i = 0; i < dataNode.children.size(); i++)
		os << ", " << *dataNode.children[i];
	os << "]";
	return os;
}
