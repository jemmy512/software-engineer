# UML
![CppRest.png](../../.Image/BoostAsio.png)

# Call Stack

## boost::asio::async_read

## boost::asio::async_read_until

## boost::asio::async_write
```C++
template <typename AsyncWriteStream, typename ConstBufferSequence, typename CompletionCondition, typename WriteHandler>
inline BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
  const ConstBufferSequence& buffers,
  CompletionCondition completion_condition,
  (WriteHandler) handler,
  typename enable_if<is_const_buffer_sequence<ConstBufferSequence>::value>::type*)
{

}

template <typename AsyncWriteStream, typename ConstBufferSequence, typename WriteHandler>
inline BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler,void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
  const ConstBufferSequence& buffers,
  (WriteHandler) handler,
  typename enable_if<is_const_buffer_sequence<ConstBufferSequence>::value>::type*)
{

}

template <typename AsyncWriteStream, typename DynamicBuffer, typename WriteHandler>
inline BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler, void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
  (DynamicBuffer) buffers,
  (WriteHandler) handler,
  typename enable_if<is_dynamic_buffer<typename decay<DynamicBuffer>::type>::value>::type*)
{

}

template <typename AsyncWriteStream, typename DynamicBuffer, typename CompletionCondition, typename WriteHandler>
inline BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler, void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
  (DynamicBuffer) buffers,
  CompletionCondition completion_condition,
  (WriteHandler) handler,
  typename enable_if<is_dynamic_buffer<typename decay<DynamicBuffer>::type>::value>::type*)
{

}

template <typename AsyncWriteStream, typename Allocator, typename WriteHandler>
inline BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler, void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, ::asio::basic_streambuf<Allocator>& b, (WriteHandler) handler)
{
  return async_write(s, basic_streambuf_ref<Allocator>(b), (WriteHandler)(handler));
}

template <typename AsyncWriteStream, typename Allocator, typename CompletionCondition, typename WriteHandler>
inline BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler, void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    (WriteHandler) handler)
{
  return async_write(s, basic_streambuf_ref<Allocator>(b), completion_condition, (WriteHandler)(handler));
}
```

tricky switch
```C++
struct write_op {
  void operator()(const boost::system::error_code& ec, std::size_t bytes_transferred, int start = 0) {
    std::size_t max_size;
    switch (start_ = start)
    {
    case 1:
      max_size = this->check_for_completion(ec, buffers_.total_consumed());
      do
      {
        stream_.async_write_some(buffers_.prepare(max_size), BOOST_ASIO_MOVE_CAST(write_op)(*this));
        return;

        default:
          buffers_.consume(bytes_transferred);
          if ((!ec && bytes_transferred == 0) || buffers_.empty())
            break;
          max_size = this->check_for_completion(ec, buffers_.total_consumed());
      } while (max_size > 0);

      handler_(ec, buffers_.total_consumed());
    }
  }
};
```

## io_context::post
```C++
template <typename LegacyCompletionHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(LegacyCompletionHandler, void ())
io_context::post((LegacyCompletionHandler) handler)
{
  async_completion<LegacyCompletionHandler, void ()> init(handler);

  bool is_continuation = boost_asio_handler_cont_helpers::is_continuation(init.completion_handler);

  // Allocate and construct an operation to wrap the handler.
  typedef detail::completion_handler<typename handler_type<LegacyCompletionHandler, void ()>::type> op;
  typename op::ptr p = { detail::addressof(init.completion_handler), op::ptr::allocate(init.completion_handler), 0 };
  p.p = new (p.v) op(init.completion_handler);

  impl_.post_immediate_completion(p.p, is_continuation);
  p.v = p.p = 0;

  return init.result.get();
}

#define BOOST_ASIO_DEFINE_HANDLER_PTR(op)
struct ptr
{
    Handler* h;
    op* v;
    op* p;

    ~ptr() {
        reset();
    }

    static op* allocate(Handler& handler) {
        typedef typename ::boost::asio::associated_allocator<Handler>::type associated_allocator_type;
        typedef typename ::boost::asio::detail::get_hook_allocator<Handler, associated_allocator_type>::type
            hook_allocator_type;
        BOOST_ASIO_REBIND_ALLOC(hook_allocator_type, op)
            a(::boost::asio::detail::get_hook_allocator<Handler, associated_allocator_type>
                ::get(handler, ::boost::asio::get_associated_allocator(handler)));
        return a.allocate(1);
    }

    void reset() {
        if (p) {
            p->~op();
            p = 0;
        }

        if (v) {
            typedef typename ::boost::asio::associated_allocator<Handler>::type associated_allocator_type;
            typedef typename ::boost::asio::detail::get_hook_allocator<Handler, associated_allocator_type>::type
                hook_allocator_type;
            BOOST_ASIO_REBIND_ALLOC(hook_allocator_type, op)
                a(::boost::asio::detail::get_hook_allocator<Handler, associated_allocator_type>
                    ::get(*h, ::boost::asio::get_associated_allocator(*h)));
            a.deallocate(static_cast<op*>(v), 1);
            v = 0;
        }
    }
}

void scheduler::post_immediate_completion(
    scheduler::operation* op, bool is_continuation)
{
  work_started();
  mutex::scoped_lock lock(mutex_);
  op_queue_.push(op);
  wake_one_thread_and_unlock(lock);
}

```