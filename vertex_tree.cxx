#include "vertex_tree.h"

VertexTree::VertexTree(){}

VertexTree::~VertexTree(){}


void VertexTree::addSon(std::vector<float>* vertex, int index, std::string object_name){
    VertexNode* node = new VertexNode(vertex, index, object_name);

    if(this->root == nullptr){
        this->root = node;
    }
    else{
        this->root->addSon(node);
    }
}

VertexNode* VertexTree::searchNearest(float x, float y, float z){
    if(this->root == nullptr) return nullptr;
    else{
        return this->root->searchNearest(x, y, z);
    }
}
