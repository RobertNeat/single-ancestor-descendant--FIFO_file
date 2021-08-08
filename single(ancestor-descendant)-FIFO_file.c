#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    int yes=mkfifo("/tmp/myfifo",0777);
    char text[30];
    char empty[30]="";
    int fd;
    
    if(yes==0){//when fifo file created properly
    printf("FIFO created\n");
    
    if(fork()==0){//child process (sends)
        for(int a=0;a<10;a++){
            fd=open("/tmp/myfifo",O_WRONLY);
            sprintf(text,"Server: sends line nr %d",a);
            printf("%s\n",text);
            write(fd,text,30);
            close(fd);
            sleep(1);
        }
        return 0;
    }
    else{//parent process (reads)
        while(1){//endless loop results in need to manualy kill parent process
            //reading
            fd=open("/tmp/myfifo", O_RDONLY);
            read(fd,text,30);
            if(strlen(text)!=0){
                printf("Client received: %s\n",text);
            }
            close(fd);
        }
    }
    
}
    return 0;
}