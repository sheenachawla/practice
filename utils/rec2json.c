#include <config.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <xalloc.h>
#include <gettext.h>
#define _(str) gettext (str)
#include <rec.h>
#include <recutl.h>
#include <json/json.h>
#include <stdio.h>

/* Forward declarations.  */
static bool rec2json_process_data (rec_db_t db);
static rec_fex_t rec2json_determine_fields (rec_rset_t rset);
static void rec2json_generate_json (rec_rset_t rset, rec_fex_t fex);

/*
 * Global variables
 */

char              table[10];
char              dname[10];
char              *field_name[50];


/*
 * Functions.
 */
 /*Command line arguments  print usage function*/
 void print_usage(void)       
 {
    printf("Usage: rec2json [REC_FILE] [DATABASE_NAME] [TABLE_NAME]\n");
    printf("REC_FILE: file to be converted into json format.\n");

 }

 static void
rec2json_generate_json (rec_rset_t rset,rec_fex_t fex)
{
    rec_mset_iterator_t iter;
    rec_fex_elem_t fex_elem[20];
    rec_record_t record;
    rec_field_t field[30];
    char *tmp;
    size_t i;
  

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
 
     json_object * jobj = json_object_new_object();
    /* Generate the data rows.  */
    iter = rec_mset_iterator (rec_rset_mset (rset));
    while (rec_mset_iterator_next (&iter, MSET_RECORD, (const void**) &record, NULL))
    {
    	
    
        for (i = 0; i < rec_fex_size (fex); i++)
        {
	              fex_elem[i] = rec_fex_get (fex, i);
	              field[i] = rec_record_get_field_by_name (record,
	                                                  rec_fex_elem_field_name (fex_elem[i]),
	                                                  rec_fex_elem_min (fex_elem[i]));

	               /*Creating a json string*/
	  				json_object *jstring = json_object_new_string(rec_field_value(field[i]));
	  				/*Each of these is like a key value pair*/
	  				json_object_object_add(jobj,field_name[i], jstring);
        }
              
             
    }
      /*Now printing the json object*/
  		printf ("The json object : %s\n",json_object_to_json_string(jobj));
}
 static rec_fex_t 
rec2json_determine_fields (rec_rset_t rset)
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


static bool rec2json_process_data(rec_db_t db)
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

          /* Build the fields that will appear in the row. */
          row_fields = rec2json_determine_fields (rset);
     
  
          /* Generate the csv data.  */
          rec2json_generate_json (rset, row_fields);

          /* Cleanup.  */
          rec_fex_destroy (row_fields);
        }
    }

  return ret;
}



int main(int   argc,char *argv[]) {
 

     int res;
     rec_db_t db;
     res = 0;
     int i;
     char *d_argv[50];
     if(argc!=2)
     {
        print_usage();
     }
     else
     {
     	
         recutl_init ("rec2json");
       
        /* Get the input data.  */
         db = recutl_build_db (2, argv);
   
         if (!db)
         {
           res = 1;
         }
         else
         /* Process the data.  */
           if (!rec2json_process_data (db))
           {
           	
             res = 1;
           }
           rec_db_destroy (db);
      }
      return res; 

}