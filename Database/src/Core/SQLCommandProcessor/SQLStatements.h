#ifndef SQLSTATEMENTS_H
#define SQLSTATEMENTS_H

#include "../../DataContainers.h"
//#include "../vm.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

enum StatementType{
    STATEMENT_SELECT,
    STATEMENT_INSERT
};

enum PrepareResult{
    PREPARE_BLANK,
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNISED_STATEMENT,
    PREPARE_SYNTAX_ERROR,
    PREPARE_SIZE_ERROR,
    PREPARE_MISSING_ARGUMENTS,
    PREPARE_MISSING_TABLE_COLUMNS
};

enum TokenType {
    KEYWORD_SELECT,
    KEYWORD_FROM,
    NOT_KEYWORD
};

struct Token{
    TokenType type;
    string value;
};

vector<string> splitInput(string input){
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
}

string filterString(string value){
    string newValue;
    for(char i : newValue){
        if(isalpha(i)){
            newValue += to_string(i);
        }
    }
    return newValue;
}

class SelectStatement{
    public:
        vector<string> columns;
        string table;
        bool isSelect = false;
        bool isFrom = false;

        PrepareResult parse(vector<string> args){
            cout << "PARSE" << endl;
            int index = 0;
            try {
                if(args[index] == "SELECT"){
                    cout << "PARSE SELECT" << endl;
                    isSelect = true;
                    index++;                
                    while(args[index] != "SELECT" && args[index] != "FROM"){
                        cout << ":" << args[index] << ":" << endl;
                        columns.push_back( args[index] );
                        index++;
                    }
                }
                if(args[index] == "FROM"){
                    cout << "PARSE FROM" << endl;
                    isFrom = true;
                    index++;
                    cout << "THIS: " << args[index] << endl;                
                    table = args[index];
                }
            } catch(int i) {
                cout << "Oh no : " << args.size() << endl;
                return PREPARE_UNRECOGNISED_STATEMENT;
            }
            if(!(isSelect && isFrom)){
                return PREPARE_MISSING_ARGUMENTS;
            }           
            return PREPARE_SUCCESS;
        }
};

/*
unordered_map <string,TokenType> const StringToToken = {
    {"SELECT",  KEYWORD_SELECT},
    {"FROM",    KEYWORD_FROM},
};

TokenType match(string input){
    if(StringToToken.count(input) == 1){
        return StringToToken.find(input)->second;
    }else{
        return NOT_KEYWORD;
    }
}

vector<Token> tokenise(vector<string> input){
    vector<Token> tokens;
    for(string i : input){
        Token currentToken = {
            match(i),
            i
        };
        tokens.push_back(currentToken);
    }

    return tokens;
}
*/

PrepareResult executeSelect(SelectStatement s, Database * dir){
    for(Table * t : dir->getTableList()){
        cout << t->getName() << " : " << s.table << endl;
        if(t->getName() == s.table){
            cout << "1" << endl;
            // Validate Table Names
            vector<Datatype> dtypes;
            for(string iName : s.columns){
                bool exists = false;
                for(int i = 0; i < t->getWidth(); i++){
                    if(iName == (t->getHeadings())[i]){
                        exists = true;
                        dtypes.push_back((t->getFormat())[i]);
                    }                                    
                } 
                if(exists == false){
                    return PREPARE_MISSING_TABLE_COLUMNS;
                }               
            }

            Table * displayTable = new Table("RESULT:", s.columns.size(), dtypes, s.columns);
            
            for(int i = 0 ; i < t->getLength(); i++){    
                vector<Field *> fields;
                for(int j = 0; j < s.columns.size(); j++){
                    fields.push_back(t->getField(s.columns[j],i));
                }
                Record * newR = new Record(fields.size(),t->getRecord(i)->getKey(), fields);
                displayTable->addRecord(newR);
            }
            displayTable->printTable();                
                
        }
    }
}

PrepareResult generate_and_run(vector<string> tokenString, Database * directory){
    cout << "GENERATE AND RUN" << endl;
    if(tokenString[0] == "SELECT") {
        SelectStatement * newStatement = new SelectStatement();
        PrepareResult result = newStatement->parse(tokenString);
        executeSelect(*newStatement, directory);
        return result;
    }
    else{ 
        return PREPARE_UNRECOGNISED_STATEMENT;
    } 

    
}

PrepareResult handleStatement(string input, Database * directory){
    cout << "HANDLESTATEMENT" << endl;
    PrepareResult result = PREPARE_BLANK;
    vector<string> inputString = splitInput(input);
    //vector<Token> tokenString = tokenise(inputString);
    //return generate_and_run(tokenString, directory);    
    generate_and_run(inputString, directory); 
}

#endif