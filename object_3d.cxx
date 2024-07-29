#include "object_3d.h"
#include <vector>

Object3d::Object3d(std::string& name, std::vector<std::vector<int>*>* vertices, std::list<std::vector<int>*>* faces){
    this->name = name;
    this->vertices = vertices;
    this->faces = faces;
}