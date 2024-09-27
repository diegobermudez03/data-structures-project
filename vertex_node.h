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
        VertexNode* left;
        VertexNode* right;
        std::vector<float>* vertex; //x, y, z
        std::string object_name;
        int cut_axis;   //0 = x, 1 = y, 2 = z
        int index;
    public:
        VertexNode(std::vector<float>* vertex, int index, short axis, std::string object_name);
        ~VertexNode();
        std::vector<float>* getVertex();
        void addSon(VertexNode* node);
        void setCutAxis(short axis);
};


#endif