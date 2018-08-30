#include <stdio.h>
#include "system.h"

int main(void){
	char op[9];
	char expressao[21];
	while (scanf("%s",op) != EOF){
		scanf("%s",expressao);
		central(op,expressao);
	}
	
	central("shutdown","0");

	return 0;
}
