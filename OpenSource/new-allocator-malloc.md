# new
```c++
// gcc master Sep 5 2021

// libstdc++-v3/libsupc++/new
void* operator new (std::size_t sz) _GLIBCXX_THROW (std::bad_alloc) {
  void *p;

  /* malloc (0) is unpredictable; avoid it.  */
  if (__builtin_expect(sz == 0, false))
    sz = 1;

    while ((p = malloc (sz)) == 0) {
        new_handler handler = std::get_new_handler ();
        if (! handler)
            _GLIBCXX_THROW_OR_ABORT(bad_alloc());
        handler();
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

# allocator
## allocator
```c++
// gcc master Sep 5 2021

// libstdc++-v3/include/bits/allocator.h
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
// libstdc++-v3/include/ext/new_allocator.h

# define __allocator_base  __gnu_cxx::new_allocator

template<typename _Tp>
using __allocator_base = __gnu_cxx::new_allocator<_Tp>;
    
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
// libstdc++-v3/include/ext/malloc_allocator.h

# define __allocator_base  __gnu_cxx::malloc_allocator

template<typename _Tp>
using __allocator_base = __gnu_cxx::malloc_allocator<_Tp>;

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
// libstdc++-v3/include/ext/pool_allocator.h

# define __allocator_base  __gnu_cxx::__pool_alloc_base

template<typename _Tp>
using __allocator_base = __gnu_cxx::__pool_alloc_base<_Tp>;

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

# malloc
## public_mALLOc
```c++
// glibc 2.3.1

#define public_mALLOc    malloc

static struct malloc_state main_arena;
static struct malloc_par mp_;

void* public_mALLOc(size_t bytes) {
    mstate ar_ptr;
    void *victim;

    __malloc_ptr_t (*hook) __MALLOC_P ((size_t, __const __malloc_ptr_t)) = __malloc_hook;
    if (hook != NULL)
        return (*hook)(bytes, RETURN_ADDRESS (0));

    arena_get(ar_ptr, bytes);
    if (!ar_ptr)
        return 0;
        
    victim = _int_malloc(ar_ptr, bytes);
    if (!victim) {
        /* Maybe the failure is due to running out of mmapped areas. */
        if (ar_ptr != &main_arena) {
            (void)mutex_unlock(&ar_ptr->mutex);
            (void)mutex_lock(&main_arena.mutex);
            victim = _int_malloc(&main_arena, bytes);
            (void)mutex_unlock(&main_arena.mutex);
        } else {
            #if USE_ARENAS
                /* ... or sbrk() has failed and there is still a chance to mmap() */
                ar_ptr = arena_get2(ar_ptr->next ? ar_ptr : 0, bytes);
                (void)mutex_unlock(&main_arena.mutex);
                if (ar_ptr) {
                    victim = _int_malloc(ar_ptr, bytes);
                    (void)mutex_unlock(&ar_ptr->mutex);
                }
            #endif
        }
    } else {
        (void)mutex_unlock(&ar_ptr->mutex);
    }
    assert(!victim || chunk_is_mmapped(mem2chunk(victim)) || ar_ptr == arena_for_chunk(mem2chunk(victim)));

    return victim;
}

/* Thread specific data */
static tsd_key_t arena_key;
static mutex_t list_lock;

typedef void *tsd_key_t;
#define tsd_key_create(key, destr) do {} while(0)
#define tsd_setspecific(key, data) ((key) = (data))
#define tsd_getspecific(key, vptr) (vptr = (key))

#define arena_get(ptr, size) do { \
    void *vptr = NULL; \
    ptr = (mstate)tsd_getspecific(arena_key, vptr); \
    if (ptr && !mutex_trylock(&ptr->mutex)) { \
        THREAD_STAT(++(ptr->stat_lock_direct)); \
    } else \
        ptr = arena_get2(ptr, (size)); \
} while(0)

static mstate arena_get2(mstate a_tsd, size_t size) {
    mstate a;
    int err;

    if (!a_tsd) {
        a = a_tsd = &main_arena;
    } else {
        a = a_tsd->next;
        if (!a) {
            /* This can only happen while initializing the new arena. */
            (void)mutex_lock(&main_arena.mutex);
            THREAD_STAT(++(main_arena.stat_lock_wait));
            return &main_arena;
        }
    }

    /* Check the global, circularly linked list for available arenas. */
repeat:
    do {
        if (!mutex_trylock(&a->mutex)) {
            THREAD_STAT(++(a->stat_lock_loop));
            tsd_setspecific(arena_key, (Void_t *)a);
            return a;
        }
        a = a->next;
    } while(a != a_tsd);

    /* If not even the list_lock can be obtained, try again.  This can
        happen during `atfork', or for example on systems where thread
        creation makes it temporarily impossible to obtain _any_
        locks. */
    if (mutex_trylock(&list_lock)) {
        a = a_tsd;
        goto repeat;
    }
    (void)mutex_unlock(&list_lock);

    /* Nothing immediately available, so generate a new arena.  */
    a = _int_new_arena(size);
    if (!a)
        return 0;

    tsd_setspecific(arena_key, (Void_t *)a);
    mutex_init(&a->mutex);
    err = mutex_lock(&a->mutex); /* remember result */

    /* Add the new arena to the global list.  */
    (void)mutex_lock(&list_lock);
    a->next = main_arena.next;
    main_arena.next = a;
    (void)mutex_unlock(&list_lock);

    if (err) /* locking failed; keep arena for further attempts later */
        return 0;

    THREAD_STAT(++(a->stat_lock_loop));
    return a;
}
```

## _int_malloc
```c++
void* _int_malloc(mstate av, size_t bytes) {
    size_t          nb;               /* normalized request size */
    unsigned int    idx;              /* associated bin index */
    mbinptr         bin;              /* associated bin */
    mfastbinptr*    fb;               /* associated fastbin */

    mchunkptr       victim;           /* inspected/selected chunk */
    size_t          size;             /* its size */
    int             victim_index;     /* its bin index */

    mchunkptr       remainder;        /* remainder from a split */
    unsigned long   remainder_size;   /* its size */

    unsigned int    block;            /* bit map traverser */
    unsigned int    bit;              /* bit map traverser */
    unsigned int    map;              /* current word of binmap */

    mchunkptr       fwd;              /* misc temp for linking */
    mchunkptr       bck;              /* misc temp for linking */

    /* Convert request size to internal form by adding SIZE_SZ bytes
    overhead plus possibly more to obtain necessary alignment and/or
    to obtain a size of at least MINSIZE, the smallest allocatable
    size. Also, checked_request2size traps (returning 0) request sizes
    that are so large that they wrap around zero when padded and
    aligned. */

    checked_request2size(bytes, nb);

    /* If the size qualifies as a fastbin, first check corresponding bin.
    This code is safe to execute even if av is not yet initialized, so we
    can try it without checking, which saves some time on this fast path. */
    if ((unsigned long)(nb) <= (unsigned long)(av->max_fast)) {
        fb = &(av->fastbins[(fastbin_index(nb))]);
        if ((victim = *fb) != 0) {
            *fb = victim->fd;
            check_remalloced_chunk(av, victim, nb);
            return chunk2mem(victim);
        }
    }

    /* If a small request, check regular bin.  Since these "smallbins"
    hold one size each, no searching within bins is necessary.
    (For a large request, we need to wait until unsorted chunks are
    processed to find best fit. But for small ones, fits are exact
    anyway, so we can check now, which is faster.) */
    if (in_smallbin_range(nb)) {
        idx = smallbin_index(nb);
        bin = bin_at(av,idx);

        if ((victim = last(bin)) != bin) {
            if (victim == 0) /* initialization check */ {
                malloc_consolidate(av);
            } else {
                bck = victim->bk;
                set_inuse_bit_at_offset(victim, nb);
                bin->bk = bck;
                bck->fd = bin;

                if (av != &main_arena)
                    victim->size |= NON_MAIN_ARENA;
                check_malloced_chunk(av, victim, nb);
                
                return chunk2mem(victim);
            }
        }
    }
    /* If this is a large request, consolidate fastbins before continuing.
        While it might look excessive to kill all fastbins before
        even seeing if there is space available, this avoids
        fragmentation problems normally associated with fastbins.
        Also, in practice, programs tend to have runs of either small or
        large requests, but less often mixtures, so consolidation is not
        invoked all that often in most programs. And the programs that
        it is called frequently in otherwise tend to fragment. */
    else {
        idx = largebin_index(nb);
        if (have_fastchunks(av))
            malloc_consolidate(av);
    }

    /* Process recently freed or remaindered chunks, taking one only if
    it is exact fit, or, if this a small request, the chunk is remainder from
    the most recent non-exact fit.  Place other traversed chunks in
    bins.  Note that this step is the only place in any routine where
    chunks are placed in bins.

    The outer loop here is needed because we might not realize until
    near the end of malloc that we should have consolidated, so must
    do so and retry. This happens at most once, and only when we would
    otherwise need to expand memory to service a "small" request. */

    for(;;) {
        while ((victim = unsorted_chunks(av)->bk) != unsorted_chunks(av)) {
            bck = victim->bk;
            size = chunksize(victim);

            /* If a small request, try to use last remainder if it is the
                only chunk in unsorted bin.  This helps promote locality for
                runs of consecutive small requests. This is the only
                exception to best-fit, and applies only when there is
                no exact fit for a small chunk. */

            if (in_smallbin_range(nb) &&
                bck == unsorted_chunks(av) &&
                victim == av->last_remainder &&
                (unsigned long)(size) > (unsigned long)(nb + MINSIZE)) {

                /* split and reattach remainder */
                remainder_size = size - nb;
                remainder = chunk_at_offset(victim, nb);
                unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
                av->last_remainder = remainder;
                remainder->bk = remainder->fd = unsorted_chunks(av);

                set_head(victim, nb | PREV_INUSE |
                    (av != &main_arena ? NON_MAIN_ARENA : 0));
                set_head(remainder, remainder_size | PREV_INUSE);
                set_foot(remainder, remainder_size);

                check_malloced_chunk(av, victim, nb);
                return chunk2mem(victim);
            }

            /* remove from unsorted list */
            unsorted_chunks(av)->bk = bck;
            bck->fd = unsorted_chunks(av);

            /* Take now instead of binning if exact fit */
            if (size == nb) {
                set_inuse_bit_at_offset(victim, size);
                if (av != &main_arena)
                    victim->size |= NON_MAIN_ARENA;
                check_malloced_chunk(av, victim, nb);
                
                return chunk2mem(victim);
            }

            /* place chunk in bin */
            if (in_smallbin_range(size)) {
                victim_index = smallbin_index(size);
                bck = bin_at(av, victim_index);
                fwd = bck->fd;
            } else {
                victim_index = largebin_index(size);
                bck = bin_at(av, victim_index);
                fwd = bck->fd;

                /* maintain large bins in sorted order */
                if (fwd != bck) {
                    /* Or with inuse bit to speed comparisons */
                    size |= PREV_INUSE;
                    /* if smaller than smallest, bypass loop below */
                    assert((bck->bk->size & NON_MAIN_ARENA) == 0);
                    if ((unsigned long)(size) <= (unsigned long)(bck->bk->size)) {
                        fwd = bck;
                        bck = bck->bk;
                    } else {
                        assert((fwd->size & NON_MAIN_ARENA) == 0);
                        while ((unsigned long)(size) < (unsigned long)(fwd->size)) {
                            fwd = fwd->fd;
                            assert((fwd->size & NON_MAIN_ARENA) == 0);
                        }
                        bck = fwd->bk;
                    }
                }
            }

            mark_bin(av, victim_index);
            victim->bk = bck;
            victim->fd = fwd;
            fwd->bk = victim;
            bck->fd = victim;
        }

        /* If a large request, scan through the chunks of current bin in
            sorted order to find smallest that fits.  This is the only step
            where an unbounded number of chunks might be scanned without doing
            anything useful with them. However the lists tend to be short. */

        if (!in_smallbin_range(nb)) {
            bin = bin_at(av, idx);

            /* skip scan if empty or largest chunk is too small */
            if ((victim = last(bin)) != bin && (unsigned long)(first(bin)->size) >= (unsigned long)(nb)) {

                while (((unsigned long)(size = chunksize(victim)) < (unsigned long)(nb)))
                    victim = victim->bk;

                remainder_size = size - nb;
                unlink(victim, bck, fwd);

                /* Exhaust */
                if (remainder_size < MINSIZE)  {
                    set_inuse_bit_at_offset(victim, size);
                    if (av != &main_arena)
                        victim->size |= NON_MAIN_ARENA;
                    check_malloced_chunk(av, victim, nb);
                    
                    return chunk2mem(victim);
                }
                /* Split */
                else {
                    remainder = chunk_at_offset(victim, nb);
                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
                    remainder->bk = remainder->fd = unsorted_chunks(av);
                    set_head(victim, nb | PREV_INUSE |
                    (av != &main_arena ? NON_MAIN_ARENA : 0));
                    set_head(remainder, remainder_size | PREV_INUSE);
                    set_foot(remainder, remainder_size);
                    check_malloced_chunk(av, victim, nb);
                    return chunk2mem(victim);
                }
            }
        }

        /* Search for a chunk by scanning bins, starting with next largest
            bin. This search is strictly by best-fit; i.e., the smallest
            (with ties going to approximately the least recently used) chunk
            that fits is selected.

            The bitmap avoids needing to check that most blocks are nonempty.
            The particular case of skipping all bins during warm-up phases
            when no chunks have been returned yet is faster than it might look. */

        ++idx;
        bin = bin_at(av,idx);
        block = idx2block(idx);
        map = av->binmap[block];
        bit = idx2bit(idx);

        for (;;) {
            /* Skip rest of block if there are no more set bits in this block.  */
            if (bit > map || bit == 0) {
                do {
                    if (++block >= BINMAPSIZE)  /* out of bins */
                        goto use_top;
                } while ((map = av->binmap[block]) == 0);

                bin = bin_at(av, (block << BINMAPSHIFT));
                bit = 1;
            }

            /* Advance to bin with set bit. There must be one. */
            while ((bit & map) == 0) {
                bin = next_bin(bin);
                bit <<= 1;
                assert(bit != 0);
            }

            /* Inspect the bin. It is likely to be non-empty */
            victim = last(bin);

            /*  If a false alarm (empty bin), clear the bit. */
            if (victim == bin) {
                av->binmap[block] = map &= ~bit; /* Write through */
                bin = next_bin(bin);
                bit <<= 1;
            } else {
                size = chunksize(victim);

                /*  We know the first chunk in this bin is big enough to use. */
                assert((unsigned long)(size) >= (unsigned long)(nb));

                remainder_size = size - nb;

                /* unlink */
                bck = victim->bk;
                bin->bk = bck;
                bck->fd = bin;

                /* Exhaust */
                if (remainder_size < MINSIZE) {
                    set_inuse_bit_at_offset(victim, size);
                if (av != &main_arena)
                victim->size |= NON_MAIN_ARENA;
                    check_malloced_chunk(av, victim, nb);
                    return chunk2mem(victim);
                } /* Split */
                else {
                    remainder = chunk_at_offset(victim, nb);

                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
                    remainder->bk = remainder->fd = unsorted_chunks(av);
                    /* advertise as last remainder */
                    if (in_smallbin_range(nb))
                        av->last_remainder = remainder;

                    set_head(victim, nb | PREV_INUSE | (av != &main_arena ? NON_MAIN_ARENA : 0));
                    set_head(remainder, remainder_size | PREV_INUSE);
                    set_foot(remainder, remainder_size);
                    check_malloced_chunk(av, victim, nb);
                    
                    return chunk2mem(victim);
                }
            }
        }

        use_top:
        /* If large enough, split off the chunk bordering the end of memory
            (held in av->top). Note that this is in accord with the best-fit
            search rule.  In effect, av->top is treated as larger (and thus
            less well fitting) than any other available chunk since it can
            be extended to be as large as necessary (up to system
            limitations).

            We require that av->top always exists (i.e., has size >=
            MINSIZE) after initialization, so if it would otherwise be
            exhuasted by current request, it is replenished. (The main
            reason for ensuring it exists is that we may need MINSIZE space
            to put in fenceposts in sysmalloc.) */

        victim = av->top;
        size = chunksize(victim);

        if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE)) {
            remainder_size = size - nb;
            remainder = chunk_at_offset(victim, nb);
            av->top = remainder;
            set_head(victim, nb | PREV_INUSE | (av != &main_arena ? NON_MAIN_ARENA : 0));
            set_head(remainder, remainder_size | PREV_INUSE);

            check_malloced_chunk(av, victim, nb);
            return chunk2mem(victim);
        } /* If there is space available in fastbins, consolidate and retry,
            to possibly avoid expanding memory. This can occur only if nb is
            in smallbin range so we didn't consolidate upon entry. */
        else if (have_fastchunks(av)) {
            assert(in_smallbin_range(nb));
            malloc_consolidate(av);
            idx = smallbin_index(nb); /* restore original bin index */
        } /* Otherwise, relay to handle system-dependent cases */
        else
            return sYSMALLOc(nb, av);
    }
}
```

## sYSMALLOc
```c++
static struct malloc_par mp_;

static void* sYSMALLOc(size_t nb, mstate av) {
    mchunkptr       old_top;        /* incoming value of av->top */
    size_t          old_size;       /* its size */
    char*           old_end;        /* its end address */

    long            size;           /* arg to first MORECORE or mmap call */
    char*           brk;            /* return value from MORECORE */

    long            correction;     /* arg to 2nd MORECORE call */
    char*           snd_brk;        /* 2nd return val */

    size_t          front_misalign; /* unusable bytes at front of new space */
    size_t          end_misalign;   /* partial page left at end of new space */
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
                front_misalign = (size_t)chunk2mem(mm) & MALLOC_ALIGN_MASK;
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
                if (mmapped_mem + arena_mem + sbrked_mem > max_total_mem)
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
                if ((unsigned long)(mmapped_mem + arena_mem + sbrked_mem) > max_total_mem)
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

        /* If contiguous, we can subtract out existing space that we hope to
            combine with new space. We add it back later only if
            we don't actually get contiguous space. */

        if (contiguous(av))
            size -= old_size;

        /* Round to a multiple of page size.
            If MORECORE is not contiguous, this ensures that we only call it
            with whole-page arguments.  And if MORECORE is contiguous and
            this is not first time through, this preserves page-alignment of
            previous calls. Otherwise, we correct to page-align below. */

        size = (size + pagemask) & ~pagemask;

        /* Don't try to call MORECORE if argument is so big as to appear
            negative. Note that since mmap takes size_t arg, it may succeed
            below even if we cannot call MORECORE. */

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

            /* If MORECORE extends previous space, we can likewise extend top size. */
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
                    front_misalign = (size_t)chunk2mem(brk) & MALLOC_ALIGN_MASK;
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
                    end_misalign = (size_t)(brk + size + correction);
                    correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;

                    assert(correction >= 0);
                    snd_brk = (char*)(MORECORE(correction));

                    /* If can't allocate correction, try to at least find out current
                    brk.  It might be enough to proceed without failing.

                    Note that if second sbrk did NOT fail, we assume that space
                    is contiguous with first sbrk. This is a safe assumption unless
                    program is multithreaded but doesn't use locks and a foreign sbrk
                    occurred between our first and second calls. */
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

                    /* If not the first time through, we either have a
                    gap due to foreign sbrk or a non-contiguous region.  Insert a
                    double fencepost at old_top to prevent consolidation with space
                    we don't own. These fenceposts are artificial chunks that are
                    marked as inuse and are in any case too small to use.  We need
                    two to make sizes and alignments work out. */

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

## struct
### malloc_state
```c++
struct malloc_state {
    /* Serialize access.  */
    mutex_t mutex;

    /* Statistics for locking.  Only used if THREAD_STATS is defined.  */
    long stat_lock_direct, stat_lock_loop, stat_lock_wait;
    long pad0_[1]; /* try to give the mutex its own cacheline */

    /* The maximum chunk size to be eligible for fastbin */
    size_t  max_fast;   /* low 2 bits used as flags */

    /* Fastbins */
    mfastbinptr      fastbins[NFASTBINS];

    /* Base of the topmost chunk -- not otherwise kept in a bin */
    mchunkptr        top;

    /* The remainder from the most recent split of a small request */
    mchunkptr        last_remainder;

    /* Normal bins packed as described above */
    mchunkptr        bins[NBINS * 2];

    /* Bitmap of bins */
    unsigned int     binmap[BINMAPSIZE];

    /* Linked list */
    struct malloc_state *next;

    /* Memory allocated from the system in this arena.  */
    size_t system_mem;
    size_t max_system_mem;
};
typedef struct malloc_state* mstate;

static struct malloc_state main_arena;
static struct malloc_par mp_;
```

### malloc_chunk
```c++
struct malloc_chunk {
    size_t                  prev_size;  /* Size of previous chunk (if free).  */
    size_t                  size;       /* Size in bytes, including overhead. */

    struct malloc_chunk*    fd;         /* double links -- used only if free. */
    struct malloc_chunk*    bk;
};
typedef struct malloc_chunk* mbinptr;
typedef struct malloc_chunk* mfastbinptr;

#define INTERNAL_SIZE_T        size_t
#define SIZE_SZ                (sizeof(INTERNAL_SIZE_T))
#define MALLOC_ALIGNMENT       (2 * SIZE_SZ)
#define MALLOC_ALIGN_MASK      (MALLOC_ALIGNMENT - 1)

#define NBINS             128
#define NSMALLBINS         64
#define SMALLBIN_WIDTH      8
#define MIN_LARGE_SIZE    512

#define chunk2mem(p)   ((Void_t*)((char*)(p) + 2*SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr)((char*)(mem) - 2*SIZE_SZ))
#define MIN_CHUNK_SIZE (sizeof(struct malloc_chunk))
#define MINSIZE (unsigned long)(((MIN_CHUNK_SIZE+MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK))
#define aligned_OK(m)  (((unsigned long)((m)) & (MALLOC_ALIGN_MASK)) == 0)
```

```c++
/* malloc_chunk details:

    (The following includes lightly edited explanations by Colin Plumb.)

    Chunks of memory are maintained using a `boundary tag' method as
    described in e.g., Knuth or Standish.  (See the paper by Paul
    Wilson ftp://ftp.cs.utexas.edu/pub/garbage/allocsrv.ps for a
    survey of such techniques.)  Sizes of free chunks are stored both
    in the front of each chunk and at the end.  This makes
    consolidating fragmented chunks into bigger chunks very fast.  The
    size fields also hold bits representing whether chunks are free or
    in use.

    An allocated chunk looks like this:

    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of previous chunk, if allocated            | |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of chunk, in bytes                         |P|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             User data starts here...                          .
            .                                                               .
            .             (malloc_usable_space() bytes)                     .
            .                                                               |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of chunk                                     |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


    Where "chunk" is the front of the chunk for the purpose of most of
    the malloc code, but "mem" is the pointer that is returned to the
    user.  "Nextchunk" is the beginning of the next contiguous chunk.

    Chunks always begin on even word boundries, so the mem portion
    (which is returned to the user) is also on an even word boundary, and
    thus at least double-word aligned.

    Free chunks are stored in circular doubly-linked lists, and look like this:

    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of previous chunk                            |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    `head:' |             Size of chunk, in bytes                         |P|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Forward pointer to next chunk in list             |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Back pointer to previous chunk in list            |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Unused space (may be 0 bytes long)                .
            .                                                               .
            .                                                               |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    `foot:' |             Size of chunk, in bytes                           |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    The P (PREV_INUSE) bit, stored in the unused low-order bit of the
    chunk size (which is always a multiple of two words), is an in-use
    bit for the *previous* chunk.  If that bit is *clear*, then the
    word before the current chunk size contains the previous chunk
    size, and can be used to find the front of the previous chunk.
    The very first chunk allocated always has this bit set,
    preventing access to non-existent (or non-owned) memory. If
    prev_inuse is set for any given chunk, then you CANNOT determine
    the size of the previous chunk, and might even get a memory
    addressing fault when trying to do so.

    Note that the `foot' of the current chunk is actually represented
    as the prev_size of the NEXT chunk. This makes it easier to
    deal with alignments etc but can be very confusing when trying
    to extend or adapt this code.

    The two exceptions to all this are
    1. The special chunk `top' doesn't bother using the
        trailing size field since there is no next contiguous chunk
        that would have to index off it. After initialization, `top'
        is forced to always exist.  If it would become less than
        MINSIZE bytes long, it is replenished.

    2. Chunks allocated via mmap, which have the second-lowest-order
        bit (IS_MMAPPED) set in their size fields.  Because they are
        allocated one-by-one, each must contain its own trailing size field. 
*/
```

```c++
/*
  Bins
    An array of bin headers for free chunks. Each bin is doubly
    linked.  The bins are approximately proportionally (log) spaced.
    There are a lot of these bins (128). This may look excessive, but
    works very well in practice.  Most bins hold sizes that are
    unusual as malloc request sizes, but are more usual for fragments
    and consolidated sets of chunks, which is what these bins hold, so
    they can be found quickly.  All procedures maintain the invariant
    that no consolidated chunk physically borders another one, so each
    chunk in a list is known to be preceeded and followed by either
    inuse chunks or the ends of memory.

    Chunks in bins are kept in size order, with ties going to the
    approximately least recently used chunk. Ordering isn't needed
    for the small bins, which all contain the same-sized chunks, but
    facilitates best-fit allocation for larger chunks. These lists
    are just sequential. Keeping them in order almost never requires
    enough traversal to warrant using fancier ordered data
    structures.

    Chunks of the same size are linked with the most
    recently freed at the front, and allocations are taken from the
    back.  This results in LRU (FIFO) allocation order, which tends
    to give each chunk an equal opportunity to be consolidated with
    adjacent freed chunks, resulting in larger free chunks and less
    fragmentation.

    To simplify use in double-linked lists, each bin header acts
    as a malloc_chunk. This avoids special-casing for headers.
    But to conserve space and improve locality, we allocate
    only the fd/bk pointers of bins, and then use repositioning tricks
    to treat these as the fields of a malloc_chunk*.
*/
typedef struct malloc_chunk* mbinptr;

/* addressing -- note that bin_at(0) does not exist */
#define bin_at(m, i) ((mbinptr)((char*)&((m)->bins[(i)<<1]) - (SIZE_SZ<<1)))

/* analog of ++bin */
#define next_bin(b)  ((mbinptr)((char*)(b) + (sizeof(mchunkptr)<<1)))

/* Reminders about list directionality within bins */
#define first(b)     ((b)->fd)
#define last(b)      ((b)->bk)
```

```c++
/* Fastbins
    An array of lists holding recently freed small chunks.  Fastbins
    are not doubly linked.  It is faster to single-link them, and
    since chunks are never removed from the middles of these lists,
    double linking is not necessary. Also, unlike regular bins, they
    are not even processed in FIFO order (they use faster LIFO) since
    ordering doesn't much matter in the transient contexts in which
    fastbins are normally used.

    Chunks in fastbins keep their inuse bit set, so they cannot
    be consolidated with other free chunks. malloc_consolidate
    releases all chunks in fastbins and consolidates them with
    other free chunks.
*/
typedef struct malloc_chunk* mfastbinptr;
```

```c++
/* Binmap
    To help compensate for the large number of bins, a one-level index
    structure is used for bin-by-bin searching.  `binmap' is a
    bitvector recording whether bins are definitely empty so they can
    be skipped over during during traversals.  The bits are NOT always
    cleared as soon as bins are empty, but instead only
    when they are noticed to be empty during traversal in malloc.
*/

/* Conservatively use 32 bits per map word, even if on 64bit system */
#define BINMAPSHIFT      5
#define BITSPERMAP       (1U << BINMAPSHIFT)
#define BINMAPSIZE       (NBINS / BITSPERMAP)

#define idx2block(i)     ((i) >> BINMAPSHIFT)
#define idx2bit(i)       ((1U << ((i) & ((1U << BINMAPSHIFT)-1))))

#define mark_bin(m,i)    ((m)->binmap[idx2block(i)] |=  idx2bit(i))
#define unmark_bin(m,i)  ((m)->binmap[idx2block(i)] &= ~(idx2bit(i)))
#define get_binmap(m,i)  ((m)->binmap[idx2block(i)] &   idx2bit(i))
```

### malloc_par
```c++
/* There is only one instance of the malloc parameters.  */
struct malloc_par {
    /* Tunable parameters */
    unsigned long       trim_threshold;
    size_t              top_pad;
    size_t              mmap_threshold;

    /* Memory map support */
    int                 n_mmaps;
    int                 n_mmaps_max;
    int                 max_n_mmaps;

    /* Cache malloc_getpagesize */
    unsigned int        pagesize;

    /* Statistics */
    size_t              mmapped_mem;
    /*size_t  sbrked_mem;*/
    /*size_t  max_sbrked_mem;*/
    size_t              max_mmapped_mem;
    size_t              max_total_mem; /* only kept for NO_THREADS */

    /* First address handed out by MORECORE/sbrk.  */
    char*               sbrk_base;
};
```