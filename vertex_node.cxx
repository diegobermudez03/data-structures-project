#include "vertex_node.h"

#include <cmath>

#include "tuple2.h"
#include <iostream>

VertexNode::VertexNode(std::vector<float>* vertex, int index, short axis, std::string object_name){
    this->vertex = vertex;
    this->index = index;
    this->cut_axis = axis;
    this->object_name = object_name;
    this->right = nullptr;
    this->left = nullptr;
}

VertexNode::~VertexNode(){
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

    //if the cut axis value is lower than us, then it goes on our left
    if(vertex->at(this->cut_axis) < this->vertex->at(this->cut_axis)){
        if(this->left != nullptr) this->left->addSon(node);
        else{
            this->left = node;
            node->setCutAxis(next_cut_axis);
        }
    }
    //if it's higher than us, it goes on our right
    else{
        if(this->right != nullptr) this->right->addSon(node);
        else{
            this->right = node;
            node->setCutAxis(next_cut_axis);
        }
    }
}


//where the first value of the tuple is the vertex, and the second the distance between that vertex and the searching one
Tuple2<VertexNode*, float>* VertexNode::nearestVertex(std::vector<float>* searching, Tuple2<VertexNode*, float>* nearest_so_far){

    float distance = this->getDistance(searching, this->vertex);
    //if the nearest is null (first one), or if our distance is lower than the nearest one, then this is the new nearest
    if(nearest_so_far == nullptr || distance < nearest_so_far->getValue2()){
        if(nearest_so_far != nullptr) delete nearest_so_far;
        nearest_so_far = new Tuple2<VertexNode*, float>(this, distance);
    }

    VertexNode* subtree_to_search;
    VertexNode* opposite_tree;
    //if the searching vertex, regarding our cut axis, is higher than we are, then we now it's inside our right subtree
    if( searching->at(this->cut_axis) > this->vertex->at(this->cut_axis) ){
        subtree_to_search = this->right;
        opposite_tree = this->left;
    }
    else {
        subtree_to_search = this->left;
        opposite_tree = this->right;
    }

    //if the subtree to search is null, then we are the nearest vertex, so this is the base case
    if(subtree_to_search == nullptr){
        return nearest_so_far;
    }
    //the recursive case
    else{
        //we get the nearest vertex on the subtree of the area where the search vertex is in
        nearest_so_far = subtree_to_search->nearestVertex(searching, nearest_so_far);

        //if the found nearest vertex absolute distance from the searched vertex is higher than 
        //the distance from the vertex to the cut axis, means that, there exists the possibility
        //that in the other side could be a nearest vertex, so only in that case we also check the opposite subtree
        if(nearest_so_far->getValue2() > abs(searching->at(this->cut_axis) - this->vertex->at(this->cut_axis)))
        {
            if(opposite_tree != nullptr) nearest_so_far = opposite_tree->nearestVertex(searching, nearest_so_far);
        }
        return nearest_so_far;
    }
}

float VertexNode::getDistance(std::vector<float>* vertex1,std::vector<float>* vertex2){

    float x_value = (vertex1->at(0)-vertex2->at(0)) * (vertex1->at(0)-vertex2->at(0));
    float y_value = (vertex1->at(1)-vertex2->at(1)) * (vertex1->at(1)-vertex2->at(1));
    float z_value = (vertex1->at(2)-vertex2->at(2)) * (vertex1->at(2)-vertex2->at(2));

    return sqrt(x_value+y_value+z_value);
}

int VertexNode::getIndex(){
    return this->index;
}

std::string VertexNode::getObjectName(){
    return this->object_name;
}