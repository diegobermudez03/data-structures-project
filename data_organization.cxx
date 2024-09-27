#include "data_organization.h"
#include <fstream>
#include <vector>
#include <deque>

short DataOrganization::load_file(std::string& file_name, std::list<std::vector<std::string>*>& result){
    //codes :
    //  0   Archivo vacio o incompleto
    //  1   Archivo no existe
    //  2   Objeto ya existe
    //  3   Resultado exitoso
    std::ifstream file(file_name);
    if(!file.is_open()) return 1;   //if there's no file, then  we return code 1
    try{
        //we will iterate until we reach the end of the file
        while(!file.eof())
        {
            std::string object_name;
            bool found = false;
            while(!file.eof() && !found){
                file >> object_name;
                if(!object_name.empty()){
                    found = true;
                }
            }
            if(!found) break;
            std::vector<std::string>* object_info = new std::vector<std::string>;
            object_info->resize(2);
            result.push_back(object_info);
            //gets the name of the object
            (*object_info)[0] = object_name;
            if(this->objects->find((*object_info)[0]) != this->objects->end()) {
                //if the object already exists we set the code 2
                (*object_info)[1] = "2"; 
                std::string line;
                //to avoid all this object and go straight to the next one
                while(line != "-1") file >> line;
                continue;   //to continue to the next iteration

            }
            int vertex_count;
            file >> vertex_count;
            //creates a vector for the vertices, reserving the size we already know will be
            std::vector<std::vector<float>*>* vertices = new std::vector<std::vector<float>*>;
            vertices->resize(vertex_count);
            //we iterate over the amount of vertex we already know will be
            for(int i = 0; i < vertex_count; i++){
                //we read the 3 axis of each vertex
                if(file.eof()) return 0;
                int x, y, z;
                file >> x;
                file >> y;
                file >> z;
                //creates a vector with a size of 3, it allocates the 3 axis of each vertex
                std::vector<float>* vertex = new std::vector<float>;
                vertex->push_back(x);
                vertex->push_back(y);
                vertex->push_back(z);
                (*vertices)[i] = vertex;
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
                face->resize(n);
                for(int i = 0; i < n; i++){
                    //we simply iterate over those vertex and we push them into the face
                    int aux;
                    file >> aux;
                    (*face)[i] = aux;
                }
                //once we end with that face, we push the face into the faces list
                faces->push_back(face);
            }
            //once we reach this part, we have read all the file succesfully, so we push  a new 3D object into our Objects list
            (*this->objects)[(*object_info)[0]] = new Object3d((*object_info)[0], vertices, faces);
            //we add the success result to the list
             (*object_info)[1] = "3";
        }
        file.close();
        return 3;
    }catch(const std::exception& e){
        file.close();
        return 0;
    }
}


//this function iterate over the map of objects, in order to add each object (a pointer to it), in a vector
//which it will return so that then the menu can iterate easily over the vector and print the objects info
std::vector<Object3d*>* DataOrganization::get_objects(){
    std::vector<Object3d*>* objects = new std::vector<Object3d*>;
    objects->resize(this->objects->size());
    std::unordered_map<std::string, Object3d*>::iterator it = this->objects->begin();
    for(int i = 0; it != this->objects->end(); ++it, i++){
        (*objects)[i] = (it->second);
    }
    return objects;
}


std::string DataOrganization::envolvente(std::string object_name){
    //these variables will keep the maximum and minimum values for each axis
    int x_max, x_min, y_max, y_min, z_max, z_min;
    //if object_name is empty, then its the global envolvente
    if(object_name.empty()){
        if(this->objects->empty()) return ""; //if there are no objects stored then we return empty string which the menu will recognize as no objects
        std::unordered_map<std::string, Object3d*>::iterator it = this->objects->begin();
        bool first = true;
        //we iterate over the objects, and for each one we call the function get points
        //that function wil compare the X, Y and Z positions to the parameters passed, and replace them
        //if it finds new maximum or minimum, the maximum and minimum variables are passed by reference
        for(; it != this->objects->end(); ++it){
            this->get_points(it->second, x_max, x_min,  y_max, y_min, z_max, z_min, first);
            if(first) first = false;
        }
    }
    else{
        //if object name wasn't empty, then we only need to find the maximum and minimum
        //values for that single object
        if(this->objects->find(object_name) == this->objects->end()) return ""; //if the object wasn't stored then return empty string
        Object3d* object = this->objects->find(object_name)->second;
        this->get_points(object, x_max, x_min, y_max, y_min, z_max, z_min, true);
    }

    std::vector<std::vector<float>*>* vertices = new std::vector<std::vector<float>*>;
    //this loop iterates 8 time (since the envolvente box will have 8 vertices)
    //and in each iteration it creates a new vertex of the box, it follows a pattern of 
    // xmax xmax xmax xmax xmin xmin xmin xmin
    // ymax ymax ymin ymin ymax ymax ymin ymin
    // zmax zmin zmax zmin zmax zmin zmax zmin
    //this way it gets all combinations which represent the location of the 8 vertices
    for(int i = 0; i < 8; i++){
        std::vector<float>* vertex = new std::vector<float>;
        int x_n, y_n, z_n;
        if(i < 4) x_n = x_max;
        else x_n = x_min;
        if(i < 2 ||  (i >3 && i < 6)) y_n = y_max;
        else y_n = y_min;
        if(i % 2 == 0) z_n = z_max;
        else z_n = z_min; 
        vertex->push_back(x_n);
        vertex->push_back(y_n);
        vertex->push_back(z_n);
        vertices->push_back(vertex);
    }
    //taking into account the order of insertion of the vertices above, and the position of each one
    //we simply iterate now 6 times to create the 6 faces, on each case we now which indexes we need to 
    //form each face
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
    //if object name was empty we know that the object we created was the env_global
    std::string new_object_name = object_name.empty() ? "env_global": "env_" + object_name;
    //if for instance, we had already an env_global before, then we added new objects, then we 
    //need to replace that object, so we check if it already existed and we delete it if so
    if(this->objects->find(new_object_name) != this->objects->end()){
        delete (*this->objects)[new_object_name];
    }
    (*this->objects)[new_object_name] = new Object3d(new_object_name, vertices, faces);
    return new_object_name;

}

//this function simply iterates over the vertices of the object passed, and simply makes the maximum and minimum comparison
//so at the end those variables will have the value of the maximum and minimum values of each axis
void DataOrganization::get_points(Object3d* object, int& x_max, int& x_min, int& y_max, int& y_min, int& z_max, int& z_min, bool first){
    std::vector<std::vector<float>*>* vertices = object->get_vertices();
    std::vector<std::vector<float>*>::iterator it = vertices->begin();
    for(; it != vertices->end(); ++it){
        int x = (*it)->at(0);
        int y = (*it)->at(1);
        int z = (*it)->at(2);
        if(first){
             x_max = x;
             x_min = x;
             y_max = y;
             y_min = y;
             z_max = z;
             z_min = z;
             first = false;
        }else{
             if(x > x_max) x_max = x;
             if(x < x_min) x_min = x;
             if(y > y_max) y_max = y;
             if(y < y_min) y_min = y;
             if(z > z_max) z_max = z;
             if(z < z_min) z_min = z;
        }
        //std::cout << "\nxmax=" << x_max << " xmin=" << x_min << " ymax=" << y_max << " ymin=" << y_min << " zmax=" << z_max << " zmin=" << z_min ;
    }
}

bool DataOrganization::guardar(std::string object_name, std::string file_name){
    if(this->objects->find(object_name) == this->objects->end()) return false;
    //we create the file
    std::ofstream file(file_name + ".txt");
    Object3d* object = this->objects->find(object_name)->second;
    //we write the object's name and vertices count
    file << object->get_name() << "\n";
    file << object->get_count_vertices() << "\n";

    //we iterate over the vertices of the object and for each vertex we write the 3 values in the 
    //inside vector, which are X, Y  and Z
    std::vector<std::vector<float>*>::iterator it = object->get_vertices()->begin();
    for(; it != object->get_vertices()->end(); ++it){
        std::vector<float>::iterator inside_it = (*it)->begin();
        for(; inside_it != (*it)->end(); ++inside_it){
            file << *inside_it << " ";
        }
        file << "\n";
    }
    //now we iterate over the faces of the object, for each face we write the size of the inside vector
    //which means the number of vertices, and then we iterate over that inside vector in order
    //to write each vertice index
    std::list<std::vector<int>*>::iterator it_faces = object->get_faces()->begin();
    for(; it_faces != object->get_faces()->end(); ++it_faces){
        file << (*it_faces)->size() << " ";
        std::vector<int>::iterator vertx_it = (*it_faces)->begin();
        for(; vertx_it != (*it_faces)->end(); ++vertx_it){
            file<< *vertx_it << " ";
        }
        file << "\n";
    }
    file << "-1";
    file.close();
    return true;
}

//this function simply checks if the object existed and if it does, then it deletes it from the map and from memory
bool DataOrganization::descargar(std::string object_name){
    if(this->objects->find(object_name) == this->objects->end()) return false;
    Object3d* object = (this->objects->find(object_name))->second;
    this->objects->erase(object_name);
    delete object;
    return true;
}

//destructor for DataOrganization, it deletes all the objects and then the map
DataOrganization::~DataOrganization(){
    std::unordered_map<std::string, Object3d*>::iterator it = this->objects->begin();
    for(;it != this->objects->begin(); ++it) delete it->second;
    delete this->objects;
}