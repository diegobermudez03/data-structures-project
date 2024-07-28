#include <iostream>
#include <vector>

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
int get_first_word(std::string& command);


int main(int argsn, char** args){
    std::string command;
    while(true){
        getline(std::cin, command);
        enter_command(command);
    }
}

void enter_command(std::string& command){
    std::string first_word = command.substr(0, get_first_word(command));
    if(first_word == "cargar") cargar_command(command);
    else if(first_word == "listado") listado_command(command);
    else if(first_word == "envolvente") envolvente_command(command);
    else if(first_word == "descargar") descargar_command(command);
    else if(first_word == "guardar") guardar_command(command);
    else if(first_word == "v_cercano") v_cercano_command(command);
    else if(first_word == "v_cercanos_caja") v_cercanos_caja_command(command);
    else if(first_word == "ruta_corta") ruta_corta_command(command);
    else if(first_word == "ruta_corta_centro") ruta_corta_centro_command(command);
    else if(first_word == "salir") exit(0);
    else{
        std::cout << "\ncomando invalido";
    }
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


//inside function, used to "split" the commands and get the first word
int get_first_word(std::string& command){
    for(int i = 0; i < command.size(); i++){
        if(command.at(i) == ' ') return i;
    }
    return command.size();
}