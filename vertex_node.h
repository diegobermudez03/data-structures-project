#ifndef __VERTEX_NODE_H__
#define __VERTEX_NODE_H__

#include <vector>
#include <string>

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
        std::vector<VertexNode*>* sons;
        std::vector<float>* vertex; //x, y, z
        std::string object_name;
    public:
        VertexNode(float x, float y, float z);
        ~VertexNode();
        std::vector<float>* getVertex();
        void addSon(VertexNode* node);
};


#endif