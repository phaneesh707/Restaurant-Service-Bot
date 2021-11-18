#include<stdio.h>
#include<stdlib.h>
#include "bot_head.h"

int main(){
    list* pl;
	init(&pl);
	create(&pl);
	// display(pl);
	bot_path(&pl);
}