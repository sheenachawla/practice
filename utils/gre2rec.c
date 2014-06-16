/*
 * testlibpq.c
 *
 *      Test the C version of libpq, the PostgreSQL frontend library.
 */
 #include <config.h>
#include <getopt.h>
#include <xalloc.h>
#include <gettext.h>
#define _(str) gettext (str)
#include <rec.h>
#include <recutl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

/*gre2rec structure*/
struct gre2rec{
  rec_db_t db;
  rec_rset_t rset;
  rec_record_t record;
  rec_field_t  recfield;

}; 

/*rec_writer pointer which writes rec files to stdout*/
rec_writer_t writ;

static void
exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}

void print_usage(void)
{
  printf("Usage: gre2rec dbname=[DATABASE_NAME] [TABLE_NAME]\nDATABASE_NAME: name of the database from which rec file is created\nTABLE_NAME: name of the table to be converted into rec format");
}

int
main(int argc, char **argv)
{
    const char *conninfo;
    PGconn     *conn;
    PGresult   *res;
    int         nFields;
    int         i,
                j;

    /*
     * If the user supplies a parameter on the command line, use it as the
     * conninfo string; otherwise default to setting dbname=postgres and using
     * environment variables or defaults for all other connection parameters.
     */
    if (argc !=3 )
        print_usage();
        
    else
    {
        conninfo = argv[1];
        /* Make a connection to the database */
        conn = PQconnectdb(conninfo);
    /* Check to see that the backend connection was successfully made */
        if (PQstatus(conn) != CONNECTION_OK)
        {
            fprintf(stderr, "Connection to database failed: %s",
            PQerrorMessage(conn));
            exit_nicely(conn);
        }
    /*
     * Our test case here involves using a cursor, for which we must be inside
     * a transaction block.  We could do the whole thing with a single
     * PQexec() of "select * from pg_database", but that's too trivial to make
     * a good example.
     */

    /* Start a transaction block */
        res = PQexec(conn, "BEGIN");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }

        writ = rec_writer_new (stdout);           //initialising rec_writer to write on stdout
        /*
     * Should PQclear PGresult whenever it is no longer needed to avoid memory
     * leaks
     */
   
     //PQclear(res);
        PQclear(res);
        char string[100]="";    //empty string,to be used in query formation while concatinating.
        struct gre2rec *g2r;    //struct gre2rec pointer

        g2r=malloc( sizeof(rec_record_t)+ sizeof(rec_field_t)+ sizeof(rec_rset_t)+ sizeof(rec_db_t));   //allocating memory to the g2r pointer.
        g2r->db=rec_db_new(); 
        strcpy(string,"select * from ");
        strcat(string,argv[2]);        //postgresqlquery to specify the contents of each table in database

        res = PQexec(conn,string);
        g2r->rset = rec_rset_new ();        //initialising a new rset i.e for postgresql it is a new table
  
        g2r->record = rec_record_new();     //initialising a new record i.e. for postgresql it is a new row
        g2r->recfield = rec_field_new ("%rec", "test");       //initialising the record descriptor
        rec_mset_append (rec_record_mset (g2r->record), MSET_FIELD, (void *) g2r->recfield, MSET_ANY);
        rec_rset_set_descriptor (g2r->rset, g2r->record); 
    //res = PQexec(conn, "FETCH ALL in myportal");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(conn));
            PQclear(res);
            exit_nicely(conn);
        }

    /* first, print out the attribute names */
        nFields = PQnfields(res);

    /* next, print out the rows */
        for (i = 0; i < PQntuples(res); i++)
        {
            g2r->record=rec_record_new();       //a new record is initialised.
            for (j = 0; j < nFields; j++)
            {   
                g2r->recfield = rec_field_new (PQfname(res, j), PQgetvalue(res, i, j));     //inserting the field_name(f) and the field_value in the field structure
                rec_mset_append (rec_record_mset (g2r->record), MSET_FIELD, (void *) g2r->recfield, MSET_ANY); //appending the field to the record
            }
            rec_mset_append (rec_rset_mset (g2r->rset), MSET_RECORD, (void *) g2r->record, MSET_ANY);    //appending the record to the rset
        }
      
        rec_db_insert_rset (g2r->db, g2r->rset, rec_db_size (g2r->db));
        rec_write_db (writ,g2r->db);        //writing the database onto stdout

        PQclear(res);

    /* close the portal ... we don't bother to check for errors ... */
        res = PQexec(conn, "CLOSE myportal");
        PQclear(res);
   
    /* end the transaction */
        res = PQexec(conn, "END");
        PQclear(res);

    /* close the connection to the database and cleanup */
        PQfinish(conn);

        return 0;
    }
}