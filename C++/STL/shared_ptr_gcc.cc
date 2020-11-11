/********************************** shared_ptr **********************************/

template<typename _Tp>
class shared_ptr : public __shared_ptr<_Tp>
{
public:
    template<
        typename _Yp,
        typename _Deleter,
        typename _Alloc,
        typename = _Constructible<_Yp*, _Deleter, _Alloc>>
    shared_ptr(_Yp* __p, _Deleter __d, _Alloc __a)
    : __shared_ptr<_Tp>(__p, std::move(__d), std::move(__a)) { }

    template<typename _Alloc, typename... _Args>
    shared_ptr(_Sp_alloc_shared_tag<_Alloc> __tag, _Args&&... __args)
    : __shared_ptr<_Tp>(__tag, std::forward<_Args>(__args)...)
    { }
};


template<typename _Tp, _Lock_policy _Lp>
class __shared_ptr : public __shared_ptr_access<_Tp, _Lp>
{
public:
    using element_type = typename remove_extent<_Tp>::type;

    template<typename _Alloc, typename... _Args>
    __shared_ptr(_Sp_alloc_shared_tag<_Alloc> __tag, _Args&&... __args)
    : _M_ptr(), _M_refcount(_M_ptr, __tag, std::forward<_Args>(__args)...)
    {
        _M_enable_shared_from_this_with(_M_ptr);
    }

    // waek_ptr::lock
    __shared_ptr(const __weak_ptr<_Tp, _Lp>& __r, std::nothrow_t) noexcept
    : _M_refcount(__r._M_refcount, std::nothrow)
    {
        _M_ptr = _M_refcount._M_get_use_count() ? __r._M_ptr : nullptr;
    }

    explicit operator bool() const noexcept
    { return _M_ptr != nullptr; }

    template<typename _Yp, typename _Yp2 = typename remove_cv<_Yp>::type>
	typename enable_if<__has_esft_base<_Yp2>::value>::type
	_M_enable_shared_from_this_with(_Yp* __p) noexcept {
	  if (auto __base = __enable_shared_from_this_base(_M_refcount, __p))
	    __base->_M_weak_assign(const_cast<_Yp2*>(__p), _M_refcount);
	}

private:
    element_type*	   _M_ptr;           // Contained pointer.
    __shared_count<_Lp>  _M_refcount;    // Reference counter.
};

template<_Lock_policy _Lp>
class __shared_count
{
public:
     template<typename _Tp, typename _Alloc, typename... _Args>
	__shared_count(_Tp*& __p, _Sp_alloc_shared_tag<_Alloc> __a, _Args&&... __args) {
        typedef _Sp_counted_ptr_inplace<_Tp, _Alloc, _Lp> _Sp_cp_type;

        typename _Sp_cp_type::__allocator_type __a2(__a._M_a);
        auto __guard = std::__allocate_guarded(__a2);
        _Sp_cp_type* __mem = __guard.get();
        auto __pi = ::new (__mem) _Sp_cp_type(__a._M_a, std::forward<_Args>(__args)...);
        __guard = nullptr;
        _M_pi = __pi;
        __p = __pi->_M_ptr();
	}

    ~__shared_count() noexcept {
	    if (_M_pi != nullptr)
	        _M_pi->_M_release();
    }

private:
    _Sp_counted_base<_Lp>*  _M_pi;
};

template<typename _Tp, typename _Alloc, _Lock_policy _Lp>
class _Sp_counted_ptr_inplace final : public _Sp_counted_base<_Lp>
{
public:
      class _Impl : _Sp_ebo_helper<0, _Alloc>
      {
        public:
            typedef  _Sp_ebo_helper<0, _Alloc>	_A_base;
            explicit _Impl(_Alloc __a) noexcept : _A_base(__a) { }
            _Alloc& _M_alloc() noexcept { return _A_base::_S_get(*this); }
            __gnu_cxx::__aligned_buffer<_Tp> _M_storage;
    };

    template<typename... _Args>
	_Sp_counted_ptr_inplace(_Alloc __a, _Args&&... __args)
	: _M_impl(__a)
	{
	  /* _GLIBCXX_RESOLVE_LIB_DEFECTS
	   * 2070.  allocate_shared should use allocator_traits<A>::construct
       *
       * ::new (static_cast<void*>(p)) T(std::forward<Args>(args)...) (until C++20)
       * std::construct_at(p, std::forward<Args>(args)...) (since C++20) */
	  allocator_traits<_Alloc>::construct(__a, _M_ptr(), std::forward<_Args>(__args)...);
	}

    ~_Sp_counted_ptr_inplace() noexcept { }

    virtual void _M_dispose() noexcept {
	    allocator_traits<_Alloc>::destroy(_M_impl._M_alloc(), _M_ptr());
    }

      // Override because the allocator needs to know the dynamic type
    virtual void _M_destroy() noexcept {
        __allocator_type __a(_M_impl._M_alloc());
        __allocated_ptr<__allocator_type> __guard_ptr{ __a, this };
        this->~_Sp_counted_ptr_inplace();
    }

private:
    _Tp* _M_ptr() noexcept { return _M_impl._M_storage._M_ptr(); }
    _Impl _M_impl;
};



template<_Lock_policy _Lp = __default_lock_policy>
class _Sp_counted_base : public _Mutex_base<_Lp>
{
public:
    _Sp_counted_base() noexcept : _M_use_count(1), _M_weak_count(1) { }

    /* Called when _M_use_count drops to zero, to release the resources managed by *this. */
    virtual void _M_dispose() noexcept = 0;

    // Called when _M_weak_count drops to zero.
    virtual void _M_destroy() noexcept { delete this; }

    void _M_release() noexcept {
        // Be race-detector-friendly.  For more info see bits/c++config.
        _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&_M_use_count);
	    if (__gnu_cxx::__exchange_and_add_dispatch(&_M_use_count, -1) == 1) {
            _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&_M_use_count);
	        _M_dispose();
            // There must be a memory barrier between dispose() and destroy()
            // to ensure that the effects of dispose() are observed in the
            // thread that runs destroy().
            // See http://gcc.gnu.org/ml/libstdc++/2005-11/msg00136.html
            if (_Mutex_base<_Lp>::_S_need_barriers) {
                __atomic_thread_fence (__ATOMIC_ACQ_REL);
            }

            // Be race-detector-friendly.  For more info see bits/c++config.
            _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&_M_weak_count);
            if (__gnu_cxx::__exchange_and_add_dispatch(&_M_weak_count, -1) == 1) {
                _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&_M_weak_count);
                _M_destroy();
            }
        }
    }

    void  _M_weak_add_ref() noexcept {
        __gnu_cxx::__atomic_add_dispatch(&_M_weak_count, 1);
    }

    void _M_weak_release() noexcept {
        // Be race-detector-friendly. For more info see bits/c++config.
        _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&_M_weak_count);
        if (__gnu_cxx::__exchange_and_add_dispatch(&_M_weak_count, -1) == 1) {
            _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&_M_weak_count);
            if (_Mutex_base<_Lp>::_S_need_barriers) {
                // See _M_release(),
                // destroy() must observe results of dispose()
                __atomic_thread_fence (__ATOMIC_ACQ_REL);
            }
            _M_destroy();
        }
      }


private:
    _Atomic_word  _M_use_count;     // #shared
    _Atomic_word  _M_weak_count;    // #weak + (#shared != 0)
};

template<typename _Tp, _Lock_policy _Lp,
    bool = is_array<_Tp>::value, bool = is_void<_Tp>::value>
class __shared_ptr_access
{
public:
    using element_type = _Tp;

    element_type& operator*() const noexcept {
        __glibcxx_assert(_M_get() != nullptr);
        return *_M_get();
    }

    element_type* operator->() const noexcept {
        _GLIBCXX_DEBUG_PEDASSERT(_M_get() != nullptr);
        return _M_get();
    }

private:
    element_type* _M_get() const noexcept {
        return static_cast<const __shared_ptr<_Tp, _Lp>*>(this)->get();
    }
};


/********************************** weak_ptr **********************************/

template<typename _Tp>
class weak_ptr : public __weak_ptr<_Tp>
{
public:
    template<typename _Yp, typename = _Constructible<const shared_ptr<_Yp>&>>
    weak_ptr(const shared_ptr<_Yp>& __r) noexcept
	: __weak_ptr<_Tp>(__r) { }

    __shared_ptr<_Tp, _Lp> lock() const noexcept {
        return __shared_ptr<element_type, _Lp>(*this, std::nothrow);
    }
};

template<typename _Tp, _Lock_policy _Lp>
class __weak_ptr
{
public:
    using element_type = typename remove_extent<_Tp>::type;

    constexpr __weak_ptr() noexcept
    : _M_ptr(nullptr), _M_refcount() { }

    template<typename _Yp, typename = _Compatible<_Yp>>
	__weak_ptr(const __shared_ptr<_Yp, _Lp>& __r) noexcept
	: _M_ptr(__r._M_ptr), _M_refcount(__r._M_refcount) { }

    long use_count() const noexcept {
        return _M_refcount._M_get_use_count();
    }

    bool expired() const noexcept {
        return _M_refcount._M_get_use_count() == 0;
    }

private:
    element_type*	 _M_ptr;         // Contained pointer.
    __weak_count<_Lp>  _M_refcount;    // Reference counter.
};

template<_Lock_policy _Lp>
class __weak_count
{
public:
    constexpr __weak_count() noexcept : _M_pi(nullptr) { }

    __weak_count(const __shared_count<_Lp>& __r) noexcept
    : _M_pi(__r._M_pi) {
        if (_M_pi != nullptr)
            _M_pi->_M_weak_add_ref();
    }

    ~__weak_count() noexcept {
        if (_M_pi != nullptr)
            _M_pi->_M_weak_release();
    }

    __weak_count& operator=(const __shared_count<_Lp>& __r) noexcept
    {
        _Sp_counted_base<_Lp>* __tmp = __r._M_pi;
        if (__tmp != nullptr)
            __tmp->_M_weak_add_ref();
        if (_M_pi != nullptr)
            _M_pi->_M_weak_release();
        _M_pi = __tmp;
        return *this;
    }

private:
    _Sp_counted_base<_Lp>*  _M_pi;
};


template<typename _Tp, typename... _Args>
inline shared_ptr<_Tp>
make_shared(_Args&&... __args)
{
    typedef typename std::remove_cv<_Tp>::type _Tp_nc;
    return std::allocate_shared<_Tp>(std::allocator<_Tp_nc>(),
                    std::forward<_Args>(__args)...);
}

template<typename _Tp, typename _Alloc, typename... _Args>
inline shared_ptr<_Tp>
allocate_shared(const _Alloc& __a, _Args&&... __args)
{
    return shared_ptr<_Tp>(_Sp_alloc_shared_tag<_Alloc>{__a},
                std::forward<_Args>(__args)...);
}

/************************** enable_shared_from_this ***************************/

template<typename _Tp>
class enable_shared_from_this
{
public:
    shared_ptr<_Tp> shared_from_this() {
        return shared_ptr<_Tp>(this->_M_weak_this);
    }

    weak_ptr<const _Tp> weak_from_this() const noexcept {
        return this->_M_weak_this;
    }

protected:
    constexpr enable_shared_from_this() noexcept { }

    enable_shared_from_this(const enable_shared_from_this&) noexcept { }

    enable_shared_from_this&
    operator=(const enable_shared_from_this&) noexcept
    { return *this; }

    ~enable_shared_from_this() { }

private:
    mutable weak_ptr<_Tp>  _M_weak_this;
};