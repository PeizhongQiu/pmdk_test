
#include <libpmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define PATH "/mnt/dax_200g/THREAD_MALLOC_"

static int malloc_num = 0;
void *add_pmalloc(size_t size)
{
    int num = ++malloc_num;

    size_t mapped_len;
    char path[100];
    sprintf(path, "%s%d", PATH, num);
    void *pmemaddr;
    int is_pmem;

    if ((pmemaddr = pmem_map_file(path, size, PMEM_FILE_CREATE,
                                  0666, &mapped_len, &is_pmem)) == NULL)
    {
        return NULL;
    }

    return (void *)pmemaddr;
}

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    int i;
    for (i = 0; i < num; i++)
    {
        //size_t mapped_len;
        size_t size = 512;
        if (add_pmalloc(size) == NULL)
        {
            printf("%d malloc error: %s\n", i, pmem_errormsg());
	    //sleep(100);
	    //pmem_errormsg();
            exit(1);
        }
        else
        {
            printf("%d malloc success\n", i);
        }
    }
    return 0;
}
