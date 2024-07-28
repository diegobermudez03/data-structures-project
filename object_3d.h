#include <string>
#ifndef __OBJECT_3D__H__
#define __OBJECT_3D__H__

class Object3d{
    protected:
        std::string name;
        std::vector<int[]> vertices;
    public:
        Object3d(std::string name, std::vector<int[]> vertices);
        ~Object3d();

};

#include "object_3d.hxx"
#endif