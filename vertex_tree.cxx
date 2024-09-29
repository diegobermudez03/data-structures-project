#include "vertex_tree.h"

#include "tuple.h"

VertexTree::VertexTree(){}

VertexTree::~VertexTree(){}


void VertexTree::addSon(std::vector<float>* vertex, int index, std::string object_name){
    VertexNode* node = new VertexNode(vertex, index, 0, object_name);

    if(this->root == nullptr){
        this->root = node;
    }
    else{
        this->root->addSon(node);
    }
}

Tuple<VertexNode*, float>* VertexTree::searchNearest(float x, float y, float z){
    if(this->root == nullptr) return nullptr;

    std::vector<float>* searched_vertex = new std::vector<float>;
    searched_vertex->push_back(x);
    searched_vertex->push_back(y);
    searched_vertex->push_back(z);

    Tuple<VertexNode*, float>* nearest =  this->root->nearestVertex(searched_vertex, nullptr);

    delete searched_vertex;
    return nearest;
}
