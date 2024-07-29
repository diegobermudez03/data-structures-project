#include <string>
#ifndef __OBJECT_3D__H__
#define __OBJECT_3D__H__
#include <list>

class Object3d{
    protected:
        std::string name;
        std::vector<std::vector<int>*>* vertices;
        std::list<std::vector<int>*>* faces;
    public:
        Object3d(std::string& name, std::vector<std::vector<int>*>* vertices, std::list<std::vector<int>*>* faces);
        ~Object3d();

};

#include "object_3d.cxx"
#endif