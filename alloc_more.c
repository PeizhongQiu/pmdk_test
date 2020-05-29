#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>

#define LAYOUT_NAME "intro_1"
#define MAX_BUF_LEN 10
#define ALLOC_NUM 3000

struct my_root
{
    size_t len;
    char buf[MAX_BUF_LEN];
};

char file_name[100];

PMEMobjpool *pop = NULL;

PMEMoid root;

struct my_root *rootp=NULL;

char buf[MAX_BUF_LEN]={0};
int main()
{
    //char file_name[100];
    int i = 0;
    for (i; i < ALLOC_NUM; i++)
    {
        sprintf(file_name, "/mnt/dax/MALLOC_%d", i);
        printf("%d\n", i);
        pop = pmemobj_create(file_name, LAYOUT_NAME,
                                         32*1024*1024, 0666);
        if (pop == NULL)
        {
            perror("pmemobj_create");
            return 1;
        }
	printf("%p\n",pop);

        // 创建根对象
        root = pmemobj_root(pop, sizeof(struct my_root));
        // 获取根对象的直接指针
        rootp = pmemobj_direct(root);

        //char buf[MAX_BUF_LEN] = {0};

        rootp->len = strlen(buf);
        // 持久化长度
        pmemobj_persist(pop, &rootp->len, sizeof(rootp->len));
        // // 持久化内容
        pmemobj_memcpy_persist(pop, rootp->buf, buf, rootp->len);
        // 关闭pool
        //pmemobj_close(pop);
	//printf("close pop\n");
    }
    return 0;
}
