/* -*- mode: C -*-
 *
 *       File:         rec-parser-perror.c
 *       Date:         Sat Nov 13 22:37:26 2010
 *
 *       GNU recutils - rec_parser_perror unit tests.
 *
 */

#include <config.h>

#include <check.h>
#include <rec.h>

/*-
 * Test: rec_parser_perror_nominal
 * Unit: rec_parser_perror
 * Description:
 * + Print the error message associated with a failed
 * + parsing.
 */
START_TEST(rec_parser_perror_nominal)
{
  rec_parser_t parser;
  rec_field_t field;
  char *str;

  str = "invalid field";
  parser = rec_parser_new_str (str, "dummy");
  fail_if (parser == NULL);
  fail_if (rec_parser_error (parser));
  fail_if (rec_parse_field (parser, &field));
  fail_if (!rec_parser_error (parser));
  rec_parser_perror (parser, "expected error while parsing: ");
  rec_parser_destroy (parser);
}
END_TEST

/*
 * Test creation function
 */
TCase *
test_rec_parser_perror (void)
{
  TCase *tc = tcase_create ("rec_parser_perror");
  tcase_add_test (tc, rec_parser_perror_nominal);

  return tc;
}

/* End of rec-parser-perror.c */
