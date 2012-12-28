#include <iostream>

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>

#include <odb/sqlite/database.hxx>

#include "person.hpp"
#include "person-odb.hxx"

using namespace std;
using namespace odb::core;

void create_person_table(odb::sqlite::database& db)
{
    unsigned long john_id, jane_id, joe_id;

    // Create a few persistent person objects.
    //

    person john ("John", "Doe", 33);
    person jane ("Jane", "Doe", 32);
    person joe ("Joe", "Dirt", 30);

    {
        transaction t (db.begin());

        odb::schema_catalog::create_schema(db);

        // Make objects persistent and save their ids for later use.
        //
        john_id = db.persist (john);
        jane_id = db.persist (jane);
        joe_id = db.persist (joe);
        
        t.commit ();
    }    
}

void query_person(odb::sqlite::database& db)
{
    typedef odb::query<person> query;

    transaction t (db.begin());
            
    auto r (db.query<person>(query::age > 30));

    for (auto i:r){
        cout << "Hello, " << i.first() << "!" << endl;
    }

    t.commit ();
}

int main (int argc, char* argv[])
{
    try{
        odb::sqlite::database db ("test.db",
                                  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
                
        create_person_table(db);
        query_person(db);
    }
    catch (const odb::exception& e){
        cerr << e.what () << endl;
        return 1;
    }
    
    return 0;
}
