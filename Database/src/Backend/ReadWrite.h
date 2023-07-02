#ifndef READWRITE_H
#define READWRITE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../DataContainers.h"

using namespace std;

const char nullTerminator = '\0';

void writeString(ofstream &wf, string value){
    for(int i = 0; i < value.length(); i++){
        char letter = value[i];
        wf.write((char*) &(letter), sizeof(char));
    }
    wf.write((char*) &(nullTerminator), sizeof(char));
}

string readString(ifstream &rf){
    string value;
    char letter;
    do{
        rf.read((char*) &(letter), sizeof(char));
        value.push_back(letter);        
    } while(letter != '\0');
    value = value.substr(0, value.size()-1);
    return value;
}

enum ReadWriteFlags{
    READFAIL,
    READSUCCESS,
    WRITEFAIL,
    WRITESUCCESS
};

/*
** File Format ** 
number of tables int
table1 name
table1 width int
table1 length int
table1 dtypes int
table1 headings
table1 records 
table2 name
table2 width int 
table2 length int
table2 dtypes int 
table2 headings
table2 records
.
.
.
*/

ReadWriteFlags writeDatabase(Database* db){
    ReadWriteFlags flag = WRITESUCCESS;
    string filename = db->getName() + ".db";
    ofstream wf(filename, ios::out | ios::binary);
    if(!wf) {
        cout << "Error Opening Data File" << endl;
        flag = WRITEFAIL;
        return flag;
    }
    vector<Table*> tables = db->getTableList();
    int tableNumber = db->getTableNumber();
    wf.write((char*) &(tableNumber), sizeof(tableNumber));

    for(int i = 0; i < tableNumber; i++){
        string tableName = tables[i]->getName();//
        int tableWidth = tables[i]->getWidth();
        int tableLength = tables[i]->getLength();
        vector<Datatype> format = tables[i]->getFormat();
        vector<string> headings = tables[i]->getHeadings();
        
        writeString(wf, tableName);
        wf.write((char*) &(tableWidth), sizeof(tableWidth));
        wf.write((char*) &(tableLength), sizeof(tableLength));
        
        for(int j = 0; j < tableWidth; j++){
            wf.write((char*) &(format[j]), sizeof(format[j]));
        }
        for(int j = 0; j < tableWidth; j++){
            writeString(wf, headings[j]);
        }
        
        for(int j = 0; j < tableLength; j++){
            Record *record = tables[i]->getRecord(j);
            int key = record->getKey();
            wf.write((char*) &(key), sizeof(key));

            for(int k = 0; k < tableWidth; k++){
                Field *field = record->getField(k);

                if(field->getdtype() == INTEGER){
                    int value = *((int*) (field->getData()));
                    wf.write((char*) &(value), sizeof(value));
                }
                if(field->getdtype() == CHARACTER){
                    char value =*((char*) (field->getData()));
                    wf.write((char*) &(value), sizeof(value));
                }
            }
        }
    }

    wf.close();
    if(!wf.good()) {
        cout << "Error writing to File" << endl;
        flag = WRITEFAIL;
        return flag;
    }
    return flag;
}

ReadWriteFlags readDatabase(Database* db){
    ReadWriteFlags flag = READSUCCESS;
    string filename = db->getName() + ".db";
    ifstream rf(filename, ios::out | ios::binary);
    if(!rf) {
        cout << "Error Opening File" << endl;
        flag = WRITEFAIL;
        return flag;
    }

    vector<Table*> tables;
    int tableNumber = 0;
    rf.read((char*) &(tableNumber), sizeof(int));

    for(int i = 0; i < tableNumber; i++){
        int tableWidth;
        int tableLength;
        vector<Datatype> format;
        vector<string> headings;

        string tableName = readString(rf);
        rf.read((char*) &(tableWidth), sizeof(int));
        rf.read((char*) &(tableLength), sizeof(int));

        for(int j = 0; j < tableWidth; j++){
            Datatype current; 
            rf.read((char*) &(current), sizeof(current));
            format.push_back(current);
        }
        for(int j = 0; j < tableWidth; j++){
            string current = readString(rf);
            headings.push_back(current);
        }

        Table* currentTable = new Table(tableName, tableWidth, format, headings);
        db->addTable(currentTable);       

        for(int j = 0; j < tableLength; j++){ 
            vector<Field*> fields;
            int key;
            rf.read((char*) &(key), sizeof(int));

            for(int k = 0; k < tableWidth; k++){
                Field* currentField;

                if(format[k] == INTEGER){ // memory leak?
                    int* value = (int*) malloc(sizeof(int));
                    rf.read((char*) value, sizeof(int));
                    intField* thisIntField = new intField();
                    thisIntField->setData((void*) value);
                    currentField = thisIntField;
                }
                if(format[k] == CHARACTER){ // memory leak?
                    char* value = (char*) malloc(sizeof(char));
                    rf.read((char*) value, sizeof(char));
                    charField* thisCharField = new charField();
                    thisCharField->setData((void*) value);
                    currentField = thisCharField;
                }
                fields.push_back(currentField);
            }
            
            Record* currentRecord = new Record(tableWidth, key, fields);

            currentTable->addRecord(currentRecord);
        }
    }
       
    rf.close();
    if(!rf.good()) {
        cout << "Error reading from File" << endl;
        flag = READFAIL;
        return flag;
    }
    return flag;
}

ReadWriteFlags backupDatabase(Database* db){
    ReadWriteFlags flag = WRITESUCCESS;
    string filename = db->getName() + "_backup" + ".db";
    ofstream wf(filename, ios::out | ios::binary);
    if(!wf) {
        cout << "Error Opening Data File" << endl;
        flag = WRITEFAIL;
        return flag;
    }
    vector<Table*> tables = db->getTableList();
    int tableNumber = db->getTableNumber();
    wf.write((char*) &(tableNumber), sizeof(tableNumber));

    for(int i = 0; i < tableNumber; i++){
        string tableName = tables[i]->getName();//
        int tableWidth = tables[i]->getWidth();
        int tableLength = tables[i]->getLength();
        vector<Datatype> format = tables[i]->getFormat();
        vector<string> headings = tables[i]->getHeadings();
        
        writeString(wf, tableName);
        wf.write((char*) &(tableWidth), sizeof(tableWidth));
        wf.write((char*) &(tableLength), sizeof(tableLength));
        
        for(int j = 0; j < tableWidth; j++){
            wf.write((char*) &(format[j]), sizeof(format[j]));
        }
        for(int j = 0; j < tableWidth; j++){
            writeString(wf, headings[j]);
        }
        
        for(int j = 0; j < tableLength; j++){
            Record *record = tables[i]->getRecord(j);
            int key = record->getKey();
            wf.write((char*) &(key), sizeof(key));

            for(int k = 0; k < tableWidth; k++){
                Field *field = record->getField(k);

                if(field->getdtype() == INTEGER){
                    int value = *((int*) (field->getData()));
                    wf.write((char*) &(value), sizeof(value));
                }
                if(field->getdtype() == CHARACTER){
                    char value =*((char*) (field->getData()));
                    wf.write((char*) &(value), sizeof(value));
                }
            }
        }
    }

    wf.close();
    if(!wf.good()) {
        cout << "Error writing to File" << endl;
        flag = WRITEFAIL;
        return flag;
    }
    return flag;
}


#endif
