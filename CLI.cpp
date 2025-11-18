#include "CLI.h"
#include <iostream>
#include <string>
#include "Square.h"
using namespace std;



void CLI::start() {
    bool isExit = false;

    while(!isExit) {
        isExit = commands();
    }
}

bool CLI::commands() {
    string command;

    cout << ">>";
    cin >> command;

    if (command == "help") {
        cout << "====================" << endl;
        cout << "Todos los comandos:" << endl;
        cout << "====================" << endl;

        // /help
        cout << "/help - ";
        cout << "Muestra este menú" << endl;
        // /ls o /list
        cout << "/list - ";
        cout << "Muestra las casillas adyacentes" << endl;
        // add
        cout << "/add - ";
        cout << "Agrega una casilla o un monstruo" << endl;
    
    } else if(command == "ls" || command == "list") {
        board.showSquares();
    } else if(command == "ls_all" || command == "list_all") {
        board.showAllSquares();
    } else if(command == "add_square") {
        string name;
        cout << "Nombre de la casilla:";
        cin >> name;
        cout << endl;

        float probability;
        cout << "Probabilidad de spawn:";
        cin >> probability;
        cout << endl;

        board.addSquare(name, probability, false);
        cout << name << " - " << probability << " Agregada!" << endl;

    } else if (command == "connect") {
        string name;
        cout << "Inserta el nombre de la primera casilla a conectar:";
        cin >> name;
        cout << endl;
        
        int firstSquareI = board.searchSquare(name);

        if(firstSquareI == -1) {
            cout << "Primera casilla no encontrada" << endl;
            return false;
        }

        cout << "Inserta el nombre de la segunda casilla a conectar:";
        cin >> name;
        cout << endl;

        int secondSquareI = board.searchSquare(name);

        if(secondSquareI == -1) {
            cout << "Segunda casilla no encontrada" << endl;
            return false;
        }

        cout << "Casillas conectadas correctamente!" << endl;

        board.connectSquares(firstSquareI, secondSquareI);
    } else if (command == "status") {
        cout << "=================" << endl;
        cout << "Casilla Actual:" << endl;
        cout << "-----------------" << endl;
        board.showActualSquare();
        cout << "==================" << endl;
        if(board.getStatus() == "peace") {
            cout << "Todo tranquilo por aquí" << endl;
        } else if(board.getStatus() == "combat") {
            cout << "Estas en combate con un monstruo" << endl;
            board.showActualMonster();
            
        }
    } else if(command == "exit") {
        cout << "Adios :)" << endl;
        return true;
    } else {
        cout << endl;
        cout << "No se reconcoe el comando" << endl;
        cout << "Usa /help para ver los comandos disponibles" << endl;
    }

    cout << endl;
    return false;
}