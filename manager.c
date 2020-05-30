#include <libpmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
        printf("%d malloc error: %s\n", i, pmem_errormsg());
        exit(1);
    }
    else
    {
        printf("%d malloc success\n", i);
    }

    pmemaddr->id = 0;
    strcpy(pmemaddr->name, "12345");
    pmemaddr++;
    pmemaddr->id = 1;
    strcpy(pmemaddr->name, "67890");
    pmemaddr++;
    pmemaddr->id = 2;
    strcpy(pmemaddr->name, "10111");

    if (is_pmem)
        pmem_persist(root, mapped_len);
    else
        pmem_msync(root, mapped_len);
    
    pmem_unmap(root, mapped_len);
    return 0;
}
