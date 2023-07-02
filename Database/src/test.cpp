#include <iostream>
#include "DataContainers.h"
#include "Backend/ReadWrite.h"

using namespace std;

int main(){
    int int1 = 1;
    char char1 = 'a';
    intField * intField1 = new intField;
    intField1->setData((void*)&int1);
    charField * charField1 = new charField;
    charField1->setData((void*)&char1);

    int int2 = 2;
    char char2 = 'b';
    intField * intField2 = new intField;
    intField2->setData((void*)&int2);
    charField * charField2 = new charField;
    charField2->setData((void*)&char2);

    vector<Datatype> dlist{INTEGER, CHARACTER};
    vector<string> hlist{"Integer", "Character"};

    Table * exampleTable = new Table("ExampleTable", 2, dlist, hlist);

    vector<Field*> field1{intField1, charField1};
    vector<Field*> field2{intField2, charField2};
    
    exampleTable->addRecord(field1);
    exampleTable->addRecord(field2);

    exampleTable->printTable();
    
    Database* db = new Database("ExampleDatabase");

    db->addTable(exampleTable);

    writeDatabase(db);

    Database* read = new Database("ExampleDatabase");

    readDatabase(read);

    (read->getTable(0))->printTable();  

}