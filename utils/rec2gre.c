/*
 * testlibpq.c
 *
 *      Test the C version of libpq, the PostgreSQL frontend library.
 */
#include <config.h>
#include <getopt.h>
#include <string.h>
#include <xalloc.h>
#include <gettext.h>
#define _(str) gettext (str)
#include <rec.h>
#include <recutl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

/* Forward declarations.  */
static bool rec2gre_process_data (rec_db_t db);
static rec_fex_t rec2gre_determine_fields (rec_rset_t rset);
static void rec2gre_generate_gre (rec_rset_t rset, rec_fex_t fex);

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
char              pass[10];
char              dname[50];
char              *field_name[50];
const char        *conninfo;
PGconn            *conn;
PGresult          *res;
int               nFields;

/*
 * Functions.
 */
 /*Command line arguments  print usage function*/
 void print_usage(void)       
 {
    printf("Usage: rec2gre [REC_FILE] [ROOT_PASSWORD] [DATABASE_NAME]\n");
    printf("REC_FILE: file to be converted into postgre format.\n");
    printf("ROOT_PASSWORD: password for root login into postgre database.\n");
    printf("DATABASE_NAME: name of the database in which the new table needs to be created.\n");
 } 

static void
exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}

static void
rec2gre_generate_gre (rec_rset_t rset,rec_fex_t fex)
{
    rec_mset_iterator_t iter;
    rec_fex_elem_t fex_elem[20];
    rec_record_t record;
    rec_field_t field[30];
  
    char *tmp;
    size_t i;

    conninfo = dname;
   

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
 
    }
   
    int k=0;
    int last_flag=0;
    int v_flag;
    int a_flag;
    char fcpy[50];
    int n,a;
    char fnull[50]="";
    char fto[50]="";
    char pri[50]="";
  
   for (i = 0; i < rec_fex_size (fex); i++)
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
                  strcat(query,ftype[k]);                               //concatinating the type of the field to the query formed for postgre create table query
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
                      strcat(query," serial");
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
                strcat(query," text");
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
                      strcat(query," seial");
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
   if(fkey[l]!=NULL || a_flag==0)                                               //fkey contains all the primary keys,if any, in the postgre query.
   {
      strcat(query,",primary key(");
      if(a_flag==0)
        strcat(query,pri);
      if(fkey[l]!=NULL)
      strcat(query,fkey[l]);
      strcat(query,")");
   }
   int u=0;
   if(funi[u]!=NULL)                                              //funi contains all the unique keys,if any, in the postgre query.
   {
      strcat(query,",unique(");
      strcat(query,funi[l]);
      strcat(query,"))");
   }
   else
      strcat(query,")");
   
  
    //PQclear(res);
  

    res = PQexec(conn,query);
     PQclear(res);
     

  

  /* Generate the data rows.  */
  char values[100]="";
  //
  iter = rec_mset_iterator (rec_rset_mset (rset));
  while (rec_mset_iterator_next (&iter, MSET_RECORD, (const void**) &record, NULL))
  {
      strcpy(values,"insert into ");
      strcat (values, table_name);
      strcat(values," values(");
      for (i = 0; i < rec_fex_size (fex); i++)
      {
            fex_elem[i] = rec_fex_get (fex, i);
            field[i] = rec_record_get_field_by_name (record,
                                                rec_fex_elem_field_name (fex_elem[i]),
                                                rec_fex_elem_min (fex_elem[i]));

            strcat(values,"\'");
            strcat(values,rec_field_value(field[i]));
            if(i==(rec_fex_size(fex)-1))
            {
                strcat(values,"\')");
               ;
            }
            else
            {
                strcat(values,"\',");
                
            }
      }
      
     
    res=PQexec(conn,values);
    PQclear(res);
    

    /* close the portal ... we don't bother to check for errors ... */
    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

   
    /* close the connection to the database and cleanup */
    

  }
 

  rec_mset_iterator_free (&iter);
  PQfinish(conn);
}

static rec_fex_t
rec2gre_determine_fields (rec_rset_t rset)
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

static bool
rec2gre_process_data (rec_db_t db)
{
  bool ret;
  rec_fex_t row_fields;
  size_t i;
  rec_rset_t rset;
  rec_record_t recdesc;
  rec_mset_iterator_t iter;
  rec_field_t field;
  rec_mset_t m;
  const char * fname;

  ret = true;
  

  for (i = 0; i < rec_db_size (db); i++)
  {
      rset = rec_db_get_rset (db, i);
      if (( (!rec_rset_type (rset) ||
                  (rec_db_size (db) == 1))))
      {
          /* Process this record set.  */
          strcat(table_name,rec_rset_type(rset));
          strcat(query,table_name);
          strcat(query,"(");

          recdesc=rec_rset_descriptor (rset);
          m=malloc( sizeof(rec_mset_t));
          int j;
          m= rec_record_mset (recdesc);                                 //this record contains the the record descriptor.
          iter = rec_mset_iterator (m);
          int k=0;
          int l,u=0,n=0,a=0;
          while (rec_mset_iterator_next (&iter, MSET_FIELD, (const void **) &field, NULL))
          {
              fname=rec_field_name(field);
              if(strstr(fname,"%type")!=NULL)                          //comparing every field name of the record descriptor.
              {
                 ftype[k]=rec_field_value(field);                     //this one is for data type
                 k++;
              }
              if(strstr(fname,"%key")!=NULL)                             //primary key
              {
                 fkey[l]=rec_field_value(field);
                 l++;
              }
              if(strstr(fname,"%unique")!=NULL)                             //unique key
              {
                 funi[u]=rec_field_value(field);
                 u++;
              }
              if(strstr(fname,"%mandatory")!=NULL)                             //mandatory key
              {
                 fnnull[n]=rec_field_value(field);
                 n++;
              }
               if(strstr(fname,"%auto")!=NULL)                             //mandatory key
              {
                 fauto[a]=rec_field_value(field);
                 a++;
              }
          }
         
         
          /* Build the fields that will appear in the row. */
          row_fields = rec2gre_determine_fields (rset);
       
  
          /* Generate the postgre data.  */
          rec2gre_generate_gre (rset, row_fields);
      
          /* Cleanup.  */
          rec_fex_destroy (row_fields);
      }
  }

  return ret;
}

int
main(int argc, char **argv)
{
    int res;
   rec_db_t db;
   

   res = 0;
   int i;
   if(argc!=3)
   {
      print_usage();
   }
   else
   {
     recutl_init ("rec2gre");
    /* Parse arguments.  */
     //strcat(pass,argv[2]);
    
     strcat(dname,argv[2]);
   
    /* Get the input data.  */
     db = recutl_build_db (2, argv);
     if (!db)
     {
       res = 1;
     }
     else
     /* Process the data.  */
       if (!rec2gre_process_data (db))
       {
         res = 1;
       }
       rec_db_destroy (db);
    }
    return res;

    return 0;
}