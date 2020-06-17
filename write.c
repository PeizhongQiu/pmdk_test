//test optane dc persistent memory
//write
//写的粒度，分配内存的大小，数据结构的大小
#include <libpmem.h>

#define PATH "/mnt/dax/ALLOC_FILE"
#define TEST_SIZE (4*1024)
#define TEST_NUM (TEST_SIZE/sizeof(int))
unsigned long long malloc_num = 0;

struct test_data
{
    int a[TEST_NUM];
};

void *add_pmalloc(size_t size, size_t *mapped_len)
{
    char path[100];
    sprintf(path, "%s%llu", PATH, malloc_num);
    struct timeval start, end;

    void *pmemaddr;
    int is_pmem;
    /* create a pmem file and memory map it */

    if ((pmemaddr = pmem_map_file(path, size, PMEM_FILE_CREATE,
                                  0666, mapped_len, &is_pmem)) == NULL)
    {
        return NULL;
    }
    ++malloc_num;

    return (void *)pmemaddr;
}

int main()
{

}