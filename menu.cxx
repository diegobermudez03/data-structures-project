#include <iostream>
#include <vector>
#include <unordered_map>

void enter_command(std::string& command);
void cargar_command(std::string& command, short initial_index);
void listado_command(std::string& command, short initial_index);
void envolvente_command(std::string& command, short initial_index);
void descargar_command(std::string& command, short initial_index);
void guardar_command(std::string& command, short initial_index);
void v_cercano_command(std::string& command, short initial_index);
void v_cercanos_caja_command(std::string& command, short initial_index);
void ruta_corta_command(std::string& command, short initial_index);
void ruta_corta_centro_command(std::string& command, short initial_index);
void ayuda_command(std::string& command, short initial_index);
void fill_help_commands();
std::string substring(std::string& command, int in_pos, int end_pos);
int char_finder(std::string& command, char end_char, int begin_pos);

std::unordered_map<std::string, std::string> help_map;

int main(int argsn, char** args){
    fill_help_commands();
    std::string command;
    while(true){
        std::cout << "\n\n$";
        getline(std::cin, command);
        enter_command(command);
    }
}

void enter_command(std::string& command){
    short initial_index = char_finder(command, ' ',0);
    std::string first_word = command.substr(0, initial_index);
    void (*command_type)(std::string&, short);
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
    if(command_type != nullptr) command_type(command, initial_index);
}

void ayuda_command(std::string& command, short initial_index){
    short end_pos = char_finder(command, ' ', initial_index + 1);
    std::string word;
    try{
        word = command.substr(initial_index +1, end_pos - initial_index);
    }catch(const std::exception& e){}
    if(word.empty()){
        std::unordered_map<std::string, std::string>::iterator it = help_map.begin();
        for(it = help_map.begin(); it != help_map.end(); ++it){
            std::cout << "\n  " << it->first << " \n" << it->second << "\n";
        }
        return;
    }
    std::string help;
    help = help_map[word];
    if(help.empty()) help = "comando no existe";
    std::cout << "\n" << help;
}

void cargar_command(std::string& command, short initial_index){
    std::string file_name = substring(command, initial_index+1, -1);
    if(file_name.empty()){
        std::cout << "\nComando invalido\n" << help_map["cargar"];
        return;
    }
    //TO DO IN NEXT 
    std::cout << "\nComando valido";
}

void listado_command(std::string& command, short initial_index){
    std::cout << "\nComando valido";
}

void envolvente_command(std::string& command, short initial_index){
    std::cout << "\nComando valido";
}

void descargar_command(std::string& command, short initial_index){
    std::cout << "\nComando valido";
}

void guardar_command(std::string& command, short initial_index){
    std::cout << "\nComando valido";
}

void v_cercano_command(std::string& command, short initial_index){
    std::cout << "\nComando valido";
}

void v_cercanos_caja_command(std::string& command, short initial_index){
    std::cout << "\nComando valido";
}

void ruta_corta_command(std::string& command, short initial_index){
    std::cout << "\nComando valido";
}

void ruta_corta_centro_command(std::string& command, short initial_index){
    std::cout << "\nComando valido";
}

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