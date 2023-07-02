#ifndef REPL_H
#define REPL_H

#include <iostream>
#include <string>
#include "../../DataContainers.h"
#include "../SQLCommandProcessor/SQLCompiler.h"


using namespace std;

int startREPL(){
    
    string prompt = "db";

    Database* directory = nullptr;

    cout << "Initialisting REPL" << endl;

    while(true){
        // Interface
        string input;
        cout << " ";
        cout << " " << ((directory == nullptr) ? prompt: directory->getName() ) << " >> ";
        getline(cin, input); 

        // SQL Command Compiler
        if(input[0] == '.'){
            switch ( handleCommand(input, directory) )
            {
                case (COMMAND_SUCCESS):
                    break;
                case (COMMAND_UNRECOGNISED_COMMAND):
                    cout << "Unrecognised Command: "<< input << endl;
                    break;
            }
        }
        else{
            switch (handleStatement(input, directory))
            {
                case (PREPARE_SUCCESS):
                    break;
                case (PREPARE_UNRECOGNISED_STATEMENT):
                    cout << "Unrecognised keyword at start of: " << input << endl;
                    break;
            }

        }
    }
}

#endif