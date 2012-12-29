#include <iostream>

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>

#include <odb/sqlite/database.hxx>

#include "person.hpp"
#include "person-odb.hxx"

using namespace std;
using namespace odb::core;

void create_person_table(shared_ptr<odb::sqlite::database> db)
{
    unsigned long john_id, jane_id, joe_id;

    // Create a few persistent person objects.
    //

    person john ("John", "Doe", 33);
    person jane ("Jane", "Doe", 32);
    person joe ("Joe", "Dirt", 30);

    {
        transaction t (db->begin());

        // Make objects persistent and save their ids for later use.
        //
        john_id = db->persist (john);
        jane_id = db->persist (jane);
        joe_id = db->persist (joe);
        
        t.commit ();
    }    
}

void query_person(shared_ptr<odb::sqlite::database> db)
{
    typedef odb::query<person> query;

    transaction t (db->begin());
            
    auto r (db->query<person>(query::age > 30));

    for (auto i:r){
        cout << "Hello, " << i.first() << "!" << endl;
    }

    t.commit ();
}

shared_ptr<odb::sqlite::database> open_database(string name, bool create=false)
{       
    int flags = SQLITE_OPEN_READWRITE;
    if (create) flags |= SQLITE_OPEN_CREATE;

    shared_ptr<odb::sqlite::database> db(new odb::sqlite::database(name, flags) );
    
    transaction t (db->begin());
    if (create){
        odb::schema_catalog::create_schema(*db);
    }    
    t.commit ();
    
    return db;
}

shared_ptr<odb::sqlite::database> open_create_database(string name)
{
    std::shared_ptr<odb::sqlite::database> db;
    try{
        db = open_database(name);
    }catch (const odb::exception& e){
        db = open_database(name,true);            
    }
    return db;
}


int main (int argc, char* argv[])
{
    try{
        auto db = open_create_database("test.db");
        create_person_table(db);
        query_person(db);
    }
    catch (const odb::exception& e){
        cerr << e.what () << endl;
        return 1;
    }
    
    return 0;
}
