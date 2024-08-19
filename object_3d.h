#include <string>
#ifndef __OBJECT_3D__H__
#define __OBJECT_3D__H__
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <vector>

class Object3d{
    protected:
        std::string name;
        std::vector<std::deque<int>> vertices;
        std::list<std::vector<int>> faces;
        std::unordered_map<int, std::unordered_set<int>> lines; 
        void add_line(int key, int value);
    public:
        Object3d();
        void assignAttr(std::string& name, std::vector<std::deque<int>>& vertices, std::list<std::vector<int>>& faces);
        std::string get_name();
        int get_count_lines();
        int get_count_faces();
        int get_count_vertices();
        std::list<std::vector<int>> get_faces();
        std::vector<std::deque<int>> get_vertices();
        ~Object3d();

};

#endif