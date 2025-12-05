#include <iostream>
#include <string>
#include <limits>
#include "Square.h"
#include "CLI.h"
#include "LinkedList.h"
#include "Utils.h"


using namespace std;

void CLI::clear() {
    cout << "\033[2J\033[1;1H";
}

void CLI::start() {
    // clear();
    bool isExit = false;
    while(!isExit) {
        isExit = commands();
    }
}

void CLI::readInput(std::string& value) {
    if (!std::getline(std::cin, value)) {
        value = "";
    }
}

float CLI::readFloatLoop(string prompt) {
    while (true) {
        cout << prompt;
        string input;
        readInput(input);

        try {
            return std::stof(input);
        } catch (...) {
            cout << "Entrada invalida. Intenta de nuevo." << endl;
        }
    }
}

unsigned int CLI::readPositiveIntLoop(string prompt) {
    while (true) {
        cout << prompt;
        string input;
        readInput(input);

        try {
            int value = std::stoi(input);
            if (value >= 0) return value;
        } catch (...) {}
        
        cout << "Entrada invalida. Ingresa un numero entero positivo." << endl;
    }
}

int CLI::readIntLoop(string prompt) {
    while (true) {
        cout << prompt;
        string input;
        readInput(input);

        try {
            return std::stoi(input);
        } catch (...) {
            cout << "Entrada invalida. Intenta de nuevo." << endl;
        }
    }
}

bool CLI::requireTokens(const LinkedList<string>& tokens, unsigned int count) {
    if (tokens.size() < count) {
        cout << "Faltan argumentos para este comando." << endl;
        return false;
    }
    return true;
}


bool CLI::commands() {
    string input;
    cout << ">>";
    readInput(input);

    LinkedList<string> tokens = Utils().split(input);

    string command = tokens.elementAt(0);

    if (command == "help") {
        cout << "====================" << endl;
        cout << "Todos los comandos:" << endl;
        cout << "====================" << endl;

        // /help
        cout << "help - ";
        cout << "Muestra este menu" << endl;
        // /register
        cout << "register - ";
        cout << "Registra tu tipo de heroe" << endl;
        // /play
        cout << "play - ";
        cout << "Inicia el juego en la casilla actual" << endl;
        // /combat
        cout << "combat - ";
        cout << "Pelea contra el monstruo de la casilla" << endl;
        // /me
        cout << "me - ";
        cout << "Muestra informacion del heroe" << endl;
        // /ls o /list
        cout << "list - ";
        cout << "Muestra las casillas adyacentes" << endl;
        // move o cs
        cout << "move - ";
        cout << "Cambia la casilla actual" << endl;
        // status
        cout << "status - ";
        cout << "Dice el status actual del tablero" << endl;
        // clear
        cout << "clear - ";
        cout << "Limpia la terminal" << endl; 
        // upgrade
        cout << "upgrade - ";
        cout << "Mejora tus estadisticas" << endl;
        // exit
        cout << "exit - ";
        cout << "Salir del juego" << endl;
        // Comandos que necesitan de administrador:
        cout << "================" << endl;
        cout << "SUDO commands:" << endl;
        cout << "================" << endl;
        // add
        cout << "add - ";
        cout << "Agrega una casilla o un monstruo" << endl;
        // load
        cout << "load - ";
        cout << "Carga monstruos o casillas desde un archivo" << endl;
        // connect
        cout << "connect - ";
        cout << "Conecta dos casillas" << endl;
        // cheetcode
        cout << "cheatcode - ";
        cout << "Muestra la ruta mas facil hacia el tesoro" << endl;
    } else if(command == "register") {
        board.selectHero();
    } else if(command == "play") {
        cout << "Iniciando juego en casilla actual" << endl;
        board.play();
    } else if (command == "combat") {
        cout << "Continua el combate" << endl;
        board.combat();
    } else if(command == "me") {
        board.showHero();
    } else if(command == "monster") {
        board.showActualMonster();
    } else if(command == "ls" || command == "list") {
        board.showSquares();
    } else if (command =="move" || command == "cs") {
        Square sq = board.getActualSquare();

        if(sq.getVisited() == false) {
            cout << "Supera la casilla actual para poder moverte" << endl;
            return false;
        }

        board.showSquares();
        cout << endl;
        cout << "¿A que casilla quieres moverte?: ";
        string squareName;
        readInput(squareName);
        bool isChange = board.changeActualSquare(squareName);
        if(isChange) {
            cout << "Te moviste con exito a la casilla: " << endl;
            board.showActualSquare();
        } else {
            cout << "Sigues en la misma casilla" << endl;
        }
    } else if (command == "status") {
        cout << "=================" << endl;
        cout << "Casilla Actual:" << endl;
        cout << "-----------------" << endl;
        board.showActualSquare();
        cout << "==================" << endl;

        bool isInBattle = board.getIsInBattle();

        if (isInBattle) {
            cout << "Estas en combate con un monstruo" << endl;
            board.showActualMonster();
        } 
        else {
            // No estas en batalla
            bool visited = board.getActualSquare().getVisited();

            if (!visited) {
                cout << "Todo tranquilo por aqui, usa el comando /play para empezar" << endl;
            } else {
                cout << "Todo tranquilo por aqui" << endl;
            }
        }
    } else if (command == "clear" || command == "cls") {
        clear();
    } else if(command == "upgrade") {
        if (!requireTokens(tokens, 2)) return false;
        string subCmd = tokens.elementAt(1);
        if(subCmd == "show") {
            board.getAbilityTree().show();
        } else if(subCmd == "select") {
            cout << "[0] Aumenta la defensa" << endl;
            cout << "[1] Aumenta la vida" << endl;
            cout << "[2] Aumenta el ataque" << endl;
            cout << "[3] Aumenta el poder" << endl;

            unsigned int attributeChoosen;

            do {
                attributeChoosen = CLI::readPositiveIntLoop("Ingresa tu opción (1-4): ");

                if (attributeChoosen < 0 || attributeChoosen > 3) {
                    cout << "Opción inválida. Intenta nuevamente." << endl;
                }

            } while (attributeChoosen < 0 || attributeChoosen > 3);

            board.getAbilityTree().show(static_cast<Attribute>(attributeChoosen));

            int option = -1;
            do {
                option = readIntLoop("Selecciona la opción:");
            } while (option != 1 && option != 2);

            if(board.getAbilityPoints() == 0) {
                cout << "No tienes puntos de habilidad disponibles" << endl;
                return false;
            } else {
                if(option == 2 && board.getAbilityPoints() < 3) {
                    cout << "No tienes puntos de habilidad suficientes (3)" << endl;
                    return false;
                }
            }

            board.getAbilityTree().upgrade(board.getHero(), static_cast<Attribute>(attributeChoosen), option == 1);
        } else {
            cout << endl;
            cout << "No se reconoce el comando" << endl;
            cout << "Usa /help para ver los comandos disponibles" << endl;
        }
    } else if(command == "exit") {
        cout << "Adios :)" << endl;
        return true;
    } else if(command == "sudo") {
        if (!requireTokens(tokens, 2)) return false;
        string subCmd = tokens.elementAt(1);
        if(subCmd == "add") {
            if (!requireTokens(tokens, 3)) return false; // /sudo add <type>
            string type = tokens.elementAt(2);

            if(type == "square") {
                string name;
                cout << "Nombre de la casilla:";
                readInput(name);
                cout << endl;

                float probability = readFloatLoop("Probabilidad de spawn:");
                cout << endl;

                board.addSquare(name, probability, false);
                cout << name << " - " << probability << " Agregada!" << endl;
            } else if(type == "monster"){
                string name;
                cout << "Nombre del monstruo:";
                readInput(name);

                float health = readFloatLoop("Vida del monstruo:");
                float defense = readFloatLoop("Defensa del monstruo:");
                float attack = readFloatLoop("Ataque del monstruo:");

                board.addMonster(name, health, attack, defense);
            }

        } else if (subCmd == "load") {
            if (!requireTokens(tokens, 3)) return false; // /sudo load <type>
            string type = tokens.elementAt(2);
            string fileName;
            if (type == "monsters") {
                cout << "Escribe el nombre del archivo a leer: ";
                readInput(fileName);
                cout << endl;
                bool areLoaded = board.loadMonstersFromCsv(fileName);
                if(!areLoaded) {
                    cout << "No se pudieron cargar los monstruos" << endl;
                    return false;
                } else {
                    cout << "Los monstruos se cargaron con exito" << endl;
                }
            } else if (type == "squares") {
                cout << "Escribe el nombre del archivo a leer: ";
                readInput(fileName);
                cout << endl;
                bool areLoaded = board.loadSquareFromCsv(fileName);
                if(!areLoaded) {
                    cout << "No se pudieron cargar las casillas" << endl;
                    return false;
                } else {
                    cout << "Las casillas se cargaron con exito" << endl;
                }
            } else if(type == "connections") {
                cout << "Escribe el nombre del archivo a leer: ";
                readInput(fileName);
                cout << endl;
                bool areLoaded = board.loadConnectionsFromCsv(fileName);
                if(!areLoaded) {
                    cout << "No se pudieron cargar las conexiones" << endl;
                    return false;
                } else {
                    cout << "Las conexiones se cargaron con exito" << endl;
                }
            } else if(type == "attacks") {
                string subType = tokens.elementAt(3);
                if(subType == "monsters") {
                    cout << "Escribe el nombre del archivo a leer: ";
                    readInput(fileName);
                    cout << endl;
                    bool areLoaded = board.loadMonsterAttacksFromCsv(fileName);
                    if(!areLoaded) {
                        cout << "No se pudieron cargar los ataques de los monstruos" << endl;
                        return false;
                    } else {
                        cout << "Los ataques se cargaron con exito" << endl;
                    }
                }
            }

        } else if(subCmd == "list" || subCmd == "ls") {
            if (!requireTokens(tokens, 4)) { 
                    cout << "Uso: sudo list <squares|monsters> -a" << endl;
                    return false;
                }

                string type = tokens.elementAt(2);
                int flagIndex = tokens.indexOf("-a");

                if (flagIndex == -1) {
                    cout << "Falta el flag -a" << endl;
                    cout << "Uso: sudo list <squares|monsters> -a" << endl;
                    return false;
                }

                if (type == "squares") {
                    board.showAllSquares();
                } 
                else if (type == "monsters") {
                    board.showAllMonsters();
                } 
                else {
                    cout << "Tipo inválido: " << type << endl;
                    cout << "Opciones válidas: squares, monsters" << endl;
            }
        } else if (subCmd == "connect") {
            unsigned int firstSquareIndex;

            firstSquareIndex = CLI::readPositiveIntLoop("Inserta el id de la primera casilla a conectar:");

            cout << endl;

            int secondSquareIndex;
            secondSquareIndex = CLI::readPositiveIntLoop("Inserta el id de la segunda casilla a conectar:");
            cout << endl;

            
            bool areConnected = board.connectSquares(firstSquareIndex, secondSquareIndex);
            if (areConnected) {
                cout << "Casillas conectadas correctamente!" << endl;
            } else {
                cout << "Las casillas no se pudieron conectar" << endl;
            }

        } else if(subCmd == "cheatcode") {
            cout << "Camino mas facil hacia el tesoro: " << endl;
            board.showCheatcode();
        } else if(subCmd == "move" || subCmd == "cs") {
            board.showAllSquares();
            cout << endl;
            cout << "¿A que casilla quieres moverte?: ";
            string squareName;
            readInput(squareName);
            bool isChange = board.changeActualSquare(squareName);
            if(isChange) {
                cout << "Te moviste con exito a la casilla: " << endl;
                board.showActualSquare();
            } else {
                cout << "Sigues en la misma casilla" << endl;
            }
        } else {
            cout << endl;
            cout << "No se reconoce el comando" << endl;
            cout << "Usa /help para ver los comandos disponibles" << endl;
        }
    } else {
        cout << endl;
        cout << "No se reconoce el comando" << endl;
        cout << "Usa /help para ver los comandos disponibles" << endl;
    }
    cout << endl;
    return false;
}