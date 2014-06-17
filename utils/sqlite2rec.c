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
        int col;
         int j=0;
  int i=0;
  #define TYPE_VALUE_SIZE 250
  char type_value[TYPE_VALUE_SIZE];
  char *fnull[100];
  char *funi[100];
  char *fpri[100];  
  char *fauto[100];
  int count=0;
  int count1=0;
  int count2=0;
  int count3=0;
  char *f[100];     //array to store all field names
  int x=0;
    
for(col=0;col<cols;col++)   //loop until field name is fetched 
{ 
    
    type_value[0] = 0;
    if(j<=cols)
    f[j]=strdup(sqlite3_column_name(stmt,col));   //all field names are copied into a variable f[] one by one.
    j++;  
    int pNotNull;
    int pPrimaryKey; 
    int pAutoinc;
    const char  *pzDataType, *pzCollSeq;
    sqlite3_table_column_metadata(handle,NULL, args[2], sqlite3_column_name(stmt,col),  &pzDataType, &pzCollSeq, &pNotNull, &pPrimaryKey,&pAutoinc );

    


     if(pAutoinc==1)         //checking if field has an auto_increment type 
     {
          fauto[count3]=strdup(sqlite3_column_name(stmt,col));    //storing the fields which are auto_incremented in an array.
          count3++;  
          
     }
     if(pNotNull==1)               //checking if field is NOT NULL i.e. mandatory
     {    
     
          fnull[count]=strdup(sqlite3_column_name(stmt,col));       //storing the fields which are mandatory in an array.
          count++;
          
     }


    if(pPrimaryKey==1)           //checking if the field is primary 
     {
            fpri[count2]=strdup(sqlite3_column_name(stmt,col));
            count2++;      
            
      }

     /*checking the type of field-if it is real*/
      if(strcmp(pzDataType,"FLOAT")==0)
      {
         snprintf (type_value, TYPE_VALUE_SIZE,"%s real", sqlite3_column_name(stmt,col));
        
      }
      
      /*checking the type of field-if it is int*/
      if(strcmp(pzDataType,"INTEGER")==0)
      {
        snprintf (type_value, TYPE_VALUE_SIZE,"%s int", sqlite3_column_name(stmt,col));
       
      }


       /*checking the type of field-if it is date*/
      /*if(MYSQL_TYPE_DATE == field->type)
      {
        snprintf (type_value, TYPE_VALUE_SIZE,"%s date", field->name);

      }*/

  if (type_value[0] != 0)
        {
          /* Insert a type field for this field.  */
          s2r->recfield = rec_field_new ("%type", type_value);
          rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY);
        }
  
  

}  
/*copying the fields in proper format(if more than 1 field which are mandatory are there in record set)*/
if(count!=0)
{
char s[100]="";
for(x=0;x<count;x++)
{
       strcat(s,fnull[x]);
       strcat(s," ");
                     
}
      s2r->recfield = rec_field_new ("%mandatory",s);
      rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY);
}



/*copying the fields in proper format(if more than 1 field which are primary keys(composite primary key in mysql) are there in record set)*/
if(count2!=0)
{
  char s[100]="";
for(x=0;x<count2;x++)
{
       strcat(s,fpri[x]);
       strcat(s," ");        
                        
}

      s2r->recfield = rec_field_new ("%key",s);
      rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY);
}

/*copying the fields in proper format(if more than 1 field which are auto_incremented are there in record set)*/
if(count3!=0)
{
  char s[100]="";
for(x=0;x<count3;x++)
{
       strcat(s,fauto[x]);
       strcat(s," ");
                     
}
      s2r->recfield = rec_field_new ("\%auto",s);
      rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY);
}

        rec_rset_set_descriptor (s2r->rset, s2r->record);   
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
