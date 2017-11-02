# -*-Makefile-*-

# <target>:<dependency>
#	<<action>


irc_server: irc_server.o message_parser.o utils.o
	clang irc_server.o message_parser.o utils.o -o irc_server

irc_server.o: irc_server.c utils.h message_parser.h
	clang -ggdb -c irc_server.c 

message_parser.o: message_parser.c
	clang -ggdb -c message_parser.c 

utils.o: utils.c
	clang -ggdb -c utils.c 

all: irc_server

clean:
	rm *.o


