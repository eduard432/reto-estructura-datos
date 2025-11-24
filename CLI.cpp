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

void CLI::readInput(string& value) {
    getline(cin, value);
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
        cout << "/help - ";
        cout << "Muestra este menú" << endl;
        // /register
        cout << "/register - ";
        cout << "Registra tu tipo de heroe" << endl;
        // /play
        cout << "/play - ";
        cout << "Inicia el juego en la casilla actual" << endl;
        // /combat
        cout << "/combat - ";
        cout << "Pelea contra el monstruo de la casilla" << endl;
        // /me
        cout << "/me - ";
        cout << "Muestra informacion del heroe" << endl;
        // /ls o /list
        cout << "/list - ";
        cout << "Muestra las casillas adyacentes" << endl;
        // move ó cs
        cout << "/move - ";
        cout << "Cambia la casilla actual" << endl;
        // status
        cout << "/status - ";
        cout << "Dice el status actual del tablero" << endl;
        // clear
        cout << "/clear - ";
        cout << "Limpia la terminal" << endl; 
        // exit
        cout << "/exit - ";
        cout << "Salir del juego" << endl;
        // Comandos que necesitan de administrador:
        // add
        cout << "/add - ";
        cout << "Agrega una casilla o un monstruo" << endl;
        // load
        cout << "/load - ";
        cout << "Carga monstruos o casillas desde un archivo" << endl;
        // connect
        cout << "/connect - ";
        cout << "Conecta dos casillas" << endl;
        // cheetcode
        cout << "/cheatcode - ";
        cout << "Muestra la ruta más fácil hacia el tesoro" << endl;
    } else if(command == "register") {
        // board.selectCharacter();
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
        cin >> squareName;
        bool isChange = board.changeActualSquare(squareName);
        if(isChange) {
            cout << "Te moviste con exito a la casilla: " << endl;
            board.showActualSquare();
        } else {
            cout << "Sigues en la misma casilla" << endl;
        }
    }  else if (command == "status") {
        cout << "=================" << endl;
        cout << "Casilla Actual:" << endl;
        cout << "-----------------" << endl;
        board.showActualSquare();
        cout << "==================" << endl;

        string status = board.getStatus();

        if(status == "peace") {
            cout << "Todo tranquilo por aquí" << endl;
        } else if(status == "inAttack") {
            cout << "Te espera una batalla" << endl;
            cout << "Tip: usa \"/combat\" para iniciar el combate " << endl; 
        } else if(status == "combat") {
            cout << "Estas en combate con un monstruo" << endl;
            board.showActualMonster();
        }
    } else if (command == "clear" || command == "cls") {
        clear();
    } else if(command == "exit") {
        cout << "Adios :)" << endl;
        return true;
    } else if(command == "sudo") {
        command = tokens.elementAt(1);
        if(command == "add") {
            string type = tokens.elementAt(2);
            if(type == "square") {
                string name;
                cout << "Nombre de la casilla:";
                readInput(name);
                cout << endl;

                float probability;
                cout << "Probabilidad de spawn:";
                cin >> probability;
                cout << endl;

                board.addSquare(name, probability, false);
                cout << name << " - " << probability << " Agregada!" << endl;
            } else if(type == "monster"){
                // TODO: implement sudo add monster
            }

        } else if (command == "load") {
            string type = tokens.elementAt(2);
            string fileName;
            if (type == "monsters") {
                cout << "Escribe el nombre del archivo a leer: ";
                cin >> fileName;
                bool areLoaded = board.loadMonstersFromCsv(fileName);
                if(!areLoaded) {
                    cout << "No se pudieron cargar los monstruos" << endl;
                    return false;
                } else {
                    cout << "Los monstruos se cargaron con éxito" << endl;
                }
            } else if (type == "squares") {
                cout << "Escribe el nombre del archivo a leer: ";
                cin >> fileName;
                bool areLoaded = board.loadSquareFromCsv(fileName);
                if(!areLoaded) {
                    cout << "No se pudieron cargar las casillas" << endl;
                    return false;
                } else {
                    cout << "Las casillas se cargaron con éxito" << endl;
                }
            } else if(type == "connections") {
                cout << "Escribe el nombre del archivo a leer: ";
                cin >> fileName;
                bool areLoaded = board.loadConnectionsFromCsv(fileName);
                if(!areLoaded) {
                    cout << "No se pudieron cargar las conexiones" << endl;
                    return false;
                } else {
                    cout << "Las conexiones se cargaron con éxito" << endl;
                }
            }

        } else if(command == "list" || command == "ls") {
            string type = tokens.elementAt(2);
            int flagIndex = tokens.indexOf("-a");
            if(type == "squares" && flagIndex != -1) {
                board.showAllSquares();
            } else if(type == "monsters" && flagIndex != -1) {
                board.showAllMonsters();
            }
        } else if (command == "connect") {
            unsigned int firstSquareIndex;
            cout << "Inserta el id de la primera casilla a conectar:";
            cin >> firstSquareIndex;
            cout << endl;

            unsigned int secondSquareIndex;

            cout << "Inserta el id de la segunda casilla a conectar:";
            cin >> secondSquareIndex;
            cout << endl;

            
            bool areConnected = board.connectSquares(firstSquareIndex, secondSquareIndex);
            if (areConnected) {
                cout << "Casillas conectadas correctamente!" << endl;
            } else {
                cout << "Las casillas no se pudieron conectar" << endl;
            }

        } else if(command == "cheatcode") {
            cout << "Camino más fácil hacia el tesoro: " << endl;
            board.showCheatcode();
        }
    } else {
        cout << endl;
        cout << "No se reconoce el comando" << endl;
        cout << "Usa /help para ver los comandos disponibles" << endl;
    }
    cout << endl;
    return false;
}