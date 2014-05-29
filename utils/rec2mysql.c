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
static void rec2mysql_parse_args (int argc, char **argv);
static bool rec2mysql_process_data (rec_db_t db);
static rec_fex_t rec2mysql_determine_fields (rec_rset_t rset);
static void rec2mysql_generate_mysql (rec_rset_t rset, rec_fex_t fex);

/*
 * Types
 */

/*
 * Global variables
 */

char             *rec2mysql_record_type    = NULL;
rec_fex_t         rec2mysql_sort_by_fields = NULL;
char              rec2mysql_delim          = ',';
char              table_name[50]         ="";
char              query[1000]             ="create table ";
char const *ftype[20];
char const *fkey[10];

/*
 * Command line options management
 */

enum
  {
    COMMON_ARGS,
    RECORD_TYPE_ARG,
    SORT_ARG
  };

static const struct option GNU_longOptions[] =
  {
    COMMON_LONG_ARGS,
    {"type", required_argument, NULL, RECORD_TYPE_ARG},
    {"sort", required_argument, NULL, SORT_ARG},
    {NULL, 0, NULL, 0}
  };


/*
 * Functions.
 */
 void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

void
recutl_print_help (void)
{
  /* TRANSLATORS: --help output, rec2mysql synopsis.
     no-wrap */
  printf (_("\
Usage: rec2mysql [OPTIONS]... [REC_FILE]\n"));

  /* TRANSLATORS: --help output, rec2mysql short description.
     no-wrap */
  fputs (_("\
Convert rec data into mysql data.\n"), stdout);

  puts ("");
  /* TRANSLATORS: --help output, rec2mysql options.
     no-wrap */
  fputs (_("\
  -d, --delim=char                    sets the deliminator (default ',')\n\
  -t, --type=TYPE                     record set to convert to mysql; if this parameter\n\
                                        is omitted then the default record set is used\n\
  -S, --sort=FIELDS                   sort the output by the specified fields.\n"),
         stdout);

  recutl_print_help_common ();
  puts ("");
  recutl_print_help_footer ();
}

static void
rec2mysql_parse_args (int argc,
                    char **argv)
{
  int ret;
  char c;

  while ((ret = getopt_long (argc,
                             argv,
                             "t:S:d:",
                             GNU_longOptions,
                             NULL)) != -1)
    {
      c = ret;
      switch (c)
        {
          COMMON_ARGS_CASES
        case RECORD_TYPE_ARG:
        case 'd':
          {
            rec2mysql_delim = optarg[0];
            break;
          }
        case 't':
          {
            rec2mysql_record_type = xstrdup (optarg);
            break;
          }
        case SORT_ARG:
        case 'S':
          {
            if (rec2mysql_sort_by_fields)
              {
                recutl_fatal (_("only one list of fields can be specified as a sorting criteria.\n"));
              }

            /* Parse the field name.  */

            if (!rec_fex_check (optarg, REC_FEX_CSV))
              {
                recutl_fatal (_("invalid field name list in -S.\n"));
              }

            rec2mysql_sort_by_fields = rec_fex_new (optarg, REC_FEX_CSV);
            if (!rec2mysql_sort_by_fields)
              {
                recutl_fatal (_("internal error creating fex.\n"));
              }

            break;
          }
        default:
          {
            exit (EXIT_FAILURE);
          }
        }
    }
}
char *field_name[30];
char *field_name1[30];
static void
rec2mysql_generate_mysql (rec_rset_t rset,
                      rec_fex_t fex)
{
  rec_mset_iterator_t iter;
  rec_fex_elem_t fex_elem[20];
  rec_record_t record;
  rec_field_t field[30];
  rec_record_t record1;
  rec_fex_elem_t fex_elem1[20];
  
  rec_field_t field1[30];
  

 
  
  char *tmp;
  size_t i;
   MYSQL *con = mysql_init(NULL);
  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", "root", "k", "test", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  } 
  

  /* Generate the row with headers.  */
  for (i = 0; i < rec_fex_size (fex); i++)
    {
      fex_elem[i] = rec_fex_get (fex, i);
      field_name[i] = xstrdup (rec_fex_elem_field_name (fex_elem[i]));
     
      /* The header is FNAME or FNAME_N where N is the index starting
         at 1.  Note that we shall remove the trailing ':', if any. */

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
  
   for (i = 0; i < rec_fex_size (fex); i++)
   {

    k=0;
     while(ftype[k]!='\0')
    {
     
     strcpy(fcpy,ftype[k]);
      strtok(fcpy," ");
    if((strcmp(fcpy,field_name[i]))==0)
      {
        v_flag=0;

        if(i==rec_fex_size(fex)-1 )
        {
          strcat(query,ftype[k]);
          last_flag=1;

        }
          
          else
          strcat(query,ftype[k]);
          k++;
          break;
          
      }
      else
        v_flag=1;
  
      k++;
    }
       if(ftype[k]=='\0' && last_flag==0 )
    {
      if(v_flag)
      {
        strcat(query,field_name[i]);
        strcat(query," varchar(50)");
      }
    }
    if(i==rec_fex_size(fex)-1)
      strcat(query,"");
    else
      strcat(query,",");
 
   }
   int l=0;
   if(fkey[l]!=NULL)
   {
    strcat(query,",primary key(");
      strcat(query,fkey[l]);
      strcat(query,"))");

   }
   else
   strcat(query,")");
   if (mysql_query(con, query)) {
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
    
      if (mysql_query(con, values)) {
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
      if (((rec2mysql_record_type)
           && rec_rset_type (rset)
           && (strcmp (rec_rset_type (rset),
                       rec2mysql_record_type) == 0))
          || (!rec2mysql_record_type
              && (!rec_rset_type (rset) ||
                  (rec_db_size (db) == 1))))
        {
          /* Process this record set.  */
          

          strcat(table_name,rec_rset_type(rset));
          strcat(query,table_name);
          strcat(query,"(");

            recdesc=rec_rset_descriptor (rset);
            m=malloc( sizeof(rec_mset_t));
            int j;
            
            m= rec_record_mset (recdesc);

              iter = rec_mset_iterator (m);
              int k=0;int l;
              while (rec_mset_iterator_next (&iter, MSET_FIELD, (const void **) &field, NULL))
              {
                fname=rec_field_name(field);

                if(strstr(fname,"%type")!=NULL)
                {
                    ftype[k]=rec_field_value(field);
                    k++;
                }
                 
               if(strstr(fname,"%key")!=NULL)
                {
                  fkey[l]=rec_field_value(field);
                  l++;
                }

              }

              k=0;
           
          if (!rec_rset_sort (rset, rec2mysql_sort_by_fields))
            recutl_out_of_memory ();

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


  recutl_init ("rec2mysql");

  /* Parse arguments.  */
  rec2mysql_parse_args (argc, argv);

  /* Get the input data.  */
  db = recutl_build_db (argc, argv);
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
  
  return res;
}

/* End of rec2mysql.c */
