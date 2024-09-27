#include "vertex_node.h"

VertexNode::VertexNode(std::vector<float>* vertex, int index, std::string object_name){
    this->vertex = vertex;
    this->index = index;
    this->object_name = object_name;
    this->sons->resize(8);
}

VertexNode::~VertexNode(){
    delete this->vertex;
    std::vector<VertexNode*>::iterator it = this->sons->begin();
    for(; it != this->sons->end(); ++it){
        delete *it;
    }
    delete this->sons;
}

std::vector<float>* VertexNode::getVertex(){
    return this->vertex;
}


int VertexNode::getPosition(float x1, float y1, float z1, float x2, float y2, float z2){
    short side[] = {1,1,1,1,1,1,1};

    //after this filter, only the correct index where the node goes wil remain in
    if(x2 > x1){
        side[0] = 0; side[3] = 0; side[4] = 0; side[7] = 0;
    }
    else{
        side[1] = 0; side[2] = 0; side[5] = 0; side[6] = 0;
    }
    if(y2 > y1){
        side[2] = 0; side[3] = 0; side[6] = 0; side[7] = 0;
    }
    else{
        side[0] = 0; side[1] = 0; side[4] = 0; side[5] = 0;
    }
    if(z2 > z1){
        side[4] = 0; side[5] = 0; side[6] = 0; side[7] = 0;
    }
    else{
        side[0] = 0; side[1] = 0; side[2] = 0; side[3] = 0;
    }

    //get the index of the side
    int index_counter = 0;
    for(; index_counter < 8; index_counter++){
        if(side[index_counter] == 1) break;
    }
    return index_counter;
}

void VertexNode::addSon(VertexNode* node){
    std::vector<float>* vertex = node->getVertex();

    int index_counter = this->getPosition((*this->vertex)[0], (*this->vertex)[1], (*this->vertex)[2], (*vertex)[0],(*vertex)[1],(*vertex)[2]);
    //base case, we insert the son
    if(this->sons->at(index_counter) == nullptr){
        (*this->sons)[index_counter] = node;
    }
    else{
        //recursive case, we send it to our selected son
        this->sons->at(index_counter)->addSon(node);
    }
}

VertexNode* VertexNode::searchNearest(float x, float y, float z){
     int index_counter = this->getPosition((*this->vertex)[0], (*this->vertex)[1], (*this->vertex)[2], x, y, z);

     if(this->sons->at(index_counter) == nullptr){
        return this;
     }
     else{
        return this->sons->at(index_counter)->searchNearest(x, y, z);
     }
}