#ifndef DATACONTAINERS_H
#define DATACONTAINERS_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum Datatype {
    SUPERCLASS,
    INTEGER,
    CHARACTER
};

class Field{
    private:
        void * data;
    public:
        virtual Datatype getdtype(){
            return SUPERCLASS;
        }
        void setData(void * Idata){
            data = Idata;
        }
        void * getData(){
            return data;
        }
};

class intField : public Field {
    public:
        Datatype getdtype(){
            return INTEGER;
        }
};
class charField : public Field {
    public:
        Datatype getdtype(){
            return CHARACTER;
        }
};

class Record{
    private:
        int length;
        int key;
        vector<Field*> fieldList;
    public:
        Record(int numberOfValues, int Ikey, vector<Field*> fields){
            length = numberOfValues;
            key = Ikey;
            fieldList = fields;
        }
        Field* getField(int index){
            return fieldList[index];
        }
        int getKey(){
            return key;
        }
        void printRecord(){
            cout << key << " : ";
            for(int i = 0; i < length; i++){
                if(fieldList[i]->getdtype() == INTEGER){
                    cout << *((int*) (fieldList[i]->getData())) << '\t';
                }
                if(fieldList[i]->getdtype() == CHARACTER){
                    cout << *((char*) (fieldList[i]->getData())) << '\t';
                }
            }
            cout << endl;
        }
};

class Table{
    private:
        string name;
        int length;   
        int nextKey;
        int width;
        vector<Datatype> dlist; 
        vector<string> hlist;
        vector<Record*> recordList;
    public:
        Table(string Tname, int Twidth, vector<Datatype> values, vector<string> headings){
            name = Tname;
            width = Twidth;
            length = 0;
            nextKey = 0;
            dlist = values;
            hlist = headings;
        }
        void addRecord(vector<Field*> fields){
            Record* currentRecord = new Record(width, nextKey, fields);
            recordList.push_back(currentRecord);
            length++;
            nextKey++;
        }
        void addRecord(Record* currentRecord){
            recordList.push_back(currentRecord);
            length++;
            nextKey++;
        }
        Record* getRecord(int index){
            return recordList[index];            
        }
        Field* getField(string heading,int index){
            int aIndex = 0;
            for(int i = 0; i < hlist.size(); i++){
                if(heading == hlist[i]){
                    aIndex = i;
                }
            }
            return recordList[index]->getField(aIndex);            
        }
        vector<Datatype> getFormat(){
            return dlist;            
        }
        vector<string> getHeadings(){
            return hlist;            
        }
        int getLength(){
            return length;
        }
        int getWidth(){
            return width;
        }
        void printTable(){
            cout << "Table: " << name << endl;
            for(int i = 0; i < width; i++){
                cout << hlist[i] << '\t';
            }
            cout << endl;   
            for(int i = 0; i < length; i++){
                recordList.at(i)->printRecord();
            }
        }
        string getName(){
            return name;
        }
};

class Database{
    private:
        string name;
        int tables = 0;
        vector<Table*> tableList;
    public:
        Database(string dbName){
            name = dbName;
        }
        void addTable(Table* Itable){
            tableList.push_back(Itable);
            tables++;
        }
        vector<string> getTableNames(){
            vector<string> names;
            for(int i = 0; i < tables; i++){
                names.push_back(tableList[i]->getName());
            }  
            return names; 
        }

        Table* getTable(string tname){
            Table* table;
            for(int i = 0; i < tables; i++){
                if(tableList[i]->getName() == tname){
                    table = tableList[i];
                }
            }
            return table;
        }

        Table* getTable(int index){
            return tableList[index];
        }

        int getTableNumber(){
            return tables;
        }

        vector<Table*> getTableList(){
            return tableList;
        }

        string getName(){
            return name;
        }

};

#endif