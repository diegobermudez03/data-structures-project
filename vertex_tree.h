#ifndef __VERTEX_TREE_H__
#define __VERTEX_TREE_H__

#include "vertex_node.h"
#include "tuple2.h"

class VertexTree{
    protected:
        VertexNode* root;
    public:
        VertexTree();
        ~VertexTree();
        void addSon(std::vector<float>* vertex, int index, std::string object_name);
        Tuple2<VertexNode*, float>* searchNearest(float x, float y, float z);
};


#endif