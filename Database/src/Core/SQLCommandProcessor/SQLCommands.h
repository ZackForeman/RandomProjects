#ifndef SQLCOMMANDS_H
#define SQLCOMMANDS_H

#include "../../Backend/ReadWrite.h"
#include <iostream>

using namespace std;

enum CommandResult{
    COMMAND_BLANK,
    COMMAND_SUCCESS,
    COMMAND_ERROR,
    COMMAND_UNRECOGNISED_COMMAND
};

/*vector<string> splitInput(string input){
    vector<string> splitString;
    string currentString = "";
    for(int i = 0; i < input.length(); i++){
        if(input.substr(i,1) != " "){
            currentString += input.substr(i,1);
        } else {
            splitString.push_back(currentString);
            currentString = "";
        }
    }
    splitString.push_back(currentString);
    
    return splitString;
}*/

CommandResult handleCommand(string input, Database* &directory){
    CommandResult result = COMMAND_BLANK;
    vector<string> args = splitInput(input);
    if(args[0] == ".exit"){
        exit(EXIT_SUCCESS);
    } else if(args[0] == ".open"){
        if(directory != nullptr){
            cout << "Close the current Database before opening another" << endl;
            return COMMAND_ERROR;
        } else {
            cout << "Opening database: " << args[1] << endl;
            directory = new Database(args[1]);
            readDatabase(directory);
            return COMMAND_SUCCESS;
        }                       
    } else if(args[0] == ".save"){
        if(directory == nullptr){
            cout << "Open a Database before trying to save" << endl;
            return COMMAND_ERROR;
        } else {
            cout << "Saving database"<< endl;
            writeDatabase(directory);
            return COMMAND_SUCCESS;
        } 
    } else if(args[0] == ".backup"){
        if(directory == nullptr){
            cout << "Open a Database before trying to make a backup" << endl;
            return COMMAND_ERROR;
        } else {
            cout << "Backing up database" << endl;
            backupDatabase(directory);
            return COMMAND_SUCCESS;
        } 
    } else if(args[0] == ".close"){
        directory = nullptr;
        return COMMAND_SUCCESS;
    } else if(args[0] == ".print"){
        if(directory == nullptr){
            cout << "Open a Database before trying to print" << endl;
            return COMMAND_ERROR;
        } else {
            cout << "Printing database"<< endl;
            for(Table * t : directory->getTableList()){
                t->printTable();
            }
            return COMMAND_SUCCESS;
        } 
    } else{
        return COMMAND_UNRECOGNISED_COMMAND;
    }
}


#endif
