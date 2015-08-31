CC=gcc
#INC=/var/lib/openshift/543dd9894382ec666100002d/app-root/runtime/data/current/test/db/include/
#LIB=/var/lib/openshift/543dd9894382ec666100002d/app-root/runtime/data/current/test/db/lib/
INC=/home/qz/test/www-jiayuan-com/db/include/
LIB=/home/qz/test/www-jiayuan-com/db/lib/
lib=sqlite3
CFLAGS=-g -I$(INC) -L$(LIB) -l$(lib)

all:db_test

src := $(shell ls *.c)
objs := $(patsubst %.c,%.o,$(src))


db_test: $(objs)
	$(CC) -o $@ $^ $(CFLAGS) 


%.o:%.c
	$(CC) -c -o $@ $^ $(CFLAGS)


clean:
	rm -rf $(all) $(objs)
	rm db_test
	rm test.db
