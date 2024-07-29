#include "object_3d.h"
#include <vector>

Object3d::Object3d(std::string& name, std::vector<std::vector<int>*>* vertices, std::list<std::vector<int>*>* faces){
    this->name = name;
    this->vertices = vertices;
    this->faces = faces;

    this->lines = new std::unordered_map<int, std::unordered_set<int>*>;
    std::list<std::vector<int>*>::iterator it = faces->begin();
    for(;it != faces->end(); ++it){
        std::vector<int>::iterator inside_it = (*it)->begin();
        int previous;
        bool first = true;
        for(; inside_it != (*it)->end(); ++inside_it){
            if(!first){
                if(previous < *inside_it) add_line(previous, *inside_it);
                else add_line(*inside_it, previous);
            }else{
                first = false;
                if(*inside_it < *((*it)->end()-1)) add_line(*inside_it, *((*it)->end()-1));
                else add_line(*((*it)->end()-1), *inside_it);
            }
            previous = *inside_it;
        }
    }
}

std::string Object3d::get_name(){
    return this->name;
}

int Object3d::get_count_vertices(){
    return this->vertices->size();
}

int Object3d::get_count_faces(){
    return this->faces->size();
}

int Object3d::get_count_lines(){
    std::unordered_map<int, std::unordered_set<int>*>::iterator it = this->lines->begin();
    int counter = 0;
    for(; it != this->lines->end(); ++it){
        counter += it->second->size();
        /*std::cout << "\n Vertex " << it->first << " connects with : ";
        std::unordered_set<int>::iterator it2 = it->second->begin();
        for(;it2 != it->second->end(); ++it2){
            std::cout << " ** " << *it2;
        }
        std::cout << "\n";*/
    }
    return counter;
}


void Object3d::add_line(int key, int value){
    if(this->lines->find(key) == this->lines->end()){
        (*this->lines)[key] = new std::unordered_set<int>;
    }
    std::unordered_set<int>* set = (*this->lines)[key];
    set->insert(value);
}