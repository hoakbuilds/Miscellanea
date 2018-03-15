#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// i) ir para inicio/fim ou recuar/avancar n bytes
// ii) avancar/recuar da posicao atual n bytes
// iii) ler n bytes para buffer
// iv)limpar o buffer
// v) terminar

int main(int argc, char* argv[]){

    int i=0;
    off_t n=-1;
    char ch='0', r[2];
    char buffer[100];
    const char begin = 'i',end = 'f',cleaner = 'l',reader = 'r' ,bar= '\n', plus='+', minus='-';
    int f = -1;
    
    if((f=open(argv[1], O_RDONLY)) < 0){
       return 0;
    }
   
    for(i=0;i<100;i++){
        buffer[i]='\0';
    } 
   
    while (ch != 's'){
        scanf ("%c %ld\n", &ch, &n);  
        
        if (strncmp(&ch, &plus, 1)==0){
            //avancar n bytes lseek
            lseek(f, n, SEEK_CUR);
        }
        else if (strncmp(&ch, &minus, 1)==0){
            //recuar n bytes
            lseek(f, (-abs(n)), SEEK_CUR);
        }
        else if (strncmp(&ch, &begin, 1)==0){
            //ir para o inicio do ficheiro e avancar n bytes
            lseek(f, n, SEEK_SET);
        }
        else if (strncmp(&ch, &end, 1)==0){
            //ir para o fim do ficheiro e recuar n bytes
            lseek(f, (-abs(n)), SEEK_END);
        }
        else if(strncmp(&ch, &reader, 1)==0){
            //ler n bytes e dar append a um buffer
            for (i=0;i<n;i++){
                read(f, &r, 1);
                strcat(buffer, r);
            }
        }
        else if(strncmp(&ch, &cleaner, 1)==0){
            //limpar o buffer
            for(i=0;i<100;i++) {
                buffer[i]='\0';
            }
        }else {
            continue;
        }
        
    }
    if(ch=='s'&&n==0){
        write(STDOUT_FILENO, &buffer, strlen(buffer));
        write(STDOUT_FILENO, &bar, 1);  
    }   
    
    return 0;
}
