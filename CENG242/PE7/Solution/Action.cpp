#include "Action.h"
#include "Exception.h"

bool check_node(const Node* node){
    try{
	    node->getData();
	}
	catch(InvalidRequest a){
	    return false;
	}
	return true;
}

Action::Action() {
	// TODO
}

Action::~Action() {
	// TODO
}

/********************** CompleteAction **************************/

CompleteAction::CompleteAction(const Node& node) {
    mynode=(Node*)&node;
}

CompleteAction::~CompleteAction() {
    delete mynode;
}

Node* act_helper_complete(const Node *mynode,const Node* node){
    Node *res=*mynode&*node;
	
	vector<Node*>& vec1=((Node*)mynode)->getChildren();
	vector<Node*>& vec2=((Node*)node)->getChildren();
	vector<Node*>& vec3=res->getChildren();
	for(int i=0;i<vec1.size();i++){
	    for(int k=0;k<vec2.size();k++){
	        if(vec1[i]->getId()==vec2[k]->getId()){
	            vec3.push_back(act_helper_complete(vec1[i],vec2[k]));
	            break;
	        }
	    }
	}
	
	//TODO
	return res;
}

Node* CompleteAction::act(const Node* node) const {
    return act_helper_complete(mynode,node);
}

/************************* CutAction ***************************/

CutAction::CutAction(char character) :c(character){
}

CutAction::~CutAction() {
}

bool derived_checker(Node* node){
    try{
        node->getData();
    }
    catch(InvalidRequest a){return false;}
    return true;
}

void acthelp(Node* &res,char c){
    vector<Node*>& vec=res->getChildren();
	int count=0;
	for(int i=0;count<2&&i<vec.size();i++){
	    acthelp(vec[i],c);
	    if(derived_checker(vec[i])&&vec[i]->getData()==c)count++;
	    
	    vector<Node*>& vec2=vec[i]->getChildren();
	    for(int i=0;count<2&&i<vec2.size();i++){
	        if(derived_checker(vec2[i])&&vec2[i]->getData()==c)count++;
	    }
	}
	
	if(count>=2){
	    DataNode *next=new DataNode(res->getId(),c);
	    delete res;
	    res=next;
	}
}

Node* CutAction::act(const Node* node) const {
	// TODO
	Node* res=new Node(*node); 
	acthelp(res,c);
	return res;
}

/************************* CompositeAction ***************************/

CompositeAction::CompositeAction() {
	// TODO
}

CompositeAction::~CompositeAction() {
	// TODO
}

CompositeAction* CompositeAction::addAction(const Action* action) {
	// TODO
	ACT_X.push_back(action);
	return this;
}

Node* CompositeAction::act(const Node* node) const {
	// TODO
	Node* node1=new Node(*node),*node2=NULL;
	for(int i=0;i<ACT_X.size();i++){
	    node2=node1;
	    node1=ACT_X[i]->act(node2);
	    delete node2;
	}
	return node1;
}