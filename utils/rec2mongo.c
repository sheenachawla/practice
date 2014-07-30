#include <config.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <xalloc.h>
#include <gettext.h>
#define _(str) gettext (str)
#include <rec.h>
#include <recutl.h>
#include <bson.h>
#include <mongoc.h>
#include <stdio.h>

/* Forward declarations.  */
static bool rec2mongo_process_data (rec_db_t db);
static rec_fex_t rec2mongo_determine_fields (rec_rset_t rset);
static void rec2mongo_generate_mongo (rec_rset_t rset, rec_fex_t fex);

/*
 * Global variables
 */

char              table_name[50]          ="";
char              query[1500]             ="create table ";
char              const *ftype[20];
char              const *fkey[10];
char              const *funi[20];
char              const *fnnull[20];
char              const *fauto[20];
char              table[10];
char              dname[10];
char              *field_name[50];


/*
 * Functions.
 */
 /*Command line arguments  print usage function*/
 void print_usage(void)       
 {
    printf("Usage: rec2mongo [REC_FILE] [DATABASE_NAME] [TABLE_NAME]\n");
    printf("REC_FILE: file to be converted into mongodb format.\n");
    printf("DATABASE_NAME: name of the database in which the new table needs to be created.\n");
    printf("TABLE_NAME : name of the table taht needs to be created\n");
 }

 static void
rec2mongo_generate_mongo (rec_rset_t rset,rec_fex_t fex)
{
    rec_mset_iterator_t iter;
    rec_fex_elem_t fex_elem[20];
    rec_record_t record;
    rec_field_t field[30];
     char *tmp;
    size_t i;

      mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    bson_error_t error;
    bson_oid_t oid;
    bson_t *doc;

    mongoc_init ();

    client = mongoc_client_new ("mongodb://localhost:27017/");
    collection = mongoc_client_get_collection (client, dname, table);

    //doc = bson_new ();
    //bson_oid_init (&oid, NULL);

    /* Generate the row with headers.  */
    for (i = 0; i < rec_fex_size (fex); i++)
    {
        fex_elem[i] = rec_fex_get (fex, i);
        field_name[i] = xstrdup (rec_fex_elem_field_name (fex_elem[i]));
     
      /* The header is FNAME or FNAME_N where N is the index starting
         at 1. */

        if (rec_fex_elem_min (fex_elem[i]) != 0)
        {
            if (asprintf (&tmp, "%s_%d",
                        field_name[i],
                        rec_fex_elem_min (fex_elem[i]) + 1) == -1)
              recutl_out_of_memory ();
        }
        else
        {
            if (asprintf (&tmp, "%s", field_name[i]) == -1)
              recutl_out_of_memory ();
        }
            printf("%s\n",field_name[i] );
 
    }
 


   /*  for (i = 0; i < rec_fex_size (fex); i++)
   {
        k=0;
        while(ftype[k]!='\0')                                      //checking for every type mentioned in the rec file against all the field names
        {
           strcpy(fcpy,ftype[k]);
           strtok(fcpy," ");
           if((strcmp(fcpy,field_name[i]))==0)
           {
              v_flag=0;
              if(i==rec_fex_size(fex)-1 )
              {
                  strcat(query,ftype[k]);                               //concatinating the type of the field to the query formed for mysql create table query
                  last_flag=1;                                           //last_flag is 1 when the field that is being checked is the last one to be inserted in the query.
              }
              else
                  strcat(query,ftype[k]);
              n=0;

              while(fnnull[n]!='\0')
              {
                  strcat(fnull,fnnull[n]);
                  if((memcmp(fnull,field_name[i],strlen(fnull)-1)==0))
                  {
                      strcat(query," NOT NULL");
                  }
                  strcpy(fnull,"\0");
                  n++;
              }
              a=0;
              while(fauto[a]!='\0')
              {
                  strcat(fto,fauto[a]);
                  if((memcmp(fto,field_name[i],strlen(fto)-1)==0))
                  {
                      a_flag=0;
                      strcat(query," AUTO_INCREMENT");
                      strcat(pri,field_name[i]);
                  }
                  strcpy(fto,"\0");
                  a++;
              }
        
              k++;
              break;
          
            }
          else
              v_flag=1;                                                 //v_flag is 1 when the field is string variable
  
          k++;
        }
       if(ftype[k]=='\0' && last_flag==0 )
       {
            if(v_flag)
            {
                strcat(query,field_name[i]);
                strcat(query," varchar(50)");
                n=0;

                while(fnnull[n]!='\0')
                {
                    strcat(fnull,fnnull[n]);
                    if((memcmp(fnull,field_name[i],strlen(fnull)-1)==0))
                    {
                        strcat(query," NOT NULL");
                    }
                    strcpy(fnull,"\0");
                    n++;
                }
                while(fauto[a]!='\0')
                {
                    strcat(fto,fauto[a]);
                    if((memcmp(fto,field_name[i],strlen(fto)-1)==0))
                    {
                      a_flag=0;
                      strcat(query," AUTO_INCREMENT");
                      strcat(pri,field_name[i]);
                    }
                    strcpy(fto,"\0");
                    a++;
                }
            }
        }

        if(i==rec_fex_size(fex)-1)
            strcat(query,"");
        else
            strcat(query,",");
   }
   int l=0;
   if(fkey[l]!=NULL || a_flag==0)                                               //fkey contains all the primary keys,if any, in the mysql query.
   {
      strcat(query,",primary key(");
      if(a_flag==0)
        strcat(query,pri);
      if(fkey[l]!=NULL)
      strcat(query,fkey[l]);
      strcat(query,")");
   }
   int u=0;
   if(funi[u]!=NULL)                                              //funi contains all the unique keys,if any, in the mysql query.
   {
      strcat(query,",unique(");
      strcat(query,funi[l]);
      strcat(query,"))");
   }
   else
      strcat(query,")");*/
    /* Generate the data rows.  */
  char values[100]="";
  //
  iter = rec_mset_iterator (rec_rset_mset (rset));
  while (rec_mset_iterator_next (&iter, MSET_RECORD, (const void**) &record, NULL))
  {
     // strcpy(values,"insert into ");
      //strcat (values, table_name);
      //strcat(values," values(");
      for (i = 0; i < rec_fex_size (fex); i++)
      {
            fex_elem[i] = rec_fex_get (fex, i);
            field[i] = rec_record_get_field_by_name (record,
                                                rec_fex_elem_field_name (fex_elem[i]),
                                                rec_fex_elem_min (fex_elem[i]));
            doc = bson_new ();
        bson_oid_init (&oid, NULL);
          BSON_APPEND_OID (doc, "_id", &oid);
            BSON_APPEND_UTF8 (doc, field_name[i], rec_field_value(field[i]));

    if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, doc, NULL, &error)) {
        printf ("%s\n", error.message);
    }

    bson_destroy (doc);
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);

          /*  strcat(values,"\"");
            strcat(values,rec_field_value(field[i]));
            if(i==(rec_fex_size(fex)-1))
            {
                strcat(values,"\")");
            }
            else
            {
                strcat(values,"\",");
            }*/
      }
    
     /* if (mysql_query(con, values))
      {                                 //mysql query for values to be inserted in the table 
          finish_with_error(con);
      }*/

  }
}

 static rec_fex_t 
rec2mongo_determine_fields (rec_rset_t rset)
{
  rec_fex_t fields;
  rec_mset_iterator_t iter_rset;
  rec_mset_iterator_t iter_record;
  rec_record_t record;
  rec_field_t field;
  int field_index;
  
  fields = rec_fex_new (NULL, REC_FEX_SIMPLE);

  iter_rset = rec_mset_iterator (rec_rset_mset (rset));
  while (rec_mset_iterator_next (&iter_rset, MSET_RECORD, (const void **) &record, NULL))
  {
      iter_record = rec_mset_iterator (rec_record_mset (record));
      while (rec_mset_iterator_next (&iter_record, MSET_FIELD, (const void **) &field, NULL))
      {
          field_index = rec_record_get_field_index_by_name (record, field);
          
          if (!rec_fex_member_p (fields,
                                 rec_field_name (field),
                                 field_index, field_index))
          {
              rec_fex_append (fields,
                              rec_field_name (field),
                              field_index, field_index);
          }
      }

      rec_mset_iterator_free (&iter_record);
  }

  rec_mset_iterator_free (&iter_rset);

  return fields;
}

static bool rec2mongo_process_data(rec_db_t db)
{
  bool ret;
  rec_fex_t row_fields;
  size_t i;
  rec_rset_t rset;

  ret = true;

  for (i = 0; i < rec_db_size (db); i++)
    {
      rset = rec_db_get_rset (db, i);
       if (( (!rec_rset_type (rset) ||
                  (rec_db_size (db) == 1))))
        {
          /* Process this record set.  */

          //if (!rec_rset_sort (rset, rec2csv_sort_by_fields))
            //recutl_out_of_memory ();

          /* Build the fields that will appear in the row. */
          row_fields = rec2mongo_determine_fields (rset);
  
          /* Generate the csv data.  */
          rec2mongo_generate_mongo (rset, row_fields);

          /* Cleanup.  */
          rec_fex_destroy (row_fields);
        }
    }

  return ret;
}


int main (int   argc,
      char *argv[])
{
 
     int res;
     rec_db_t db;
     res = 0;
     int i;
     char *d_argv[50];
     if(argc!=4)
     {
        print_usage();
     }
     else
     {
         recutl_init ("rec2mongo");
        /* Parse arguments.  */
         strcat(dname,argv[2]);
         strcat(table,argv[3]);
        /* Get the input data.  */
         db = recutl_build_db (2, argv);
         if (!db)
         {
           res = 1;
         }
         else
         /* Process the data.  */
           if (!rec2mongo_process_data (db))
           {
             res = 1;
           }
           rec_db_destroy (db);
      }
      return res;   
}