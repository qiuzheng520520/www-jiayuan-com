CC=gcc
#INC=/home/qz/test/www-jiayuan-com/db/include
#LIB=/home/qz/test/www-jiayuan-com/db/lib
#lib=sqlite3
#CFLAGS=-I$(INC) -L$(LIB) -l$(lib)

target=connect

all:$(target)

client:connect.c
	#$(CC)  $(CFLAGS) $^ -o $@
	$(CC)  -lsqlite3 $^ -o $@

clean:
	rm $(target)
	rm -rf html.txt
	rm -rf result.txt
	#rm -rf start_no.txt
	rm -rf html.txt
