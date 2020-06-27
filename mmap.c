#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include <errno.h>

typedef struct{
    char name[4];
    int age;
}people;

int malloc_num = 0;

int main(int argc,char **argv)//map a normal file as shared mem:¡¡
{
    int fd,i;
    people *p_map;
	int num = atoi(argv[1]);
	char path[100];
	extern int errno;
	for(i = 0;i<num;i++)
	{
		sprintf(path,"PATH%d",malloc_num);
		malloc_num++;
		fd = open(path,O_CREAT|O_RDWR|O_TRUNC,00777);
	
//	    lseek(fd,sizeof(people)*5-1,SEEK_SET);
//	    write(fd,"",1);
	    p_map=(people*)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		if (p_map == MAP_FAILED) {
			printf("%d malloc error\n",i);
			printf("errno: %2d\t%s\n",errno,strerror(errno));
			return 0;
		} else {
			printf("%d malloc ok\n",i);
		} 
	    close(fd);
	    
	}
//    char temp;
//    temp='a';
//    for(i=0;i<10;i++)
//
//    {
//
//        temp+=1;
//
//        memcpy((*(p_map+i)).name,&temp,2);
//
//        (*(p_map+i)).age=20+i;
//
//    }
    munmap(p_map,sizeof(people)*10);

    printf("umapok\n");
	return 0;
}
