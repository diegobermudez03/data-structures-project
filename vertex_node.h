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
        int index;
        int getPosition(float x1, float y1, float z1, float x2, float y2, float z2);
    public:
        VertexNode(std::vector<float>* vertex, int index, std::string object_name);
        ~VertexNode();
        std::vector<float>* getVertex();
        void addSon(VertexNode* node);
        VertexNode* searchNearest(float x, float y, float z);
};


#endif