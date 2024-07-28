#include <iostream>
#include <vector>
#include <unordered_map>

void enter_command(std::string& command);
void cargar_command(std::string& command);
void listado_command(std::string& command);
void envolvente_command(std::string& command);
void descargar_command(std::string& command);
void guardar_command(std::string& command);
void v_cercano_command(std::string& command);
void v_cercanos_caja_command(std::string& command);
void ruta_corta_command(std::string& command);
void ruta_corta_centro_command(std::string& command);
void ayuda_command(std::string& command);
void fill_help_commands();
int char_finder(std::string& command, char end_char, int begin_pos);

std::unordered_map<std::string, std::string> help_map;

int main(int argsn, char** args){
    fill_help_commands();
    std::string command;
    while(true){
        std::cout << "\n$";
        getline(std::cin, command);
        enter_command(command);
    }
}

void enter_command(std::string& command){
    std::string first_word = command.substr(0, char_finder(command, ' ',0));
    if(first_word == "cargar") cargar_command(command);
    else if(first_word == "listado") listado_command(command);
    else if(first_word == "envolvente") envolvente_command(command);
    else if(first_word == "descargar") descargar_command(command);
    else if(first_word == "guardar") guardar_command(command);
    else if(first_word == "v_cercano") v_cercano_command(command);
    else if(first_word == "v_cercanos_caja") v_cercanos_caja_command(command);
    else if(first_word == "ruta_corta") ruta_corta_command(command);
    else if(first_word == "ruta_corta_centro") ruta_corta_centro_command(command);
    else if(first_word == "ayuda") ayuda_command(command);
    else if(first_word == "salir") exit(0);
    else{
        std::cout << "\ncomando invalido";
    }
}

void ayuda_command(std::string& command){
    short initial_pos = char_finder(command, ' ',0);
    short end_pos = char_finder(command, ' ', initial_pos + 1);
    std::string word = command.substr(initial_pos +1, end_pos - initial_pos);
    std::string help;
    help = help_map[word];
    if(help.empty()) help = "comando no existe";
    std::cout << "\n" << help;
}

void cargar_command(std::string& command){
    std::cout << "\nComando valido";
}

void listado_command(std::string& command){
    std::cout << "\nComando valido";
}

void envolvente_command(std::string& command){
    std::cout << "\nComando valido";
}

void descargar_command(std::string& command){
    std::cout << "\nComando valido";
}

void guardar_command(std::string& command){
    std::cout << "\nComando valido";
}

void v_cercano_command(std::string& command){
    std::cout << "\nComando valido";
}

void v_cercanos_caja_command(std::string& command){
    std::cout << "\nComando valido";
}

void ruta_corta_command(std::string& command){
    std::cout << "\nComando valido";
}

void ruta_corta_centro_command(std::string& command){
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

//inside function, used to "split" the commands and get the first word, second word, etc
int char_finder(std::string& command, char end_char, int begin_pos){
    for(int i = begin_pos; i < command.size(); i++){
        if(command.at(i) == end_char) return i;
    }
    return command.size();
}