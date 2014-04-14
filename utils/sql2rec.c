/* -*- mode: C -*-
 *
 *       File:         sql2rec.c
 *       Date:         Fri Aug 20 16:35:25 2010
 *
 *       GNU recutils - sql to rec converter.
 *
 */

/* Copyright (C) 2010, 2011, 2012 Jose E. Marchesi */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <getopt.h>
#include <xalloc.h>
#include <gettext.h>
#define _(str) gettext (str)
#include <rec.h>
#include <recutl.h>
#include <my_global.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*sql2rec structure*/
struct sql2rec{
  rec_db_t db;
  rec_rset_t rset;
  rec_record_t record;
  rec_field_t  recfield;

};

/*rec_writer pointer which writes rec files to stdout*/
rec_writer_t writ;


//mysql function for errors
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);  //initializing mysql 
   writ = rec_writer_new (stdout);           //initialising rec_writer to write on stdout
  
  if (con == NULL)                    //checking if mysql variable con is NUll
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, "localhost", "root", argv[1], argv[2], 0, NULL, 0) == NULL)     //connecting to the mysql database//argv[1]= password for mysql
                                                                                             //argv[2]=database name 
  {
      finish_with_error(con);
      
  } 
  if(mysql_query(con,"show tables"))
  {
    finish_with_error(con);
  }

   
  MYSQL_RES *tablesList = mysql_store_result(con);        //variable tablelist stores the values of all tables in database given by user.
  int num_fields1 = mysql_num_rows(tablesList);           
  
  char string[100]="";    //empty string,to be used in query formation while concatinating.
  struct sql2rec *s2r;    //struct sql2rec pointer

  s2r=malloc( sizeof(rec_record_t)+ sizeof(rec_field_t)+ sizeof(rec_rset_t)+ sizeof(rec_db_t));   //allocating memory to the s2r pointer.
  s2r->db=rec_db_new();         //creatng new database


  while (num_fields1!=0)            //loop executes till all record sets of database are included.
  {
    num_fields1--;
    MYSQL_ROW res= mysql_fetch_row(tablesList); //res stores the result of the query show tables
    strcpy(string,"select * from ");
    strcat(string,res[0]);        //mysql query to specify the contents of each table in database
    
 
  if (mysql_query(con, string))
  {  
      finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);    //storing the mysql query result

  if (result == NULL) 
  {
      finish_with_error(con);
  }  


  int num_fields = mysql_num_fields(result);    //number of fields in result 
  

  MYSQL_ROW row;
  MYSQL_FIELD *field,*field2;
  /*initializing flags used for special keys */
  int count=0;
  int count1=0;
  int count2=0;
  int count3=0;
  char *f[100];     //array to store all field names
  s2r->rset = rec_rset_new ();        //initialising a new rset i.e for mysql it is a new table
  
  s2r->record = rec_record_new();     //initialising a new record i.e. for mysql it is a new row
  s2r->recfield = rec_field_new ("%rec", res[0]);       //initialising the record descriptor
  rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY);

  
  int j=0;
  int i=0;
  #define TYPE_VALUE_SIZE 250
  char type_value[TYPE_VALUE_SIZE];
  char *fnull[100];
  char *funi[100];
  char *fpri[100];  
  char *fauto[100];
  int x=0;
    
while(field = mysql_fetch_field(result))   //loop until field name is fetched 
{ 
    
    type_value[0] = 0;
    if(j<=num_fields)
    f[j]=strdup(field->name);   //all field names are copied into a variable f[] one by one.
    j++;  
    


     if(field->flags & AUTO_INCREMENT_FLAG)         //checking if field has an auto_increment type 
     {
          fauto[count3]=strdup(field->name);    //storing the fields which are auto_incremented in an array.
          count3++;  
          
      }
     if(field->flags & NOT_NULL_FLAG)               //checking if field is NOT NULL i.e. mandatory
     {    
     
          fnull[count]=strdup(field->name);       //storing the fields which are mandatory in an array.
          count++;
          
      }

    if(field->flags & UNIQUE_KEY_FLAG)           //checking if field is unique
     {
          funi[count1]=strdup(field->name);
          count1++;
             
      }

    if(field->flags & PRI_KEY_FLAG)           //checking if the field is primary 
     {
            fpri[count2]=strdup(field->name);
            count2++;      
            
      }

     /*checking the type of field-if it is real*/
      if(MYSQL_TYPE_FLOAT == field->type || MYSQL_TYPE_DECIMAL == field->type || MYSQL_TYPE_DOUBLE ==field->type)
      {
         snprintf (type_value, TYPE_VALUE_SIZE,"%s real", field->name);
        
      }
      
      /*checking the type of field-if it is int*/
      if(MYSQL_TYPE_TINY == field->type || MYSQL_TYPE_SHORT == field->type || MYSQL_TYPE_LONG == field->type || MYSQL_TYPE_INT24 ==field->type || MYSQL_TYPE_LONGLONG == field->type)
      {
        snprintf (type_value, TYPE_VALUE_SIZE,"%s int", field->name);
       
      }

       /*checking the type of field-if it is enum*/
      if(MYSQL_TYPE_ENUM == field->type)
      {
        snprintf (type_value, TYPE_VALUE_SIZE,"%s enum", field->name);
      
      }

       /*checking the type of field-if it is date*/
      if(MYSQL_TYPE_DATE == field->type)
      {
        snprintf (type_value, TYPE_VALUE_SIZE,"%s date", field->name);

      }

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


/*copying the fields in proper format(if more than 1 field which are unique are there in record set)*/
if(count1!=0)
{
  char s[100]="";
for(x=0;x<count1;x++)
{
       strcat(s,funi[x]);
       strcat(s," ");
                     
}
      s2r->recfield = rec_field_new ("\%unique",s);
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
  while ((row = mysql_fetch_row(result)))     //loop until every row of result is fetched
  { 
      
      s2r->record=rec_record_new();       //a new record is initialised.
      
      for( i = 0; i < num_fields; i++)     //loops for field value .
      {
        
            s2r->recfield = rec_field_new (f[i], row[i]);     //inserting the field_name(f) and the field_value in the field structure
            rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY); //appending the field to the record
            
      } 
       rec_mset_append (rec_rset_mset (s2r->rset), MSET_RECORD, (void *) s2r->record, MSET_ANY);    //appending the record to the rset

  }
  rec_db_insert_rset (s2r->db, s2r->rset, rec_db_size (s2r->db)); //inserting the record sets into database
  mysql_free_result(result);
  
}
rec_write_db (writ,s2r->db);        //writing the database onto stdout

  mysql_close(con);
  
  exit(0);
}