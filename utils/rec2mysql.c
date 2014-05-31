/* -*- mode: C -*-
 *
 *       File:         rec2mysql.c

 *
 *       GNU recutils - rec to mysql converter.
 *
 */

#include <config.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <xalloc.h>
#include <gettext.h>
#define _(str) gettext (str)
#include <rec.h>
#include <recutl.h>
 #include <my_global.h>
#include <mysql.h>

/* Forward declarations.  */
static bool rec2mysql_process_data (rec_db_t db);
static rec_fex_t rec2mysql_determine_fields (rec_rset_t rset);
static void rec2mysql_generate_mysql (rec_rset_t rset, rec_fex_t fex);

/*
 * Global variables
 */

char              table_name[50]          ="";
char              query[1000]             ="create table ";
char              const *ftype[20];
char              const *fkey[10];
char              const *funi[20];
char              const *fnnull[20];
char              pass[10];
char              dname[10];
char              *field_name[50];


/*
 * Functions.
 */
 /*Command line arguments  print usage function*/
 void print_usage(void)       
 {
    printf("Usage: rec2mysql [REC_FILE] [ROOT_PASSWORD] [DATABASE_NAME]\n");
    printf("REC_FILE: file to be converted into mysql format.\n");
    printf("ROOT_PASSWORD: password for root login into mysql database.\n");
    printf("DATABASE_NAME: name of the database in which the new table needs to be created.\n");
 }
 /*Mysql error function*/
void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}



static void
rec2mysql_generate_mysql (rec_rset_t rset,rec_fex_t fex)
{
    rec_mset_iterator_t iter;
    rec_fex_elem_t fex_elem[20];
    rec_record_t record;
    rec_field_t field[30];
  
    char *tmp;
    size_t i;
    MYSQL *con = mysql_init(NULL);
  
    if (con == NULL) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }  

    if (mysql_real_connect(con, "localhost", "root", pass, dname, 0, NULL, 0) == NULL)      //mysql connection
    {
        finish_with_error(con);
    } 
  

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
    char fcpy[50];
    int n;
    char fnull[50]="";
  
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
            }
        }

        if(i==rec_fex_size(fex)-1)
            strcat(query,"");
        else
            strcat(query,",");
   }
   int l=0;
   if(fkey[l]!=NULL)                                               //fkey contains all the primary keys,if any, in the mysql query.
   {
      strcat(query,",primary key(");
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
      strcat(query,")");
   
    if (mysql_query(con, query))
    {                                  //mysql query for table creation being executed.
        finish_with_error(con);
    }
  

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

            strcat(values,"\"");
            strcat(values,rec_field_value(field[i]));
            if(i==(rec_fex_size(fex)-1))
            {
                strcat(values,"\")");
            }
            else
            {
                strcat(values,"\",");
            }
      }
    
      if (mysql_query(con, values))
      {                                 //mysql query for values to be inserted in the table 
          finish_with_error(con);
      }

  }

  rec_mset_iterator_free (&iter);
  mysql_close(con);
}

static rec_fex_t
rec2mysql_determine_fields (rec_rset_t rset)
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
rec2mysql_process_data (rec_db_t db)
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
          int l,u=0,n=0;
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
          }

          /* Build the fields that will appear in the row. */
          row_fields = rec2mysql_determine_fields (rset);
  
          /* Generate the mysql data.  */
          rec2mysql_generate_mysql (rset, row_fields);

          /* Cleanup.  */
          rec_fex_destroy (row_fields);
      }
  }

  return ret;
}

int
main (int argc, char *argv[])
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
     recutl_init ("rec2mysql");
    /* Parse arguments.  */
     strcat(pass,argv[2]);
     strcat(dname,argv[3]);
    /* Get the input data.  */
     db = recutl_build_db (2, argv);
     if (!db)
     {
       res = 1;
     }
     else
     /* Process the data.  */
       if (!rec2mysql_process_data (db))
       {
         res = 1;
       }
       rec_db_destroy (db);
    }
    return res;
}

/* End of rec2mysql.c */
