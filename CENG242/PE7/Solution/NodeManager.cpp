
#include "NodeManager.h"

NodeManager::NodeManager() {
}

NodeManager::~NodeManager() {
	for(int i=0;i<tree.size();i++){
	    tree[i]->getChildren().clear();
	    delete tree[i];
	}
}

void NodeManager::addRelation(int parent, int child) {
	//Node *P=NULL,*C=NULL;
	int m=parent;
	if(child>m)m=child;
	if(father.size()<m+1){
	    father.resize(m+1,-1);
	    index.resize(m+1,-1);
	}
	father[child]=parent;
	
	if(index[child]==-1){
	    index[child]=tree.size();
	    tree.push_back(new Node(child));
	}
	if(index[parent]==-1){
	    index[parent]=tree.size();
	    tree.push_back(new Node(parent));
	}
	*tree[index[parent]]+=*tree[index[child]];
}





void NodeManager::setDataToNode(int id, char data) {
	// TODO
	if(index.size()<id+1){
	    father.resize(id+1,-1);
	    index.resize(id+1,-1);
	}
	if(index[id]==-1){
	    index[id]=tree.size();
	    tree.push_back(new DataNode(id,data));
	    return;
	}
	
	
	Node *current=tree[index[id]];
	DataNode *next=new DataNode(id,data);
	tree[index[id]]=next;           //changing tree pointer
	
	vector<Node*>& vecOld=current->getChildren();
	vector<Node*>& vecNew=next->getChildren();
	for(int i=0;i<vecOld.size();i++)vecNew.push_back(vecOld[i]);    //adding children
	vecOld.clear();     //clear to make sure not to delete pointers
	
	if(father[id]!=-1){
	    vector<Node*>& vec=tree[index[father[id]]]->getChildren();
	    for(int i=0;i<vec.size();i++){
	        if(vec[i]->getId()==id){
	            vec[i]=next;            //changing father's pointer
	            break;
	        }
	    }
	}
	delete current;
}

const Node& NodeManager::getNode(int id) {
	return *tree[index[id]];
}