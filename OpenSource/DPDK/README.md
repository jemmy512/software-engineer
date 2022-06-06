# eal_init

![](../Image/DPDK/mem.png)

## rte_eal_config_create
```c++
rte_config_init()
    switch (rte_config.process_type)
    case RTE_PROC_PRIMARY:
        rte_eal_config_create()
            mem_cfg_fd = open("/var/run/config", O_RDWR | O_CREAT, 0600)
            ftruncate(mem_cfg_fd, sizeof(*rte_config.mem_config))
            fcntl(mem_cfg_fd, F_SETLK, &wr_lock)
            rte_mem_cfg_addr = eal_get_virtual_area(rte_mem_cfg_addr, &cfg_len_aligned, page_sz, 0, 0)
            mapped_mem_cfg_addr = mmap(rte_mem_cfg_addr, cfg_len_aligned, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, mem_cfg_fd, 0)
            memcpy(rte_mem_cfg_addr, &early_mem_config, sizeof(early_mem_config))
        eal_mcfg_update_from_internal();
        break;

    case RTE_PROC_SECONDARY:
        rte_eal_config_attach()
            mem_cfg_fd = open(pathname, O_RDWR)
            mem_config = (struct rte_mem_config *) mmap(NULL, sizeof(*mem_config), PROT_READ, MAP_SHARED, mem_cfg_fd, 0)
        eal_mcfg_wait_complete();
            struct rte_mem_config *mcfg = rte_eal_get_configuration()->mem_config;
            while (mcfg->magic != RTE_MAGIC)
                rte_pause();

```

## eal_hugepage_info_init
```c++
struct hugepage_info {
    uint64_t hugepage_sz;
    char hugedir[PATH_MAX];
    uint32_t num_pages[RTE_MAX_NUMA_NODES];
    int lock_descriptor;
};

eal_hugepage_info_init()
    hugepage_info_init()
        opendir("/sys/kernel/mm/hugepages")
            /*  hugepages-2048kB
                    free_hugepages
                    resv_hugepages
                    surplus_hugepages
                    nr_hugepages_mempolicy
                    nr_hugepages
                    nr_overcommit_hugepages
                hugepages-1048576kB */
        hpi->hugepage_sz = 2048kB | 1048576kB

        get_hugepage_dir(hpi->hugepage_sz, hpi->hugedir, sizeof(hpi->hugedir))
            fopen("/proc/mounts", "r")

        calc_num_pages(hpi, dirent)
            eal_parse_sysfs_value("/sys/devices/system/node/node%u/hugepages", &num_pages)
                /*  hugepages-2048kB
                        free_hugepages
                        surplus_hugepages
                        nr_hugepages
                    hugepages-1048576kB */
        /* sort the page directory entries by size, largest to smallest */
        qsort(&internal_config.hugepage_info[0], num_sizes, sizeof(internal_config.hugepage_info[0]), compare_hpi)

    tmp_hpi = create_shared_memory()
        fd = open("/var/run/hugepage_info", flags, 0600)
        ftruncate(fd, mem_size)
        mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)
    memcpy(tmp_hpi, hpi, sizeof(internal_config.hugepage_info))
```

## rte_eal_memzone_init
```c++
struct rte_mem_config {
    struct malloc_heap malloc_heaps[RTE_MAX_HEAPS];
    struct rte_fbarray memzones;
};

struct rte_fbarray {
    char name[RTE_FBARRAY_NAME_LEN];
    unsigned int count;
    unsigned int len;
    unsigned int elt_sz;
    void *data;
    rte_rwlock_t rwlock;
};

rte_eal_memzone_init()
    rte_fbarray_init(&mcfg->memzones, "memzone", RTE_MAX_MEMZONE 2560, sizeof(struct rte_memzone))
        page_sz = sysconf(_SC_PAGESIZE)
        mmap_len = calc_data_size(page_sz, elt_sz, len)
        data = eal_get_virtual_area(NULL, &mmap_len, page_sz, 0, 0)
            mapped_addr = mmap(requested_addr, (size_t)map_sz, PROT_NONE, mmap_flags, -1, 0)
        if (!internal_config.no_shconf)
            mmap(data, mmap_len, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)
        else
            fd = open("/var/run/fbarray_%s", O_CREAT | O_RDWR, 0600)
            ftruncate(fd, len)
            map_addr = mmap(data, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0)
```

## rte_eal_memory_init
```c++
static struct {
    int *fds;
    int memseg_list_fd;
    int len;
    int count;
} fd_list[RTE_MAX_MEMSEG_LISTS];

rte_eal_memory_init()
    rte_eal_memseg_init()
        memseg_primary_init()
            alloc_memseg_list()
                rte_fbarray_init()

            alloc_va_space()
                addr = eal_get_virtual_area(msl->base_va, &mem_sz, page_sz, 0, flags)
                msl->base_va = addr
                msl->len = mem_sz

    eal_memalloc_init()
        rte_memseg_list_walk(fd_list_create_walk, NULL)
            for (i = 0; i < RTE_MAX_MEMSEG_LISTS; i++)
                fd_list_create_walk()
                    alloc_list(msl_idx, len)
                        if (!internal_config.single_file_segments)
                            data = malloc(sizeof(int) * len)
                            fd_list[list_idx].fds = data
                            fd_list[list_idx].len = len
                        else
                            fd_list[list_idx].fds = NULL
                            fd_list[list_idx].len = 0

                        fd_list[list_idx].count = 0
                        fd_list[list_idx].memseg_list_fd = -1


    rte_eal_hugepage_init()
        eal_memalloc_alloc_seg_bulk()
            alloc_seg_walk()
                alloc_seg()
                    fd = get_seg_fd(path, sizeof(path), hi, list_idx, seg_idx)
                        if (internal_config.in_memory)
                            return get_seg_memfd()
                                if (internal_config.single_file_segments)
                                    fd = memfd_create("seg_%d", RTE_MFD_HUGETLB)
                                    fd_list[list_idx].memseg_list_fd = fd
                                else
                                    fd = memfd_create("seg_%i-%i", RTE_MFD_HUGETLB)
                                    fd_list[list_idx].fds[seg_idx] = fd

                        if (internal_config.single_file_segments)
                            fd = fd_list[list_idx].memseg_list_fd
                            if (fd < 0)
                                fd = open("rtemap_%d", O_CREAT | O_RDWR, 0600)
                            fd_list[list_idx].memseg_list_fd = fd
                        else
                            fd = fd_list[list_idx].fds[seg_idx]
                            if (fd < 0)
                                fd = open("rtemap_%d", O_CREAT | O_RDWR, 0600)
                            fd_list[list_idx].fds[seg_idx] = fd

                    if (internal_config.single_file_segments)
                        resize_hugefile(fd, map_offset, alloc_sz, true)
                            if (internal_config.in_memory)
                                resize_hugefile_in_memory(fd, fa_offset, page_sz, grow)
                                    fallocate(fd, flags, fa_offset, page_sz)
                            else
                                resize_hugefile_in_filesystem(fd, fa_offset, page_sz, grow)
                                    ftruncate(fd, new_size)
                    else
                        ftruncate(fd, alloc_sz)

                    addr = RTE_PTR_ADD(cur_msl->base_va, cur_idx * page_sz)
                    va = mmap(addr, alloc_sz, PROT_READ | PROT_WRITE, mmap_flags, fd, map_offset)
                    iova = rte_mem_virt2iova()
                        rte_mem_virt2phy()
                            fd = open("/proc/self/pagemap", O_RDONLY)
                            virt_pfn = (unsigned long)virtaddr / page_size;
                            offset = sizeof(uint64_t) * virt_pfn
                            lseek(fd, offset, SEEK_SET)
                            read(fd, &page, PFN_MASK_SIZE)
                            physaddr = ((page & 0x7fffffffffffffULL) * page_size) + ((unsigned long)virtaddr % page_size)

                    ms->addr = addr
                    ms->hugepage_sz = alloc_sz
                    ms->len = alloc_sz
                    ms->nchannel = rte_memory_get_nchannel()
                    ms->nrank = rte_memory_get_nrank()
                    ms->iova = iova
                    ms->socket_id = socket_id
```

## rte_eal_malloc_heap_init
```c++
struct rte_mem_config {
    struct malloc_heap malloc_heaps[RTE_MAX_HEAPS];
    struct rte_fbarray memzones;
};

struct malloc_heap {
    rte_spinlock_t lock;
    LIST_HEAD(, malloc_elem) free_head[RTE_HEAP_NUM_FREELISTS];
    struct malloc_elem *volatile first;
    struct malloc_elem *volatile last;

    unsigned int alloc_count;
    unsigned int socket_id;
    size_t total_size;
    char name[RTE_HEAP_NAME_MAX_LEN];
} __rte_cache_aligned;

struct malloc_elem {
    struct malloc_elem *orig_elem;
    struct malloc_elem *volatile prev;
    struct malloc_elem *volatile next;
    LIST_ENTRY(malloc_elem) free_list;
    struct malloc_heap *heap;
    struct rte_memseg_list *msl;
    volatile enum elem_state state;
    uint32_t pad;
    size_t size;
    size_t orig_size;
    uint64_t header_cookie;         /* Cookie marking start of data */
                                    /* trailer cookie at start + size */
} __rte_cache_aligned;

rte_eal_malloc_heap_init()
    for (i = 0; i < RTE_MAX_MEMSEG_LISTS; i++)
        while (ms_idx >= 0)
            malloc_add_seg()
                malloc_heap_add_memory()
                    malloc_elem_init(elem, heap, msl, len, elem, len)
                    malloc_elem_insert(elem)
                    elem = malloc_elem_join_adjacent_free(elem)
                    malloc_elem_free_list_insert(elem)
```

## rte_eal_intr_init
```c++
struct rte_intr_source {
    TAILQ_ENTRY(rte_intr_source) next;
    struct rte_intr_handle intr_handle;
    struct rte_intr_cb_list callbacks; /* rte_intr_callback.next */
    uint32_t active;
};

struct rte_intr_callback {
	TAILQ_ENTRY(rte_intr_callback) next;
	rte_intr_callback_fn cb_fn;
	void *cb_arg;
	uint8_t pending_delete;
	rte_intr_unregister_callback_fn ucb_fn;
};

struct rte_intr_handle {
    union {
        int vfio_dev_fd;
        int uio_cfg_fd;
    };
    int fd;
    enum rte_intr_handle_type type;
    uint32_t max_intr;
    uint32_t nb_efd;
    uint8_t efd_counter_size;
    int efds[RTE_MAX_RXTX_INTR_VEC_ID];
    struct rte_epoll_event elist[RTE_MAX_RXTX_INTR_VEC_ID];
    int *intr_vec;
};

struct rte_epoll_event {
    volatile uint32_t status;
    int fd;
    int epfd;
    struct rte_epoll_data epdata;
};

struct rte_epoll_data {
    uint32_t event;
    void *data;
    rte_intr_event_cb_t cb_fun;
    void *cb_arg;
};
```

```c++
TAILQ_INIT(&intr_sources)
pipe(intr_pipe.pipefd)
rte_ctrl_thread_create(&intr_thread, "eal-intr-thread", NULL, eal_intr_thread_main, NULL)

eal_intr_thread_main()
    for (;;) {
        static struct epoll_event pipe_event = {
            .events = EPOLLIN | EPOLLPRI,
        };
        struct rte_intr_source *src;
        unsigned numfds = 0;

        int pfd = epoll_create(1);
        pipe_event.data.fd = intr_pipe.readfd;
        /**
         * add pipe fd into wait list, this pipe is used to
         * rebuild the wait list.
         */
        epoll_ctl(pfd, EPOLL_CTL_ADD, intr_pipe.readfd, &pipe_event)

        TAILQ_FOREACH(src, &intr_sources, next) {
            struct epoll_event ev;
            memset(&ev, 0, sizeof(ev));
            ev.events = EPOLLIN | EPOLLPRI | EPOLLRDHUP | EPOLLHUP;
            ev.data.fd = src->intr_handle.fd;

            epoll_ctl(pfd, EPOLL_CTL_ADD, src->intr_handle.fd, &ev);
        }

        eal_intr_handle_interrupts(pfd, numfds) {
            for (;;) {
                nfds = epoll_wait(pfd, events, totalfds, EAL_INTR_EPOLL_WAIT_FOREVER);
                ret = eal_intr_process_interrupts(events, nfds) {
                    for (n = 0; n < nfds; n++) {
                        if (events[n].data.fd == intr_pipe.readfd){
                            int r = read(intr_pipe.readfd, buf.charbuf, sizeof(buf.charbuf));
                            RTE_SET_USED(r);
                            return -1;
                        }

                        /* set the length to be read dor different handle type */
                        switch (src->intr_handle.type) {
                        case RTE_INTR_HANDLE_UIO_INTX:
                            bytes_read = sizeof(buf.uio_intr_count);
                            break;
                        case RTE_INTR_HANDLE_ALARM:
                            bytes_read = sizeof(buf.timerfd_num);
                            break;
                        case RTE_INTR_HANDLE_VFIO_LEGACY:
                            bytes_read = sizeof(buf.vfio_intr_count);
                            break;
                        default:
                            bytes_read = 1;
                            break;
                        }

                        if (bytes_read > 0) {
                            bytes_read = read(events[n].data.fd, &buf, bytes_read);
                            call = true;
                        }

                        if (call) {
                            /* Finally, call all callbacks. */
                            TAILQ_FOREACH(cb, &src->callbacks, next) {
                                /* make a copy and unlock. */
                                struct rte_intr_callback active_cb = *cb;
                                rte_spinlock_unlock(&intr_lock);

                                /* call the actual callback */
                                active_cb.cb_fn(active_cb.cb_arg);

                                /*get the lock back. */
                                rte_spinlock_lock(&intr_lock);
                            }
                        }
                        /* we done with that interrupt source, release it. */
                        src->active = 0;

                        /* notify the pipe fd waited by epoll_wait to rebuild the wait list */
                        if (rv > 0 && write(intr_pipe.writefd, "1", 1) < 0) {
                            rte_spinlock_unlock(&intr_lock);
                            return -EPIPE;
                        }
                    }
                }

                if (ret < 0)
                    return;
            }
        }
        close(pfd);
    }
```

### rte_intr_callback_register
```c++
fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);

dev->vfio_req_intr_handle.fd = fd;
dev->vfio_req_intr_handle.type = RTE_INTR_HANDLE_VFIO_REQ;
dev->vfio_req_intr_handle.vfio_dev_fd = vfio_dev_fd;

ret = rte_intr_callback_register(&dev->vfio_req_intr_handle, pci_vfio_req_handler, (void *)&dev->device);
    struct rte_intr_source *src = alloc(1, sizeof(*src));
    src->intr_handle = *intr_handle;
    TAILQ_INIT(&src->callbacks);
    TAILQ_INSERT_TAIL(&(src->callbacks), callback, next);
    TAILQ_INSERT_TAIL(&intr_sources, src, next);

    write(intr_pipe.writefd, "1", 1)
```

## rte_eal_alarm_init
```c++
```

# memory

## rte_malloc
```c++
malloc_heap_alloc()
```

## rte_memzone_reserve

```c++
struct rte_memzone {
    char name[32];
    union {
        phys_addr_t phys_addr;
        rte_iova_t iova;
    };

    union {
        void *addr;
        uint64_t addr_64;
    };

    size_t len;
    uint64_t hugepage_sz;
    int32_t socket_id;
    uint32_t flags;
};

mz_addr = malloc_heap_alloc()
mz_idx = rte_fbarray_find_next_free(arr, 0)
rte_fbarray_set_used(arr, mz_idx)
mz = rte_fbarray_get(arr, mz_idx)

mz->iova = rte_malloc_virt2iova(mz_addr);
mz->addr = mz_addr;
mz->len = requested_len == 0
    ? elem->size - elem->pad - MALLOC_ELEM_OVERHEAD
    : requested_len;
mz->hugepage_sz = elem->msl->page_sz;
mz->socket_id = elem->msl->socket_id;
mz->flags = 0;
```

## malloc_heap_alloc
```c++
struct malloc_heap {
    rte_spinlock_t lock;
    LIST_HEAD(, malloc_elem) free_head[RTE_HEAP_NUM_FREELISTS];
    struct malloc_elem *volatile first;
    struct malloc_elem *volatile last;

    unsigned int alloc_count;
    unsigned int socket_id;
    size_t total_size;
    char name[RTE_HEAP_NAME_MAX_LEN];
};

heap_id = malloc_socket_to_heap_id(socket)
malloc_heap_alloc_on_heap_id()
    heap_alloc()
        elem = find_suitable_element(heap, size, flags, align, bound, contig)
        elem = malloc_elem_alloc(elem, size, align, bound, contig)
```