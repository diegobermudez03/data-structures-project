#ifndef __DATA_ORGANIZATION__H__
#define __DATA_ORGANIZATION__H__
#include <vector>
#include <unordered_map>
#include "object_3d.h"

class DataOrganization{
    protected:
        std::unordered_map<std::string, Object3d*>* objects = new std::unordered_map<std::string, Object3d*>;
        void get_points(Object3d* object, int& x_max, int& x_min, int& y_max, int& y_min, int& z_max, int& z_min, bool first);
    public:
        short load_file(std::string& file_name, std::list<std::vector<std::string>*>& result);
        std::vector<Object3d*>* get_objects();
        std::string envolvente(std::string object_name);
        bool descargar(std::string object_name);
        bool guardar(std::string object_name, std::string file_name);
        std::vector<float>* cercano(float vx, float vy, float vz,std::string& object_name, int& index, float& distance);
        ~DataOrganization();
};

#endif