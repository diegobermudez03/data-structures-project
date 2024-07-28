#ifndef __DATA_ORGANIZATION__H__
#define __DATA_ORGANIZATION__H__
#include <vector>
#include "object_3d.h"

class DataOrganization{
    protected:
        std::vector<Object3d>* objects = new std::vector<Object3d>;
    public:
        short load_file(std::string& file_name);
        ~DataOrganization();
};

#include "data_organization.cxx"
#endif