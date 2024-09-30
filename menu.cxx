#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

#include "object_3d.h"
#include "data_organization.h"
#include "tuple.h"

void enter_command(std::string& command);

void cargar_command(std::list<std::string>* words);
void listado_command(std::list<std::string>* words);
void envolvente_command(std::list<std::string>* words);
void descargar_command(std::list<std::string>* words);
void guardar_command(std::list<std::string>* words);
void v_cercano_command(std::list<std::string>* words);
void v_cercanos_caja_command(std::list<std::string>* words);
void ruta_corta_command(std::list<std::string>* words);
void ruta_corta_centro_command(std::list<std::string>* words);
void ayuda_command(std::list<std::string>* words);

void fill_help_commands();
std::list<std::string>* split(std::string&command);
int char_finder(std::string& command, char end_char, int begin_pos);


//global variables
std::unordered_map<std::string, std::string> help_map;
DataOrganization* data_org;

//Entry point of the program, simply prints the entry command char $ and listens for inputs
int main(int argsn, char** args){
    fill_help_commands(); 
    data_org = new DataOrganization;
    std::string command;
    while(true){
        std::cout << "\n\n$";   //prints terminal character
        getline(std::cin, command);
        enter_command(command);
    }
}

//logic redirection of commands, it redirects each command to its correspondent controller
void enter_command(std::string& command){
    std::list<std::string>* words = split(command); //we split the command into the words, so the command is easy to manage
    std::string first_word = words->back(); //gets the initial command
    words->pop_back();  //pops the command word from the list, so we are left with the remaining of the command
    void (*command_type)(std::list<std::string>*) = nullptr;
    //depending on the first word of the command, our function pointer will point to the indicated function
    //its made this way since all funcions receive the same parameters, so we mantain the code DRY
    if(first_word == "cargar") command_type = cargar_command;
    else if(first_word == "listado") command_type =  listado_command;
    else if(first_word == "envolvente") command_type = envolvente_command;
    else if(first_word == "descargar") command_type = descargar_command;
    else if(first_word == "guardar") command_type = guardar_command;
    else if(first_word == "v_cercano") command_type = v_cercano_command;
    else if(first_word == "v_cercanos_caja") command_type = v_cercanos_caja_command;
    else if(first_word == "ruta_corta") command_type = ruta_corta_command;
    else if(first_word == "ruta_corta_centro") command_type = ruta_corta_centro_command;
    else if(first_word == "ayuda") command_type = ayuda_command;
    else if(first_word == "salir") {
        delete data_org;
        exit(0);
    }
    else{
        std::cout << "\ncomando invalido";
    }
    if(command_type != nullptr) command_type(words);
    delete words;   //cleaning memory
}

//controller for help command of any type, if any type was given, it shows all the commands help
void ayuda_command(std::list<std::string>* words){
    //if there are no words, that means that the command was only "help", so then, we print all the help commands
    if(words->size() == 0){
        std::unordered_map<std::string, std::string>::iterator it = help_map.begin();
        for(; it != help_map.end(); ++it){
            std::cout << "\n  " << it->first << " \n" << it->second << "\n";
        }
        return;
    }
    //we get the word for which the help was asked
    std::string word = words->back();
    std::string help;
    help = help_map[word];  //we retrieve the help text from the map, so we can print, if there's no entry in the map, the command simply doesn't exist
    if(help.empty()) help = "comando no existe";
    std::cout << "\n" << help;
}

void cargar_command(std::list<std::string>* words){
    //it should only be 1 word, so if there'are less or more, then it's worng
    if(words->size() != 1){
        std::cout << "\nComando invalido\n" << help_map["cargar"];
        return;
    }
    //we get the file_name from the command
    std::string file_name = words->back();
    //this list we create will contain a vector, which will only have 2 items inside, is used so 
    //that we can pass it by reference to the function, the function will read the objects , and if there
    // are many objects in a single file, then it writes the result of each one on this list
    std::list<std::vector<std::string>*> result;
    short code = data_org->load_file(file_name, result);
    if(code == 0) std::cout << "\n(Archivo vacio o incompleto) El archivo " << file_name << " no contiene un objeto 3D valido";
    else if(code == 1)  std::cout << "\n(Archivo no existe) El archivo " << file_name << " no existe o es ilegible";
    if(!result.empty()){
        std::list<std::vector<std::string>*>::iterator it = result.begin();
        //if we got responses from objects, we iterate over them and print the output of each object
        for(; it != result.end(); ++it){
            if((**it)[1] == "2")  std::cout << "\n(Objeto ya existe) El objeto " << (**it)[0] << " ya ha sido cargado en memoria";
            else if((**it)[1] == "3") std::cout << "\n(Resultado exitoso) El objeto " << (**it)[0] << " ha sido cargado exitosamente desde el archivo";
        }
    }
}

void listado_command(std::list<std::string>* words){
    //there shouldn't be any words at all, so if there are, the command it's wrong
    if(words->size() != 0){
        std::cout << "\nComando invalido\n" << help_map["listado"];
        return;
    }
    //we get the objects stored in our DataOrg object
    std::vector<Object3d*>* objects = data_org->get_objects();
    if(objects->empty()){
        std::cout <<"\n(Memoria vacia) Ningun objeto ha sido cargado en memoria";
        return;
    }
    std::cout << "\n(Resultado exitoso) Hay " << objects->size() << " objetos en memoria:\n";
    std::vector<Object3d*>::iterator it = objects->begin();
    //we iterate over the vector of objects and we print the info of each one
    for(; it!= objects->end(); ++it){
        std::cout << "\n" << (*it)->get_name() << " contiene " << std::to_string((*it)->get_count_vertices()) << " vertices, " << std::to_string((*it)->get_count_lines()) << " aristas y " << std::to_string((*it)->get_count_faces()) << " caras";
    }
}

void envolvente_command(std::list<std::string>* words){
    if(words->size() > 1){
        std::cout << "\nComando invalido\n" << help_map["envolvente"];
        return;
    }
    std::string object_name = words->size() == 1 ? words->back(): "";
    std::string env_name = data_org->envolvente(object_name);
    if(env_name.empty() && object_name.empty())     std::cout << "\n(Memoria vacia) Ningun objeto ha sido cargado en memoria";
    else if(env_name.empty() && !object_name.empty()) std::cout << "\n(Objeto no existe) El objeto " << object_name << " no ha sido cargado en memoria";
    else if(object_name.empty()) std::cout << "\n(Resultado exitoso) La caja envolvente de los objetos en memoria se ha generado con el nombre " << env_name << " y se ha agregado a los objetos en memoria";
    else std::cout << "\n(Resultado exitoso) La caja envolvente del objeto " << object_name << " se ha generado con el nombre " << env_name << " y se ha agregado a los objetos en memoria";
}

void descargar_command(std::list<std::string>* words){
    if(words->size() != 1){
        std::cout << "\nComando invalido\n" << help_map["descargar"];
        return;
    }
    std::string object_name = words->back();
    if(data_org->descargar(object_name) == true) std::cout << "\n(Resultado exitoso) El objeto " << object_name << " ha sido eliminado de la memoria de trabajo";
    else std::cout << "\n(Objeto no existe) El objeto " << object_name << " no ha sido cargado en memoria";
}

void guardar_command(std::list<std::string>* words){
    if(words->size() != 2){
        std::cout << "\nComando invalido\n" << help_map["guardar"];
        return;
    }
    std::string object_name = words->back();
    words->pop_back();
    std::string file_name = words->back();
    if(data_org->guardar(object_name, file_name)) std::cout << "\n(Resultado exitoso) la informacion del objeto " << object_name << " ha sido guardada exitosamente en el archivo " << file_name;
    else std::cout << "\n(Objeto no existe) El objeto " << object_name << " no ha sido cargado en memoria";
}

void v_cercano_command(std::list<std::string>* words){
    if(words->size() == 4 || words->size() == 3){
        float px, py, pz;
        std::string object_name = "";
        try{
            px = std::stof(words->back());
            words->pop_back();
            py = std::stof(words->back());
            words->pop_back();
            pz = std::stof(words->back());
            words->pop_back();

            if(!words->empty()){
                object_name = words->back();
            }
            Tuple<VertexNode*, float>* nearest = data_org->cercano(px, py, pz, object_name);
            if(nearest == nullptr){
                if(object_name != "") std::cout << "\n(Objecto no existe) El objeto " << object_name << " no ha sido cargado en memoria";
                else std::cout << "\n(Memoria vacia) Nigun objeto ha sido cargado en memoria";
                return;
            }
            std::vector<float>* vertex = nearest->getValue1()->getVertex();
            std::cout << "(Resultado exitoso) El vertice " << nearest->getValue1()->getIndex() << " (" << vertex->at(0) << ", " << vertex->at(1) << ", " << vertex->at(2) << ") del objeto " << nearest->getValue1()->getObjectName() << " es el mas cercano al punto";
            std::cout << "(" << px << ", " << py << ", " << pz << "), a una distancia de " << nearest->getValue2();

            delete nearest;
            return;
        }catch(const std::exception& e){}
    }
    std::cout << "\nComando invalido\n" << help_map["v_cercano"];
    return;
}

void v_cercanos_caja_command(std::list<std::string>* words){
    if(words->size() != 1){
        std::cout << "\nComando invalido\n" << help_map["v_cercanos_caja"];
        return;
    }
    //TO DO NEXT
    std::cout << "\nComando valido";
}

void ruta_corta_command(std::list<std::string>* words){
    if(words->size() == 3){
        int i1, i2;
        try{
            i1 = std::stoi(words->back());
            words->pop_back();
            i2 = std::stoi(words->back());
            words->pop_back();
            //TO DO NEXT
            std::cout << "\nComando valido";
            return;
        }catch(const std::exception& e){}
    }
    std::cout << "\nComando invalido\n" << help_map["ruta_corta"];
    return;
}

void ruta_corta_centro_command(std::list<std::string>* words){
    if(words->size() == 2){
        int i1;
        try{
            i1 = std::stoi(words->back());
            words->pop_back();
        }catch(const std::exception& e){}
        std::string object_name = words->back();
        //TO DO NEXT
        std::cout << "\nComando valido";
        return;
    }
    std::cout << "\nComando invalido\n" << help_map["ruta_corta"];
    return;
}

//function called at the very beginning of the program, it fills a hashmap with all the possible help commands and its correspondent help description
void fill_help_commands(){
    help_map["cargar"] = "  USO: cargar <nombre_archivo>\n    carga el objeto a memoria";
    help_map["listado"] = "  USO: listado\n    lista los objetos cargados en memoria";
    help_map["envolvente"] = "  USO: envolvente\n    genera la caja envolvente de todos los objetos\n  USO: envolvente <nombre_objeto>\n    genera la caja envolvente del objeto indicado";
    help_map["descargar"] = " USO: descargar <nombre_objeto>\n    elimina el objeto de memoria";
    help_map["guardar"] = "  USO: guardar <nombre_objeto> <nombre_archivo>\n    exporta a un archivo de texto la informacion del objeto indicado";
    help_map["salir"] = "  USO: salir\n    termina la ejecucion del programa de forma segura";
    help_map["v_cercano"] = "  USO: v_cercano <px> <py> <pz>\n    identifica, entre todos los objetos, el vertice mas cercano al punto indicado\n  USO: v_cercano <px> <py> <pz> <nombre_objeto>\n    identifica el vertice del objeto mas cercano al punto indicado";
    help_map["v_cercanos_caja"] = "  USO: v_cercanos_caja <nombre_objeto>\n    identifica los vertices del objeto mas cercanos a la caja envolvente del mismo";
    help_map["ruta_corta"] = "  USO: ruta-corta <i1> <i2> <nombre_objeto>\n    la ruta mas corta que conexta los vertices i1 y i2 del objeto";
    help_map["ruta_corta_centro"] = "  USO: ruta_corta_centro <i1 nombre_objeto>\n    identifica los indices de los vertices que conforman la ruta mas corta entre vertice dado y el centro del objeto";
}

//inside function, used to "split" the commands and get the first word, second word, etc
int char_finder(std::string& command, char end_char, int begin_pos){
    //we simply receive a starting position and the char we are  looking for, the rest is simple iteration
    if(begin_pos < command.size()){
        for(int i = begin_pos; i < command.size(); i++){
            if(command.at(i) == end_char) return (i);
        }
    }
    return (command.size());
}

//this function is our own split implementation, so we get a list of words, that we can easily manage to understand the exact command
std::list<std::string>* split(std::string&command){
    std::list<std::string>* words = new std::list<std::string>;
    int starting = 0;
    int ending = 0;
    while(true){
        try{
            //we use our char_finder function in order to find every space, taking as the starting point the ending
            //index of the previous word +1, this is how we divide the sentence into words
            ending = char_finder(command, ' ', starting);
            std::string word = command.substr(starting, ending-starting);
            if(!word.empty()) words->push_front(word);
            starting = ending+1;
        }catch(const std::exception& e){
            break;
        }
    }
    return (words);
}