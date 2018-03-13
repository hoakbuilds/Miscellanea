#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void append(char *buffer, char r){
    
    int l = strlen(buffer);
    buffer[l]=r;
    buffer[l+1]='\0';
    r='\0';
}

int main(int argc, char* argv[]){
	
	int fd = -1;
    fd = open(argv[1], O_RDONLY);

    if( 0 > fd ){
        return 0;
    }

    off_t maxpos = lseek(fd, 0, SEEK_END);
    off_t minpos = lseek(fd, 0, SEEK_SET);
    off_t currpos = minpos;
    off_t n = -1;
    int i = 0;
    const char mais = '+';
    const char barran = '\n';
    const char menos = '-';
    const char inicio = 'i';
    const char fim = 'f';
    const char ler = 'r';
    const char limpar = 'l';
    char r= '0', c = '0';
    char buffer[100];

    for(i=0;i<100;i++){ 
        buffer[i]='\0';
    }       

    while( c != 's' ){

        scanf("%c %ld\n", &c, &n);

        if( 0==strncmp(&c, &inicio, 1)  ){

            currpos = lseek(fd, n, SEEK_SET);
            
        }else if( 0==strncmp(&c, &menos, 1) ){

            if( ( currpos - n ) < minpos ){
                n = ( minpos - currpos );
            }

            currpos = lseek(fd, (-abs(n)), SEEK_CUR);
                
        }else if( 0==strncmp(&c, &mais, 1)){

            if( ( currpos + n ) > maxpos ){
                n = ( maxpos - currpos );
            }
                
            currpos = lseek(fd, n, SEEK_CUR);

        }else if( 0==strncmp(&c, &fim, 1)){

            currpos = lseek(fd, (-abs(n)), SEEK_END);
            
        }else if( 0==strncmp(&c, &ler, 1)){
            
            if( currpos == maxpos ) continue;
            if( ( currpos + n ) > maxpos ){
                n = ( maxpos - currpos );
            }

            for(i=0; i<n; i++){
                if(currpos == maxpos ) break;
                read(fd, &r, 1);
                append(buffer, r);
            }

        }else if( 0==strncmp(&c, &limpar, 1)){

            if( 0 == n ){
                for(i=0;i<100;i++){ 
                    buffer[i]='\0';
                }
            }

        }else continue;

    }

    if( c == 's' && n == 0){
        write(STDOUT_FILENO, &buffer, strlen(buffer));
        write(STDOUT_FILENO, &barran, 1);
    }

    return 0;
}