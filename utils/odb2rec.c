#include <config.h>
#include <getopt.h>
#include <xalloc.h>
#include <gettext.h>
#define _(str) gettext (str)
#include <rec.h>
#include <recutl.h>
#include "ocilib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TYPE_VALUE_SIZE 250


/*odb2rec structure*/
struct odb2rec{
  rec_db_t db;
  rec_rset_t rset;
  rec_record_t record;
  rec_field_t  recfield;

};

/*rec_writer pointer which writes rec files to stdout*/
rec_writer_t writ;


void err_handler(OCI_Error *err)
{
    printf("error ORA-% 05i-msg:%s\n",OCI_ErrorGetOCICode(err),OCI_ErrorGetString(err) );
}

void print_usage(void)
{
    printf("Usage: odb2rec [USERNAME] [PASSWORD] [TABLE_NAME]\nPASSWORD: password for login into oracle database\nTABLE_NAME: name of the table from which rec file is created\n");
}
 
int main(int argc, char *argv[])
{
    if(argc!=4)
    {
        print_usage();
    }
    else
    {
        int i=0;
        int n=0;
        OCI_Connection* cn;
        OCI_Statement* st;
        OCI_Resultset* rs;
        writ = rec_writer_new (stdout);           //initialising rec_writer to write on stdout
        
        char type_value[TYPE_VALUE_SIZE];
         
        
        if(!OCI_Initialize(err_handler, NULL, OCI_ENV_DEFAULT)) //initializing oracle db
        return EXIT_FAILURE;
     
        cn = OCI_ConnectionCreate("XE", argv[1], argv[2], OCI_SESSION_DEFAULT); //connecting to the oracle database, here argv[1] is the username and argv[2] is the password.
        st = OCI_StatementCreate(cn);
        
        char string[100]="";    //empty string,to be used in query formation while concatinating.
        struct odb2rec *o2r;    //struct odb2rec pointer

        o2r=malloc( sizeof(rec_record_t)+ sizeof(rec_field_t)+ sizeof(rec_rset_t)+ sizeof(rec_db_t));   //allocating memory to the o2r pointer.
        o2r->db=rec_db_new();  //creating new database

        strcpy(string,"select * from ");
        strcat(string,argv[3]);

      
        OCI_ExecuteStmt(st, string);
        rs = OCI_GetResultset(st);
        n  = OCI_GetColumnCount(rs);

        o2r->rset = rec_rset_new ();        //initialising a new rset i.e for oracle it is a new table
        o2r->record = rec_record_new();     //initialising a new record i.e. for oracle it is a new row
        o2r->recfield = rec_field_new ("%rec", argv[3]);       //initialising the record descriptor
        rec_mset_append (rec_record_mset (o2r->record), MSET_FIELD, (void *) o2r->recfield, MSET_ANY);
       

       for(i=1;i<=n;i++)
       {
            
            type_value[0] = 0;
            OCI_Column *col = OCI_GetColumn(rs, i);
             /*checking the type of field-if it is real*/
       
            if(strcmp(OCI_GetColumnSQLType(col),"NUMBER")==0)
            {
                snprintf (type_value, TYPE_VALUE_SIZE,"%s int", OCI_ColumnGetName(col));
            
            }
           
            if(strcmp(OCI_GetColumnSQLType(col),"DATE")==0)
            {
                snprintf (type_value, TYPE_VALUE_SIZE,"%s date", OCI_ColumnGetName(col));
            
            }
            if(strcmp(OCI_GetColumnSQLType(col),"FLOAT")==0 )
            {
                snprintf (type_value, TYPE_VALUE_SIZE,"%s real", OCI_ColumnGetName(col));
            
            }
            if (type_value[0] != 0)
            {
              /* Insert a type field for this field.  */
              o2r->recfield = rec_field_new ("%type", type_value);
              rec_mset_append (rec_record_mset (o2r->record), MSET_FIELD, (void *) o2r->recfield, MSET_ANY);
            }
        }
        
        rec_rset_set_descriptor (o2r->rset, o2r->record);
     
        while (OCI_FetchNext(rs))
        {
           
            o2r->record=rec_record_new();       //a new record is initialised.
            for(i = 1; i <= n; i++)
            {
                
                OCI_Column *col = OCI_GetColumn(rs, i);
                o2r->recfield = rec_field_new (OCI_ColumnGetName(col), OCI_GetString(rs,i));     //inserting the field_name(f) and the field_value in the field structure
                rec_mset_append (rec_record_mset (o2r->record), MSET_FIELD, (void *) o2r->recfield, MSET_ANY); //appending the field to the record
            }
            rec_mset_append (rec_rset_mset (o2r->rset), MSET_RECORD, (void *) o2r->record, MSET_ANY);    //appending the record to the rset
          
        }
        
        rec_db_insert_rset (o2r->db, o2r->rset, rec_db_size (o2r->db)); //inserting the record sets into database
        rec_write_db (writ,o2r->db);        //writing the database onto stdout

     
        OCI_Cleanup();
     
        return EXIT_SUCCESS;
    }
}