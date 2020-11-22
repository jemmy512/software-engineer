# CppRest
The [C++ REST SDK](https://github.com/microsoft/cpprestsdk) is a Microsoft project for cloud-based client-server communication in native code using a modern asynchronous C++ API design. This project aims to help C++ developers connect to and interact with services.

Features:
* [Programming with Tasks](https://github.com/microsoft/cpprestsdk/wiki/Programming-with-Tasks)
* [JSON](https://github.com/microsoft/cpprestsdk/wiki/JSON)
* Asynchronous Stream
* URIs
* [HTTP Client](https://github.com/microsoft/cpprestsdk/wiki/HTTP-Client)
* HTTP Listener
* [Websocket Client](https://github.com/microsoft/cpprestsdk/wiki/Web-Socket)
* OAuth Client

![CppRest.png](../../.Image/CppRest.png)

## Send Request
```C++
overrideable::g_casablancaHttpRequestFunc // CB-> handel http response

pplx::task<http_response> http_client::request
    http_pipeline::propagate
        oauth2_handler::propagate
            oauth2_config::_authenticate_request
                req.headers().add(header_names::authorization, "Bearer " + token().access_token());

            winhttp_client::propagate   // window platform
                _http_client_communicator::async_send_request
                    _http_client_communicator::open_and_send_request_async
                        _http_client_communicator::open_and_send_request
                            winhttp_client::send_request
                                winhttp_client::_start_request_send

            asio_client::propagate // create asio_context, obtain a reused connection from pool
                auto result_task = pplx::create_task(context->m_request_completion);
                    _http_client_communicator::async_send_request
                        _http_client_communicator::push_request             // 1. gurantee order
                            m_requests_queue.push(request);
                        _http_client_communicator::open_and_send_request    // 2. don't gurantee order
                            _http_client_communicator::open_and_send_request
                                asio_client::send_request
                                    asio_context::start_request
                                        ssl_proxy_tunnel::start_proxy_connect   // if it's ssl and not connected
                                            ssl_proxy_tunnel::write_connect
                                            basic_resolver.hpp::async_resolve
                                                ssl_proxy_tunnel::handle_resolve
                                                    ssl_proxy_tunnel::connect   // handler: ssl_proxy_tunnel::handle_tcp_connect
                                                        asio_connection_fast_ipv4_fallback::connect
                                                            asio_connection_fast_ipv4_fallback::connect_unlock  // if connection is not reused
                                                                asio_connection::async_connect
                                                                    reactive_socket_service.hpp::async_connect
                                                                        reactive_socket_service_base::start_connect_op
                                                                            // ctrl socket to async, else post_immediate_completion
                                                                asio_connection_fast_ipv4_fallback::handle_tcp_connect
                                                                    // call ssl or normal socket connection handler
                                                            ssl_proxy_tunnel::handle_tcp_connect                // if connection is reused
                                                                asio_connection_fast_ipv4_fallback::async_write
                                                                    asio_connection::async_write
                                                                        --->
                                                                    ssl_proxy_tunnel::handle_write_request
                                                                        ssl_proxy_tunnel::async_read_until
                                                                            asio_connection::async_read_until
                                                                        ssl_proxy_tunnel::handle_status_line
                                                                            start_http_request_flow    // web::http::status_codes::OK
                                                                                --->
                                                                            ssl_proxy_tunnel::handle_body_read
                                                                                // check proxy auth required
                                                            asio_context::handle_connect
                                                                asio_context::write_request
                                                                    --->
                                        start_http_request_flow
                                            // compose raw request stream, start timer: ctx->m_timer.start();
                                            basic_resolver.hpp::async_resolve   // if it's not ssl and not connected
                                                asio_context::handle_resolve
                                                    asio_context::connect
                                                        asio_connection_fast_ipv4_fallback::connect
                                                            --->
                                            asio_context::write_request
                                                asio_connection_fast_ipv4_fallback::async_handshake     // if ssl and not reused
                                                    asio_connection::async_handshake
                                                        stream.hpp::async_handshake
                                                            ....
                                                        asio_context::handle_handshake
                                                            asio_connection_fast_ipv4_fallback::async_write
                                                                --->
                                                asio_connection_fast_ipv4_fallback::async_write
                                                    asio_connect::async_write                           // else
                                                        boost::asio::async_write(m_socket, buffer, writeHandler);
                                                            write.hpp::async_write(stream, buffer, completion, handler)
                                                                write.hpp::start_write_buffer_sequence_op(stream, buffer, bufferIterator, completion_condition, handler)
                                                                    write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator, CompletionCondition, WriteHandler>(
                                                                        stream, buffers, completion_condition, handler
                                                                    )(boost::system::error_code(), 0, 1); // (error_code, bytes_transferred, start)
                                                                        write.hpp::write_op::operator()             // while loop until write completed
                                                                            ssl::stream.hpp::async_write_some       // while loop until write completed
                                                                                ssl::io.hpp::async_io
                                                                                    ssl::io.hpp::io_op::operator()  // while loop until write completed
                                                                                        ssl::write_op.hpp::operator()
                                                                                            ssl::engine::write
                                                                                                ssl::engine::perform
                                                                                                    ssl::engin::write
                                                                                                        ::SSL_write
                                                                            basic_stream_socket::async_write_some
                                                                                reactive_socket_service_base::async_send
                                                                                    reactive_socket_service_base::start_op
                                                                                        epoll_reactor::start_op
                                                                                            epoll_reactor::post_immediate_completion
                                                                                                scheduler::post_immediate_completion
                                                                                                    op_queue_.push(op);
                                                                                                    wake_one_thread_and_unlock(lock);
                                                                                                        posix_event.hpp::maybe_unlock_and_signal_one
                                                                                                            ::pthread_cond_signal
                                                                                                        epoll_reactor::interrupt
                                                                                                            epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, interrupter_.read_descriptor(), &ev);
                return result_task; // return a async pplx::task<response> object to client, client then use response.extract_string() to get the real response string

// write callback for boost::asio::async_write
asio_context::handle_write_headers // request header has sent, then send request body
    asio_context::handle_write_chunked_body //  data is chunked
        ....
    asio_context::handle_write_large_body   // data is not chunked
        // continue write request payload untill completed
        asio_context::handle_write_body // both request header and body sent, wait & handle reponse
            boost::asio::async_read_until;
                    ...
                asio_context::handle_status_line
                    asio_context::read_headers
                      asio_context::complete_headers
                        m_request.set_body(Concurrency::streams::istream());
                        m_request_completion.set(m_response);

                      asio_context::handle_read_content
                        asio_context::async_read_until_buffersize
                          boost::asio::async_read(m_socket, buffer, readCondition, readHandler);
                        request_context::complete_request
                          m_response._get_impl()->_complete(body_size);
                            http_msg_base::_complete
                              m_data_available.set(body_size); // notify client which is blocked at reponse.extract_string
                          request_context::finish;
                            m_http_client->finish_request();
                              _http_client_communicator::finish_request
                                m_requests_queue.pop();
                                open_and_send_request(request);

                      asio_context::handle_chunk_header
                        asio_context::handle_chunk
                          // if to_read == 0 complete_request
                          stream_decompressor::decompress
                          // comtinue read and handle_chunk_header
                        request_context::complete_request
                          --->
```

## Receive Response
```C++
_TaskProcHandle::_RunChoreBridge
  _PPLTaskHandle::_invoke
    _Perform
      _Continue
        _LogWorkItemAndInvokeUserLambda
          MercuryNetworkConnection::handleIncomingMercuryEvent
            --->

ws_client_wspp.cpp::connect_impl
  endpoint.hpp::run

    io_service::run
      win_iocp_io_service::run
        win_iocp_io_service::do_one
          ....
          strand_service::dispatch
            connection.hpp::handle_async_read
              connection<config>::handle_read_http_response
                connection<config>::read_frame

                  connection<config>::async_read_at_least | connection<config>::handle_async_read
                    read.hpp::async_read    // boost
                      connection.hpp::handle_async_read
                          connection<config>::handle_read_frame   // invoke by connection::m_handle_read_frame
                            m_message_handler   // set by ws_client_wspp.cpp::connect_impl set_message_handler

                              MercuryNetworkConnection::handleIncomingMercuryEvent    // set at MercuryNetworkConnection::connectToMercury set_message_handler
                                  MercuryConnectionManager::onMercuryEventArrived
                                      MercuryConnectionManager::fireMercuryEventArrived
```

# PPLX
PPLX is a special version of PPL for non-winodws platform.

The [Parallel Patterns Library (PPL)](https://docs.microsoft.com/en-us/cpp/parallel/concrt/parallel-patterns-library-ppl?view=msvc-160) provides an imperative programming model that promotes scalability and ease-of-use for developing concurrent applications. The PPL builds on the scheduling and resource management components of the [Concurrency Runtime](https://docs.microsoft.com/en-us/cpp/parallel/concrt/concurrency-runtime?view=msvc-160). It raises the level of abstraction between your application code and the underlying threading mechanism by providing generic, type-safe algorithms and containers that act on data in parallel. The PPL also lets you develop applications that scale by providing alternatives to shared state.

The PPL provides the following features:
* [Task Parallelism](https://docs.microsoft.com/en-us/cpp/parallel/concrt/task-parallelism-concurrency-runtime?view=msvc-160): a mechanism that works on top of the Windows ThreadPool to execute several work items (tasks) in parallel
* [Parallel algorithms](https://docs.microsoft.com/en-us/cpp/parallel/concrt/parallel-algorithms?view=msvc-160): generic algorithms that works on top of the Concurrency Runtime to act on collections of data in parallel
* [Parallel containers and objects](https://docs.microsoft.com/en-us/cpp/parallel/concrt/parallel-containers-and-objects?view=msvc-160): generic container types that provide safe concurrent access to their elements
* [Cancellation in PPL](https://docs.microsoft.com/en-us/cpp/parallel/concrt/cancellation-in-the-ppl?view=msvc-160): Explains how to cancel the work that is being performed by a parallel algorithm.

![pplx.png](../../.Image/Pplx.png)

## task::task
```C++
task::task
  _CreateImpl
    _Task_ptr<_ReturnType>::_Make
      std::make_shared<_Task_impl<_ReturnType>>(_Ct, _Scheduler_arg);
  _SetTaskCreationCallstack(_CAPTURE_CALLSTACK());
  _TaskInitMaybeFunctor(_Param, details::_IsCallable(_Param,0));
    _TaskInitWithFunctor(const _Function& _Func)
      _M_Impl->_ScheduleTask
        --->

    _TaskInitNoFunctor(task_completion_event<_ReturnType>& _Event)
      _Event._RegisterTask(_M_Impl)
        _RegisterTask
          _M_Impl->_M_tasks.push_back(_TaskParam)    // 1.

          _TaskParam->_CancelWithExceptionHolder     // 2.

          _TaskParam->_FinalizeAndRunContinuations   // 3.
            _M_Result.Set(_Result);
              _M_TaskCollection._Complete();
                condition_variable.notify_all();
              _RunTaskContinuations
                _RunContinuation // while loop
                  _ScheduleContinuationTask
                    _ScheduleTask
                      --->
```

##  task::then
```C++
task::then
  _M_unitTask._ThenImpl
    _GetImpl()->_ScheduleContinuation
      _PTaskHandle->_M_next = _M_Continuations;

      _Task_impl_base::_ScheduleContinuationTask(_PTaskHandle);
        _Task_impl_base::_ScheduleTask
          _TaskCollectionImpl::_ScheduleTask(_PTaskHandle, _InliningMode);
              linux_scheduler::schedule
                  crossplat::threadpool::shared_instance().schedule(boost::bind(proc, param));

      _Task_impl_base::_Cancel(true);

      _Task_impl_base::_CancelWithExceptionHolder(_GetExceptionHolder(), true);
```

## task::wait
```C++
_Task_impl_base::_Wait
    _TaskCollection_impl::_Wait
        event_impl::wait
            condition_variable.wait

```