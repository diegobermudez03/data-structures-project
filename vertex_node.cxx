#include "vertex_node.h"

#include <cmath>

VertexNode::VertexNode(std::vector<float>* vertex, int index, short axis, std::string object_name){
    this->vertex = vertex;
    this->index = index;
    this->cut_axis = axis;
    this->object_name = object_name;
}

VertexNode::~VertexNode(){
    delete this->vertex;
    delete this->left;
    delete this->right;
}

std::vector<float>* VertexNode::getVertex(){
    return this->vertex;
}

void VertexNode::setCutAxis(short axis){
    this->cut_axis = axis;
}


void VertexNode::addSon(VertexNode* node){
    std::vector<float>* vertex = node->getVertex();
    int next_cut_axis = cut_axis+1;
    if(next_cut_axis > 2) next_cut_axis = 0;    
    if((*vertex)[this->cut_axis] < this->vertex->at(this->cut_axis)){
        if(this->left == nullptr){
            this->left->addSon(node);
        }
        else{
            this->left = node;
            node->setCutAxis(next_cut_axis);
        }
    }else{
        if(this->right == nullptr){
            this->right->addSon(node);
        }
        else{
            this->right = node;
            node->setCutAxis(next_cut_axis);
        }
    }
}
