#include <memory>   // std::auto_ptr
#include <iostream>

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>

#include <odb/sqlite/database.hxx>

#include "person.hpp"
#include "person-odb.hxx"

using namespace std;
using namespace odb::core;

int main (int argc, char* argv[])
{
    try{
        odb::sqlite::database db ("test.db",
                                  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
                
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

typedef odb::query<person> query;
typedef odb::result<person> result;
        {
            transaction t (db.begin());
            
            result r (db.query<person>(query::age > 30));

            for (auto i:r){
                cout << "Hello, " << i.first() << "!" << endl;
            }

            t.commit ();
        }

    }
    catch (const odb::exception& e){
        cerr << e.what () << endl;
        return 1;
    }
    
    return 0;
}
