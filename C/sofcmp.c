#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>
#include <dirent.h>

/*struct stat {
               dev_t     st_dev;          ID of device containing file 
               ino_t     st_ino;          Inode number 
               mode_t    st_mode;         File type and mode 
               nlink_t   st_nlink;        Number of hard links 
               uid_t     st_uid;          User ID of owner 
               gid_t     st_gid;          Group ID of owner 
               dev_t     st_rdev;         Device ID (if special file) 
               off_t     st_size;         Total size, in bytes 
               blksize_t st_blksize;      Block size for filesystem I/O 
               blkcnt_t  st_blocks;       Number of 512B blocks allocated 

                Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. 

               struct timespec st_atim;   Time of last access 
               struct timespec st_mtim;   Time of last modification 
               struct timespec st_ctim;   Time of last status change 

           #define st_atime st_atim.tv_sec       Backward compatibility 
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           }*/


int main (){

    /* outputs de comparação entre file1 e file2
    st_blocks { "Blocks Usados Igual\n", "Blocks Usados Diferente\n" };
    st_size { "Tamanho Igual\n", "Tamanho Diferente\n" };
    st_uid { "User Permissions Igual\n", "User Permissions Diferente\n" };
    st_gid { "Group Permissions Igual\n", "Group Permissions Diferente\n" };
    st{ "Other Permissions Igual\n", "Other Permissions Diferente\n" };
    { "Ficheiros Igual\n", "Ficheiros Diferente\n" };
    { "Nomes Iguais\n", "Nomes Diferente\n" };*/


    char* delim = " ";
    char input[1024];
    char *nameFile1 = NULL, *nameFile2 = NULL, *op = NULL;
    struct stat statFile1, statFile2;

    if( read(STDIN_FILENO, &input, 1024) < 0){
        printf("Erro\n");
    }else{

        if( (nameFile1 = strtok(input, delim)) == NULL ){ 
            printf("Erro\n"); 
            return 0;
        } else if( (nameFile2 = strtok(NULL, delim)) == NULL ){
            printf("Erro\n");
            return 0;
        }else {
            if( (op = strtok(NULL, delim)) == NULL ){
                if( strncmp(nameFile1, nameFile2, strlen(nameFile1)) == 0){
                    printf("Nomes Iguais\n");
                    return 0;
                } else if( stat(nameFile1, &statFile1) == -1 ){
                    //printf("Erro\n");
                    perror("stat\n");
                    return 0;
                }else if ( stat(nameFile2, &statFile2) == -1 ){
                    //printf("Erro\n");
                    perror("stat\n");
                    return 0;
                }

                if( ( ( ( (statFile1.st_mode & __S_IFMT) == __S_IFDIR ) 
                && ( (statFile2.st_mode & __S_IFMT) != __S_IFDIR ) ) 
                || 
                ( ( (statFile2.st_mode & __S_IFMT) == __S_IFDIR) 
                && ( (statFile1.st_mode & __S_IFMT) != __S_IFDIR) ) ) ){
                    printf("Erro\n");
                    return 0;
                }else if( ( (statFile1.st_mode & __S_IFMT) == __S_IFREG )
                && ( (statFile2.st_mode & __S_IFMT) == __S_IFREG ) ){
                    if( statFile1.st_size == statFile2.st_size ){
                        printf("Tamanho Igual\n");
                    }else printf("Tamanho Diferente\n");
                    if( statFile1.st_blocks == statFile2.st_blocks ){
                        printf("Blocks Usados Igual\n");    
                    }else printf("Blocks Usados Diferente\n");
                    if( statFile1.st_uid == statFile2.st_uid ){
                        printf("User Permissions Igual\n");        
                    }else printf("User Permissions Diferente\n");
                    if( statFile1.st_gid == statFile2.st_gid ){
                        printf("Group Permissions Igual\n");   
                    }else printf("Group Permissions Diferente\n");
                    if( (statFile1.st_mode & ~__S_IFMT) == (statFile1.st_mode & ~__S_IFMT) ){
                        printf("Other Permissions Igual\n");
                    }else{
                        printf("Other Permissions Diferente\n");
                    }
                    if( statFile1.st_size == statFile2.st_size
                    &&  statFile1.st_blocks == statFile2.st_blocks
                    &&  statFile1.st_uid == statFile2.st_uid
                    &&  statFile1.st_gid == statFile2.st_gid                       
                    && ((statFile1.st_mode & ~__S_IFMT) == (statFile1.st_mode & ~__S_IFMT))
                    ){
                        printf("Ficheiros Igual\n");
                    }else printf("Ficheiros Diferente\n");
                }

            
            }/* PARTE III ESTENOGRAFIA */
            else if( strncmp(nameFile1, nameFile2, strlen(nameFile1)) == 0){
                printf("Nomes Iguais.\n");
                if( strncmp(op, "G", 1) == 0){
                    printf("SECRET STUFF\n");
                }
            }else if( strncmp(op, "H", 1) == 0){
                    /*COPIAR DO FILE2 PARA O FINAL DO FILE1*/
                    printf("We can pretend.\n");
                }

        }

    }

    return 0;

}