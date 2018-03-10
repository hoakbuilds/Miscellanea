#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

 /*
 Five types of instructions:
     (i) go to the beginning or end of file or move forward/backwards n bytes
     (ii) go forwards/backwards n bytes from the current position 
     (iii) read n bytes to a buffer
     (iv) clean the buffer
     (v) finish

    + n : avan¸car n bytes
    - n : recuar n bytes
    i n : ir para o inicio do ficheiro e e avan¸car n bytes
    f n : ir para o fim do ficheiro e recuar n bytes
    r n : read/ler n bytes e append a um buffer.
    l 0 : limpar o buffer
    s 0 : stop
*/

void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int main(int argc, char* argv[]){
	
	int fd = -1;
    fd = open(argv[1], O_RDONLY);

    if( 0 > fd ){
        return 0;
    }

    char c = 0;
    char r = 0;
    char buffer[100];
    __off_t offset = 0;
    int n = 0, l = 0, i = 0;
    const char barran = '\n';

    
    scanf("%c %d", &c, &n);

    while( c != 's' || n != 0){
        
        if( c == '+'){
            offset = lseek(fd, n, SEEK_CUR);
        }else if( c == '-'){
            lseek(fd, 0, SEEK_SET);
            offset = lseek(fd, offset-n, SEEK_CUR);
        }else if( c == 'i'){
            lseek(fd, 0, SEEK_SET);
            offset = lseek(fd, n, SEEK_CUR);
        }else if( c == 'f'){
            offset = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, SEEK_SET);
            offset = lseek(fd, offset, SEEK_SET);
        }else if( c == 'r'){
           for(i=0;i<n;i++){
                l+=read(fd, &r, 1);
                append(buffer, r);
            }
        }else if( c == 'l' && n == 0){
            write(STDOUT_FILENO, &buffer, l);
            write(STDOUT_FILENO, &barran, 1);
            printf("%s", buffer);
            for(i=0;i<100;i++){
                buffer[i]='\0';
            }
        }else if( c == 's' && n == 0){
            break;
        }

        scanf("%c %d", &c, &n);

    }

    return 0;
}