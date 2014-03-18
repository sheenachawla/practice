/* -*- mode: C -*-
 *
 *       File:         csv2rec.c
 *       Date:         Fri Aug 20 16:35:25 2010
 *
 *       GNU recutils - csv to rec converter.
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
 
  char string1[100]="select * from ";     //mysql query to specify the contents of the table (name of table to be specified in argv[[3]])
  strcat(string1,argv[3]);
  if (mysql_query(con, string1))
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
  
  writ = rec_writer_new (stdout);           //initialising rec_writer to write on stdout
  
  struct sql2rec *s2r;    //struct sql2rec pointer

  //allocating memory to s2r pointer
  s2r=malloc( sizeof(rec_record_t)+ sizeof(rec_field_t)+ sizeof(rec_rset_t));
  
  char *f[100];     //array to store all field names
  s2r->rset = rec_rset_new ();        //initialising a new rset i.e for mysql it is a new table
  rec_rset_set_type (s2r->rset, argv[3]);   //setting the rset name
  int j=0;
  int i=0;
      
while(field = mysql_fetch_field(result))   //loop until field name is fetched 
{
    if(j<=num_fields)
    f[j]=strdup(field->name);   //all field names are copied into a variable f[] one by one.
    j++;

}    
  while ((row = mysql_fetch_row(result)))     //loop until every row of result is fetched
  { 
      
      s2r->record=rec_record_new();       //a new record is initialised.
      
      for( i = 0; i < num_fields; i++)     //i have put 2 loops together one for field value and other for the field name.
      {
       
            s2r->recfield = rec_field_new (f[i], row[i]);     //inserting the field_name(f) and the field_value in the field structure
            rec_mset_append (rec_record_mset (s2r->record), MSET_FIELD, (void *) s2r->recfield, MSET_ANY); //appending the field to the record
            
      } 
       rec_mset_append (rec_rset_mset (s2r->rset), MSET_RECORD, (void *) s2r->record, MSET_ANY);    //appending the record to the rset
  }
  
  rec_write_rset (writ,s2r->rset);
  mysql_free_result(result);
  mysql_close(con);
  
  exit(0);
}