#include "object_3d.h"
#include "tuple3.h"
#include <vector>
#include <iostream>

Object3d::Object3d(std::string& name, std::vector<std::vector<float>*>* vertices, std::list<std::vector<int>*>* faces){
    this->name = name;
    this->vertices = vertices;
    this->faces = faces;

    //since with the "listado" command we must return the count of lines, we need a way to count them easily
    //simply counting the pairs of vertex in faces isn't enough, since we can have redundancies, causing false duplicate lines
    //so, the way to count them, is firstly, to store them in a map, where a vertex is a key, and the value is a SET of the vertex
    //with which it is connected to, when we iterate over the faces to do this, we check to add the higher index to the lower index, so 
    //that no matter the order in which it appears 2 3 or 3 2, it will be stored in the {2, {3}}, the SET helps to avoid duplicates
    //example:
    //  {0, {6,2,8}}
    //  {2, {4,5}}
    this->lines = new std::unordered_map<int, std::unordered_set<int>*>;
    std::list<std::vector<int>*>::iterator it = faces->begin();
    //we iterate over the faces
    for(;it != faces->end(); ++it){
        //we get an iterator for the vector of each face
        std::vector<int>::iterator inside_it = (*it)->begin();
        int previous;
        bool first = true;
        //we iterate over the vector with vertex of each face
        for(; inside_it != (*it)->end(); ++inside_it){
            //the logic is to compare by pairs, each vertex with the preious one, and then on
            if(!first){
                //we simply compare the previous vertex with the current one, and depending on which one is higher, we call the add_line method with the correspondent order
                if(previous < *inside_it) add_line(previous, *inside_it);
                else add_line(*inside_it, previous);
            }else{
                //if it's the first vertex, then there's no previous vertex yet, but technically, it's the last vertex of the face, so we check with that vertex
                first = false;
                //we must substract 1 to the end address to get the actual last position
                if(*inside_it < *((*it)->end()-1)) add_line(*inside_it, *((*it)->end()-1));
                else add_line(*((*it)->end()-1), *inside_it);
            }
            //we replace the previous variable with the current, now previous vertex
            previous = *inside_it;
        }
    }
}

Object3d::~Object3d(){
    //we delete the memory
    if (vertices != nullptr) {
        //if vertices isn't null then we iterate over the vertices and delete the inside vectors
        //then we delete the vector of vectors
        std::vector<std::vector<float>*>::iterator it = this->vertices->begin();
        for (; it != this->vertices->end(); ++it) delete *it;
        delete this->vertices;
    }

    if (faces != nullptr) {
        //we iterate over the list of vectors and we delete the vectors inside, then we delete the list
        std::list<std::vector<int>*>::iterator it = this->faces->begin();
        for (; it != this->faces->end(); ++it) delete *it;
        delete this->faces;
    }
    if (lines != nullptr) {
        //we iterate over the map and we delete the sets inside it, then we delete the map
        std::unordered_map<int, std::unordered_set<int>*>::iterator it = this->lines->begin();
        for (; it != this->lines->end(); ++it) {
               delete it->second;
         }
        delete this->lines;
    }
}

 std::unordered_set<int>* Object3d::get_neighbors_of(int index){
    return this->lines->find(index)->second;
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

//this function simply is the one that counts the lines, it iterates over our map of lines, and it accumulates the size of the sets
int Object3d::get_count_lines(){
    std::unordered_map<int, std::unordered_set<int>*>::iterator it = this->lines->begin();
    int counter = 0;
    for(; it != this->lines->end(); ++it) counter += it->second->size();
    return counter;
}

//this function is used to add a line to our map structure
void Object3d::add_line(int key, int value){
    //if the key doesn't already exist, then we need to create it, with its correspondent empty set
    if(this->lines->find(key) == this->lines->end()){
        (*this->lines)[key] = new std::unordered_set<int>;
    }
    //here we are sure that the key will exist, so we continue to insert the vertex to the set
    std::unordered_set<int>* set = (*this->lines)[key];
    set->insert(value);
}

std::vector<std::vector<float>*>* Object3d::get_vertices(){
    return this->vertices;
}

std::list<std::vector<int>*>* Object3d::get_faces(){
    return this->faces;
}

Tuple3<float, float, float>* Object3d::getVertexCentro() {
    float sumX = 0.0, sumY = 0.0, sumZ = 0.0;
    int vertexCount = this->vertices->size();
    
    std::vector<std::vector<float>*>::iterator it = this->vertices->begin();
    for (; it != vertices->end(); ++it) {
        std::vector<float>* vertex = *it;
        sumX += (*vertex)[0];  
        sumY += (*vertex)[1];  
        sumZ += (*vertex)[2];  
    }

    float centerX = sumX / vertexCount;
    float centerY = sumY / vertexCount;
    float centerZ = sumZ / vertexCount;

    return new Tuple3<float, float, float>(centerX, centerY, centerZ);
}
