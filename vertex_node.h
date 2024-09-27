#ifndef __VERTEX_NODE_H__
#define __VERTEX_NODE_H__

#include <vector>

//  FRONT
//  __________________
//  |       |       |
//  |   0   |    1  |
//  |       |       |
//  -----------------
//  |       |       |
//  |   2   |   4   |
//  |       |       |
//  -----------------


//  BACK
//  __________________
//  |       |       |
//  |   5   |    6  |
//  |       |       |
//  -----------------
//  |       |       |
//  |   7   |   8   |
//  |       |       |
//  -----------------

class VertexNode{
    protected:
        std::vector<VertexNode*> sons;
        std::vector<float>  vertex; //x, y, z
    public:
        VertexNode();
        ~VertexNode();
        void addSon(VertexNode* son);
};


#endif