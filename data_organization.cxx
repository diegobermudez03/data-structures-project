#include "data_organization.h"
#include <fstream>
#include <vector>
#include <deque>

short DataOrganization::load_file(std::string& file_name, std::string& object_name){
    //codes :
    //  0   Archivo vacio o incompleto
    //  1   Archivo no existe
    //  2   Objeto ya existe
    //  3   Resultado exitoso
    std::ifstream file(file_name);
    if(!file.is_open()) return 1;   //if there's no file, then  we return code 1
    try{
        //we will iterate until we reach the end of the file
        while(!file.eof()){
            //gets the name of the object
            file >> object_name;
            if(this->objects->find(object_name) != this->objects->end()) return 2; //if the object already exists, we return the code 2
            int vertex_count;
            file >> vertex_count;
            //creates a vector for the vertices, reserving the size we already know will be
            std::vector<std::deque<int>*>* vertices = new std::vector<std::deque<int>*>;
            vertices->reserve(vertex_count);
            //we iterate over the amount of vertex we already know will be
            for(int i = 0; i < vertex_count; i++){
                //we read the 3 axis of each vertex
                if(file.eof()) return 0;
                int x, y, z;
                file >> x;
                file >> y;
                file >> z;
                //creates a vector with a size of 3, it allocates the 3 axis of each vertex
                std::deque<int>* vertex = new std::deque<int>;
                vertex->push_front(x);
                vertex->push_front(y);
                vertex->push_front(z);
                vertices->push_back(vertex);
            }
            //we create a list of vector (the axis) for the faces, the number of faces is unknown
            std::list<std::vector<int>*>* faces = new std::list<std::vector<int>*>;
            while(true){
                //while true, unless we reach -1 indicating the end, or if we reach the eof, without finding the -1, that indicates something is wrong with the file, so code 0
                int n;
                file >> n;
                if(n == -1) break;
                if(file.eof()) return 0;
                //we create a vector for each face, reserving the n posotions we already know there are (number of vertex)
                std::vector<int>* face = new std::vector<int>;
                face->reserve(n);
                for(int i = 0; i < n; i++){
                    //we simply iterate over those vertex and we push them into the face
                    int aux;
                    file >> aux;
                    face->push_back(aux);
                }
                //once we end with that face, we push the face into the faces list
                faces->push_back(face);
            }
            //once we reach this part, we have read all the file succesfully, so we push  a new 3D object into our Objects list
            (*this->objects)[object_name] = new Object3d(object_name, vertices, faces);
        }
        file.close();
        return 3;
    }catch(const std::exception& e){
        file.close();
        return 0;
    }
}


std::vector<Object3d*>* DataOrganization::get_objects(){
    std::vector<Object3d*>* objects = new std::vector<Object3d*>;
    objects->reserve(this->objects->size());
    std::unordered_map<std::string, Object3d*>::iterator it = this->objects->begin();
    for(; it != this->objects->end(); ++it){
        objects->push_back(it->second);
    }
    return objects;
}

std::string DataOrganization::envolvente(std::string object_name){
    int x_max, x_min, y_max, y_min, z_max, z_min;
    if(object_name.empty()){
        std::unordered_map<std::string, Object3d*>::iterator it = this->objects->begin();
        bool first = true;
        for(; it != this->objects->end(); ++it){
            this->get_points(it->second, x_max, x_min,  y_max, y_min, z_max, x_min, first);
            if(first) first = false;
        }
    }
    else{
        if(this->objects->find(object_name) == this->objects->end()) return "";
        Object3d* object = this->objects->find(object_name)->second;
        int x_max, x_min, y_max, y_min, z_max, z_min;
        this->get_points(object, x_max, x_min, y_max, y_min, z_max, z_min, true);
    }

    std::vector<std::deque<int>*>* vertices = new std::vector<std::deque<int>*>;
    for(int i = 0; i < 8; i++){
        std::deque<int>* vertex = new std::deque<int>;
        int x_n, y_n, z_n;
        if(i < 4) x_n = x_max;
        else x_n = x_min;
        if(i < 2 ||  (i >3 && i < 6)) y_n = y_max;
        else y_n = y_min;
        if(i % 2 == 0) z_n = z_max;
        else z_n = z_min; 

        vertex->push_front(x_n);
        vertex->push_front(y_n);
        vertex->push_front(z_n);
        vertices->push_back(vertex);
    }
    std::list<std::vector<int>*>* faces = new std::list<std::vector<int>*>;
    for(int i = 0; i < 6;i++){
        int i1, i2, i3, i4;
        switch(i){
            case 0: i1 = 0, i2 = 1, i3 = 3, i4 = 2;break;
            case 1: i1 = 0, i2 = 4, i3 = 6, i4 = 2; break;
            case 2: i1 = 1, i2 = 3, i3 = 7, i4 = 5; break;
            case 3: i1 = 3, i2 = 2, i3 = 6, i4 = 7; break;
            case 4: i1 = 1, i2 = 5, i3 = 4, i4 = 0; break;
            case 5: i1 = 7, i2 = 6, i3 = 4, i4 = 5; break;
        }
        std::vector<int>* face = new std::vector<int>;
        face->push_back(i1);
        face->push_back(i2);
        face->push_back(i3);
        face->push_back(i4);

        faces->push_back(face);
    }
    std::string new_object_name = object_name.empty() ? "env_global": "env_" + object_name;
    (*this->objects)[new_object_name] = new Object3d(new_object_name, vertices, faces);
    return new_object_name;

}

void DataOrganization::get_points(Object3d* object, int& x_max, int& x_min, int& y_max, int& y_min, int& z_max, int& z_min, bool first){
    std::vector<std::deque<int>*>* vertices = object->get_vertices();
    std::vector<std::deque<int>*>::iterator it = vertices->begin();
    for(; it != vertices->end(); ++it){
        int x = (*it)->at(0);
        int y = (*it)->at(1);
        int z = (*it)->at(2);
        if(first){
             x_max = x;
             x_min = x_max;
             y_max = y;
             y_min = y_max;
             z_max = z;
             z_min = z_max;
        }else{
             if(x > x_max) x_max = x;
             if(x < x_min) x_min = x;
             if(y > y_max) y_max = y;
             if(y < y_min) y_min = y;
             if(z > z_max) z_max = z;
             if(z < z_min) z_min = z;
        }
    }
}

bool DataOrganization::descargar(std::string object_name){
    if(this->objects->find(object_name) == this->objects->end()) return false;
    Object3d* object = (this->objects->find(object_name))->second;
    this->objects->erase(object_name);
    delete object;
    return true;
}