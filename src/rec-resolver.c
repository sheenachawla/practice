/* -*- mode: C -*- Time-stamp: "2010-04-07 21:32:29 jemarch"
 *
 *       File:         rec-resolver.c
 *       Date:         Mon Jan 11 14:29:18 2010
 *
 *       GNU recutils - Resolver
 *
 */

/* Copyright (C) 2010 Jose E. Marchesi */

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

#include <malloc.h>
#include <string.h>
#include <regex.h>

#include <rec.h>

/* Static forward references.  */

struct rec_resolver_part_s;

static char *rec_resolver_parse_int (char *p, int *num);
static bool rec_resolve_part (rec_record_t record, struct rec_resolver_part_s *part, FILE *out);
static bool rec_parse_part (char *str, struct rec_resolver_part_s *part);

/* 
 * Data structures
 */

struct rec_resolver_part_s
{
  char *field_name;

  char prefix_mod;    /* '/' */
  int min;            /* If 'max' is -1 then 'min' acts like an index.
                         Otherwise it is a lower bound.  */
  int max;            /* Upper bound.  */
};


/*
 * Public functions
 */

bool
rec_resolver_check (char *expr)
{
  int ret;
  static char *regexp_str = "(/?%?[a-zA-Z][a-zA-Z0-9_])+";
  regex_t regexp;

  /* Compile the regexp.  */
  if ((ret = regcomp (&regexp, regexp_str, REG_EXTENDED)) != 0)
    {
      fprintf (stderr, "rec_resolver_check: error compiling regexp.\n");
      return false;
    }

  /* Check.  */
  return (regexec (&regexp, regexp_str, 0, NULL, 0) == 0);
}

bool
rec_resolve (rec_db_t db,
             char *type,
             rec_record_t record,
             char *expr,
             FILE *out)
{
  bool res;
  char *expr_copy;
  char *part_str;
  struct rec_resolver_part_s part;

  /* 
   * Syntax:
   *
   *    PART,...
   */

  res = true;

  expr_copy = strdup (expr);
  if (expr_copy)
    {
      part_str = strsep (&expr_copy, ",");
      do
        {
          if (rec_parse_part (part_str, &part))
            {
              res = res && rec_resolve_part (record, &part, out);
              if (!res)
                {
                  break;
                }
            }
          else
            {
              /* Parse error.  */
              res = false;
              break;
            }
        }
      while ((part_str = strsep (&expr_copy, ",")));

      free (expr_copy);
    }

  return res;
}

char *
rec_resolve_str (rec_db_t db,
                 char *type,
                 rec_record_t record,
                 char *expr)
{
  char *result;
  size_t result_size;
  FILE *stm;
  
  result = NULL;
  stm = open_memstream (&result, &result_size);

  if (stm)
    {
      rec_resolve (db, type, record, expr, stm);
      fclose (stm);
    }

  return result;
}

/*
 * Private functions
 */

bool
rec_resolve_part (rec_record_t record,
                  struct rec_resolver_part_s *part,
                  FILE *out)
{
  bool ret;
  rec_record_elem_t elem_field;
  int index, num_found;
  rec_field_t field;
  bool slash_p;
  rec_field_name_t field_name;

  num_found = 0;

  field_name = rec_parse_field_name_str (part->field_name);
  slash_p = (part->prefix_mod == '/');
  index = part->min;

  /* Get the result string.  */
  elem_field = rec_record_null_elem();
  while (rec_record_elem_p (elem_field = rec_record_next_field (record, elem_field)))
    {
      field = rec_record_elem_field (elem_field);

      if (rec_field_name_equal_p (field_name,
                                  rec_field_name (field)))
        {
          ret = true;
          
          if ((index == -1) ||
              (index == num_found))
            {
              if (slash_p)
                {
                  fprintf (out, rec_field_value (field));
                  fprintf (out, "\n");
                }
              else
                {
                  rec_writer_t writer;
                  
                  writer = rec_writer_new (out);
                  rec_write_field (writer, field);
                  rec_writer_destroy (writer);
                }
            }

          num_found++;
        }
    }
  
  return ret;
}

static char *
rec_resolver_parse_int (char *p,
                        int *num)
{
  int res;
  char number[100];
  size_t number_size;
  
  number_size = 0;
  while ((*p != 0) && (*p < '9') && (*p > '0'))
    {
      /* Add a digit.  */
      number[number_size++] = *p;
      p++;
    }
  number[number_size] = 0;
  
  /* The following call cannot fail.  */
  res = atoi (number);
  *num = res;
}

static bool
rec_parse_part (char *str,
                struct rec_resolver_part_s *part)
{
  bool ret;
  char *b, *p;
  char *field_name_str;

  ret = true;
  p = str;

  /* 'Empty' part.  */
  part->field_name = NULL;
  part->prefix_mod = 0;
  part->min = -1;
  part->max = -1;

  /* Syntax:
   *
   *    [/]FNAME[min-max]
   */

  /* Process the optional slash.  */
  if (p[0] == '/')
    {
      part->prefix_mod = p[0];
      p++;
    }

  /* Get the field name.  */
  b = p;
  while ((*p != 0) && (*p != '['))
    {
      p++;
    }

  if ((p - b) > 0)
    {
      size_t size = (p - b) + 1;

      field_name_str = malloc (size + 1);
      strncpy (field_name_str, b, size - 1);
      field_name_str[size - 1] = ':';
      field_name_str[size] = '0';
      
      part->field_name = field_name_str;
    }

  /* Get the subscript, if any.  */
  if ((part->field_name)
      && (*p == '['))
    {
      char number[100];
      size_t number_size = 0;

      p++;
      while ((*p != 0) && (*p <= '9') && (*p >= '0'))
        {
          number[number_size++] = *p;
          p++;
        }
      number[number_size] = 0;

      if (*p == ']')
        {
          part->min = atoi (number);
        }
      else 
        {
          /* Expected ]: parse error. */
          ret = false;
        }
    }
  

  if (!(part->field_name))
    {
      /* No field name: parse error.  */
      ret = false;
    }

  return ret;
}


/* End of rec-resolver.c */

