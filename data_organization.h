#ifndef __DATA_ORGANIZATION__H__
#define __DATA_ORGANIZATION__H__
#include <vector>
#include "object_3d.h"

class DataOrganization{
    protected:
        std::vector<Object3d*>* objects = new std::vector<Object3d*>;
        bool exists(std::string& object_name);
    public:
        short load_file(std::string& file_name);
        std::vector<Object3d*>* get_objects();
        ~DataOrganization();
};

#include "data_organization.cxx"
#endif