#include "vertex_node.h"

VertexNode::VertexNode(float x, float y, float z){
    this->vertex->push_back(x);
    this->vertex->push_back(y);
    this->vertex->push_back(z);

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

void VertexNode::addSon(VertexNode* node){
    short side[] = {1,1,1,1,1,1,1};
    short x, y, z;
    std::vector<float>* vertex = node->getVertex();

    //after this filter, only the correct index where the node goes wil remain in
    if((*vertex)[0] > (*this->vertex)[0]){
        side[0] = 0; side[3] = 0; side[4] = 0; side[7] = 0;
    }
    else{
        side[1] = 0; side[2] = 0; side[5] = 0; side[6] = 0;
    }
    if((*vertex)[1] > (*this->vertex)[1]){
        side[2] = 0; side[3] = 0; side[6] = 0; side[7] = 0;
    }
    else{
        side[0] = 0; side[1] = 0; side[4] = 0; side[5] = 0;
    }
    if((*vertex)[2] > (*this->vertex)[2]){
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

    //base case, we insert the son
    if(this->sons->at(index_counter) == nullptr){
        (*this->sons)[index_counter] = node;
    }
    else{
        //recursive case, we send it to our selected son
        this->sons->at(index_counter)->addSon(node);
    }
   


}