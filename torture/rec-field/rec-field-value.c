/* -*- mode: C -*-
 *
 *       File:         rec-field-value.c
 *       Date:         Sun Mar  1 17:04:00 2009
 *
 *       GNU recutils - rec_field_value unit tests
 *
 */

/* Copyright (C) 2009, 2010 Jose E. Marchesi */

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
#include <string.h>
#include <check.h>

#include <rec.h>

/*
 * Test: rec_field_value_001
 * Description:
 *   Get the value of a field with an empy value
 * Success conditions:
 *   1. The call should not produce an error.
 *   2. The value of the field should be properly
 *      returned.
 */
START_TEST(rec_field_value_001)
{
  rec_field_t field;
  rec_field_name_t fname;
  const char *field_value;
  
  fname = rec_field_name_new ();
  rec_field_name_set (fname, 0, "");
  field = rec_field_new (fname, "");
  fail_if(field == NULL);

  field_value = rec_field_value (field);
  fail_if(strcmp (field_value, "") != 0);
}
END_TEST

/*
 * Test: rec_field_value_002
 * Description:
 *   Get the value of a field with a non-empty value
 * Success conditions:
 *   1. The call should not produce an error.
 *   2. The value of the field should be properly
 *      returned.
 */
START_TEST(rec_field_value_002)
{
  rec_field_t field;
  rec_field_name_t fname;
  const char *field_value;
  
  fname = rec_field_name_new ();
  rec_field_name_set (fname, 0, "");
  field = rec_field_new (fname, "foo");
  fail_if(field == NULL);

  field_value = rec_field_value (field);
  fail_if(strcmp (field_value, "foo") != 0);
}
END_TEST

/*
 * Test case creation function
 */
TCase *
test_rec_field_value (void)
{
  TCase *tc = tcase_create("rec_field_value");
  tcase_add_test (tc, rec_field_value_001);
  tcase_add_test (tc, rec_field_value_002);

  return tc;
}

/* End of rec-field-value.c */
