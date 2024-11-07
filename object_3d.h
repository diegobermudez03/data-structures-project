#include <string>
#ifndef __OBJECT_3D__H__
#define __OBJECT_3D__H__
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Object3d{
    protected:
        std::string name;
        std::vector<std::vector<float>*>* vertices;
        std::list<std::vector<int>*>* faces;
        std::unordered_map<int, std::unordered_set<int>*>* lines; 
        void add_line(int key, int value);
    public:
        Object3d(std::string& name, std::vector<std::vector<float>*>* vertices, std::list<std::vector<int>*>* faces);
        std::string get_name();
        int get_count_lines();
        int get_count_faces();
        int get_count_vertices();
        std::list<std::vector<int>*>* get_faces();
        std::vector<std::vector<float>*>* get_vertices();
        std::unordered_set<int>* get_neighbors_of(int index);
        std::unordered_set<int>* get_lines_of(int index);
        Tuple3<float, float, float>* getVertexCentro();
        ~Object3d();

};

#endif