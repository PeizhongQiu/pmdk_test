#include <libpmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//#define PATH "/mnt/dax_200g/THREAD_MALLOC_"

//static int malloc_num = 0;

struct test_data
{
    int id;
    char name[50];
};

int main()
{
    size_t size = 512 * 1024;
    int is_pmem;
    size_t mapped_len;
    struct test_data *pmemaddr = pmem_map_file("/mnt/dax_200g/THREAD_MALLOC_0",size, PMEM_FILE_CREATE,
                                  0666, &mapped_len, &is_pmem);
    struct test_data *root = pmemaddr;
    if (pmemaddr == NULL)
    {
        printf("malloc error: %s\n",pmem_errormsg());
        exit(1);
    }
    else
    {
        printf("malloc success\n");
    }

    pmemaddr->id = 0;
    strcpy(pmemaddr->name, "12345");
    pmem_persist(pmemaddr, sizeof(test_data));
    pmemaddr++;
    pmemaddr->id = 1;
    strcpy(pmemaddr->name, "67890");
    pmem_persist(pmemaddr, sizeof(test_data));
    pmemaddr++;
    pmemaddr->id = 2;
    strcpy(pmemaddr->name, "10111");
	pmem_persist(pmemaddr, sizeof(test_data));
       
    pmem_unmap(root, mapped_len);
    return 0;
}
