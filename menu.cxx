#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

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
std::string substring(std::string& command, int in_pos, int end_pos);
std::list<std::string>* split(std::string&command);
int char_finder(std::string& command, char end_char, int begin_pos);

std::unordered_map<std::string, std::string> help_map;

//Entry point of the program, simply prints the entry command char $ and listens for inputs
int main(int argsn, char** args){
    fill_help_commands();
    std::string command;
    while(true){
        std::cout << "\n\n$";
        getline(std::cin, command);
        enter_command(command);
    }
}

//logic redirection of commands, it redirects each command to its correspondent controller
void enter_command(std::string& command){
    std::list<std::string>* words = split(command);
    std::string first_word = words->back(); //gets the initial command
    words->pop_back();  //pops the command from the list
    void (*command_type)(std::list<std::string>*);
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
    else if(first_word == "salir") exit(0);
    else{
        std::cout << "\ncomando invalido";
    }

    /*std::list<std::string>::iterator it = words->begin();
    for(; it != words->end();++it){
        std::cout << "\n"<< *it;
    }*/
    if(command_type != nullptr) command_type(words);
    delete words;
}

//controller for help command of any type, if any type was given, it shows all the commands help
void ayuda_command(std::list<std::string>* words){
    if(words->size() == 0){
        std::unordered_map<std::string, std::string>::iterator it = help_map.begin();
        for(it = help_map.begin(); it != help_map.end(); ++it){
            std::cout << "\n  " << it->first << " \n" << it->second << "\n";
        }
        return;
    }
    std::string word = words->back();
    std::string help;
    help = help_map[word];
    if(help.empty()) help = "comando no existe";
    std::cout << "\n" << help;
}

void cargar_command(std::list<std::string>* words){
    //it should only be 1 word, so if there'are less or more, then it's worng
    if(words->size() != 1){
        std::cout << "\nComando invalido\n" << help_map["cargar"];
        return;
    }
    //TO DO NEXT 
    std::cout << "\nComando valido";
}

void listado_command(std::list<std::string>* words){
    //there shouldn't be any words at all, so if there are, the command it's wrong
    if(words->size() != 0){
        std::cout << "\nComando valido\n" << help_map["listado"];
        return;
    }
    //TO DO NEXT
    std::cout << "\nComando valido";;
}

void envolvente_command(std::list<std::string>* words){
    std::cout << "\nComando valido";
}

void descargar_command(std::list<std::string>* words){
    std::cout << "\nComando valido";
}

void guardar_command(std::list<std::string>* words){
    std::cout << "\nComando valido";
}

void v_cercano_command(std::list<std::string>* words){
    std::cout << "\nComando valido";
}

void v_cercanos_caja_command(std::list<std::string>* words){
    std::cout << "\nComando valido";
}

void ruta_corta_command(std::list<std::string>* words){
    std::cout << "\nComando valido";
}

void ruta_corta_centro_command(std::list<std::string>* words){
    std::cout << "\nComando valido";
}

//function called at the very beginning of the program, it fills a hashmap with all the possible help commands and its correspondent help description
void fill_help_commands(){
    help_map["cargar"] = "  cargar 'nombre_archivo'\n    carga el objeto a memoria";
    help_map["listado"] = "  listado\n    lista los objetos cargados en memoria";
    help_map["envolvente"] = "  envolvente\n    caja envolvente de todos los objetos\n  envolvente 'nombre_objeto'\n    calcula la caja envolvente del objeto";
    help_map["descargar"] = " descargar 'nombre_objeto'\n    elimina el objeto de memoria";
    help_map["guardar"] = "  guardar 'nombre_objeto' 'nombre_archivo'\n    exporta a un archivo de texto la informacion del objeto";
    help_map["salir"] = "  salir\n    termina la ejecucion del programa de forma segura";
    help_map["v_cercano"] = "  v_cercano 'px py pz'\n    'identifica, entre todos los objetos, el vertice mas cercano al punto indicado\n  v_cercano 'px py pz nombre_objeto'\n    identifica el vertice del objeto mas cercano al punto indicado";
    help_map["v_cercanos_caja"] = "  v_cercanos_caja 'nombre_objeto'\n    identifica los vertices del objeto mas cercanos";
    help_map["ruta_corta"] = "  ruta-corta 'i1 i2 nombre_objeto'\n    la ruta mas corta que conexta los vertices i1 y i2 del objeto";
    help_map["ruta_corta_centro"] = "  ruta_corta_centro 'i1 nombre_objeto'\n    identifica los indices de los vertices que conforman la ruta mas corta entre vertice dado y el centro del objeto";
}


//Own substring method, so that we can control if the initial index is out of range
std::string substring(std::string& command, int in_pos, int end_pos){
    end_pos = end_pos < 0 ? 4294967295 : end_pos;
    if(command.size() < in_pos) return "";
    return command.substr(in_pos, end_pos);

}

//inside function, used to "split" the commands and get the first word, second word, etc
int char_finder(std::string& command, char end_char, int begin_pos){
    if(begin_pos < command.size()){
        for(int i = begin_pos; i < command.size(); i++){
            if(command.at(i) == end_char) return i;
        }
    }
    return command.size();
}

std::list<std::string>* split(std::string&command){
    std::list<std::string>* words = new std::list<std::string>;
    int starting = 0;
    int ending = 0;
    while(true){
        try{
            ending = char_finder(command, ' ', starting);
            std::string word = command.substr(starting, ending-starting);
            if(!word.empty()) words->push_front(word);
            starting = ending+1;
        }catch(const std::exception& e){
            break;
        }
    }
    return words;
}