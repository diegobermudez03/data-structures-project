#include "vertex_tree.h"

VertexTree::VertexTree(){}

VertexTree::~VertexTree(){}


void VertexTree::addSon(VertexNode* node){
    if(this->root == nullptr){
        this->root = node;
    }
    else{
        this->root->addSon(node);
    }
}
