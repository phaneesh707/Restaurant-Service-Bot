a.exe:bot_server.o bot_client.o
	gcc bot_server.o bot_client.o
bot_client.o:bot_client.c bot_head.h
	gcc -c bot_client.c
bot_server.o:bot_server.c bot_head.h
	gcc -c bot_server.c