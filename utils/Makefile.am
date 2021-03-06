# utils/ Makefile.am
# GNU rec

# Copyright (C) 2009, 2010 Jose E. Marchesi

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

if COMPILE_MDB2REC
   MDB2REC = mdb2rec
else
   MDB2REC =
endif

bin_PROGRAMS = recinf recsel recins recdel recset recfix recfmt \
               csv2rec rec2csv mysql2rec rec2mysql sqlite2rec $(MDB2REC) rec2sqlite rec2gre gre2rec odb2rec rec2odb mongo2rec rec2mongo rec2json

COMMONSRC = recutl.h recutl.c
COMMONLIBS = $(top_builddir)/lib/librecutils.la $(top_builddir)/src/librec.la

if CRYPT
  COMMONLIBS += $(LTLIBGCRYPT)
endif

AM_CFLAGS =
if USE_COVERAGE
  AM_CFLAGS += -fprofile-arcs -ftest-coverage
endif

AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/src \
              -I$(top_srcdir)/libcsv -DLOCALEDIR=\"$(localedir)\" \
              -DMDB_DATETIME=$(MDB_DATETIME)

recinf_SOURCES = $(COMMONSRC) \
                 recinf.c
recinf_LDADD = $(COMMONLIBS)

recsel_SOURCES = $(COMMONSRC) \
                 recsel.c
recsel_LDADD = $(COMMONLIBS)

recins_SOURCES = $(COMMONSRC) \
                 recins.c
recins_LDADD = $(COMMONLIBS)

recdel_SOURCES = $(COMMONSRC) \
                 recdel.c
recdel_LDADD = $(COMMONLIBS)

recset_SOURCES = $(COMMONSRC) \
                 recset.c
recset_LDADD = $(COMMONLIBS)

recfix_SOURCES = $(COMMONSRC) \
                 recfix.c
recfix_LDADD = $(COMMONLIBS)

recfmt_SOURCES = $(COMMONSRC) \
                 recfmt.c
recfmt_LDADD = $(COMMONLIBS)

csv2rec_SOURCES = $(COMMONSRC) \
                  csv2rec.c
csv2rec_LDADD = $(COMMONLIBS) \
                $(top_builddir)/libcsv/libcsv.la

rec2csv_SOURCES = $(COMMONSRC) \
                  rec2csv.c
rec2csv_LDADD = $(COMMONLIBS) \
                $(top_builddir)/libcsv/libcsv.la

mdb2rec_SOURCES = $(COMMONSRC) \
                  mdb2rec.c
mdb2rec_CFLAGS = $(GLIB_CFLAGS)
mdb2rec_LDADD = $(COMMONLIBS) $(MDBLIBS)

mysql2rec_SOURCES = $(COMMONSRC) \
                  mysql2rec.c
                 
mysql2rec_CFLAGS = -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG
mysql2rec_LDFLAGS =  -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz  -ldl
mysql2rec_LDADD = $(COMMONLIBS)  

rec2mysql_SOURCES = $(COMMONSRC) \
                  rec2mysql.c
                 
rec2mysql_CFLAGS = -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG
rec2mysql_LDFLAGS =  -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl
rec2mysql_LDADD = $(COMMONLIBS)

sqlite2rec_SOURCES = $(COMMONSRC) \
                 sqlite2rec.c
sqlite2rec_CFLAGS =-I/usr/local/include 
sqlite2rec_LDFLAGS = -L/usr/local/bin  -lsqlite3 -lm
sqlite2rec_LDADD = $(COMMONLIBS)

rec2sqlite_SOURCES = $(COMMONSRC) \
                 rec2sqlite.c
rec2sqlite_CFLAGS =-I/usr/local/include 
rec2sqlite_LDFLAGS = -L/usr/local/bin  -lsqlite3 
rec2sqlite_LDADD = $(COMMONLIBS)


rec2gre_SOURCES = $(COMMONSRC) \
                 rec2gre.c
rec2gre_CFLAGS =-I/usr/include/postgresql 
rec2gre_LDFLAGS = -L/usr/lib  -lpq -lm
rec2gre_LDADD = $(COMMONLIBS)


gre2rec_SOURCES = $(COMMONSRC) \
                 gre2rec.c
gre2rec_CFLAGS =-I/usr/include/postgresql 
gre2rec_LDFLAGS = -L/usr/lib  -lpq 
gre2rec_LDADD = $(COMMONLIBS)


odb2rec_SOURCES = $(COMMONSRC) \
                 odb2rec.c
odb2rec_CFLAGS =-I/usr/local/include 
odb2rec_LDFLAGS = -L/usr/local/lib -locilib 
odb2rec_LDADD = $(COMMONLIBS)

rec2odb_SOURCES = $(COMMONSRC) \
                 rec2odb.c
rec2odb_CFLAGS =-I/usr/local/include 
rec2odb_LDFLAGS = -L/usr/local/lib -locilib 
rec2odb_LDADD = $(COMMONLIBS)

mongo2rec_SOURCES = $(COMMONSRC) \
                 mongo2rec.c
mongo2rec_CFLAGS = -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0 
mongo2rec_LDFLAGS = -L/usr/local/lib -lssl -lcrypto -lrt -lmongoc-1.0 -lbson-1.0
mongo2rec_LDADD=  $(COMMONLIBS)  

rec2mongo_SOURCES = $(COMMONSRC) \
                 rec2mongo.c
rec2mongo_CFLAGS = -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0 
rec2mongo_LDFLAGS = -L/usr/local/lib -lssl -lcrypto -lrt -lmongoc-1.0 -lbson-1.0
rec2mongo_LDADD=  $(COMMONLIBS)            

rec2json_SOURCES = $(COMMONSRC) \
                 rec2json.c
rec2json_CFLAGS =-I/usr/local/include 
rec2json_LDFLAGS = -L/usr/local/lib -ljson 
rec2json_LDADD = $(COMMONLIBS)

# End of Makefile.am
