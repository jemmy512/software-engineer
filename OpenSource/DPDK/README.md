* [eal_init](#eal_init)
    * [rte_eal_config_create](#rte_eal_config_create)
    * [eal_hugepage_info_init](#eal_hugepage_info_init)
    * [rte_eal_memzone_init](#rte_eal_memzone_init)
    * [rte_eal_memory_init](#rte_eal_memory_init)
    * [rte_eal_malloc_heap_init](#rte_eal_malloc_heap_init)
    * [rte_eal_intr_init](#rte_eal_intr_init)
        * [rte_intr_callback_register](#rte_intr_callback_register)
        * [rte_eth_dev_rx_intr_ctl_q](#rte_eth_dev_rx_intr_ctl_q)
    * [rte_eal_alarm_init](#rte_eal_alarm_init)
    * [rte_eal_pci_init](#rte_eal_pci_init)
    * [rte_bus_scan](#rte_bus_scan)
    * [rte_bus_probe](#rte_bus_probe)

* [memory](#memory)
    * [rte_malloc](#rte_malloc)
    * [rte_memzone_reserve](#rte_memzone_reserve)
    * [malloc_heap_alloc](#malloc_heap_alloc)
    * [ring](#ring)
        * [rte_ring_create](#rte_ring_create)
        * [rte_ring_dequeue_bulk](#rte_ring_dequeue_bulk)
    * [mempool](#mempool)
        * [rte_mempool_create](#rte_mempool_create)
        * [rte_pktmbuf_pool_create](#rte_pktmbuf_pool_create)
        * [rte_mempool_get_bulk](#rte_mempool_get_bulk)
        * [rte_mempool_put_bulk](#rte_mempool_put_bulk)
    * [ret_mbuf](#ret_mbuf)

* [dev](#dev)
    * [rte_eth_dev_configure](#rte_eth_dev_configure)
    * [rte_eth_rx_queue_setup](#rte_eth_rx_queue_setup)
    * [rte_eth_tx_queue_setup](#rte_eth_tx_queue_setup)
    * [rte_eth_dev_start](#rte_eth_dev_start)
    * [rte_eth_rx_burst](#rte_eth_rx_burst)
    * [rte_eth_tx_burst](#rte_eth_tx_burst)

# eal_init

![](../Image/DPDK/mem-arch.png)

---

![](../Image/DPDK/dpdk-mempool.svg)

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

http://blog.chinaunix.net/uid-28541347-id-5784092.html

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

### eal_intr_thread_main
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
        /* add pipe fd into wait list, this pipe is used to rebuild the wait list. */
        epoll_ctl(pfd, EPOLL_CTL_ADD, intr_pipe.readfd, &pipe_event)

        TAILQ_FOREACH(src, &intr_sources, next) {
            struct epoll_event ev;
            memset(&ev, 0, sizeof(ev));
            ev.events = EPOLLIN | EPOLLPRI | EPOLLRDHUP | EPOLLHUP;
            ev.data.fd = src->intr_handle.fd;

            epoll_ctl(pfd, EPOLL_CTL_ADD, src->intr_handle.fd, &ev);
        }

        eal_intr_handle_interrupts(pfd, numfds) {
            struct epoll_event events[totalfds];
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

### register rte_intr_source
```c++
int eth_vhost_install_intr(struct rte_eth_dev *dev)
{
    struct rte_vhost_vring vring;
    struct vhost_queue *vq;
    int count = 0;
    int nb_rxq = dev->data->nb_rx_queues;
    int i;
    int ret;

    /* uninstall firstly if we are reconnecting */
    if (dev->intr_handle)
        eth_vhost_uninstall_intr(dev);

    dev->intr_handle = malloc(sizeof(*dev->intr_handle));
    memset(dev->intr_handle, 0, sizeof(*dev->intr_handle));

    dev->intr_handle->efd_counter_size = sizeof(uint64_t);

    dev->intr_handle->intr_vec = malloc(nb_rxq * sizeof(dev->intr_handle->intr_vec[0]));

    for (i = 0; i < nb_rxq; i++) {
        vq = dev->data->rx_queues[i];
        if (!vq) {
            VHOST_LOG(INFO, "rxq-%d not setup yet, skip!\n", i);
            continue;
        }

        ret = rte_vhost_get_vhost_vring(vq->vid, (i << 1) + 1, &vring);
        if (ret < 0) {
            VHOST_LOG(INFO,
                "Failed to get rxq-%d's vring, skip!\n", i);
            continue;
        }

        if (vring.kickfd < 0) {
            VHOST_LOG(INFO,
                "rxq-%d's kickfd is invalid, skip!\n", i);
            continue;
        }
        dev->intr_handle->intr_vec[i] = RTE_INTR_VEC_RXTX_OFFSET + i;
        dev->intr_handle->efds[i] = vring.kickfd;
        count++;
    }

    dev->intr_handle->nb_efd = count;
    dev->intr_handle->max_intr = count + 1;
    dev->intr_handle->type = RTE_INTR_HANDLE_VDEV;

    return 0;
}
```

### register ctrl callback
```c++
static struct rte_pci_driver rte_ixgbevf_pmd = {
    .id_table = pci_id_ixgbevf_map,
    .drv_flags = RTE_PCI_DRV_NEED_MAPPING,
    .probe = eth_ixgbevf_pci_probe,
    .remove = eth_ixgbevf_pci_remove,
};

int eth_ixgbevf_pci_probe(struct rte_pci_driver *pci_drv __rte_unused,
    struct rte_pci_device *pci_dev)
{
    return rte_eth_dev_pci_generic_probe(pci_dev,
        sizeof(struct ixgbe_adapter), eth_ixgbevf_dev_init);
}

fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);

dev->vfio_req_intr_handle.fd = fd;
dev->vfio_req_intr_handle.type = RTE_INTR_HANDLE_VFIO_REQ;
dev->vfio_req_intr_handle.vfio_dev_fd = vfio_dev_fd;

ret = rte_intr_callback_register(intr_handle, cb, cb_arg);
    struct rte_intr_callback *callback = calloc(1, sizeof(*callback))
    callback->cb_fn = cb;
    callback->cb_arg = cb_arg;
    callback->pending_delete = 0;
    callback->ucb_fn = NULL;

    struct rte_intr_source *src = alloc(1, sizeof(*src));
    src->intr_handle = *intr_handle;
    TAILQ_INIT(&src->callbacks);
    TAILQ_INSERT_TAIL(&(src->callbacks), callback, next);
    TAILQ_INSERT_TAIL(&intr_sources, src, next);

    write(intr_pipe.writefd, "1", 1)
```

### register data callback
```c++
static int event_register(struct lcore_conf *qconf)
{
    struct lcore_rx_queue *rx_queue;
    uint8_t portid, queueid;
    uint32_t data;
    int ret;
    int i;

    /* register callback for each queue indexed at id */
    for (i = 0; i < qconf->n_rx_queue; ++i) {
        rx_queue = &(qconf->rx_queue_list[i]);
        portid = rx_queue->port_id;
        queueid = rx_queue->queue_id;
        data = portid << CHAR_BIT | queueid;

        ret = rte_eth_dev_rx_intr_ctl_q(portid, queueid,
            RTE_EPOLL_PER_THREAD, RTE_INTR_EVENT_ADD, (void *)((uintptr_t)data)
        );
    }

    return 0;
}

rte_eth_dev_rx_intr_ctl_q(uint16_t port_id, uint16_t queue_id, int epfd, int op, void *data)
    dev = &rte_eth_devices[port_id];
    intr_handle = dev->intr_handle;
    vec = intr_handle->intr_vec[queue_id];

    rte_intr_rx_ctl(intr_handle, epfd, op, vec, data);
        switch (op) {
        case RTE_INTR_EVENT_ADD:
            epfd_op = EPOLL_CTL_ADD;
            epdata = &rev->epdata;
            epdata->event  = EPOLLIN | EPOLLPRI | EPOLLET;
            epdata->data   = data;
            epdata->cb_fun = (rte_intr_event_cb_t)eal_intr_proc_rxtx_intr;
            epdata->cb_arg = (void *)intr_handle;

            rc = rte_epoll_ctl(epfd, epfd_op, intr_handle->efds[efd_idx], rev);
                if (epfd == RTE_EPOLL_PER_THREAD)
                    epfd = rte_intr_tls_epfd();
                if (op == EPOLL_CTL_ADD) {
                    event->status = RTE_EPOLL_VALID;
                    event->fd = fd;  /* ignore fd in event */
                    event->epfd = epfd;
                    ev.data.ptr = (void *)event;
                }
                ev.events = event->epdata.event;
                epoll_ctl(epfd, op, fd, &ev);
        }

rte_event_eth_rx_adapter_queue_add()
    rxa_sw_add()
        rxa_add_intr_queue()
            rxa_config_intr()
                rxa_create_intr_thread(rx_adapter)
                    rx_adapter->intr_ring = rte_ring_create();
                    rx_adapter->epoll_events = rte_zmalloc_socket();
                    rte_ctrl_thread_create(&rx_adapter->rx_intr_thread, thread_name, NULL, rxa_intr_thread, rx_adapter);

                    rxa_intr_thread(void *arg)
                        struct rte_event_eth_rx_adapter *rx_adapter = arg;
                        struct rte_epoll_event *epoll_events = rx_adapter->epoll_events;
                        int n, i;

                        while (1) {
                            n = rte_epoll_wait(rx_adapter->epd, epoll_events, RTE_EVENT_ETH_INTR_RING_SIZE, -1);

                            for (i = 0; i < n; i++) {
                                rxa_intr_ring_enqueue(rx_adapter, epoll_events[i].epdata.data);
                            }
                        }

rte_epoll_wait(int epfd, struct rte_epoll_event *events, int maxevents, int timeout)
    struct epoll_event evs[maxevents];
    while (1) {
        rc = epoll_wait(epfd, evs, maxevents, timeout);
        if (likely(rc > 0)) {
            rc = eal_epoll_process_event(evs, rc, events);
                for (i = 0; i < n; i++) {
                    struct rte_epoll_event *rev = evs[i].data.ptr;
                    events[count].status        = RTE_EPOLL_VALID;
                    events[count].fd            = rev->fd;
                    events[count].epfd          = rev->epfd;
                    events[count].epdata.event  = evs[i].events;
                    events[count].epdata.data   = rev->epdata.data;
                    if (rev->epdata.cb_fun)
                        rev->epdata.cb_fun(rev->fd, rev->epdata.cb_arg);
                            eal_intr_proc_rxtx_intr()
                                switch (intr_handle->type) {
                                case RTE_INTR_HANDLE_UIO:
                                case RTE_INTR_HANDLE_UIO_INTX:
                                    bytes_read = sizeof(buf.uio_intr_count);
                                    break;
                                }

                                do {
                                    nbytes = read(fd, &buf, bytes_read);
                                } while (1);
                }
        }
    }
```

## rte_eal_alarm_init
```c++
```

## rte_bus_scan
```c++
struct rte_pci_bus rte_pci_bus = {
    .bus = {
        .scan = rte_pci_scan,
        .probe = pci_probe,
        .find_device = pci_find_device,
        .plug = pci_plug,
        .unplug = pci_unplug,
        .parse = pci_parse,
        .dma_map = pci_dma_map,
        .dma_unmap = pci_dma_unmap,
        .get_iommu_class = rte_pci_get_iommu_class,
        .dev_iterate = rte_pci_dev_iterate,
        .hot_unplug_handler = pci_hot_unplug_handler,
        .sigbus_handler = pci_sigbus_handler,
    },
    .device_list = TAILQ_HEAD_INITIALIZER(rte_pci_bus.device_list),
    .driver_list = TAILQ_HEAD_INITIALIZER(rte_pci_bus.driver_list),
};

RTE_REGISTER_BUS(pci, rte_pci_bus.bus);
```

```c++
struct rte_bus *bus;
TAILQ_FOREACH(bus, &rte_bus_list, next) {
    bus->scan()
        rte_pci_scan()
            struct rte_pci_addr addr; /* 0000:01:11.4 <domain.bus.devid.function> */
            struct dirent * dir = opendir("/sys/bus/pci/devices")
            while ((e = readdir(dir)) != NULL) {
                snprintf(dirname, sizeof(dirname), "%s/%s", rte_pci_get_sysfs_path(), e->d_name);
                pci_scan_one(dirname, &addr);
                    struct rte_pci_device *dev = malloc(sizeof(*dev))
                    dev->device.bus = &rte_pci_bus.bus;
                    dev->addr = *addr;
                    dev->id.device_id = (uint16_t)tmp;
                    dev->device.numa_node = tmp;
                    dev->id.class_id = (uint32_t)tmp & RTE_CLASS_ANY_ID;

                    pci_parse_sysfs_resource("%s/resource", dev);
                    pci_get_kernel_driver_by_path( "%s/driver", driver, sizeof(driver));
                    dev->kdrv = RTE_KDRV_IGB_UIO; /* RTE_KDRV_VFIO, RTE_KDRV_UIO_GENERIC */

                    rte_pci_add_device(dev);
                        TAILQ_INSERT_TAIL(&rte_pci_bus.device_list, pci_dev, next)
            }
}
```

## rte_bus_probe

```c++
struct rte_bus *bus, *vbus = NULL;
TAILQ_FOREACH(bus, &rte_bus_list, next)
    bus->probe();
        pci_probe()
            FOREACH_DEVICE_ON_PCIBUS(dev) {
                pci_probe_all_drivers()
                    struct rte_pci_driver *dr = NULL;
                    FOREACH_DRIVER_ON_PCIBUS(dr) {
                        if (!rte_pci_match(dr, dev))
                            return 1;
                        rte_pci_probe_one_driver(dr, dev);
                            if (!already_probed && (dr->drv_flags & RTE_PCI_DRV_NEED_MAPPING)) {
                                /* map resources for devices that use igb_uio */
                                rte_pci_map_device(dev);
                            }
                            dr->probe(dr, dev);
                                eth_ixgbe_pci_probe()
                                    rte_eth_dev_create(&pci_dev->device)
                                    eth_dev_pci_specific_init()

                                    eth_ixgbe_dev_init(eth_dev, init_param)
                                        eth_dev->dev_ops = &ixgbe_eth_dev_ops;
                                        eth_dev->rx_pkt_burst = &ixgbe_recv_pkts;
                                        eth_dev->tx_pkt_burst = &ixgbe_xmit_pkts;
                                        eth_dev->tx_pkt_prepare = &ixgbe_prep_pkts;

                                        rte_intr_callback_register(intr_handle, ixgbe_dev_interrupt_handler, eth_dev);
                                        ixgbe_fdir_filter_init(eth_dev)

                                    rte_eth_dev_probing_finish()
                                        _rte_eth_dev_callback_process(dev, RTE_ETH_EVENT_NEW, NULL)
                                            struct rte_eth_dev_callback *cb_lst;
                                            struct rte_eth_dev_callback dev_cb;
                                            TAILQ_FOREACH(cb_lst, &(dev->link_intr_cbs), next) {
                                                dev_cb = *cb_lst;
                                                rc = dev_cb.cb_fn(dev->data->port_id, dev_cb.event,
                                                        dev_cb.cb_arg, dev_cb.ret_param);
                                                cb_lst->active = 0;
                                            }

                    }
            }

```

# memory

## rte_malloc
```c++
rte_malloc_socket(type, size, align, SOCKET_ID_ANY)
    malloc_heap_alloc()
        /* 1. alloc on local socket */
        heap_id = malloc_socket_to_heap_id(socket)
            for (i = 0; i < RTE_MAX_HEAPS; i++) {
                struct malloc_heap *heap = &mcfg->malloc_heaps[i];
                if (heap->socket_id == socket_id)
                    return i;
            }
        malloc_heap_alloc_on_heap_id(type, size, heap_id, flags, align, bound, contig)
            heap_alloc()
                elem = find_suitable_element()
                    malloc_elem_free_list_index()
                        /*  heap->free_head[0] - (0   , 2^8]
                        *   heap->free_head[1] - (2^8 , 2^10]
                        *   heap->free_head[2] - (2^10 ,2^12]
                        *   heap->free_head[3] - (2^12, 2^14]
                        *   heap->free_head[4] - (2^14, MAX_SIZE] */
                elem = malloc_elem_alloc(elem, size, align, bound, contig)

        /* 2. alloc on remote socket */
        for (i = 0; i < (int) rte_socket_count(); i++) {
            if (i == heap_id)
                continue;
            ret = malloc_heap_alloc_on_heap_id();
            if (ret != NULL)
                return ret;
        }
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

## ring

* [DPDK Ring Library](http://doc.dpdk.org/guides/prog_guide/ring_lib.html#single-producer-enqueue)

```c++
struct rte_ring {
    char name[RTE_MEMZONE_NAMESIZE] __rte_cache_aligned;
    int flags;
    const struct rte_memzone *memzone;

    uint32_t size;
    uint32_t mask;
    uint32_t capacity;
    char pad0 __rte_cache_aligned;

    struct rte_ring_headtail prod __rte_cache_aligned;
    char pad1 __rte_cache_aligned;

    struct rte_ring_headtail cons __rte_cache_aligned;
    char pad2 __rte_cache_aligned;
};

struct rte_ring_headtail {
    volatile uint32_t head;
    volatile uint32_t tail;
    uint32_t single;
};
```

### rte_ring_create
```c++

```

### rte_ring_dequeue_bulk
```c++
rte_ring_do_dequeue()
    __rte_ring_move_cons_head()
    DEQUEUE_PTRS(r, &r[1], cons_head, obj_table, n, void *)
    update_tail(&r->cons, cons_head, cons_next, is_sc, 0)
```

```c++
rte_ring_do_enqueue()
    __rte_ring_move_prod_head(r, is_sp, n, behavior, &prod_head, &prod_next, &free_entries)
    ENQUEUE_PTRS(r, &r[1], prod_head, obj_table, n, void *);
    update_tail(&r->prod, prod_head, prod_next, is_sp, 1);
```

### Anatomy
* Multiple Producers Enqueue
    1. rte_ring_move_prod_head
        * On both cores, ring->prod_head and ring->cons_tail are copied in local variables.
            * ![](../Image/DPDK/ring-mp-1.svg)
        * modify ring->prod_head in the ring structure to point to the same location as prod_next.
            * ![](../Image/DPDK/ring-mp-2.svg)
            * If ring->prod_head is different to local variable prod_head, the CAS operation fails, and the code restarts at first step.
            * Otherwise, ring->prod_head is set to local prod_next, the CAS operation is successful, and processing continues.
    2. ENQUEUE_PTRS
        * ![](../Image/DPDK/ring-mp-3.svg)
        * The core 1 updates one element of the ring(obj4), and the core 2 updates another one (obj5).
    3. update_tail
        * ![](../Image/DPDK/ring-mp-4.svg)
            * Each core now wants to update ring->prod_tail. A core can only update it if ring->prod_tail is equal to the prod_head local variable.
        *  ![](../Image/DPDK/ring-mp-4.svg)
            * Once ring->prod_tail is updated by core 1, core 2 is allowed to update it too. The operation is also finished on core 2.
## mempool
```c++
struct rte_mempool {
    char name[RTE_MEMZONE_NAMESIZE];

    union {
        void *pool_data;
        uint64_t pool_id;
    };
    void *pool_config;
    const struct rte_memzone *mz;
    unsigned int flags;
    int socket_id;
    uint32_t size;
    uint32_t cache_size;

    uint32_t elt_size;
    uint32_t header_size;
    uint32_t trailer_size;

    unsigned private_data_size;

    int32_t ops_index;

    struct rte_mempool_cache *local_cache;

    uint32_t populated_size;
    struct rte_mempool_objhdr_list elt_list;
    uint32_t nb_mem_chunks;
    struct rte_mempool_memhdr_list mem_list;
};
```

### rte_mempool_create
```c++
rte_mempool_create_empty()
    rte_mempool_calc_obj_size()
    mz = rte_memzone_reserve()
        --->
    mp = mz->addr

rte_mempool_set_ops_byname() /* ring_sp_sc, ring_sp_mc, ring_mp_sc, ring_mp_mc */
rte_mempool_populate_default()
    /* 1. alloc ring */
    mempool_ops_alloc_once()
        rte_mempool_ops_alloc()
            mp->ops->alloc(mp)
                common_ring_alloc()
                    rte_ring_create()

    /* 2. alloc for each obj */
    for (mz_id = 0, n = mp->size; n > 0; mz_id++, n -= ret) {
        rte_mempool_ops_calc_mem_size()
        rte_memzone_reserve_aligned()
        if (pg_sz == 0 || (mz_flags & RTE_MEMZONE_IOVA_CONTIG))
            rte_mempool_populate_iova()
                __rte_mempool_populate_iova()
                    memhdr = rte_zmalloc("MEMPOOL_MEMHDR", sizeof(struct rte_mempool_memhdr), 0)
                    memhdr->mp = mp;
                    memhdr->addr = vaddr;
                    memhdr->iova = iova;
                    memhdr->len = len;
                    memhdr->free_cb = free_cb;
                    memhdr->opaque = opaque;
                    rte_mempool_ops_populate(obj_cb)
                        obj_cb()
                            mempool_add_elem(mempool_add_elem)
                                STAILQ_INSERT_TAIL(&mp->elt_list, hdr, next)
                        rte_mempool_ops_enqueue_bulk()
        else
            rte_mempool_populate_virt()
                __rte_mempool_populate_iova()
    }

rte_mempool_obj_iter()
```

### rte_pktmbuf_pool_create
```c++
rte_pktmbuf_pool_create_by_ops()
    rte_mempool_create_empty()
        rte_memzone_reserve()
            --->
    rte_mempool_set_ops_byname()
    rte_pktmbuf_pool_init()
    rte_mempool_populate_default()
    rte_mempool_obj_iter(mp, rte_pktmbuf_init, NULL)
```

### rte_mempool_get_bulk
```c++
cache = rte_mempool_default_cache()
    mp->local_cache[lcore_id]
rte_mempool_generic_get(cache)
    __mempool_generic_get()
        /* 1. get from local cache*/
        for (index = 0, len = cache->len - 1; index < n; ++index, len--, obj_table++)
            *obj_table = cache_objs[len];

        /* 2. get from ring */
        rte_mempool_ops_dequeue_bulk()
            mp->ops->dequeue()
                common_ring_sc_dequeue()
                    rte_ring_sc_dequeue_bulk()
```

### rte_mempool_put_bulk
```c++
cache = rte_mempool_default_cache()
    mp->local_cache[lcore_id]
rte_mempool_generic_put(cache)
    __mempool_generic_put()
        /* 1. put to cache */
        rte_memcpy(&cache->objs[cache->len], obj_table, sizeof(void *) * n)

        /* 2. put to ring*/
        rte_mempool_ops_enqueue_bulk()
            mp->ops->enqueue()
                common_ring_sp_enqueue()
                    rte_ring_sp_enqueue_bulk()
                        __rte_ring_do_enqueue()
                            __rte_ring_move_prod_head()
                            ENQUEUE_PTRS(r, &r[1], prod_head, obj_table, n, void *)
                            update_tail()
```

## ret_mbuf

![](../Image/DPDK/rte_mbuf.svg)

![](../Image/DPDK/rte_mbuf_chain.svg)

![](../Image/DPDK/rte_mbuf-gso.svg)

```c++
struct rte_mbuf {
    MARKER cacheline0;

    void *buf_addr;

    union {
        rte_iova_t buf_iova;
        rte_iova_t buf_physaddr;
    } __rte_aligned(sizeof(rte_iova_t));

    MARKER64 rearm_data;
    uint16_t data_off;

    union {
        rte_atomic16_t refcnt_atomic;

        uint16_t refcnt;
    };
    uint16_t nb_segs;


    uint16_t port;
    uint64_t ol_flags;

    MARKER rx_descriptor_fields1;

    union {
        uint32_t packet_type;
        struct {
            uint32_t l2_type:4;
            uint32_t l3_type:4;
            uint32_t l4_type:4;
            uint32_t tun_type:4;

            union {
                uint8_t inner_esp_next_proto;
                struct {
                    uint8_t inner_l2_type:4;
                    uint8_t inner_l3_type:4;
                };
            };
            uint32_t inner_l4_type:4;
        };
    };

    uint32_t pkt_len;
    uint16_t data_len;
    uint16_t vlan_tci;

    union {
        union {
            uint32_t rss;

            struct {
                union {
                    struct {
                        uint16_t hash;
                        uint16_t id;
                    };
                    uint32_t lo;
                };
                uint32_t hi;
            } fdir;

            struct rte_mbuf_sched sched;

            struct {
                uint32_t reserved1;
                uint16_t reserved2;
                uint16_t txq;
            } txadapter;

            uint32_t usr;
        } hash;
    };


    uint16_t vlan_tci_outer;

    uint16_t buf_len;

    uint64_t timestamp;

    /* second cache line - fields only used in slow path or on TX */
    MARKER cacheline1 __rte_cache_min_aligned;

    union {
        void *userdata;
        uint64_t udata64;
    };

    struct rte_mempool *pool;
    struct rte_mbuf *next;

    /* fields to support TX offloads */
    union {
        uint64_t tx_offload;
        struct {
            uint64_t l2_len:RTE_MBUF_L2_LEN_BITS;
            uint64_t l3_len:RTE_MBUF_L3_LEN_BITS;
            uint64_t l4_len:RTE_MBUF_L4_LEN_BITS;
            uint64_t tso_segsz:RTE_MBUF_TSO_SEGSZ_BITS;

            uint64_t outer_l3_len:RTE_MBUF_OUTL3_LEN_BITS;
            uint64_t outer_l2_len:RTE_MBUF_OUTL2_LEN_BITS;
        };
    };

    uint16_t priv_size;
    uint16_t timesync;
    uint32_t seqn;

    struct rte_mbuf_ext_shared_info *shinfo;
    uint64_t dynfield1[2];
}
```

# dev

![](../Image/DPDK/ixgbe_rx_queue.png)

![](../Image/DPDK/dev-config-setup.jpg)

Ref:
* http://blog.chinaunix.net/uid-28541347-id-5785122.html

## rte_eth_dev_configure
```c++
rte_eth_dev_configure(uint16_t port_id, uint16_t nb_rx_q, uint16_t nb_tx_q, const struct rte_eth_conf *dev_conf)
    struct rte_eth_dev* dev = &rte_eth_devices[port_id]

    /* Check the numbers of RX and TX queues */
    /* Check the device supports requested interrupts */
    /* Check offloading capabilities */
    /* Check device supports requested rss hash functions. */

    memcpy(&dev->data->dev_conf, dev_conf, sizeof(dev->data->dev_conf))

    rte_eth_dev_rx_queue_config(dev, nb_rx_q)
        dev->data->rx_queues = rte_zmalloc(sizeof(dev->data->rx_queues[0]) * nb_queues)

    rte_eth_dev_tx_queue_config(dev, nb_tx_q)
        dev->data->tx_queues = rte_zmalloc(sizeof(dev->data->tx_queues[0]) * nb_queues)

    /* eth_dev->dev_ops = &ixgbe_eth_dev_ops */
    (*dev->dev_ops->dev_configure)(dev)

    /* Validate Rx Tx offloads. */
```

## rte_eth_rx_queue_setup
```c++
struct rte_eth_dev* dev = &rte_eth_devices[port_id]
(*dev->dev_ops->rx_queue_setup)(dev, rx_queue_id, nb_rx_desc, socket_id, &local_conf, mp)
    ixgbe_dev_rx_queue_setup()
        /* 1. alloc ixgbe_rx_queue */
        struct ixgbe_rx_queue* rxq = rte_zmalloc_socket(sizeof(struct ixgbe_rx_queue))
        rxq->mb_pool = mp;
        rxq->nb_rx_desc = nb_desc;
        rxq->rx_free_thresh = rx_conf->rx_free_thresh;
        rxq->queue_id = queue_idx;

        rxq->rdt_reg_addr = IXGBE_PCI_REG_ADDR(hw, IXGBE_RDT(rxq->reg_idx));
        rxq->rdh_reg_addr = IXGBE_PCI_REG_ADDR(hw, IXGBE_RDH(rxq->reg_idx));

         /* 2. alloc rx ring */
        const struct rte_memzone* rz = rte_eth_dma_zone_reserve(queue_idx, RX_RING_SZ, IXGBE_ALIGN)
        rxq->rx_ring_phys_addr = rz->iova;
        rxq->rx_ring = (union ixgbe_adv_rx_desc *) rz->addr;
        rxq->sw_ring = rte_zmalloc_socket(sizeof(struct ixgbe_rx_entry) * nb_rx_q)
        rxq->sw_sc_ring = rte_zmalloc_socket(sizeof(struct ixgbe_scattered_rx_entry) * nb_rx_q)

        dev->data->rx_queues[queue_idx] = rxq

        ixgbe_reset_rx_queue(adapter, rxq)
            rxq->rx_nb_avail = 0;
            rxq->rx_next_avail = 0;
            rxq->rx_free_trigger = (uint16_t)(rxq->rx_free_thresh - 1);
            rxq->rx_tail = 0;
            rxq->nb_rx_hold = 0;
            rxq->pkt_first_seg = NULL;
            rxq->pkt_last_seg = NULL;
```

## rte_eth_tx_queue_setup
```c++
```

## rte_eth_dev_start
```c++
(*dev->dev_ops->dev_start)(dev)
    ixgbe_dev_start()
        rte_intr_disable(intr_handle);

        hw->adapter_stopped = 0;
        ixgbe_stop_adapter(hw);

        ixgbe_pf_reset_hw(hw);

        /* check and configure queue intr-vector mapping */
        rte_intr_efd_enable(intr_handle, intr_vector)

        ixgbe_dev_tx_init(dev);
            /* Setup the Base and Length of the Tx Descriptor Rings */
            for (i = 0; i < dev->data->nb_tx_queues; i++) {
                txq = dev->data->tx_queues[i];
                bus_addr = txq->tx_ring_phys_addr;
                IXGBE_WRITE_REG(hw, IXGBE_TDBAL(txq->reg_idx), (uint32_t)(bus_addr & 0x00000000ffffffffULL));
                IXGBE_WRITE_REG(hw, IXGBE_TDBAH(txq->reg_idx), (uint32_t)(bus_addr >> 32));
                IXGBE_WRITE_REG(hw, IXGBE_TDLEN(txq->reg_idx), txq->nb_tx_desc * sizeof(union ixgbe_adv_tx_desc));
                /* Setup the HW Tx Head and TX Tail descriptor pointers */
                IXGBE_WRITE_REG(hw, IXGBE_TDH(txq->reg_idx), 0);
                IXGBE_WRITE_REG(hw, IXGBE_TDT(txq->reg_idx), 0);
            }

            /* Device configured with multiple TX queues. */
            ixgbe_dev_mq_tx_configure(dev);

        ixgbe_dev_rx_init(dev);
            /* Setup the Base and Length of the Rx Descriptor Rings */
            for (i = 0; i < dev->data->nb_rx_queues; i++) {
                rxq = dev->data->rx_queues[i];
                bus_addr = rxq->rx_ring_phys_addr;
                IXGBE_WRITE_REG(hw, IXGBE_RDBAL(rxq->reg_idx), (uint32_t)(bus_addr & 0x00000000ffffffffULL));
                IXGBE_WRITE_REG(hw, IXGBE_RDBAH(rxq->reg_idx), (uint32_t)(bus_addr >> 32));
                IXGBE_WRITE_REG(hw, IXGBE_RDLEN(rxq->reg_idx), rxq->nb_rx_desc * sizeof(union ixgbe_adv_rx_desc));
                IXGBE_WRITE_REG(hw, IXGBE_RDH(rxq->reg_idx), 0);
                IXGBE_WRITE_REG(hw, IXGBE_RDT(rxq->reg_idx), 0);
            }

            /* Device configured with multiple RX queues. */
            ixgbe_dev_mq_rx_configure(dev);

        ixgbe_vlan_offload_config(dev, mask);

        ixgbe_flow_ctrl_enable(dev, hw);

        ixgbe_dev_rxtx_start(dev);
            /* Setup Transmit Threshold Registers */
            for (i = 0; i < dev->data->nb_tx_queues; i++) {
                txq = dev->data->tx_queues[i];
                txdctl = IXGBE_READ_REG(hw, IXGBE_TXDCTL(txq->reg_idx));
                txdctl |= txq->pthresh & 0x7F;
                txdctl |= ((txq->hthresh & 0x7F) << 8);
                txdctl |= ((txq->wthresh & 0x7F) << 16);
                IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(txq->reg_idx), txdctl);
            }

            for (i = 0; i < dev->data->nb_tx_queues; i++) {
                txq = dev->data->tx_queues[i];
                if (!txq->tx_deferred_start) {
                    ret = ixgbe_dev_tx_queue_start(dev, i);
                        txdctl = IXGBE_READ_REG(hw, IXGBE_TXDCTL(txq->reg_idx));
                        txdctl |= IXGBE_TXDCTL_ENABLE;
                        IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(txq->reg_idx), txdctl);
                        IXGBE_WRITE_REG(hw, IXGBE_TDH(txq->reg_idx), 0);
                        IXGBE_WRITE_REG(hw, IXGBE_TDT(txq->reg_idx), 0);
                    dev->data->rx_queue_state[rx_queue_id] = RTE_ETH_QUEUE_STATE_STARTED;
                }
            }

            for (i = 0; i < dev->data->nb_rx_queues; i++) {
                rxq = dev->data->rx_queues[i];
                if (!rxq->rx_deferred_start) {
                    ret = ixgbe_dev_rx_queue_start(dev, i);
                        ixgbe_alloc_rx_queue_mbufs(rxq)
                            /* Initialize software ring entries
                             * establish relation ship: mempool, queue, DMA, ring */
                            for (i = 0; i < rxq->nb_rx_desc; i++) {
                                volatile union ixgbe_adv_rx_desc *rxd;
                                struct rte_mbuf *mbuf = rte_mbuf_raw_alloc(rxq->mb_pool);
                                mbuf->data_off = RTE_PKTMBUF_HEADROOM;
                                mbuf->port = rxq->port_id;

                                dma_addr = rte_cpu_to_le_64(rte_mbuf_data_iova_default(mbuf));
                                rxd = &rxq->rx_ring[i];
                                rxd->read.hdr_addr = 0;
                                rxd->read.pkt_addr = dma_addr;
                                rxe[i].mbuf = mbuf;
                            }
                }
            }

        ixgbe_setup_link(hw, speed, link_up);
```

## rte_eth_rx_burst
```c++
rte_eth_rx_burst(uint16_t port_id, uint16_t queue_id, struct rte_mbuf **rx_pkts, const uint16_t nb_pkts)
    nb_rx = (*dev->rx_pkt_burst)(dev->data->rx_queues[queue_id], rx_pkts, nb_pkts)
        ixgbe_recv_pkts()
            nb_rx = 0;
            nb_hold = 0;
            rxq = rx_queue;
            rx_id = rxq->rx_tail;
            rx_ring = rxq->rx_ring;
            sw_ring = rxq->sw_ring;
            vlan_flags = rxq->vlan_flags;

            while (nb_rx < nb_pkts) {
                rxdp = &rx_ring[rx_id];
                staterr = rxdp->wb.upper.status_error;
                if (!(staterr & rte_cpu_to_le_32(IXGBE_RXDADV_STAT_DD)))
                    break;

                rxd = *rxdp;

                nmb = rte_mbuf_raw_alloc(rxq->mb_pool);
                rxe = &sw_ring[rx_id];
                rxm = rxe->mbuf;
                rxe->mbuf = nmb;
                rxdp->read.hdr_addr = 0; /* set DD 0 */
                dma_addr = rte_cpu_to_le_64(rte_mbuf_data_iova_default(nmb));
                rxdp->read.pkt_addr = dma_addr;

                rx_pkts[nb_rx++] = rxm;
            }

            rxq->rx_tail = rx_id;

            return nb_rx;
```

## rte_eth_tx_burst
```c++
/* descriptor write-back:
 * 1. Updating by writing back into the Tx descriptor
    * TXDCTL[n].WTHRESH = 0 and a descriptor that has RS set is ready to be written back.
    * TXDCTL[n].WTHRESH > 0 and TXDCTL[n].WTHRESH descriptors have accumulated.
    * TXDCTL[n].WTHRESH > 0 and the corresponding EITR counter has reached zero.
       The timer expiration flushes any accumulated descriptors and sets an interrupt event(TXDW).
 * 2. Update by writing to the head pointer in system memory */

rte_eth_tx_burst(uint16_t port_id, uint16_t queue_id, struct rte_mbuf **tx_pkts, uint16_t nb_pkts)
    (*dev->tx_pkt_burst)(dev->data->tx_queues[queue_id], tx_pkts, nb_pkts)
        ixgbe_xmit_pkts()
            /* Determine if the descriptor ring needs to be cleaned. */
            if (txq->nb_tx_free < txq->tx_free_thresh)
                ixgbe_xmit_cleanup(txq);

            tx_id = txq->tx_tail;

            for (nb_tx = 0; nb_tx < nb_pkts; nb_tx++) {
                /* Determine how many (if any) context descriptors are needed for offload functionality. */

                /* Keep track of how many descriptors are used this loop */
                nb_used = (uint16_t)(tx_pkt->nb_segs + new_ctx);

                /* Determine the last TX descriptor to allocate in the TX ring */
                tx_last = (uint16_t) (tx_id + nb_used - 1);

                /* Make sure there are enough TX descriptors available to transmit the entire packet */
                if (nb_used > txq->nb_tx_free) {
                    ixgbe_xmit_cleanup(txq);
                }

                /* send mbuf to sw_ring */
                m_seg = tx_pkt;
                do {
                    txd = &txr[tx_id];
                    txn = &sw_ring[txe->next_id];
                    rte_prefetch0(&txn->mbuf->pool);

                    txe->mbuf = m_seg;

                    /* Set up Transmit Data Descriptor. */
                    slen = m_seg->data_len;
                    buf_dma_addr = rte_mbuf_data_iova(m_seg);
                    txd->read.buffer_addr = rte_cpu_to_le_64(buf_dma_addr);
                    txd->read.cmd_type_len = rte_cpu_to_le_32(cmd_type_len | slen);
                    txd->read.olinfo_status = rte_cpu_to_le_32(olinfo_status);
                    txe->last_id = tx_last;
                    tx_id = txe->next_id;
                    txe = txn;
                    m_seg = m_seg->next;
                } while (m_seg != NULL);

                /* The last packet data descriptor needs End Of Packet (EOP) */
                cmd_type_len |= IXGBE_TXD_CMD_EOP;
                txq->nb_tx_used = (uint16_t)(txq->nb_tx_used + nb_used);
                txq->nb_tx_free = (uint16_t)(txq->nb_tx_free - nb_used);

                /* Set RS bit only on threshold packets' last descriptor */
                if (txq->nb_tx_used >= txq->tx_rs_thresh) {
                    cmd_type_len |= IXGBE_TXD_CMD_RS;
                }
                txd->read.cmd_type_len |= rte_cpu_to_le_32(cmd_type_len);
            }

            IXGBE_PCI_REG_WRITE_RELAXED(txq->tdt_reg_addr, tx_id);
            txq->tx_tail = tx_id;
```

![](../Image/DPDK/vhost-net-virtio-net-ovs.png)
The vhost-net/virtio-net architecture provides a working solution which has been widely deployed over the years.
1. On the one hand the solution is very convenient for a user developing an application running on a VM given that it uses standard Linux sockets to connect to the network (through the host).
2. On the other hand, the solution is not optimal and contains a number of performance overheads, e.g, context switching and interrupt processing overhead, which will be described later on.

![](../Image/DPDK/vhost-user-virtio-user-ovs.png)

# virtio-user

![](../Image/DPDK/virtio-vhost.png)

* [Redhat: Introducing virtio-networking: Combining virtualization and networking for modern IT](https://www.redhat.com/en/blog/introducing-virtio-networking-combining-virtualization-and-networking-modern-it)
* [Redhat: Introduction to virtio-networking and vhost-net](https://www.redhat.com/en/blog/introduction-virtio-networking-and-vhost-net)
* [Redhat: Deep dive into Virtio-networking and vhost-net](https://www.redhat.com/en/blog/deep-dive-virtio-networking-and-vhost-net)
* [Hands on vhost-net: Do. Or do not. There is no try](https://www.redhat.com/en/blog/hands-vhost-net-do-or-do-not-there-no-try)
* [Redhat: How vhost-user came into being: Virtio-networking and DPDK](https://www.redhat.com/en/blog/how-vhost-user-came-being-virtio-networking-and-dpdk)

```c++
static struct rte_pci_driver rte_virtio_pmd = {
    .driver = {
        .name = "net_virtio",
    },
    .id_table = pci_id_virtio_map,
    .drv_flags = 0,
    .probe = eth_virtio_pci_probe,
    .remove = eth_virtio_pci_remove,
};

RTE_INIT(rte_virtio_pmd_init)
{
    rte_eal_iopl_init();
    rte_pci_register(&rte_virtio_pmd);
}

/* VirtIO PCI vendor/device ID. */
#define VIRTIO_PCI_VENDORID     0x1AF4
#define VIRTIO_PCI_LEGACY_DEVICEID_NET 0x1000
#define VIRTIO_PCI_MODERN_DEVICEID_NET 0x1041

static const struct rte_pci_id pci_id_virtio_map[] = {
	{ RTE_PCI_DEVICE(VIRTIO_PCI_VENDORID, VIRTIO_PCI_LEGACY_DEVICEID_NET) },
	{ RTE_PCI_DEVICE(VIRTIO_PCI_VENDORID, VIRTIO_PCI_MODERN_DEVICEID_NET) },
	{ .vendor_id = 0, /* sentinel */ },
};

eth_virtio_pci_probe()
    eth_dev = rte_eth_dev_pci_allocate(pci_dev, sizeof(struct virtio_hw), eth_virtio_dev_init)

    eth_virtio_dev_init(eth_dev)
        eth_dev->dev_ops = &virtio_eth_dev_ops;
        eth_dev->data->mac_addrs = rte_zmalloc()
        hw->port_id = eth_dev->data->port_id;
        if (!hw->virtio_user_dev)
		    ret = vtpci_init()
                if (virtio_read_caps(dev, hw) == 0)
                    virtio_hw_internal[hw->port_id].vtpci_ops = &modern_ops;
                    hw->modern = 1;
        return 0;

        virtio_init_device()


    rte_eth_dev_probing_finish()
        _rte_eth_dev_callback_process(dev, RTE_ETH_EVENT_NEW, NULL);
        dev->state = RTE_ETH_DEV_ATTACHED;

```

```c++
static struct rte_bus rte_vdev_bus = {
    .scan           = vdev_scan,
    .probe          = vdev_probe,
    .find_device    = rte_vdev_find_device,
    .plug           = vdev_plug,
    .unplug         = vdev_unplug,
    .parse          = vdev_parse,
    .dev_iterate    = rte_vdev_dev_iterate,
};

rte_bus_register(&rte_vdev_bus);

rte_bus_probe()
    struct rte_bus *bus, *vbus = NULL;
    TAILQ_FOREACH(bus, &rte_bus_list, next)
        bus->probe();
            vdev_probe()
                TAILQ_FOREACH(dev, &vdev_device_list, next)
                    vdev_probe_all_drivers(dev)
                        driver->probe(dev)

static struct rte_vdev_driver virtio_user_driver = {
    .probe = virtio_user_pmd_probe,
    .remove = virtio_user_pmd_remove,
};

RTE_PMD_REGISTER_VDEV(net_virtio_user, virtio_user_driver);

virtio_user_pmd_probe()
    rte_kvargs_parse(rte_vdev_device_args(dev), valid_args);

    eth_dev = virtio_user_eth_dev_alloc(dev);

    struct virtio_hw *hw = eth_dev->data->dev_private;
    virtio_user_dev_init(hw->virtio_user_dev, path, queues, cq, queue_size, mac_addr, &ifname, server_mode, mrg_rx  buf, in_order, packed_vq);
        virtio_user_dev_setup()
            if (dev->is_server)
                dev->ops = &virtio_ops_user;
            else
                dev->ops = &virtio_ops_kernel;
                dev->vhostfds = malloc(dev->max_queue_pairs * sizeof(int));
                dev->tapfds = malloc(dev->max_queue_pairs * sizeof(int));
                for (q = 0; q < dev->max_queue_pairs; ++q) {
                    dev->vhostfds[q] = -1;
                    dev->tapfds[q] = -1;
                }

            dev->ops->setup(dev)
                vhost_kernel_setup()
                    for (i = 0; i < dev->max_queue_pairs; ++i) {
                        vhostfd = open(dev->path, O_RDWR);
                        dev->vhostfds[i] = vhostfd;
                    }

                vhost_user_setup()
                    fd = socket(AF_UNIX, SOCK_STREAM, 0);
                    if (dev->is_server) {
                        dev->listenfd = fd;
                        virtio_user_start_server(dev, &un);
                    } else {
                        connect(fd, (struct sockaddr *)&un, sizeof(un));
                        dev->vhostfd = fd;
                    }

        virtio_user_fill_intr_handle()

    eth_virtio_dev_init(eth_dev);
        virtio_init_device()
            vtpci_set_status(hw, VIRTIO_CONFIG_STATUS_ACK)
            virtio_alloc_queues(eth_dev);
            virtio_configure_intr()
            vtpci_reinit_complete(hw);

    rte_eth_dev_probing_finish(eth_dev);
```