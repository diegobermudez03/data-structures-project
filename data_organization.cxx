#include "data_organization.h"
#include <fstream>

short DataOrganization::load_file(std::string& file_name){
    std::ifstream file(file_name);
    if(!file.is_open()) return 1;
    try{
        while(true){
            std::string object_name;
            file >> object_name;
            int vertex_count;
            file >> vertex_count;
            for(int i = 0; i < vertex_count; i++){
                
            }
        }
    }catch(const std::exception& e){
        return 0;
    }
}