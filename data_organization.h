#ifndef __DATA_ORGANIZATION__H__
#define __DATA_ORGANIZATION__H__
#include <vector>
#include <deque>
#include <unordered_map>
#include "object_3d.h"
#include "tuple2.h"
#include "tuple3.h"
#include "vertex_node.h"

class DataOrganization{
    protected:
        std::unordered_map<std::string, Object3d*>* objects = new std::unordered_map<std::string, Object3d*>;
        void get_points(Object3d* object, float& x_max, float& x_min, float& y_max, float& y_min, float& z_max, float& z_min, bool first);
    public:
        short load_file(std::string& file_name, std::list<std::vector<std::string>*>& result);
        std::vector<Object3d*>* get_objects();
        std::string envolvente(std::string object_name);
        bool descargar(std::string object_name);
        bool guardar(std::string object_name, std::string file_name);
        Tuple2<VertexNode*, float>* cercano(float vx, float vy, float vz,std::string& object_name);
        std::vector<Tuple3<std::vector<float>*, VertexNode*, float>*>* cercanosCaja(std::string& object_name);
        bool checkExistance(std::string object_name);
        Tuple2<std::deque<int>*, double>* rutaCorta(int i1, int i2, std::string object_name);
        Tuple3<std::deque<int>*, double, Tuple3<double, double, double>*>* rutaCortaCentro(int index, std::string object_name);
        float DataOrganization::getDistance(std::vector<float>* vertex1,std::vector<float>* vertex2);
        ~DataOrganization();
};

#endif