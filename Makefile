# -*-Makefile-*-

# <target>:<dependency>
#	<<action>


irc_server: irc_server.o
	clang irc_server.o -o irc_server

irc_server.o: irc_server.c
	clang -ggdb -c irc_server.c 

all: irc_server

clean:
	rm *.o


