#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]){
	
	FILE *f = NULL;
	
	if( argc == 2 ) {
		
		if( strlen(argv[1]) > 6 && 0==strncmp(argv[1], "-base=",6) ){
			printf("Comi só a base da pizza.\n");
			return 0;
		} else{
			
			if( (f=fopen(argv[1], "r")) == NULL  ){
				fprintf(stdout, "File Not Found %s\n", argv[1]);
				return 0;
			} else {
			printf("We got ourselves a file\n");
			}		
			
		}
		
	}
	
	if( argc == 3 ) {
		
		if( strlen(argv[1]) > 6 && 0==strncmp(argv[1], "-base=",6) ){
			printf("Comi a base da pizza mas desta vez também havia molho de tomate. :(\n");
			if( (f=fopen(argv[2], "r")) == NULL  ){
				fprintf(stdout, "File Not Found %s\n", argv[1]);
				return 0;
			} else {
			printf("Encontrei um cogumelo na pizza.\n");
			} 
		} else{
				
		}
	}
	
	if( argc == 4 ) {
		
	}
	
	if( argc > 4 ) {
		
		
	}


	return 0;
}

