#ifndef __VERTEX_TREE_H__
#define __VERTEX_TREE_H__

#include "vertex_node.h"

class VertexTree{
    protected:
        VertexNode* root;
    public:
        VertexTree();
        void addSon(std::vector<float>* vertex, int index, std::string object_name);
        VertexNode* searchNearest(float x, float y, float z);
};


#endif