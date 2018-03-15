#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processbase(int base, int numero){

	if(8 == base){
		printf("%o\n", numero);
	}

	if(16 == base){
		printf("%x\n", numero);
	}

	if(10 == base){
		printf("%d\n", numero);		
	}

}

void processfile(FILE* f, int op, int base){
	
	const char *delim = " ";
	long int a=0;
	int calculo = 0;
	char linha[1001];
	char *tok=NULL;
	
	if(0 == op){ calculo = 0;
	}else { calculo= 1; }
	
	while( fgets(linha, 1000, f) != NULL ){
		
		tok = strtok(linha, delim);
		
		while( tok != NULL ) {
			
			if(16 == base){ 
				a = strtol(tok, &tok, base);
			} else a = atoi(tok);
			if(0 == op){
				calculo += a;
			} else {
				calculo *= a;
			}
			
			tok = strtok(NULL, delim);

		}
		processbase(base, calculo);
		if(0 == op){  calculo = 0;
	}else calculo= 1;
		a = 0;
	}
}

int main(int argc, char* argv[]){
	
	FILE *f = NULL;

	int i = 1;
	int op = 0, base = 10;

	if ( argc == 1 ){ /* default stdin, default base 10, default soma */
		f = stdin;
		processfile(f, op, base);
	}

	for ( i = 1; i< argc; i++){
		if( (strlen(argv[i]) > 7) && (0==strncmp(argv[i], "-base=10",8))){ /* stdin + base X + default soma */
			base=10;
			//printf("Esta pizza tinha base 10\n");
		}
		else if( (strlen(argv[i]) > 7) && (0==strncmp(argv[i], "-base=16",8))){ /* stdin + base X + default soma */
			base=16;
			//printf("Esta pizza tinha base 16\n");
		}  
		else if( (strlen(argv[i]) > 6) && (0==strncmp(argv[i], "-base=8",7))){ /* stdin + base X + default soma */
			base=8;
			//printf("Esta pizza tinha base 8\n");
		}  
		else if( (strlen(argv[i]) > 4) && (0==strncmp(argv[i], "-op=+",5))){	 /* sem base nem ficheiro, stdin + soma */
			op=0;
			//printf("Esta pizza tinha mais. \n");
		}
		else if( (strlen(argv[i]) > 4) && (0==strncmp(argv[i], "-op=*",5))){    /* sem base nem ficheiro, stdin + multiplicação */
			op=1;
			//printf("Esta pizza multiplicação. \n");
		}
		else break;
	}
	
	if (i==argc){ 
		processfile(stdin, op, base);
	}else {	
			for ( ; i< argc; i++) {
				
				f=fopen(argv[i], "r");
				
				if( f == NULL ){
					printf("File Not Found %s\n", argv[i]);
				} else {
					processfile(f, op, base);
				}
				
			}
		}

	return 0;
}
