#include "object_3d.h"
#include "tuple3.h"
#include <vector>
#include <iostream>

Object3d::Object3d(std::string& name, std::vector<std::vector<float>*>* vertices, std::list<std::vector<int>*>* faces) {
    this->name = name;
    this->vertices = vertices;
    this->faces = faces;

    // Initialize the vector on the heap, with the size equal to the number of vertices
    lines = new std::vector<std::unordered_set<int>*>(vertices->size());

    // Initialize each set pointer in the vector
    for (size_t i = 0; i < vertices->size(); ++i) {
        (*lines)[i] = new std::unordered_set<int>();
    }

    // Iterate over the faces to populate the line information
    for (auto it = faces->begin(); it != faces->end(); ++it) {
        std::vector<int>* face = *it;
        int num_vertices = face->size();

        // Iterate over each pair of adjacent vertices in the face
        for (int i = 0; i < num_vertices; ++i) {
            int v1 = (*face)[i];
            int v2 = (*face)[(i + 1) % num_vertices];  // Wrap around to form a closed loop

            // Ensure we always add the line in a consistent order (smaller index first)
            if (v1 < v2) {
                add_line(v1, v2);
            } else {
                add_line(v2, v1);
            }
        }
    }
}

void Object3d::add_line(int v1, int v2) {
    (*lines)[v1]->insert(v2);
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
        std::vector<std::unordered_set<int>*>::iterator it = this->lines->begin();
        for (; it != this->lines->end(); ++it) {
               delete *it;
         }
        delete this->lines;
    }
}

std::unordered_set<int>* Object3d::get_neighbors_of(int index) {
    // Create a new set to store the neighbors of the given index
    std::unordered_set<int>* neighbors = new std::unordered_set<int>();

    // Get the neighbors stored directly in the vertex with the given index
    std::unordered_set<int>* current_set = (*lines)[index];
    std::unordered_set<int>::iterator it = current_set->begin();
    for (; it != current_set->end(); ++it) {
        neighbors->insert(*it);
    }
    // Iterate over all vertices to find those which have a connection to the given index
    for (int i = 0; i < lines->size(); i++) {
        if(lines->at(i)->find(index) != lines->at(i)->end()){
            neighbors->insert(i);
        }
    }
    return neighbors;
}


std::unordered_set<int>* Object3d::get_lines_of(int index){
    return this->lines->at(index);
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
    std::vector<std::unordered_set<int>*>::iterator it = this->lines->begin();
    int counter = 0;
    for(; it != this->lines->end(); ++it){
        counter += (*it)->size();
    }
    return counter;
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
