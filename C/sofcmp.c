#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int samefile( struct stat file1, struct stat file2){
    
    if( file1.st_size == file2.st_size
    &&  file1.st_blocks == file2.st_blocks
    &&  (file1.st_mode & S_IRWXU ) == (file2.st_mode & S_IRWXU)
    &&  (file1.st_mode & S_IRWXG ) == (file2.st_mode & S_IRWXG)                       
    &&  (file1.st_mode & S_IRWXO ) == (file2.st_mode & S_IRWXO)){
         return 1;
        }else return 0;

}

int main (){

    int i=0, c1=0,c2=0;
    char* delim = " ";
    char input[1024];
    char *nameFile1 = NULL, *nameFile2 = NULL;
    struct stat sf1, sf2;
    struct dirent *dir1, *dir2;
    DIR *d1, *d2;   

    if( read(STDIN_FILENO, &input, 1024) < 0){
        printf("Error\n");
    }else{
        
        if( (nameFile1 = strtok(input, delim)) == NULL ){ 
            printf("Error\n");
            return 0;
        } else if( (nameFile2 = strtok(NULL, delim)) == NULL ){
            printf("Error\n");
            return 0;
        }else {
            for(i=0; i<strlen(nameFile2);i++){
                if( nameFile2[i] < 33 || nameFile2[i] > 126 ){
                    nameFile2[i] = '\0';
                }
            }
            i=0;
            if( ( strncmp(nameFile1, nameFile2, strlen(nameFile2)) == 0 ) && ( strncmp(nameFile1,nameFile2, strlen(nameFile1) ) == 0 ) ){
                printf("Nomes Iguais\n");
                return 0;
            }else if( ( S_ISREG(sf1.st_mode) && S_ISDIR(sf2.st_mode) ) || ( S_ISDIR(sf1.st_mode) && S_ISREG(sf2.st_mode) ) ){
                printf("Error\n");
                return 0;
            }else if( stat(nameFile1, &sf1) == -1 ){
                printf("Error\n");                   
                return 0;
            }else if ( stat(nameFile2, &sf2) == -1 ){
                printf("Error\n");
                return 0;
            }else if( S_ISREG(sf1.st_mode) && S_ISREG(sf2.st_mode) ){
                if( sf1.st_size == sf2.st_size ){
                    printf("Tamanho Igual\n");
                }else printf("Tamanho Diferente\n");
                if( sf1.st_blocks == sf2.st_blocks ){
                    printf("Blocks Usados Igual\n");    
                }else printf("Blocks Usados Diferente\n");
                if( (sf1.st_mode & S_IRWXU ) == (sf2.st_mode & S_IRWXU) ){
                    printf("User Permissions Igual\n");        
                }else printf("User Permissions Diferente\n");
                if( (sf1.st_mode & S_IRWXG ) == (sf2.st_mode & S_IRWXG) ){
                    printf("Group Permissions Igual\n");   
                }else printf("Group Permissions Diferente\n");
                if( (sf1.st_mode & S_IRWXO ) == (sf2.st_mode & S_IRWXO) ){
                    printf("Other Permissions Igual\n");
                }else{
                    printf("Other Permissions Diferente\n");
                }
                if( (sf1.st_size == sf2.st_size)
                &&  (sf1.st_blocks == sf2.st_blocks)
                && ( (sf1.st_mode & S_IRWXU ) == (sf2.st_mode & S_IRWXU) )
                && ( (sf1.st_mode & S_IRWXG ) == (sf2.st_mode & S_IRWXG) )     
                && ( (sf1.st_mode & S_IRWXO ) == (sf2.st_mode & S_IRWXO) ) ){ 
                    printf("Ficheiros Igual\n");
                }else printf("Ficheiros Diferente\n");
            }else if( S_ISDIR( sf1.st_mode ) && S_ISDIR( sf2.st_mode ) ){

                if( ( (d1 = opendir(nameFile1)) == NULL) ){
                    printf("Error\n");
                }else if ( ( (d2 = opendir(nameFile2)) == NULL) ){
                    printf("Error\n");
                }                

                while( (dir1 != NULL) || (dir2 != NULL) ){
                    dir1 = readdir(d1); 
                    dir2 = readdir(d2);

                    if( dir1 != NULL ){ c1++;}else{ if(dir2!=NULL){ i=-1; }else{break;} break;}
                    if( dir2 != NULL ){ c2++;}else{ if(dir1!=NULL){ i=-1; }else{break;} break;}

                    if( (strchr(dir1->d_name, '.') != NULL) || (strchr(dir2->d_name, '.') != NULL) ) continue;

                    if( ( strncmp(dir1->d_name, dir2->d_name, strlen(dir1->d_name)) == 0 ) && ( strncmp(dir1->d_name,dir2->d_name, strlen(dir2->d_name) ) == 0 ) ){

                        if( (stat(dir1->d_name, &sf1) == -1) ){
                            printf("Error\n");
                        }
                        else if( (stat(dir1->d_name, &sf2) == -1) ){
                            printf("Error\n");
                        }

                        if( samefile( sf1, sf2 ) == 1 ){
                            continue;
                        }else {
                            i=-1;
                            break;
                        }

                    }                    
                       
                }

                if( (c1 == c2) ){
                    printf("Directories Igual\n");
                    closedir(d1);
                    closedir(d2);
                }else if(i==-1){
                    printf("Directories Diferente\n");
                    closedir(d1);
                    closedir(d2);
                }
                

            }

            
            }

        }

    

    return 0;

}