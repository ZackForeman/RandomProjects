#ifndef SQLCOMPILER_H
#define SQLCOMPILER_H

#include <iostream>
#include <string>
#include <vector>
#include "SQLStatements.h"
#include "SQLCommands.h"

using namespace std;



/*

PrepareResult stringToCharArray(char to[], int length, string &from){
    if(from.length() > length){
        return PREPARE_SIZE_ERROR;
    }
    
    for(int i = 0; i <= from.length(); i++){
        if(i < from.length()){
            to[i] = from[i];
        } else {
            to[i] = '\0';
        }
        
    }

    return PREPARE_SUCCESS;
}

PrepareResult stringToInt(uint32_t &to, string &from){
    to = stoi(from);
    return PREPARE_SUCCESS;
}

*/

#endif