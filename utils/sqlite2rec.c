#include <config.h>
#include <getopt.h>
#include <xalloc.h>
#include <gettext.h>
#define _(str) gettext (str)
#include <rec.h>
#include <recutl.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

/*sqlite2rec structure*/
struct sqlite2rec{
  rec_db_t db;
  rec_rset_t rset;
  rec_record_t record;
  rec_field_t  recfield;
  };

/*rec_writer pointer which writes rec files to stdout*/
rec_writer_t writ;

void print_usage(void)
{
  printf("Usage: sqlite2rec [DATABASE_NAME] [TABLE_NAME]\nDATABASE_NAME: name of the database from which rec file is created\n TABLE_NAME: name of the table which is converted into rec format\n");
}



int main(int argc, char** args)
{
    if(argc!=3)
    {
        print_usage();
    }
    else
    {
        writ = rec_writer_new (stdout);           //initialising rec_writer to write on stdout
        struct sqlite2rec *s2r;    //struct sqlite2rec pointer

        s2r=malloc( sizeof(rec_record_t)+ sizeof(rec_field_t)+ sizeof(rec_rset_t)+ sizeof(rec_db_t));   //allocating memory to the s2r pointer.
        s2r->db=rec_db_new();         //creatng new database
        s2r->rset = rec_rset_new ();        //initialising a new rset i.e for mysql it is a new table
        s2r->record = rec_record_new();     //initialising a new record i.e. for mysql it is a new row
        s2r->recfield = rec_field_new ("%rec", args[2]);       //initialising the record descriptor
        rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY);
        rec_rset_set_descriptor (s2r->rset, s2r->record); 


    // Create an int variable for storing the return code for each call
        int retval;
   
    // The number of queries to be handled,size of each query and pointer
        int q_cnt = 5,q_size = 150,ind = 0;
        char queries[100]; //= malloc(sizeof(char) * q_cnt * q_size);
       
    // A prepered statement for fetching tables
        sqlite3_stmt *stmt;
   
    // Create a handle for database connection, create a pointer to sqlite3
        sqlite3 *handle;
   
    // try to create the database. If it doesnt exist, it would be created
    // pass a pointer to the pointer to sqlite3, in short sqlite3**
        retval = sqlite3_open(args[1],&handle);
    // If connection failed, handle returns NULL
        if(retval)
        {
            printf("Database connection failed\n");
            return -1;
        }
       // select those rows from the table
        strcpy(queries, "SELECT * from ");
        strcat(queries,args[2]);
      
        retval = sqlite3_prepare_v2(handle,queries,-1,&stmt,0);
        if(retval)
        {
            printf("Selecting data from DB Failed\n");
            return -1;
        }
   
    // Read the number of rows fetched
        int cols = sqlite3_column_count(stmt);
           
        while(1)
        {
        // fetch a row's status
            retval = sqlite3_step(stmt);
            s2r->record=rec_record_new();       //a new record is initialised.
            if(retval == SQLITE_ROW)
            {
            // SQLITE_ROW means fetched a row
            // sqlite3_column_text returns a const void* , typecast it to const char*
                int col;
                for( col=0 ; col<cols;col++)
                {
                    const char *val = (const char*)sqlite3_column_text(stmt,col);
                    s2r->recfield = rec_field_new (sqlite3_column_name(stmt,col), val);     //inserting the field_name(f) and the field_value in the field structure
                    rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY); //appending the field to the record   
                }
            }
            else if(retval == SQLITE_DONE)
            {
            // All rows finished
                break;
            }
            else
            {
                // Some error encountered
                printf("Some error encountered\n");
                return -1;
            }
            rec_mset_append (rec_rset_mset (s2r->rset), MSET_RECORD, (void *) s2r->record, MSET_ANY);    //appending the record to the rset
        }

        rec_db_insert_rset (s2r->db, s2r->rset, rec_db_size (s2r->db));
        rec_write_db (writ,s2r->db);        //writing the database onto stdout
   
        // Close the handle to free memory
        sqlite3_close(handle);
        return 0;
    }
}
