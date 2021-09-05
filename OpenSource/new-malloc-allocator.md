# new
```c++
//libsupc++/new_op.cc
void* operator new (std::size_t sz) _GLIBCXX_THROW (std::bad_alloc) {
  void *p;

  /* malloc (0) is unpredictable; avoid it.  */
  if (__builtin_expect (sz == 0, false))
    sz = 1;

    while ((p = malloc (sz)) == 0) {
        new_handler handler = std::get_new_handler ();
        if (! handler)
            _GLIBCXX_THROW_OR_ABORT(bad_alloc());
        handler ();
    }

  return p;
}

```

```c++
// Default placement versions of operator new.
void* operator new(std::size_t, void* __p) { return __p; }

void* operator new[](std::size_t, void* __p) { return __p; }
```

```c++ 
void operator delete(void* ptr, std::size_t) noexcept {
  ::operator delete (ptr);
}

// Default placement versions of operator delete.
inline void operator delete  (void*, void*) noexcept { }
inline void operator delete[](void*, void*) noexcept { }
```

# malloc
```c++
static Void_t* sYSMALLOc(INTERNAL_SIZE_T nb, mstate av) {
    mchunkptr       old_top;        /* incoming value of av->top */
    INTERNAL_SIZE_T old_size;       /* its size */
    char*           old_end;        /* its end address */

    long            size;           /* arg to first MORECORE or mmap call */
    char*           brk;            /* return value from MORECORE */

    long            correction;     /* arg to 2nd MORECORE call */
    char*           snd_brk;        /* 2nd return val */

    INTERNAL_SIZE_T front_misalign; /* unusable bytes at front of new space */
    INTERNAL_SIZE_T end_misalign;   /* partial page left at end of new space */
    char*           aligned_brk;    /* aligned offset into brk */

    mchunkptr       p;              /* the allocated/returned chunk */
    mchunkptr       remainder;      /* remainder from allocation */
    unsigned long   remainder_size; /* its size */

    unsigned long   sum;            /* for updating stats */

    size_t          pagemask  = mp_.pagesize - 1;


#if HAVE_MMAP

    /* If have mmap, and the request size meets the mmap threshold, and
    the system supports mmap, and there are few enough currently
    allocated mmapped regions, try to directly map this request
    rather than expanding top. */

    if ((unsigned long)(nb) >= (unsigned long)(mp_.mmap_threshold) &&
        (mp_.n_mmaps < mp_.n_mmaps_max)) {

        char* mm;             /* return value from mmap call*/

        /* Round up size to nearest page.  For mmapped chunks, the overhead
        is one SIZE_SZ unit larger than for normal chunks, because there
        is no following chunk whose prev_size field could be used. */
        size = (nb + SIZE_SZ + MALLOC_ALIGN_MASK + pagemask) & ~pagemask;

        /* Don't try if size wraps around 0 */
        if ((unsigned long)(size) > (unsigned long)(nb)) {

            mm = (char*)(MMAP(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE));

            if (mm != MAP_FAILED) {

                /* The offset to the start of the mmapped region is stored
                in the prev_size field of the chunk. This allows us to adjust
                returned start address to meet alignment requirements here
                and in memalign(), and still be able to compute proper
                address argument for later munmap in free() and realloc(). */

                front_misalign = (INTERNAL_SIZE_T)chunk2mem(mm) & MALLOC_ALIGN_MASK;
                if (front_misalign > 0) {
                    correction = MALLOC_ALIGNMENT - front_misalign;
                    p = (mchunkptr)(mm + correction);
                    p->prev_size = correction;
                    set_head(p, (size - correction) |IS_MMAPPED);
                } else {
                    p = (mchunkptr)mm;
                    set_head(p, size|IS_MMAPPED);
                }

                /* update statistics */
                if (++mp_.n_mmaps > mp_.max_n_mmaps)
                    mp_.max_n_mmaps = mp_.n_mmaps;

                sum = mp_.mmapped_mem += size;
                if (sum > (unsigned long)(mp_.max_mmapped_mem)) {
                    mp_.max_mmapped_mem = sum;
                }
                
                #ifdef NO_THREADS
                    sum += av->system_mem;
                    if (sum > (unsigned long)(mp_.max_total_mem))
                    mp_.max_total_mem = sum;
                #endif

                check_chunk(av, p);

                return chunk2mem(p);
            }
        }
    }
#endif

    /* Record incoming configuration of top */

    old_top  = av->top;
    old_size = chunksize(old_top);
    old_end  = (char*)(chunk_at_offset(old_top, old_size));

    brk = snd_brk = (char*)(MORECORE_FAILURE);

    /* If not the first time through, we require old_size to be
        at least MINSIZE and to have prev_inuse set. */

    assert((old_top == initial_top(av) && old_size == 0) 
        || ((unsigned long) (old_size) >= MINSIZE && prev_inuse(old_top) && ((unsigned long)old_end & pagemask) == 0));

    /* Precondition: not enough current space to satisfy nb request */
    assert((unsigned long)(old_size) < (unsigned long)(nb + MINSIZE));

    /* Precondition: all fastbins are consolidated */
    assert(!have_fastchunks(av));


    if (av != &main_arena) {
        heap_info *old_heap, *heap;
        size_t old_heap_size;

        /* First try to extend the current heap. */
        old_heap = heap_for_ptr(old_top);
        old_heap_size = old_heap->size;

        if (grow_heap(old_heap, MINSIZE + nb - old_size) == 0) {
            av->system_mem += old_heap->size - old_heap_size;
            arena_mem += old_heap->size - old_heap_size;

            #if 0
                if(mmapped_mem + arena_mem + sbrked_mem > max_total_mem)
                    max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
            #endif
                set_head(old_top, (((char *)old_heap + old_heap->size) - (char *)old_top) | PREV_INUSE);
        } else if ((heap = new_heap(nb + (MINSIZE + sizeof(*heap)), mp_.top_pad))) {
            /* Use a newly allocated heap.  */
            heap->ar_ptr = av;
            heap->prev = old_heap;
            av->system_mem += heap->size;
            arena_mem += heap->size;
            
            #if 0
                if((unsigned long)(mmapped_mem + arena_mem + sbrked_mem) > max_total_mem)
                max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
            #endif
            
            /* Set up the new top.  */
            top(av) = chunk_at_offset(heap, sizeof(*heap));
            set_head(top(av), (heap->size - sizeof(*heap)) | PREV_INUSE);

            /* Setup fencepost and free the old top chunk. */
            /* The fencepost takes at least MINSIZE bytes, because it might
            become the top chunk again later.  Note that a footer is set
            up, too, although the chunk is marked in use. */
            old_size -= MINSIZE;
            set_head(chunk_at_offset(old_top, old_size + 2*SIZE_SZ), 0|PREV_INUSE);
            if (old_size >= MINSIZE) {
                set_head(chunk_at_offset(old_top, old_size), (2*SIZE_SZ)|PREV_INUSE);
                set_foot(chunk_at_offset(old_top, old_size), (2*SIZE_SZ));
                set_head(old_top, old_size|PREV_INUSE|NON_MAIN_ARENA);
                _int_free(av, chunk2mem(old_top));
            } else {
                set_head(old_top, (old_size + 2*SIZE_SZ)|PREV_INUSE);
                set_foot(old_top, (old_size + 2*SIZE_SZ));
            }
        }

    } else { /* av == main_arena */
        /* Request enough space for nb + pad + overhead */

        size = nb + mp_.top_pad + MINSIZE;

        /*
            If contiguous, we can subtract out existing space that we hope to
            combine with new space. We add it back later only if
            we don't actually get contiguous space.
        */

        if (contiguous(av))
            size -= old_size;

        /*
            Round to a multiple of page size.
            If MORECORE is not contiguous, this ensures that we only call it
            with whole-page arguments.  And if MORECORE is contiguous and
            this is not first time through, this preserves page-alignment of
            previous calls. Otherwise, we correct to page-align below.
        */

        size = (size + pagemask) & ~pagemask;

        /*
            Don't try to call MORECORE if argument is so big as to appear
            negative. Note that since mmap takes size_t arg, it may succeed
            below even if we cannot call MORECORE.
        */

        if (size > 0)
            brk = (char*)(MORECORE(size));

        if (brk != (char*)(MORECORE_FAILURE)) {
            /* Call the `morecore' hook if necessary.  */
            if (__after_morecore_hook)
            (*__after_morecore_hook) ();
        } else {
            /* If have mmap, try using it as a backup when MORECORE fails or
            cannot be used. This is worth doing on systems that have "holes" in
            address space, so sbrk cannot extend to give contiguous space, but
            space is available elsewhere.  Note that we ignore mmap max count
            and threshold limits, since the space will not be used as a
            segregated mmap region. */

            #if HAVE_MMAP
                /* Cannot merge with old top, so add its size back in */
                if (contiguous(av))
                size = (size + old_size + pagemask) & ~pagemask;

                /* If we are relying on mmap as backup, then use larger units */
                if ((unsigned long)(size) < (unsigned long)(MMAP_AS_MORECORE_SIZE))
                size = MMAP_AS_MORECORE_SIZE;

                /* Don't try if size wraps around 0 */
                if ((unsigned long)(size) > (unsigned long)(nb)) {

                    char *mbrk = (char*)(MMAP(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE));

                    if (mbrk != MAP_FAILED) {

                        /* We do not need, and cannot use, another sbrk call to find end */
                        brk = mbrk;
                        snd_brk = brk + size;

                        /* Record that we no longer have a contiguous sbrk region.
                        After the first time mmap is used as backup, we do not
                        ever rely on contiguous space since this could incorrectly
                        bridge regions. */
                        set_noncontiguous(av);
                    }
                }
            #endif
        }

        if (brk != (char*)(MORECORE_FAILURE)) {
            if (mp_.sbrk_base == 0)
            mp_.sbrk_base = brk;
            av->system_mem += size;

            /*
            If MORECORE extends previous space, we can likewise extend top size.
            */

            if (brk == old_end && snd_brk == (char*)(MORECORE_FAILURE)){
                set_head(old_top, (size + old_size) | PREV_INUSE);
            } else if (old_size && brk < old_end) {
                /* Oops!  Someone else killed our space..  Can't touch anything.  */
                assert(0);
            }
            /* Otherwise, make adjustments:

            * If the first time through or noncontiguous, we need to call sbrk
                just to find out where the end of memory lies.

            * We need to ensure that all returned chunks from malloc will meet
                MALLOC_ALIGNMENT

            * If there was an intervening foreign sbrk, we need to adjust sbrk
                request size to account for fact that we will not be able to
                combine new space with existing space in old_top.

            * Almost all systems internally allocate whole pages at a time, in
                which case we might as well use the whole last page of request.
                So we allocate enough more memory to hit a page boundary now,
                which in turn causes future contiguous calls to page-align. */

            else {
                /* Count foreign sbrk as system_mem.  */
                if (old_size) {
                    av->system_mem += brk - old_end;
                }
                front_misalign = 0;
                end_misalign = 0;
                correction = 0;
                aligned_brk = brk;

                /* handle contiguous cases */
                if (contiguous(av)) {

                    /* Guarantee alignment of first new chunk made from this space */

                    front_misalign = (INTERNAL_SIZE_T)chunk2mem(brk) & MALLOC_ALIGN_MASK;
                    if (front_misalign > 0) {
                        /* Skip over some bytes to arrive at an aligned position.
                            We don't need to specially mark these wasted front bytes.
                            They will never be accessed anyway because
                            prev_inuse of av->top (and any chunk created from its start)
                            is always true after initialization. */

                        correction = MALLOC_ALIGNMENT - front_misalign;
                        aligned_brk += correction;
                    }

                    /* If this isn't adjacent to existing space, then we will not
                    be able to merge with old_top space, so must add to 2nd request. */

                    correction += old_size;

                    /* Extend the end address to hit a page boundary */
                    end_misalign = (INTERNAL_SIZE_T)(brk + size + correction);
                    correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;

                    assert(correction >= 0);
                    snd_brk = (char*)(MORECORE(correction));

                    /*
                    If can't allocate correction, try to at least find out current
                    brk.  It might be enough to proceed without failing.

                    Note that if second sbrk did NOT fail, we assume that space
                    is contiguous with first sbrk. This is a safe assumption unless
                    program is multithreaded but doesn't use locks and a foreign sbrk
                    occurred between our first and second calls.
                    */

                    if (snd_brk == (char*)(MORECORE_FAILURE)) {
                        correction = 0;
                        snd_brk = (char*)(MORECORE(0));
                    } else {
                        /* Call the `morecore' hook if necessary.  */
                        if (__after_morecore_hook)
                            (*__after_morecore_hook) ();
                    }
                }
                /* handle non-contiguous cases */
                else {
                    /* MORECORE/mmap must correctly align */
                    assert(((unsigned long)chunk2mem(brk) & MALLOC_ALIGN_MASK) == 0);

                    /* Find out current end of memory */
                    if (snd_brk == (char*)(MORECORE_FAILURE)) {
                        snd_brk = (char*)(MORECORE(0));
                    }
                }

                /* Adjust top based on results of second sbrk */
                if (snd_brk != (char*)(MORECORE_FAILURE)) {
                    av->top = (mchunkptr)aligned_brk;
                    set_head(av->top, (snd_brk - aligned_brk + correction) | PREV_INUSE);
                    av->system_mem += correction;

                    /*
                    If not the first time through, we either have a
                    gap due to foreign sbrk or a non-contiguous region.  Insert a
                    double fencepost at old_top to prevent consolidation with space
                    we don't own. These fenceposts are artificial chunks that are
                    marked as inuse and are in any case too small to use.  We need
                    two to make sizes and alignments work out.
                    */

                    if (old_size != 0) {
                        /*  Shrink old_top to insert fenceposts, keeping size a
                            multiple of MALLOC_ALIGNMENT. We know there is at least
                            enough space in old_top to do this. */
                        old_size = (old_size - 4*SIZE_SZ) & ~MALLOC_ALIGN_MASK;
                        set_head(old_top, old_size | PREV_INUSE);

                        /* Note that the following assignments completely overwrite
                            old_top when old_size was previously MINSIZE.  This is
                            intentional. We need the fencepost, even if old_top otherwise gets
                            lost. */
                        chunk_at_offset(old_top, old_size)->size = (2*SIZE_SZ)|PREV_INUSE;

                        chunk_at_offset(old_top, old_size + 2*SIZE_SZ)->size = (2*SIZE_SZ)|PREV_INUSE;

                        /* If possible, release the rest. */
                        if (old_size >= MINSIZE) {
                            _int_free(av, chunk2mem(old_top));
                        }
                    }
                }
            }

            /* Update statistics */
            #ifdef NO_THREADS
                sum = av->system_mem + mp_.mmapped_mem;
                if (sum > (unsigned long)(mp_.max_total_mem))
                mp_.max_total_mem = sum;
            #endif

        }
    } /* if (av !=  &main_arena) */

    if ((unsigned long)av->system_mem > (unsigned long)(av->max_system_mem))
        av->max_system_mem = av->system_mem;
    check_malloc_state(av);

    /* finally, do the allocation */
    p = av->top;
    size = chunksize(p);

    /* check that one of the above allocation paths succeeded */
    if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE)) {
        remainder_size = size - nb;
        remainder = chunk_at_offset(p, nb);
        av->top = remainder;
        set_head(p, nb | PREV_INUSE | (av != &main_arena ? NON_MAIN_ARENA : 0));
        set_head(remainder, remainder_size | PREV_INUSE);
        check_malloced_chunk(av, p, nb);
        return chunk2mem(p);
    }

    /* catch all failure paths */
    MALLOC_FAILURE_ACTION;
    return 0;
}
```

# allocator
## allocator
```c++
template<typename _Tp>
class allocator : public __allocator_base<_Tp> {
public:
    typedef _Tp        value_type;
    typedef size_t     size_type;
    typedef ptrdiff_t   difference_type;

    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 3035. std::allocator's constructors should be constexpr
    constexpr allocator()  { }

    constexpr allocator(const allocator& __a) : __allocator_base<_Tp>(__a) { }

    allocator& operator=(const allocator&) = default;

    template<typename _Tp1>
    constexpr allocator(const allocator<_Tp1>&)  { }

    constexpr ~allocator()  { }

    constexpr _Tp* allocate(size_t __n) {
        #ifdef __cpp_lib_is_constant_evaluated
            if (std::is_constant_evaluated())
                return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
        #endif
            return __allocator_base<_Tp>::allocate(__n, 0);
    }

    constexpr void deallocate(_Tp* __p, size_t __n) {
        #ifdef __cpp_lib_is_constant_evaluated
            if (std::is_constant_evaluated()) {
                ::operator delete(__p);
                return;
            }
        #endif
            __allocator_base<_Tp>::deallocate(__p, __n);
    }

    friend constexpr bool operator==(const allocator&, const allocator&) { return true; }
};
```

## new_allocator
```c++
template<typename _Tp>
class new_allocator {
public:
    typedef _Tp             value_type;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t   difference_type;
    typedef _Tp*            pointer;
    typedef const _Tp*      const_pointer;
    typedef _Tp&            reference;
    typedef const _Tp&      const_reference;

    template<typename _Tp1>
    struct rebind { typedef new_allocator<_Tp1> other; };

    constexpr new_allocator() noexcept { }

    constexpr new_allocator(const new_allocator&) noexcept { }

    template<typename _Tp1>
    constexpr new_allocator(const new_allocator<_Tp1>&) noexcept { }

    ~new_allocator() noexcept { }

    pointer address(reference __x) const
    { return std::__addressof(__x); }

    const_pointer address(const_reference __x) const
    { return std::__addressof(__x); }

    // NB: __n is permitted to be 0.  The C++ standard says nothing
    // about what the return value is when __n == 0.
    _Tp* allocate(size_type __n, const void* = static_cast<const void*>(0)) {
        // _GLIBCXX_RESOLVE_LIB_DEFECTS
        // 3308. std::allocator<void>().allocate(n)
        static_assert(sizeof(_Tp) != 0, "cannot allocate incomplete types");

        if (__builtin_expect(__n > this->_M_max_size(), false)) {
            // _GLIBCXX_RESOLVE_LIB_DEFECTS
            // 3190. allocator::allocate sometimes returns too little storage
            if (__n > (std::size_t(-1) / sizeof(_Tp)))
            std::__throw_bad_array_new_length();
            std::__throw_bad_alloc();
        }

        if (alignof(_Tp) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
            std::align_val_t __al = std::align_val_t(alignof(_Tp));
            return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp), __al));
        }
    
        return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
    }

      // __p is not permitted to be a null pointer.
    void deallocate(_Tp* __p, size_type __n __attribute__ ((__unused__))) {
        #if __cpp_sized_deallocation
        # define _GLIBCXX_SIZED_DEALLOC(p, n) (p), (n) * sizeof(_Tp)
        #else
        # define _GLIBCXX_SIZED_DEALLOC(p, n) (p)
        #endif

        #if __cpp_aligned_new
        if (alignof(_Tp) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
            ::operator delete(_GLIBCXX_SIZED_DEALLOC(__p, __n),
                    std::align_val_t(alignof(_Tp)));
            return;
        }
        #endif
        
        ::operator delete(_GLIBCXX_SIZED_DEALLOC(__p, __n));
    }

    size_type max_size() const noexcept
    { return _M_max_size(); }

    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 402. wrong new expression in [some_] allocator::construct
    void construct(pointer __p, const _Tp& __val)
    { ::new((void *)__p) _Tp(__val); }

    void destroy(pointer __p) { __p->~_Tp(); }

    template<typename _Up>
    friend constexpr bool operator==(const new_allocator&, const new_allocator<_Up>&)
    { return true; }

private:
    constexpr size_type _M_max_size() const noexcept{
        #if __PTRDIFF_MAX__ < __SIZE_MAX__
        return std::size_t(__PTRDIFF_MAX__) / sizeof(_Tp);
        #else
        return std::size_t(-1) / sizeof(_Tp);
        #endif
    }
};
```

## malloc_allocator
```c++
template<typename _Tp>
class malloc_allocator {
public:
  typedef _Tp             value_type;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t   difference_type;

  typedef _Tp*            pointer;
  typedef const _Tp*      const_pointer;
  typedef _Tp&            reference;
  typedef const _Tp&      const_reference;

  template<typename _Tp1>
  struct rebind { typedef malloc_allocator<_Tp1> other; };

  constexpr malloc_allocator() { }

  constexpr malloc_allocator(const malloc_allocator&) { }

  template<typename _Tp1>
  constexpr malloc_allocator(const malloc_allocator<_Tp1>&) { }

    ~malloc_allocator() { }

    pointer address(reference __x) const
    { return std::__addressof(__x); }

    const_pointer address(const_reference __x) const
    { return std::__addressof(__x); }
    
    _Tp* allocate(size_type __n, const void* = 0) {
        static_assert(sizeof(_Tp) != 0, "cannot allocate incomplete types");
        
        if (__builtin_expect(__n > this->_M_max_size(), false)) {
            // _GLIBCXX_RESOLVE_LIB_DEFECTS
            // 3190. allocator::allocate sometimes returns too little storage
            if (__n > (std::size_t(-1) / sizeof(_Tp)))
              std::__throw_bad_array_new_length();
            std::__throw_bad_alloc();
          }

        _Tp* __ret = 0;
        
        if (alignof(_Tp) > alignof(std::max_align_t)) {
          __ret = static_cast<_Tp*>(::aligned_alloc(alignof(_Tp), __n * sizeof(_Tp)));
        }

        if (!__ret)
          __ret = static_cast<_Tp*>(std::malloc(__n * sizeof(_Tp)));
        if (!__ret)
          std::__throw_bad_alloc();
      
      if (reinterpret_cast<std::size_t>(__ret) % alignof(_Tp)) {
        // Memory returned by malloc is not suitably aligned for _Tp.
        deallocate(__ret, __n);
        std::__throw_bad_alloc();
      }

      return __ret;
  }

  // __p is not permitted to be a null pointer.
  void deallocate(_Tp* __p, size_type)
  { std::free(static_cast<void*>(__p)); }

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 402. wrong new expression in [some_] allocator::construct
  void construct(pointer __p, const _Tp& __val)
  { ::new((void *)__p) value_type(__val); }

  void destroy(pointer __p) { __p->~_Tp(); }

private:
    size_type _M_max_size() const {
        #if __PTRDIFF_MAX__ < __SIZE_MAX__
        return std::size_t(__PTRDIFF_MAX__) / sizeof(_Tp);
        #else
        return std::size_t(-1) / sizeof(_Tp);
        #endif
    }
};
```

## pool_allocator
### __pool_alloc_base
```c++
class __pool_alloc_base {
    typedef std::size_t size_t;
        
protected:
    enum { _S_align = 8 };
    enum { _S_max_bytes = 128 };
    enum { _S_free_list_size = (size_t)_S_max_bytes / (size_t)_S_align };
    
    union _Obj {
        union _Obj* _M_free_list_link;
        char        _M_client_data[1];    // The client sees this.
    };
        
    static _Obj* volatile         _S_free_list[_S_free_list_size];

    // Chunk allocation state.
    static char*                  _S_start_free;
    static char*                  _S_end_free;
    static size_t                 _S_heap_size;     
    
    size_t _M_round_up(size_t __bytes)
    { return ((__bytes + (size_t)_S_align - 1) & ~((size_t)_S_align - 1)); }
    
    const _Obj* volatile* _M_get_free_list(size_t __bytes) throw ();

    __mutex& _M_get_mutex() throw ();

    // Returns an object of size __n, and optionally adds to size __n
    // free list.
    void* _M_refill(size_t __n);
    
    // Allocates a chunk for nobjs of size size.  nobjs may be reduced
    // if it is inconvenient to allocate the requested number.
    char* _M_allocate_chunk(size_t __n, int& __nobjs);
};


__gnu_cxx::__mutex& get_palloc_mutex() {
    static __gnu_cxx::__mutex palloc_mutex;
    return palloc_mutex;
}

__pool_alloc_base::_Obj* volatile* __pool_alloc_base::_M_get_free_list(size_t __bytes) throw ()
{
    size_t __i = ((__bytes + (size_t)_S_align - 1) / (size_t)_S_align - 1);
    return _S_free_list + __i;
}

__mutex& __pool_alloc_base::_M_get_mutex() throw ()
{ return get_palloc_mutex(); }

// Allocate memory in large chunks in order to avoid fragmenting the
// heap too much.  Assume that __n is properly aligned.  We hold the
// allocation lock.
char* __pool_alloc_base::_M_allocate_chunk(size_t __n, int& __nobjs) {
    char* __result;
    size_t __total_bytes = __n * __nobjs;
    size_t __bytes_left = _S_end_free - _S_start_free;

    if (__bytes_left >= __total_bytes) {
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return __result ;
    } else if (__bytes_left >= __n) {
	    __nobjs = (int)(__bytes_left / __n);
        __total_bytes = __n * __nobjs;
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return __result;
    } else {
        // Try to make use of the left-over piece.
        if (__bytes_left > 0) {
            _Obj* volatile* __free_list = _M_get_free_list(__bytes_left);
            ((_Obj*)(void*)_S_start_free)->_M_free_list_link = *__free_list;
            *__free_list = (_Obj*)(void*)_S_start_free;
        }

        size_t __bytes_to_get = (2 * __total_bytes + _M_round_up(_S_heap_size >> 4));
        __try {
            _S_start_free = static_cast<char*>(::operator new(__bytes_to_get));
        } __catch(const std::bad_alloc&) {
            // Try to make do with what we have.  That can't hurt.  We
            // do not try smaller requests, since that tends to result
            // in disaster on multi-process machines.
            size_t __i = __n;
            for (; __i <= (size_t) _S_max_bytes; __i += (size_t) _S_align) {
                _Obj* volatile* __free_list = _M_get_free_list(__i);
                _Obj* __p = *__free_list;
                
                if (__p != 0) {
                    *__free_list = __p->_M_free_list_link;
                    _S_start_free = (char*)__p;
                    _S_end_free = _S_start_free + __i;
                    return _M_allocate_chunk(__n, __nobjs);
                    // Any leftover piece will eventually make it to the
                    // right free list.
                }
            }
            // What we have wasn't enough.  Rethrow.
            _S_start_free = _S_end_free = 0;   // We have no chunk.
            __throw_exception_again;
	    }
        _S_heap_size += __bytes_to_get;
        _S_end_free = _S_start_free + __bytes_to_get;
        return _M_allocate_chunk(__n, __nobjs);
    }
}

// Returns an object of size __n, and optionally adds to "size
// __n"'s free list.  We assume that __n is properly aligned.  We
// hold the allocation lock.
void* __pool_alloc_base::_M_refill(size_t __n) {
    int __nobjs = 20;
    char* __chunk = _M_allocate_chunk(__n, __nobjs);
    _Obj* volatile* __free_list;
    _Obj* __result;
    _Obj* __current_obj;
    _Obj* __next_obj;

    if (__nobjs == 1)
      return __chunk;
    __free_list = _M_get_free_list(__n);

    // Build free list in chunk.
    __result = (_Obj*)(void*)__chunk;
    *__free_list = __next_obj = (_Obj*)(void*)(__chunk + __n);
    
    for (int __i = 1; ; __i++) {
        __current_obj = __next_obj;
        __next_obj = (_Obj*)(void*)((char*)__next_obj + __n);
        if (__nobjs - 1 == __i) {
            __current_obj->_M_free_list_link = 0;
            break;
        } else {
            __current_obj->_M_free_list_link = __next_obj;
        }
    }
    
    return __result;
}

  __pool_alloc_base::_Obj* volatile __pool_alloc_base::_S_free_list[_S_free_list_size];

  char* __pool_alloc_base::_S_start_free = 0;

  char* __pool_alloc_base::_S_end_free = 0;

  size_t __pool_alloc_base::_S_heap_size = 0;

  // Instantiations.
  template class __pool_alloc<char>;
  template class __pool_alloc<wchar_t>;
```

### __pool_alloc
```c++
template<typename _Tp>
class __pool_alloc : private __pool_alloc_base {
private:
  static _Atomic_word      _S_force_new;

public:
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

  template<typename _Tp1>
  struct rebind { typedef __pool_alloc<_Tp1> other; };
  
  __pool_alloc() { }

  __pool_alloc(const __pool_alloc&) { }

  template<typename _Tp1>
    __pool_alloc(const __pool_alloc<_Tp1>&) { }

  ~__pool_alloc() { }

  pointer address(reference __x) const
  { return std::__addressof(__x); }

  const_pointer address(const_reference __x) const
  { return std::__addressof(__x); }

  size_type max_size() const 
  { return std::size_t(-1) / sizeof(_Tp); }

  template<typename _Up, typename... _Args>
  void construct(_Up* __p, _Args&&... __args)
  { ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }

  template<typename _Up>
  void destroy(_Up* __p) { __p->~_Up(); }

  pointer allocate(size_type __n, const void* = 0);

  void deallocate(pointer __p, size_type __n);      
};

template<typename _Tp>
_Atomic_word
__pool_alloc<_Tp>::_S_force_new;

template<typename _Tp>
_Tp*  __pool_alloc<_Tp>::allocate(size_type __n, const void*) {
    using std::size_t;
    pointer __ret = 0;

    if (__builtin_expect(__n != 0, true)) {
        if (__n > this->max_size())
            std::__throw_bad_alloc();

        const size_t __bytes = __n * sizeof(_Tp);

        if (alignof(_Tp) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
            std::align_val_t __al = std::align_val_t(alignof(_Tp));
            return static_cast<_Tp*>(::operator new(__bytes, __al));
        }

        // If there is a race through here, assume answer from getenv
        // will resolve in same direction.  Inspired by techniques
        // to efficiently support threading found in basic_string.h.
        if (_S_force_new == 0) {
            if (std::getenv("GLIBCXX_FORCE_NEW"))
                __atomic_add_dispatch(&_S_force_new, 1);
            else
                __atomic_add_dispatch(&_S_force_new, -1);
        }

        if (__bytes > size_t(_S_max_bytes) || _S_force_new > 0)
            __ret = static_cast<_Tp*>(::operator new(__bytes));
        else {
            _Obj* volatile* __free_list = _M_get_free_list(__bytes);
            
            __scoped_lock sentry(_M_get_mutex());
            _Obj* __result = *__free_list;
            
            if (__builtin_expect(__result == 0, 0))
                __ret = static_cast<_Tp*>(_M_refill(_M_round_up(__bytes)));
            else {
                *__free_list = __result->_M_free_list_link;
                __ret = reinterpret_cast<_Tp*>(__result);
            }
            
            if (__ret == 0)
                std::__throw_bad_alloc();
        }
    }

    return __ret;
}

template<typename _Tp>
void __pool_alloc<_Tp>::deallocate(pointer __p, size_type __n) {
    using std::size_t;
    if (__builtin_expect(__n != 0 && __p != 0, true)) {

        if (alignof(_Tp) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
            ::operator delete(__p, std::align_val_t(alignof(_Tp)));
            return;
        }

        const size_t __bytes = __n * sizeof(_Tp);
        if (__bytes > static_cast<size_t>(_S_max_bytes) || _S_force_new > 0) {
            ::operator delete(__p);            
        } else {
            _Obj* volatile* __free_list = _M_get_free_list(__bytes);
            _Obj* __q = reinterpret_cast<_Obj*>(__p);

            __scoped_lock sentry(_M_get_mutex());
            __q ->_M_free_list_link = *__free_list;
            *__free_list = __q;
        }
    }
}
```