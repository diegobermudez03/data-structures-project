#ifndef __VERTEX_NODE_H__
#define __VERTEX_NODE_H__

#include <vector>
#include <string>
#include "tuple2.h"


class VertexNode{
    protected:
        VertexNode* left;
        VertexNode* right;
        std::vector<float>* vertex; //x, y, z
        std::string object_name;
        int cut_axis;   //0 = x, 1 = y, 2 = z
        int index;

        float getDistance(std::vector<float>* vertex1,std::vector<float>* vertex2);
    public:
        VertexNode(std::vector<float>* vertex, int index, short axis, std::string object_name);
        ~VertexNode();
        int getIndex();
        std::vector<float>* getVertex();
        void addSon(VertexNode* node);
        void setCutAxis(short axis);
        std::string getObjectName();
        Tuple2<VertexNode*, float>* nearestVertex(std::vector<float>* searching, Tuple2<VertexNode*, float>* nearest_so_far);
};


#endif