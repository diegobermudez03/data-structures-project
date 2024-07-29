#include "data_organization.h"
#include <fstream>
#include <vector>

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
            if(this->exists(object_name)) return 2; //if the object already exists, we return the code 2
            int vertex_count;
            file >> vertex_count;
            //creates a vector for the vertices, reserving the size we already know will be
            std::vector<std::vector<int>*>* vertices = new std::vector<std::vector<int>*>;
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
                std::vector<int>* vertex = new std::vector<int>(3);
                vertex->push_back(x);
                vertex->push_back(y);
                vertex->push_back(z);
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
            this->objects->push_back(new Object3d(object_name, vertices, faces));
        }
        file.close();
        return 3;
    }catch(const std::exception& e){
        file.close();
        return 0;
    }
}

//simply a function to check if an object already exists with the given name
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