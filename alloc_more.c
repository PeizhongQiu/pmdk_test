#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>

#define LAYOUT_NAME "intro_1"
#define MAX_BUF_LEN 10
#define ALLOC_NUM 100000

struct my_root
{
    size_t len;
    char buf[MAX_BUF_LEN];
};

int main()
{
    char file_name[100];
    int i = 0;
    for (i; i < ALLOC_NUM; i++)
    {
        sprintf(file_name, "/mnt/dax/MALLOC_%d", i);
        printf("%d\n", i);
        PMEMobjpool *pop = pmemobj_create(file_name, LAYOUT_NAME,
                                          PMEMOBJ_MIN_POOL, 0666);
        if (pop == NULL)
        {
            perror("pmemobj_create");
            return 1;
        }

        // // 创建根对象
        // PMEMoid root = pmemobj_root(pop, sizeof(struct my_root));
        // // 获取根对象的直接指针
        // struct my_root *rootp = pmemobj_direct(root);

        // char buf[MAX_BUF_LEN] = {0};
        // if (scanf("%9s", buf) == EOF) {
        // 	fprintf(stderr, "EOF\n");
        // 	return 1;
        // }

        // rootp->len = strlen(buf);
        // // 持久化长度
        // pmemobj_persist(pop, &rootp->len, sizeof(rootp->len));
        // // 持久化内容
        // pmemobj_memcpy_persist(pop, rootp->buf, buf, rootp->len);
        // 关闭pool
        pmemobj_close(pop);
    }
    return 0;
}