#include "data_organization.h"
#include <fstream>
#include <vector>
#include <iostream>

short DataOrganization::load_file(std::string& file_name){
    std::ifstream file(file_name);
    if(!file.is_open()) return 1;
    try{
        while(!file.eof()){
            //gets the name of the object
            std::string object_name;
            file >> object_name;
            if(this->exists(object_name)) return 2;
            int vertex_count;
            file >> vertex_count;
            //creates a vector for the vertices, allocating the size we already know will be
            std::vector<std::vector<int>*>* vertices = new std::vector<std::vector<int>*>;
            vertices->reserve(vertex_count);
            for(int i = 0; i < vertex_count; i++){
                int x, y, z;
                file >> x;
                file >> y;
                file >> z;
                //creates a vector with a size of 3, it allocates the 3 axis of each vertex
                std::vector<int>* vertex = new std::vector<int>(3);
                vertex->push_back(x);
                vertex->push_back(y);
                vertex->push_back(z);
                vertices->push_back(vertex);
            }
            std::list<std::vector<int>*>* faces = new std::list<std::vector<int>*>;
            while(true){
                int n;
                file >> n;
                if(n == -1) break;
                if(file.eof()) return 0;
                std::vector<int>* face = new std::vector<int>;
                face->reserve(n);
                for(int i = 0; i < n; i++){
                    int aux;
                    file >> aux;
                    face->push_back(aux);
                }
                faces->push_back(face);
            }
            this->objects->push_back(new Object3d(object_name, vertices, faces));
        }
        file.close();
        return 3;
    }catch(const std::exception& e){
        file.close();
        return 0;
    }
}

bool DataOrganization::exists(std::string& object_name){
    std::vector<Object3d*>::iterator it = this->objects->begin();
    for(; it != this->objects->end(); ++it){
        if((*it)->get_name() == object_name) return true;
    }
    return false;
}

std::vector<Object3d*>* DataOrganization::get_objects(){
    return this->objects;
}