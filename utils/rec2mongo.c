#include <config.h>
#include <bson.h>
#include <mongoc.h>
#include <stdio.h>

int
main (int   argc,
      char *argv[])
{
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    bson_error_t error;
    bson_oid_t oid;
    bson_t *doc;

    mongoc_init ();

    client = mongoc_client_new ("mongodb://localhost:27017/");
    collection = mongoc_client_get_collection (client, argv[1], argv[2]);

    doc = bson_new ();
    bson_oid_init (&oid, NULL);
    BSON_APPEND_OID (doc, "_id", &oid);
    BSON_APPEND_UTF8 (doc, "hello", "world");
    

    if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, doc, NULL, &error)) {
        printf ("%s\n", error.message);
    }

    bson_destroy (doc);
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);

    return 0;
}