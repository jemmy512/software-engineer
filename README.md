# Table of Contents

1. [Formal Entry](#Formal-Entry)
2. [Programmer Cultivation](#Programmer-Cultivation)
    1. [Coding Cultivation](#Coding-Cultivation)
    2. [Code Review](#Code-Review)
    3. [Safety Precaution](#Safety-Precaution)
    4. [Testing](#Testing)
    5. [Publishing](#Publishing)
3. [Computer Science](#Computer-Science)
    1. [Operating System](#Computer-Science)
    2. [Network](#Network)
    3. [Data Structure](#Data-Structure)
    4. [Database](#Database)
4. [Programming Language](#Programming-Language)
    * [C/C++](#CC)
5. [System Design](#System-Design)
6. [Linux](#Linux)
    1. [Kernel](#Kernel)
    2. [Memory Management](#Memory-Management)
    3. [Linux Network](#Linux-Network)
    4. [AIO](#AIO)
    5. [Lock-free](#Lock-free)
    6. [Memory Order](#Memory-Order)
    7. [CPU Cache](#CPU-Cache)
7. [Distributed Architecture](#Distributed-Architecture)
    1. [Distributed Messages System](#Distributed-Messages-System)
    2. [Logs & Data](#Logs--Data)
    3. [Distributed monitoring and tracking](#Distributed-monitoring-and-tracking)
    4. [Data Analysis](#Data-Analysis)
    5. [Distributed Architecture Engineering Design](#Distributed-Architecture-Engineering-Design)
    6. [Design Pattern](#Design-Pattern)
    7. [Failure testing of distributed systems](#Failure-testing-of-distributed-systems)
    8. [Scalability](#Scalability)
    9. [Consistent Hashing](#Consistent-Hashing)
    10. [Cache](#Cache)
    11. [Message Queue](#Message-Queue)
    12. [Log](#Log)
    13. [Performance](#Performance)
    14. [Search](#Search)
    15. [Architecture Practices by Companies](#Architecture-Practices-by-Companies)
8. [Microservice](#Microservice)
    1. [API Gatway](#API-Gatway)
    2. [Microservice VS SOA, IaaS, Paas, Monolithic](#Microservice-VS-SOA-IaaS-Paas-Monolithic)
    3. [Practice](#Practice)
    4. [Authentication & Authorization](#Authentication--Authorization)
    5. [Design Pattern](#Design-Pattern)
9. [Thanks](#Thanks)

# Formal Entry
- [ ] [The key to Accelerating Your Coding Skills](http://blog.thefirehoseproject.com/posts/learn-to-code-and-be-self-reliant/)
- [ ] [Character Encoding](https://en.wikipedia.org/wiki/Character_encoding)

# Programmer Cultivation
- [ ] https://www.quora.com/What-are-some-of-the-most-basic-things-every-programmer-should-know
- [ ] https://97-things-every-x-should-know.gitbooks.io/97-things-every-programmer-should-know/content/en/index.html
- [ ] [How to Ask Question The Smart Way](http://www.catb.org/~esr/faqs/smart-questions.html)

### Coding Cultivation
- [ ] :orange_book: Refactoring: Improving the Design of Existing Code
- [ ] :orange_book: Working Effectively with Legacy Code
- [ ] :orange_book: Clean Code: A Handbook of Agile Software Craftsmanship :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/CS/clean-code.md)
- [ ] :orange_book: The Clean Coder：A Code of Conduct for Professional Programmers

### Code Review
- [ ] [Code Review Best Practices](https://medium.com/palantir/code-review-best-practices-19e02780015f?)
- [ ] [How Google Does Code Review](https://dzone.com/articles/how-google-does-code-review)

### Safety Precaution
- [ ] https://www.owasp.org/index.php/Main_Page
- [ ] [Secure Coding Practice Guidelines](https://security.berkeley.edu/secure-coding-practice-guidelines)
- [ ] [SEI SERT Coding Standards](https://wiki.sei.cmu.edu/confluence/display/seccode/SEI+CERT+Coding+Standards)
- [ ] [Hardening Your HTTP Security Headers](https://www.keycdn.com/blog/http-security-headers)

### Testing
- [ ] :orange_book: Perfect Software: And Other Illusions about Testing
- [ ] :orange_book: How Google Tests Software

### Publishing
- [x] [Checklist](https://github.com/mtdvio/going-to-production)

# Computer Science
## Operating System
- [ ] :orange_book: Computer Systems A Programmer’s Perspective :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/CS/computer-system-a-programmers-perspective.md)
- [ ] :orange_book: Modern Operating Systems :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/CS/modern-operating-system.md)
- [ ] :orange_book: Advanced Programming in the UNIX Environment

## Network
- [ ] :orange_book: TCP/IP ILLustrated Volume 1: The Protocols :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/CS/tcp-ip-illustrated-volume-1.md)
- [ ] :orange_book: UNIX Network Programming, Volume 1: The Sockets Networking API :pencil2: [Book Notes: UNP](https://github.com/Jemmy512/book-notes/blob/master/Linux/unp.md) :pencil2: [Book Notes: Linux Programming](https://github.com/Jemmy512/book-notes/blob/master/Linux/linux-programming.md)
- [ ] :orange_book: UNIX Network Programming, Volume 2: Interprocess Communications
- [ ] :orange_book: [Linux System Programming](http://igm.univ-mlv.fr/~yahya/progsys/linux.pdf)
- [ ] :orange_book: Computer Networking: A Top-Down Approach
- [ ] :orange_book: Computer Networks, 5th Edition
- [ ] :orange_book: Practical Packet Analysis: Using Wireshark to Solve Real-World Network Problems, 2nd Edition

- [ ] [Internet protocol suite (wikipedia)](https://en.wikipedia.org/wiki/Internet_protocol_suite)
- [ ] [Let’s Code a TCP/IP Stack, 1: Ethernet & ARP](https://www.saminiir.com/lets-code-tcp-ip-stack-1-ethernet-arp/#tuntap-devices)
- [ ] [Let’s Code a TCP/IP Stack, 2: IPV4 & ICMPv4](https://www.saminiir.com/lets-code-tcp-ip-stack-2-ipv4-icmpv4)
- [ ] [Let’s Code a TCP/IP Stack, 3: TCP Basics & Handshake](https://www.saminiir.com/lets-code-tcp-ip-stack-3-tcp-handshake)
- [ ] [Let’s Code a TCP/IP Stack, 4: Tcp Data Flow & Socket API](https://www.saminiir.com/lets-code-tcp-ip-stack-4-tcp-data-flow-socket-api)
- [ ] [Let’s Code a TCP/IP Stack, 5: TCP Retransaction](https://www.saminiir.com/lets-code-tcp-ip-stack-5-tcp-retransmission)

- [ ] [C10k Problem](http://www.kegel.com/c10k.html)
- [ ] [C10m Problem](http://highscalability.com/blog/2013/5/13/the-secret-to-10-million-concurrent-connections-the-kernel-i.html)
- [ ] [Congestion Avoidance and Control.pdf](https://ee.lbl.gov/papers/congavoid.pdf)
- [ ] [Nginx HTTP/2](https://www.nginx.com/wp-content/uploads/2015/09/NGINX_HTTP2_White_Paper_v4.pdf)

* ARP
    - [ ] RFC 826 - An Ethernet Address Resolution Protocol

* Tunnel
    - [ ] RFC 1853 - IP in IP Tunneling
    - [ ] RFC 2784 - Generic Routing Encapsulation (GRE)
    - [ ] RFC 2661 - Layer Two Tunneling Protocol “L2TP”
    - [ ] RFC 2637 - Point-to-Point Tunneling Protocol (PPTP)

* TCP
    - [ ] RFC 793 - Transmission Control Protocol
    - [ ] RFC 813 - Window and Acknowledgement Strategy in TCP
    - [ ] RFC 879 - The TCP Maximum Segment Size and Related Topics
    - [ ] RFC 896 - Congestion Control in IP/TCP Internetworks
    - [ ] RFC 2581 - TCP Congestion Control
        - [ ] RFC 5681 - TCP Congestion Control
        - [ ] RFC 6582 - The NewReno Modification to TCP’s Fast Recovery Algorithm
    - [ ] RFC 2018 - TCP Selective Acknowledgment Options
        - [ ] RFC 2883 - An Extension to the Selective Acknowledgement (SACK) Option for TCP
    - [ ] RFC 2988 - Computing TCP’s Retransmission Timer
    - [ ] RFC 6298 - Computing TCP’s Retransmission Timer

* HTTP
    - [ ] RFC 7230 - Hypertext Transfer Protocol (HTTP/1.1): Message Syntax and Routing
    - [ ] RFC 7231 - Hypertext Transfer Protocol (HTTP/1.1): Semantics and Content
    - [ ] RFC 7232 - Hypertext Transfer Protocol (HTTP/1.1): Conditional Requests
    - [ ] RFC 7233 - Hypertext Transfer Protocol (HTTP/1.1): Range Requests
    - [ ] RFC 7234 - Hypertext Transfer Protocol (HTTP/1.1): Caching
    - [ ] RFC 7235 - Hypertext Transfer Protocol (HTTP/1.1): Authentication
    - [ ] RFC 7540 - Hypertext Transfer Protocol Version 2 (HTTP/2)
    - [ ] RFC 7541 - HPACK: Header Compression for HTTP/2

## Database
- [ ] :orange_book: Database System Concepts(Fifth Edition)
- [ ] :orange_book: High Performance MySQL,3rd
- [ ] :orange_book: Inside MySAQL: InnoDB Storage Engine
- [ ] :orange_book: Relational Database Index Design and the Optimizers
- [ ] [MySQL Internals Manual](https://dev.mysql.com/doc/internals/en/)
- [ ] [How to Analyze and Tune MySQL Queries for Better Performance](https://www.mysql.com/cn/why-mysql/presentations/tune-mysql-queries-performance/)
- [ ] [MySQL Performance Tuning 101](https://www.mysql.com/cn/why-mysql/presentations/mysql-performance-tuning101/)
- [ ] [MySQL Performance Schema & Sys Schema](https://www.mysql.com/cn/why-mysql/presentations/mysql-performance-sys-schema/)
- [ ] [MySQL Performance: Demystified Tuning & Best Practices](https://www.mysql.com/cn/why-mysql/presentations/mysql-performance-tuning-best-practices/)
- [ ] [MySQL Security Best Practices](https://www.mysql.com/cn/why-mysql/presentations/mysql-performance-sys-schema//)
- [ ] [MySQL Cluster Deployment Best Practices](https://www.mysql.com/cn/why-mysql/presentations/mysql-performance-tuning-best-practices/)
- [ ] [MySQL High Availability with InnoDB Cluster](https://www.mysql.com/cn/why-mysql/presentations/mysql-high-availability-innodb-cluster/)

## Data Structure
- [ ] :orange_book: Data Structures and Algorithm Analysis in C:Second Edition

## Algorithm
- [ ] :orange_book: Algorithms，Fouth Edition
- [ ] :orange_book: Grokking Algorithms: An illustrated guide for programmers and other curious people
- [ ] :orange_book: Programming Pearls (2/e)
- [ ] :orange_book: Data Structures and Algorithm Analysis in C:Second Edition

# Programming Language

### C/C++
<details>
<summary>Open/Close</summary>

- [ ] :orange_book: The C Programming Language
- [ ] :orange_book: C Programming: A Modern Approach
- [ ] :orange_book: C Traps and Pitfalls
- [x] :orange_book: C++ Primer, 5th Edition :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Cpp/cpp-primer.md)
- [x] :orange_book: Effective C++ :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Cpp/effective-cpp.md)
- [ ] :orange_book: More Effective C++ :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Cpp/more-effective-cpp.md)
- [x] :orange_book: Modern Effective C++ :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Cpp/effective-modern-cpp.md)
- [x] :orange_book: Inside C++ Object Model :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Cpp/inside-the-cpp-object-model.md)
- [x] :orange_book: C++ Templates The Complete Guide :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Cpp/cpp-templates-the-complete-guid.md)
- [x] :orange_book: Modern C++ Design :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Cpp/modern-cpp-design.md)
- [ ] [C++ FAQ](http://www.stroustrup.com/bs_faq.html)
- [x] [How C++ Resolves a Function Call](https://preshing.com/20210315/how-cpp-resolves-a-function-call/)
- [x] [How to Use C++ for Cross-Platform Development](https://gusc.lv/2021/03/how-to-use-c-for-cross-platform-development/)
- [x] [Paramter Passing in C and C++](https://wolchok.org/posts/parameter-passing/)

* OOP
    - [x] [Inheritance Without Pointers](https://www.fluentcpp.com/2021/01/29/inheritance-without-pointers/)
    - [x] [Runtime Polymorphism Without Objects or Virtual Functions](https://www.fluentcpp.com/2020/05/15/runtime-polymorphism-without-virtual-functions/)
    - [x] [coolshell: C++ virtual function table analysis (CN)](https://coolshell.cn/articles/12165.html)
    - [x] [The cost of dynamic (virtual calls) vs. static (CRTP) dispatch in C++](https://eli.thegreenplace.net/2013/12/05/the-cost-of-dynamic-virtual-calls-vs-static-crtp-dispatch-in-c)
    - [x] [The Sad True about C++ Copy Elision](https://wolchok.org/posts/sad-truth-about-cxx-copy-elision/)

* Const & Mutable
    - [x] [Const Correctness](https://arne-mertz.de/2016/07/const-correctness/)
    - [x] [Mutable](https://arne-mertz.de/2017/10/mutable/)
    - [x] [How to Share Code with Const and Non-Const Functions in C++](https://www.cppstories.com/2020/11/share-code-const-nonconst.html)

* STL
    - [x] [Creating STL Containers in Shared Memory](https://www.drdobbs.com/creating-stl-containers-in-shared-memory/184401639)

* C++ Memory Model
    - [x] [Memory layout of C ++ objects (CN)](https://coolshell.cn/articles/12176.html)
    - [x] [C++ objects Memory layout (CN)](https://mp.weixin.qq.com/s/I3mQAZAycd5KJnbfywYT8g)
    - [x] [std::memory_order](https://en.cppreference.com/w/cpp/atomic/memory_order)
    - [x] [C++ Memory Model](https://www.modernescpp.com/index.php/c-memory-model)
    - [x] [Sequential Consistency](https://www.modernescpp.com/index.php/sequential-consistency)
    - [x] [The Atomic Flag](https://www.modernescpp.com/index.php/the-atomic-flag)
    - [x] [The Atomic Boolean](https://www.modernescpp.com/index.php/the-atomic-boolean)
    - [x] [Atomics](https://www.modernescpp.com/index.php/atomics)
    - [x] [Synchronization and Ordering Constraints](https://www.modernescpp.com/index.php/synchronization-and-ordering-constraints)
    - [x] [Sequential Consistency applied](https://www.modernescpp.com/index.php/sequential-consistency-applied)
    - [x] [Acquire-Release Semantic](https://www.modernescpp.com/index.php/acquire-release-semantic)
    - [x] [Transitivity of the Acquire-Release Semantic](https://www.modernescpp.com/index.php/transivity-of-the-acquire-release-semantic)
    - [x] [memory_order_consume](https://www.modernescpp.com/index.php/memory-order-consume)
    - [x] [Acquire-Release Semantic - The typical Misunderstanding](https://www.modernescpp.com/index.php/acquire-release-semantic-the-typical-misunderstanding)
    - [x] [Fences are Memory Barriers](https://www.modernescpp.com/index.php/fences-as-memory-barriers)
    - [x] [Acquire-Release Fences](https://www.modernescpp.com/index.php/acquire-release-fences)
    - [x] [Relaxed Semantic](https://www.modernescpp.com/index.php/relaxed-semantic)

* CRTP
    - [x] [Curiously Recurring Template Pattern (CRTP)](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)
    - [x] [The CRTP, episode One: Definition](https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/)
    - [x] [The CRTP, episode Two: What the CRTP can bring to your code](https://www.fluentcpp.com/2017/05/16/what-the-crtp-brings-to-code/)
    - [x] [The CRTP, episode Three: An implementation helper for the CRTP](https://www.fluentcpp.com/2017/05/19/crtp-helper/)
    - [x] [Mixin Classes: The Yang of the CRTP](https://www.fluentcpp.com/2017/12/12/mixin-classes-yang-crtp/)
    - [x] [How to Turn a Hierarchy of Virtual Methods into a CRTP](https://www.fluentcpp.com/2018/05/22/how-to-transform-a-hierarchy-of-virtual-methods-into-a-crtp/)
    - [x] [Replacing CRTP Static Polymorphism With Concepts](https://www.fluentcpp.com/2020/09/11/replacing-crtp-static-polymorphism-with-concepts/)
    - [x] [Removing Duplicates in C++ CRTP Base Classes](https://www.fluentcpp.com/2018/08/28/removing-duplicates-crtp-base-classes/)
    - [x] [How to Reduce the Code Bloat of a Variadic CRTP](https://www.fluentcpp.com/2018/07/03/how-to-reduce-the-code-bloat-of-a-variadic-crtp/)
    - [x] [Variadic CRTP Packs: From Opt-in Skills to Opt-in Skillsets](https://www.fluentcpp.com/2018/06/26/variadic-crtp-packs-from-opt-in-skills-to-opt-in-skillsets/)
    - [x] [Variadic CRTP: An Opt-in for Class Features, at Compile Time](https://www.fluentcpp.com/2018/06/22/variadic-crtp-opt-in-for-class-features-at-compile-time/)

* Template
    - [x] [One Trick with Private Names and Function Templates](https://www.cppstories.com/2020/12/private-names-trick)
    - [x] [Modern C++ Features – Class Template Argument Deduction](https://arne-mertz.de/2017/06/class-template-argument-deduction/)
    - [x] [Build Throughput Series: Template Metaprogramming Fundamentals](https://devblogs.microsoft.com/cppblog/build-throughput-series-template-metaprogramming-fundamentals/)
    - [x] [Build Throughput Series: More Efficient Template Metaprogramming](https://devblogs.microsoft.com/cppblog/build-throughput-series-more-efficient-template-metaprogramming/)
    - [x] [How to Pass a Variadic Pack as a First Argument of a Function](https://www.fluentcpp.com/2021/01/22/how-to-pass-a-variadic-pack-as-a-first-argument-of-a-function-in-cpp/)

* C++11
    - [x] [Herb Sutter: Move Simply](https://herbsutter.com/2020/02/17/move-simply/)
    - [x] [C++ Move Semantics - The Complete Guide](http://cppmove.com/)
    - [x] [Andreas: Can I touch a moved-from object](https://andreasfertig.blog/2021/04/can-i-touch-a-moved-from-object/)

* C++17
    - [x] [Table: C++17 Features.pdf](https://github.com/Jemmy512/book-notes/blob/master/Cpp/table-cpp17-features.pdf)
    - [x] [How std::any Works](https://www.fluentcpp.com/2021/02/05/how-stdany-works/)
    - [ ] [Everything You Need to Know About std::variant from C++17](https://www.bfilipek.com/2018/06/variant.html)
    - [x] [Runtime Polymorphism with std::variant and std::visit](https://www.bfilipek.com/2020/04/variant-virtual-polymorphism.html)
    - [ ] [Simplify code with ‘if constexpr’ in C++17](https://www.bfilipek.com/2018/03/ifconstexpr.html)

* C++ 20
    - [x] [Table: C++20 Features.pdf](https://github.com/Jemmy512/book-notes/blob/master/Cpp/table-cpp20-features.pdf)
    - [ ] [All C++20 core language features with examples](https://oleksandrkvl.github.io/2021/04/02/cpp-20-overview.html)
    - [x] [C++20: Aggregate, POD, trivial type, standard layout class, what is what](https://andreasfertig.blog/2021/01/cpp20-aggregate-pod-trivial-type-standard-layout-class-what-is-what/)
    - [x] [Notes on C++ SFINAE, Modern C++ and C++20 Concepts](https://www.cppstories.com/2016/02/notes-on-c-sfinae/)
    - [x] [std::index_sequence and its Improvement in C++20](https://www.fluentcpp.com/2021/03/05/stdindex_sequence-and-its-improvement-in-c20/)
    - [ ] [Raymond Chen: C++ coroutines]()
        * [A map through the three major coroutine series](https://devblogs.microsoft.com/oldnewthing/20210504-01/?p=105178)
        <details>
        <summary>Open/Close</summary>

        * Awaitable Objects
            * [Getting started with awaitable objects](https://devblogs.microsoft.com/oldnewthing/20191209-00/?p=103195)
                * [Constructible awaitable or function returning awaitable?](https://devblogs.microsoft.com/oldnewthing/20191210-00/?p=103197)
                * [Framework interop](https://devblogs.microsoft.com/oldnewthing/20191211-00/?p=103201)
                * [Awaiting an IAsyncAction without preserving thread context](https://devblogs.microsoft.com/oldnewthing/20191212-00/?p=103207)
            * [Short-circuiting suspension, part 1](https://devblogs.microsoft.com/oldnewthing/20191213-00/?p=103210) 
            * [Short-circuiting suspension, part 2](https://devblogs.microsoft.com/oldnewthing/20191216-00/?p=103217) 
                * [no callable ‘await_resume’ function found for type](https://devblogs.microsoft.com/oldnewthing/20191217-00/?p=103219)
            * [Defining the co_await operator](https://devblogs.microsoft.com/oldnewthing/20191218-00/?p=103221)
                * [The co_await operator and the function search algorithm](https://devblogs.microsoft.com/oldnewthing/20191219-00/?p=103230)
                * [The problem of the synchronous apartment-changing callback](https://devblogs.microsoft.com/oldnewthing/20191220-00/?p=103232)
                * [The problem of the DispatcherQueue task that runs too soon, part1](https://devblogs.microsoft.com/oldnewthing/20191223-00/?p=103255) [:link: Part 2](https://devblogs.microsoft.com/oldnewthing/20191224-00/?p=103262) [:link: Part 3](https://devblogs.microsoft.com/oldnewthing/20191225-00/?p=103265) [:link: Part 4](https://devblogs.microsoft.com/oldnewthing/20191226-00/?p=103268)
            
        * Awaitable Signals
            * Creating a co_await awaitable signal that can be awaited multiple times
                * [:link: part 1](https://devblogs.microsoft.com/oldnewthing/20210301-00/?p=104914) [:link: part 2](https://devblogs.microsoft.com/oldnewthing/20210302-00/?p=104918) [:link: part 3](https://devblogs.microsoft.com/oldnewthing/20210303-00/?p=104922) [:link: part 4](https://devblogs.microsoft.com/oldnewthing/20210304-00/?p=104926) [:link: part 5](https://devblogs.microsoft.com/oldnewthing/20210305-00/?p=104934)   
                * [:link: part 6](https://devblogs.microsoft.com/oldnewthing/20210308-00/?p=104938)
                    * Creating other types of synchronization objects that can be used with co_await
                        * [1: The one-shot event](https://devblogs.microsoft.com/oldnewthing/20210309-00/?p=104942)
                        * [2: The basic library](https://devblogs.microsoft.com/oldnewthing/20210310-00/?p=104945)
                        * [3: Parallel resumption](https://devblogs.microsoft.com/oldnewthing/20210311-00/?p=104949)
                        * [4: The manual-reset event](https://devblogs.microsoft.com/oldnewthing/20210312-00/?p=104955)
                        * [5: The auto-reset event](https://devblogs.microsoft.com/oldnewthing/20210315-00/?p=104964)
                        * [6: The semaphore](https://devblogs.microsoft.com/oldnewthing/20210316-00/?p=104971)
                        * [7: The mutex and recursive](https://devblogs.microsoft.com/oldnewthing/20210317-00/?p=104973)
                        * [8: The shared mutex](https://devblogs.microsoft.com/oldnewthing/20210318-00/?p=104977)
                        * [9: The shared mutex (continued)](https://devblogs.microsoft.com/oldnewthing/20210319-00/?p=104979)
                        * [10: Wait for an event to clear](https://devblogs.microsoft.com/oldnewthing/20210322-00/?p=104981)
            * [Creating a task completion source for a C++ coroutine]()
                * [Producing a result](https://devblogs.microsoft.com/oldnewthing/20210323-00/?p=104987)
                * [Producing a result with references](https://devblogs.microsoft.com/oldnewthing/20210324-00/?p=104995)
                * [Producing nothing](https://devblogs.microsoft.com/oldnewthing/20210325-00/?p=105002)
                * [Failing to produce a result](https://devblogs.microsoft.com/oldnewthing/20210326-00/?p=105009)
            
        * Coroutine Promises
            * [The mental model for coroutine promises](https://devblogs.microsoft.com/oldnewthing/20210329-00/?p=105015)
            * [Basic implementation of a promise type](https://devblogs.microsoft.com/oldnewthing/20210330-00/?p=105019)
            * [The initial and final suspend, and improving our return_value method](https://devblogs.microsoft.com/oldnewthing/20210331-00/?p=105028)
                * [What happens if an exception occurs in my return_value?](https://devblogs.microsoft.com/oldnewthing/20210401-00/?p=105043)
            * [Making the promise itself be the shared state, the inspiration](https://devblogs.microsoft.com/oldnewthing/20210402-00/?p=105047)
            * [Making the promise itself be the shared state, the outline](https://devblogs.microsoft.com/oldnewthing/20210405-00/?p=105054)
            * [Building a result holder for movable types](https://devblogs.microsoft.com/oldnewthing/20210406-00/?p=105057)
            * [Accepting types via return_void and return_value](https://devblogs.microsoft.com/oldnewthing/20210407-00/?p=105061)
            * [Awaiting the simple_task](https://devblogs.microsoft.com/oldnewthing/20210408-00/?p=105063)
            * [Managing the reference count of the coroutine state](https://devblogs.microsoft.com/oldnewthing/20210409-00/?p=105065)
                * [The lifetime of objects involved in the coroutine function](https://devblogs.microsoft.com/oldnewthing/20210412-00/?p=105078)
                * [Tradeoffs of making the promise be the shared state](https://devblogs.microsoft.com/oldnewthing/20210413-00/?p=105093)
            * [Making it impossible to co_await a task twice](https://devblogs.microsoft.com/oldnewthing/20210414-00/?p=105095)
            * [Getting rid of our mutex](https://devblogs.microsoft.com/oldnewthing/20210415-00/?p=105109)
            * [Getting rid of our reference count](https://devblogs.microsoft.com/oldnewthing/20210416-00/?p=105115)
                * [Allowing the awaiter to be destroyed while suspended](https://devblogs.microsoft.com/oldnewthing/20210419-00/?p=105119)
                * [Getting rid of our atomic variant discriminator](https://devblogs.microsoft.com/oldnewthing/20210420-28/?p=105128)
                * [Cold-start coroutines](https://devblogs.microsoft.com/oldnewthing/20210421-00/?p=105135)
                * [Improving cold-start coroutines which complete synchronously](https://devblogs.microsoft.com/oldnewthing/20210422-00/?p=105139)
                * [Associating multiple task types with the same promise type](https://devblogs.microsoft.com/oldnewthing/20210423-00/?p=105146)
            * [What does it mean when I declare my coroutine as noexcept?](https://devblogs.microsoft.com/oldnewthing/20210426-00/?p=105153)
            * [How do I create a coroutine that terminates on an unhandled exception?](https://devblogs.microsoft.com/oldnewthing/20210427-00/?p=105157)
            * [Snooping in on the coroutine body](https://devblogs.microsoft.com/oldnewthing/20210428-00/?p=105160)
            * [Adding custom resume context support to our awaiter](https://devblogs.microsoft.com/oldnewthing/20210429-00/?p=105165)
                * [Waiting synchronously for our coroutine to complete](https://devblogs.microsoft.com/oldnewthing/20210430-00/?p=105171)
                * [Converting among tasks that use the same promise](https://devblogs.microsoft.com/oldnewthing/20210503-00/?p=105173)
            * [Promise constructors](https://devblogs.microsoft.com/oldnewthing/20210504-00/?p=105176)
        * Mix
            * [Why is coroutine_handle::resume() potentially-throwing?](https://devblogs.microsoft.com/oldnewthing/20210505-00/?p=105186)
            * [A subtle way your await_suspend can access the coroutine frame when it shouldn’t](https://devblogs.microsoft.com/oldnewthing/20210507-00/?p=105196)

        </details>
    - [ ] [Asymmetric Transfer: C++ coroutines]()
        * [Coroutine Theory](https://lewissbaker.github.io/2017/09/25/coroutine-theory)
        * [Understanding operator co_await](https://lewissbaker.github.io/2017/11/17/understanding-operator-co-await)
        * [Understanding the promise type](https://lewissbaker.github.io/2018/09/05/understanding-the-promise-type)
        * [Understanding Symmetric Transfer](https://lewissbaker.github.io/2020/05/11/understanding_symmetric_transfer)
    - [x] [constexpr Dynamic Memory Allocation, C++20](https://www.cppstories.com/2021/constexpr-new-cpp20/)

</details>

# System Design

- [ ] :orange_book: Domain-Driven Design: Tackling Complexity in the Heart of Software
- [ ] :orange_book: The Art of UNIX Programming
- [ ] :orange_book: Clean Architecture

- [x] [Grokking System Design](https://www.educative.io/courses/grokking-the-system-design-interview)  [:pencil2: Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Arch/object-oriented-design.md)
- [ ] [Grokking Advanced System Design](https://github.com/Jemmy512/book-notes/blob/master/Arch/system-design-advanced.md)
- [x] [Grokking the Object Oriented Design](https://www.educative.io/courses/grokking-the-object-oriented-design-interview)  [:pencil2: Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Arch/object-oriented-design.md)
- [ ] [System Design Primer](https://github.com/donnemartin/system-design-primer)
- [ ] [Six Programming Paradigm](https://www.ybrikman.com/writing/2014/04/09/six-programming-paradigms-that-will)
- [ ] [Programming Paradigms for Dummies.pdf](https://www.info.ucl.ac.be/~pvr/VanRoyChapter.pdf)
- [ ] [Stanford Programming Paradigm](https://see.stanford.edu/Course/CS107)
- [ ] [The Twelve-Factor App](https://12factor.net)
- [ ] [Avoid Over Engineering](https://medium.com/@rdsubhas/10-modern-software-engineering-mistakes-bc67fbef4fc8)

- [ ] [Best Practices for Designing a Pragmatic RESTful API](https://www.vinaysahni.com/best-practices-for-a-pragmatic-restful-api)
- [ ] [HTTP API Desgin](https://github.com/interagent/http-api-design)
- [ ] [API Guildlines](https://github.com/Microsoft/api-guidelines/blob/vNext/Guidelines.md)
- [ ] [The Problem With Logging](https://blog.codinghorror.com/the-problem-with-logging)


# Linux
- [ ] [Red Hat Enterprise Linux](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/)
- [ ] [x86-TSO: A Rigorous and Usable Programmer’s Model for x86 Multiprocessors](https://www.cl.cam.ac.uk/~pes20/weakmemory/cacm.pdf)
- [x] [Spurious wakeup](https://en.wikipedia.org/wiki/Spurious_wakeup)  [:link: C++ Condition Variable](https://www.modernescpp.com/index.php/c-core-guidelines-be-aware-of-the-traps-of-condition-variables)

### Kernel
- [x] :pencil2: [Linux Kernel 4.19](https://github.com/Jemmy512/book-notes/blob/master/Linux/linux-kernel.md)
- [x] :pencil2: [Understanding Linux Kernel](https://github.com/Jemmy512/book-notes/blob/master/Linux/understanding-linux-kernel.md)
- [x] :pencil2: [Linux Kernel Development](https://github.com/Jemmy512/book-notes/blob/master/Linux/linux-kernel-development.md)
- [x] [RCU]() [:link: Part 1](https://lwn.net/Articles/262464/) [:link: Part 2](https://lwn.net/Articles/263130/) [:link: Part 3](https://lwn.net/Articles/264090/)
- [x] [Linux Insides](https://github.com/0xAX/linux-insides)
- [x] [LWN’s kernel page](https://lwn.net/Kernel/Index/)
- [x] [Learn Linux Kernel from Android Perspective](https://learnlinuxconcepts.blogspot.com/2014/10/this-blog-is-to-help-those-students-and.html)
- [x] [Linux Kernel Doc](https://www.kernel.org/doc/)
- [x] [Kernel Planet: Kernel Developers Doc](https://planet.kernel.org)
- [x] [Linux Performance and Tuning Guidelines.pdf](https://lenovopress.com/redp4285.pdf)
- [x] [Linux Performance](http://www.brendangregg.com/linuxperf.html)
- [x] [Optimizing web servers for high throughput and low latency](https://dropbox.tech/infrastructure/optimizing-web-servers-for-high-throughput-and-low-latency)

### Memory Management
- [ ] [What Every Programmer Should Know About Memory.pdf](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)
- [ ] [Memory Barriers: a Hardware View for Software Hackers.pdf](https://irl.cs.ucla.edu/~yingdi/web/paperreadingwhymb.2010.06.07c.pdf)
- [ ] [A Tutorial Introduction to the ARM and POWER Relaxed Memory Models.pdf](https://www.cl.cam.ac.uk/~pes20/ppc-supplemental/test7.pdf)
- [x] [ptmalloc](http://www.malloc.de/en/)
- [x] [tcmalloc](https://github.com/google/tcmalloc) [:link: Ref](https://wallenwang.com/2018/11/tcmalloc/) [:link: Ref](https://www.programmersought.com/article/84461226079/)
- [x] [jemalloc.pdf](http://people.freebsd.org/~jasone/jemalloc/bsdcan2006/jemalloc.pdf)
- [x] [C dynamic memory allocation](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)
- [x] [Research on ptmalloc, tcmalloc and jemalloc memory allocation strategies](https://owent.net/2013/867.html)
- [x] [Memory optimization summary: ptmalloc, tcmalloc, and jemalloc](http://www.cnhalo.net/2016/06/13/memory-optimize)
- [x] [Scalable memory allocation using jemalloc](https://www.facebook.com/notes/facebook-engineering/scalable-memory-allocation-using-jemalloc/480222803919)

### Linux Network
- [ ] :orange_book: [Linux High Performance Server Programming (CN)](https://book.douban.com/subject/24722611/) :pencil2:  [Linux Programmnig Noetes](https://github.com/Jemmy512/book-notes/blob/master/Linux/linux-programming.md) :pencil2: [Linux System Notes](https://github.com/Jemmy512/book-notes/blob/master/Linux/LinuxBasic.md)
- [ ] :orange_book: Network tuning

- [ ] [Linux Advanced Routing & Traffic Control HOWTO](https://lartc.org)
- [ ] [Red Hat Enterprise Linux Network Performance Tuning Guide.pdf](https://access.redhat.com/sites/default/files/attachments/20150325_network_performance_tuning.pdf)
- [ ] [Awesome Pcap Tools](https://github.com/caesar0301/awesome-pcaptools)
- [ ] [Making Linux TCP Fast.pdf](https://netdevconf.info/1.2/papers/bbr-netdev-1.2.new.new.pdf)
- [ ] [Monitoring and Tuning the Linux Networking Stack: Receiving Data](https://blog.packagecloud.io/eng/2016/06/22/monitoring-tuning-linux-networking-stack-receiving-data/)
- [ ] [Monitoring and Tuning the Linux Networking Stack: Sending Data](https://blog.packagecloud.io/eng/2017/02/06/monitoring-tuning-linux-networking-stack-sending-data/)

### AIO
- [x] [Boost application performance using asynchronous I/O](https://developer.ibm.com/articles/l-async/)
- [ ] [Lazy Asynchronous I/O For Event-Driven Servers](https://www.usenix.org/legacy/event/usenix04/tech/general/full_papers/elmeleegy/elmeleegy_html/html.html)
- [ ] [IOCP](http://sysinternals.d4rk4.ru/Information/IoCompletionPorts.html)
- [x] [Understanding Reactor Pattern: Thread-Based and Event-Driven](https://dzone.com/articles/understanding-reactor-pattern-thread-based-and-eve)
- [ ] [The Design and Implementation of the Reactor.pdf](https://www.dre.vanderbilt.edu/~schmidt/PDF/Reactor2-93.pdf)
- [ ] [The Secret To 10 Million Concurrent Connections -The Kernel Is The Problem, Not The Solution](http://highscalability.com/blog/2013/5/13/the-secret-to-10-million-concurrent-connections-the-kernel-i.html)
- [x] [Epoll is fundamentally broken 1/2](https://idea.popcount.org/2017-02-20-epoll-is-fundamentally-broken-12)
- [x] [Epoll is fundamentally broken 2/2](https://idea.popcount.org/2017-03-20-epoll-is-fundamentally-broken-22)


### Lock-free
- [x] [An Introduction to Lock-Free Programming](https://preshing.com/20120612/an-introduction-to-lock-free-programming/)
- [ ] [Lock-Free Data Structures](https://www.drdobbs.com/lock-free-data-structures/184401865)
- [ ] [Lock-Free Data Structures.pdf](https://erdani.com/publications/cuj-2004-10.pdf)
- [ ] [Is Parallel Programming Hard, And, If So, What Can You Do About It?](https://mirrors.edge.kernel.org/pub/linux/kernel/people/paulmck/perfbook/perfbook.html)
- [ ] [Non-blocking Algorithm](https://en.wikipedia.org/wiki/Non-blocking_algorithm)
- [ ] [Read Copy Update](https://en.wikipedia.org/wiki/Read-copy-update)
- [ ] [Seqlock](https://en.wikipedia.org/wiki/Seqlock)
- [ ] [Implementing Lock-Free Queues](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.53.8674&rep=rep1&type=pdf)
- [ ] [Simple, Fast, and Practical Non-Blocking and Blocking Concurrent Queue Algorithms.pdf](https://www.cs.rochester.edu/~scott/papers/1996_PODC_queues.pdf)
- [ ] [Implementing a Recursive Mutex](https://preshing.com/20120305/implementing-a-recursive-mutex)

### Memory Order
- [x] [Weak vs. Strong Memory Models](https://preshing.com/20120930/weak-vs-strong-memory-models/)
- [x] [This Is Why They Call It a Weakly-Ordered CPU](https://preshing.com/20121019/this-is-why-they-call-it-a-weakly-ordered-cpu/)
- [x] [Memory Barriers Are Like Source Control Operations](https://preshing.com/20120710/memory-barriers-are-like-source-control-operations/)
- [x] [Acquire and Release Semantics](https://preshing.com/20120913/acquire-and-release-semantics/)
- [x] [Memory Ordering at Compile Time](https://preshing.com/20120625/memory-ordering-at-compile-time/)
- [x] [The Happens-Before Relation](https://preshing.com/20130702/the-happens-before-relation)
- [x] [The Synchronizes-With Relation](https://preshing.com/20130823/the-synchronizes-with-relation/)
- [x] [Acquire and Release Fences Don't Work the Way You'd Expect](https://preshing.com/20131125/acquire-and-release-fences-dont-work-the-way-youd-expect/)
- [x] [Acquire and Release Fences](https://preshing.com/20130922/acquire-and-release-fences)
- [x] [Roll Your Own Lightweight Mutex](https://preshing.com/20120226/roll-your-own-lightweight-mutex/)
- [x] [Can Reordering of Release/Acquire Operations Introduce Deadlock?](https://preshing.com/20170612/can-reordering-of-release-acquire-operations-introduce-deadlock/)
- [x] [You Can Do Any Kind of Atomic Read-Modify-Write Operation](https://preshing.com/20150402/you-can-do-any-kind-of-atomic-read-modify-write-operation/)
- [x] [The Purpose of memory_order_consume in C++11](https://preshing.com/20140709/the-purpose-of-memory_order_consume-in-cpp11)
- [x] [Atomic vs. Non-Atomic Operations](https://preshing.com/20130618/atomic-vs-non-atomic-operations)
- [x] [Memory Reordering Caught in the Act](https://preshing.com/20120515/memory-reordering-caught-in-the-act)

### CPU Cache
- [x] [Gallery of Processor Cache Effects](http://igoro.com/archive/gallery-of-processor-cache-effects/) [TODO:?]()
- [x] [coolshell: CPU Cache](https://coolshell.cn/articles/20793.html)
- [x] [L1 cache lines](https://vorbrodt.blog/2019/02/02/cache-lines/)


# Distributed Architecture
- [ ] :orange_book: [Distributed Systems for fun and profit](http://book.mixu.net/distsys/single-page.html)
- [ ] :orange_book: Designing Data Intensive Applications
- [ ] :orange_book: [Distributed Systems: Principles and Paradigms.pdf](http://barbie.uta.edu/~jli/Resources/MapReduce&Hadoop/Distributed%20Systems%20Principles%20and%20Paradigms.pdf)
- [ ] :orange_book: [Designing Distributed Systems: Patterns and Paradigms for Scalable, Reliable Services](https://azure.microsoft.com/en-us/resources/designing-distributed-systems/) :pencil2: [Book Notes](https://github.com/Jemmy512/book-notes/blob/master/Arch/designing-distributed-systems.md)
- [ ] :orange_book: [Principles of Distributed Systems.pdf](https://disco.ethz.ch/courses/podc_allstars/lecture/podc.pdf)
- [ ] :newspaper: [Transaction Across DataCenter](https://snarfed.org/transactions_across_datacenters_io.html)   [:tv: YouTuBe](https://www.youtube.com/watch?v=srOgpXECblk)
- [ ] [Scalable Web Architecture and Distributed Systems](http://www.aosabook.org/en/distsys.html)
- [ ] [Scalability, Availability & Stability Patterns](https://www.slideshare.net/jboner/scalability-availability-stability-patterns)
- [ ] [System Design Primer](https://github.com/donnemartin/system-design-primer)
- [ ] [An introduction to distributed systems](https://github.com/aphyr/distsys-class)

- [ ] [Byzantine fault](https://en.wikipedia.org/wiki/Byzantine_fault) [PDF](https://www.microsoft.com/en-us/research/uploads/prod/2016/12/The-Byzantine-Generals-Problem.pdf)
- [ ] [The Byzantine Generals Problem](https://www.drdobbs.com/cpp/the-byzantine-generals-problem/206904396)
- [ ] [Practical Byzantine Fault Tolerance.pdf](http://pmg.csail.mit.edu/papers/osdi99.pdf)
- [ ] [CAP Theorem](https://en.wikipedia.org/wiki/CAP_theorem)
- [ ] [A Brief Tour of FLP Impossibility](https://www.the-paper-trail.org/post/2008-08-13-a-brief-tour-of-flp-impossibility/)
- [ ] [DLS.pdf](http://groups.csail.mit.edu/tds/papers/Lynch/jacm88.pdf)
- [ ] [Introduction to Distributed System Priciples(CN)](http://guanzhou.pub/2018/06/04/Distributed/)

- [ ] [CAP Twelve Years Later: How the "Rules" Have Changed](https://www.infoq.com/articles/cap-twelve-years-later-how-the-rules-have-changed/)
- [ ] [Harvest, yield, and scalable tolerant systems](https://www.semanticscholar.org/paper/9c9ceb29a358149e9617d103f5624f325bf08b1e?p2df)
- [ ] [Base: An Acid Alternative](https://queue.acm.org/detail.cfm?id=1394128)
- [ ] [Eventually Consistent](https://www.allthingsdistributed.com/2008/12/eventually_consistent.html)

### Distributed Messages System
- [ ] [Kafka: a Distributed Messaging System for Log Processing.pdf](http://notes.stephenholiday.com/Kafka.pdf)
- [ ] [Wormhole: Reliable Pub-Sub to Support Geo-replicated Internet Services.pdf](https://www.usenix.org/system/files/conference/nsdi15/nsdi15-paper-sharma.pdf)
- [ ] [board the Databus! LinkedIn's Scalable Consistent Change Data Capture Platform](https://engineering.linkedin.com/research/2012/all-aboard-the-databus-linkedlns-scalable-consistent-change-data-capture-platform)

### Logs & Data
- [ ] [The Log: What every software engineer should know about real-time data's unifying abstraction](https://engineering.linkedin.com/distributed-systems/log-what-every-software-engineer-should-know-about-real-time-datas-unifying)
- [ ] [The Log-Structured Merge-Tree (LSM-Tree).pdf](https://www.cs.umb.edu/~poneil/lsmtree.pdf)
- [ ] [Immutability Changes Everything.pdf](http://cidrdb.org/cidr2015/Papers/CIDR15_Paper16.pdf) [Video](https://vimeo.com/52831373)
- [ ] [Tango: Distributed Data Structures over a Shared Log.pdf](https://www.microsoft.com/en-us/research/wp-content/uploads/2013/11/Tango.pdf)

### Distributed monitoring and tracking
- [ ] [Dapper, a Large-Scale Distributed Systems Tracing Infrastructure.pdf](http://static.googleusercontent.com/media/research.google.com/en//pubs/archive/36356.pdf)

### Data Analysis
- [ ] [The Unified Logging Infrastructure for Data Analytics at Twitter.pdf](http://vldb.org/pvldb/vol5/p1771_georgelee_vldb2012.pdf)
- [ ] [Scaling Big Data Mining Infrastructure: The Twitter Experience.pdf](http://www.datascienceassn.org/sites/default/files/Scaling%20Big%20Data%20Mining%20Infrastructure%20-%20The%20Twitter%20Experience.pdf)
- [ ] [Dremel: Interactive Analysis of Web-Scale Datasets.pdfd](http://static.googleusercontent.com/media/research.google.com/en/us/pubs/archive/36632.pdf)
- [ ] [Resilient Distributed Datasets: A Fault-Tolerant Abstraction for In-Memory Cluster Computing.pdf](https://www.usenix.org/system/files/conference/nsdi12/nsdi12-final138.pdf)

- [ ] [Distributed Programming Model.pdf](https://web.cs.ucdavis.edu/~pandey/Research/Papers/icdcs01.pdf)
- [ ] [PSYNC: A partially synchronous language for fault-tolerant distributed algorithms.pdf](https://www.di.ens.fr/~cezarad/popl16.pdf)
- [ ] [Logic and Lattices for Distributed Programming.pdf](https://dsf.berkeley.edu/papers/UCB-lattice-tr.pdf)

- [ ] [Services Engineering Reading List](https://github.com/mmcgrana/services-engineering)
- [ ] [Readings in distributed systems](http://christophermeiklejohn.com/distributed/systems/2013/07/12/readings-in-distributed-systems.html)
- [ ] [Google Research - Distributed Systems and Parallel Computing](https://research.google/pubs/)

### Distributed Architecture Engineering Design
- [ ] [Designs, Lessons and Advice from Building Large Distributed Systems.pdf](https://www.cs.cornell.edu/projects/ladis2009/talks/dean-keynote-ladis2009.pdf)
- [ ] [Building Software Systems At Google and Lessons Learned](https://www.youtube.com/watch?v=modXC5IWTJI)
- [ ] [The Twelve-Factor App](https://12factor.net)
- [ ] [Notes on Distributed Systems for Young Bloods](https://www.somethingsimilar.com/2013/01/14/notes-on-distributed-systems-for-young-bloods/)
- [ ] [On Designing and Deploying Internet-Scale Services](https://www.usenix.org/legacy/event/lisa07/tech/full_papers/hamilton/hamilton_html/index.html)
- [ ] [4 Things to Keep in Mind When Building a Platform for the Enterprise](https://blog.box.com/blog/4-things-to-keep-in-mind-when-building-a-platform-for-the-enterprise/)
- [ ] [Principles of Chaos Engineering](https://www.usenix.org/conference/srecon17americas/program/presentation/rosenthal)
- [ ] [Building Fast & Resilient Web Applications](https://www.igvita.com/2016/05/20/building-fast-and-resilient-web-applications/)
- [ ] [Designing For Resiliency Will Be So 2013](http://highscalability.com/blog/2012/12/31/designing-for-resiliency-will-be-so-2013.html)
- [ ] [Ten design principles for Azure applications](https://docs.microsoft.com/en-us/azure/architecture/guide/design-principles/)
- [ ] [Eventually Consistent](https://www.allthingsdistributed.com/2008/12/eventually_consistent.html)
- [ ] [Writing Code that Scales](https://www.codeproject.com/Articles/151520/Write-Scalable-Code)
- [ ] [Automate and Abstract: Lessons from Facebook on Engineering for Scale](https://architecht.io/lessons-from-facebook-on-engineering-for-scale-f5716f0afc7a)

### Design Pattern
- [ ] [Martin Fowler: Patterns of Distributed Systems](https://martinfowler.com/articles/patterns-of-distributed-systems/)
    - [ ] [Consistent Core](https://martinfowler.com/articles/patterns-of-distributed-systems/consistent-core.html)
    - [ ] [Generation Clock](https://martinfowler.com/articles/patterns-of-distributed-systems/generation.html)
    - [ ] [Hear Beat](https://martinfowler.com/articles/patterns-of-distributed-systems/heartbeat.html)
    - [ ] [High-Water Mark](https://martinfowler.com/articles/patterns-of-distributed-systems/high-watermark.html)
    - [ ] [Low-Water Mark](https://martinfowler.com/articles/patterns-of-distributed-systems/low-watermark.html)
    - [ ] [Leader Follwers](https://martinfowler.com/articles/patterns-of-distributed-systems/leader-follower.html)
    - [ ] [Quorum](https://martinfowler.com/articles/patterns-of-distributed-systems/quorum.html)
    - [ ] [Request Pipeline](https://martinfowler.com/articles/patterns-of-distributed-systems/request-pipeline.html)
    - [ ] [Segemented Log](https://martinfowler.com/articles/patterns-of-distributed-systems/log-segmentation.html)
    - [ ] [Single Scoekt Channel](https://martinfowler.com/articles/patterns-of-distributed-systems/single-socket-channel.html)
    - [ ] [Singular Update Queue](https://martinfowler.com/articles/patterns-of-distributed-systems/singular-update-queue.html)
    - [ ] [Write-Ahead Log](https://martinfowler.com/articles/patterns-of-distributed-systems/wal.html)
    - [ ] [Lease](https://martinfowler.com/articles/patterns-of-distributed-systems/time-bound-lease.html)
    - [ ] [State Watch](https://martinfowler.com/articles/patterns-of-distributed-systems/state-watch.html)
    - [ ] [Idempotent Receiver](https://martinfowler.com/articles/patterns-of-distributed-systems/idempotent-receiver.html)

- [ ] [MicroSoft Cloud Design Patterns](https://docs.microsoft.com/en-us/azure/architecture/patterns/)
    <details>
    <summary>Open/Close</summary>

    * Design and implementation
        - [ ] [Ambassador](https://docs.microsoft.com/en-us/azure/architecture/patterns/ambassador)
        - [ ] [Anti-corruption Layer](https://docs.microsoft.com/en-us/azure/architecture/patterns/anti-corruption-layer)
        - [ ] [Backends for Frontends](https://docs.microsoft.com/en-us/azure/architecture/patterns/backends-for-frontends)
        - [ ] [Command and Query Responsibility Segregation (CQRS)](https://docs.microsoft.com/en-us/azure/architecture/patterns/cqrs)
        - [ ] [Compute Resource Consolidation](https://docs.microsoft.com/en-us/azure/architecture/patterns/compute-resource-consolidation)
        - [ ] [External Configuration Store](https://docs.microsoft.com/en-us/azure/architecture/patterns/external-configuration-store)
        - [ ] [Gateway Aggregation](https://docs.microsoft.com/en-us/azure/architecture/patterns/gateway-aggregation)
        - [ ] [Gateway Offloading](https://docs.microsoft.com/en-us/azure/architecture/patterns/gateway-offloading)
        - [ ] [Gateway Routing](https://docs.microsoft.com/en-us/azure/architecture/patterns/gateway-routing)
        - [ ] [Leader Election](https://docs.microsoft.com/en-us/azure/architecture/patterns/leader-election)
        - [ ] [Pipes and Filters](https://docs.microsoft.com/en-us/azure/architecture/patterns/pipes-and-filters)
        - [ ] [Sidecar](https://docs.microsoft.com/en-us/azure/architecture/patterns/sidecar)
        - [ ] [Static Content Hosting](https://docs.microsoft.com/en-us/azure/architecture/patterns/static-content-hosting)
        - [ ] [Strangler Fig](https://docs.microsoft.com/en-us/azure/architecture/patterns/strangler-fig)

    * Management and monitoring
        - [x] [Ambassador](https://docs.microsoft.com/en-us/azure/architecture/patterns/ambassador)
        - [x] [Anti-corruption Layer](https://docs.microsoft.com/en-us/azure/architecture/patterns/anti-corruption-layer)
        - [x] [External Configuration Store](https://docs.microsoft.com/en-us/azure/architecture/patterns/external-configuration-store)
        - [x] [Gateway Aggregation](https://docs.microsoft.com/en-us/azure/architecture/patterns/gateway-aggregation)
        - [x] [Gateway Offloading](https://docs.microsoft.com/en-us/azure/architecture/patterns/gateway-offloading)
        - [x] [Gateway Routing](https://docs.microsoft.com/en-us/azure/architecture/patterns/gateway-routing)
        - [x] [Health Endpoint Monitoring](https://docs.microsoft.com/en-us/azure/architecture/patterns/health-endpoint-monitoring)
        - [x] [Sidecar](https://docs.microsoft.com/en-us/azure/architecture/patterns/sidecar)
        - [ ] [Strangler Fig](https://docs.microsoft.com/en-us/azure/architecture/patterns/strangler-fig)

    * Messaging
        - [x] [Anti-corruption Layer](https://docs.microsoft.com/en-us/azure/architecture/patterns/anti-corruption-layer)
        - [ ] [Claim Check](https://docs.microsoft.com/en-us/azure/architecture/patterns/claim-check)
        - [x] [Choreography](https://docs.microsoft.com/en-us/azure/architecture/patterns/choreography)
        - [ ] [Competing Consumers](https://docs.microsoft.com/en-us/azure/architecture/patterns/competing-consumers)
        - [x] [Pipes and Filters](https://docs.microsoft.com/en-us/azure/architecture/patterns/pipes-and-filters)
        - [ ] [Priority Queue](https://docs.microsoft.com/en-us/azure/architecture/patterns/priority-queue)
        - [ ] [Publisher/Subscriber](https://docs.microsoft.com/en-us/azure/architecture/patterns/publisher-subscriber)
        - [x] [Queue-Based Load Leveling](https://docs.microsoft.com/en-us/azure/architecture/patterns/queue-based-load-leveling)
        - [x] [Scheduler Agent Supervisor](https://docs.microsoft.com/en-us/azure/architecture/patterns/scheduler-agent-supervisor)
        - [x] [Sequential Convoy](https://docs.microsoft.com/en-us/azure/architecture/patterns/sequential-convoy)
        - [ ] [Asynchronous Request-Reply](https://docs.microsoft.com/en-us/azure/architecture/patterns/async-request-reply)

    * Data management
        - [ ] [Cache-Aside](https://docs.microsoft.com/en-us/azure/architecture/patterns/cache-aside)
        - [x] [Command and Query Responsibility Segregation (CQRS)](https://docs.microsoft.com/en-us/azure/architecture/patterns/cqrs)
        - [ ] [Event Sourcing](https://docs.microsoft.com/en-us/azure/architecture/patterns/event-sourcing)
        - [ ] [Index Table](https://docs.microsoft.com/en-us/azure/architecture/patterns/index-table)
        - [ ] [Materialized View](https://docs.microsoft.com/en-us/azure/architecture/patterns/materialized-view)
        - [ ] [Sharding](https://docs.microsoft.com/en-us/azure/architecture/patterns/sharding)
        - [x] [Static Content Hosting](https://docs.microsoft.com/en-us/azure/architecture/patterns/static-content-hosting)
        - [ ] [Valet Key](https://docs.microsoft.com/en-us/azure/architecture/patterns/valet-key)
        - [ ] [Saga](https://docs.microsoft.com/en-us/azure/architecture/reference-architectures/saga/saga)

    * Performance and scalability
        - [x] [Cache-Aside](https://docs.microsoft.com/en-us/azure/architecture/patterns/cache-aside)
        - [ ] [Choreography](https://docs.microsoft.com/en-us/azure/architecture/patterns/choreography)
        - [x] [Command and Query Responsibility Segregation (CQRS)](https://docs.microsoft.com/en-us/azure/architecture/patterns/cqrs)
        - [x] [Event Sourcing](https://docs.microsoft.com/en-us/azure/architecture/patterns/event-sourcing)
        - [x] [Deployment Stamps](https://docs.microsoft.com/en-us/azure/architecture/patterns/deployment-stamp)
        - [x] [Geodes](https://docs.microsoft.com/en-us/azure/architecture/patterns/geodes)
        - [x] [Index Table](https://docs.microsoft.com/en-us/azure/architecture/patterns/index-table)
        - [x] [Materialized View](https://docs.microsoft.com/en-us/azure/architecture/patterns/materialized-view)
        - [x] [Priority Queue](https://docs.microsoft.com/en-us/azure/architecture/patterns/priority-queue)
        - [x] [Queue-Based Load Leveling](https://docs.microsoft.com/en-us/azure/architecture/patterns/queue-based-load-leveling)
        - [x] [Sharding](https://docs.microsoft.com/en-us/azure/architecture/patterns/sharding)
        - [x] [Static Content Hosting](https://docs.microsoft.com/en-us/azure/architecture/patterns/static-content-hosting)
        - [x] [Throttling](https://docs.microsoft.com/en-us/azure/architecture/patterns/throttling)

    * Availability
        - [ ] [Deployment Stamps](https://docs.microsoft.com/en-us/azure/architecture/patterns/deployment-stamp)
        - [ ] [Geodes](https://docs.microsoft.com/en-us/azure/architecture/patterns/geodes)
        - [ ] [Health Endpoint Monitoring](https://docs.microsoft.com/en-us/azure/architecture/patterns/health-endpoint-monitoring)
        - [ ] [Queue-Based Load Leveling](https://docs.microsoft.com/en-us/azure/architecture/patterns/queue-based-load-leveling)
        - [ ] [Throttling](https://docs.microsoft.com/en-us/azure/architecture/patterns/throttling)

    * Resiliency
        - [ ] [Bulkhead](https://docs.microsoft.com/en-us/azure/architecture/patterns/bulkhead)
        - [ ] [Circuit Breaker](https://docs.microsoft.com/en-us/azure/architecture/patterns/circuit-breaker)
        - [ ] [Compensating Transaction](https://docs.microsoft.com/en-us/azure/architecture/patterns/compensating-transaction)
        - [x] [Health Endpoint Monitoring](https://docs.microsoft.com/en-us/azure/architecture/patterns/health-endpoint-monitoring)
        - [x] [Leader Election](https://docs.microsoft.com/en-us/azure/architecture/patterns/leader-election)
        - [x] [Queue-Based Load Leveling](https://docs.microsoft.com/en-us/azure/architecture/patterns/queue-based-load-leveling)
        - [ ] [Retry](https://docs.microsoft.com/en-us/azure/architecture/patterns/retry)
        - [ ] [Scheduler Agent Supervisor](https://docs.microsoft.com/en-us/azure/architecture/patterns/scheduler-agent-supervisor)

    * Security
        - [ ] [Federated Identity](https://docs.microsoft.com/en-us/azure/architecture/patterns/federated-identity)
        - [ ] [Gatekeeper](https://docs.microsoft.com/en-us/azure/architecture/patterns/gatekeeper)
        - [x] [Valet Key](https://docs.microsoft.com/en-us/azure/architecture/patterns/valet-key)

    </details>

- [ ] [AWS Cloud Pattern](http://en.clouddesignpattern.org/index.php/Main_Page)
- [ ] [Google: Design patterns for container-based distributed systems.pdf](https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/45406.pdf)
- [ ] [A pattern language for microservices](https://microservices.io/patterns/index.html)
- [ ] [SOA Patterns](https://patterns.arcitura.com/soa-patterns)

### Failure testing of distributed systems

### Scalability
- [ ] [4 Architecture Issues When Scaling Web Applications: Bottlenecks, Database, CPU, IO](http://highscalability.com/blog/2014/5/12/4-architecture-issues-when-scaling-web-applications-bottlene.html)
- [ ] [Scaling Stateful Objects](http://ithare.com/scaling-stateful-objects/)
- [ ] [Scale Up vs Scale Out: Hidden Costs](https://blog.codinghorror.com/scaling-up-vs-scaling-out-hidden-costs/)
- [ ] [Best Practices for Scaling Out](https://www.infoq.cn/article/hiXg6WRDjvNE0VNuwzPg)
- [ ] [Scalability Worst Practices](https://www.infoq.com/articles/scalability-worst-practices)
- [ ] [Reddit: Lessons Learned From Mistakes Made Scaling To 1 Billion Pageviews A Month](http://highscalability.com/blog/2013/8/26/reddit-lessons-learned-from-mistakes-made-scaling-to-1-billi.html)
- [ ] [Autoscaling Pinterest](https://medium.com/@Pinterest_Engineering/auto-scaling-pinterest-df1d2beb4d64)
- [ ] [Square: Autoscaling Based on Request Queuing](https://medium.com/square-corner-blog/autoscaling-based-on-request-queuing-c4c0f57f860f)
- [ ] [PayPal: Autoscaling Applications](https://medium.com/paypal-engineering/autoscaling-applications-paypal-fb5bb9fdb821)
- [ ] [Trivago: Your Definite Guide For Autoscaling Jenkins](http://tech.trivago.com/2017/02/17/your-definite-guide-for-autoscaling-jenkins/)
- [ ] [Scryer: Netflix’s Predictive Auto Scaling Engine](https://netflixtechblog.com/scryer-netflixs-predictive-auto-scaling-engine-a3f8fc922270)

### Consistent Hashing
- [ ] [Consistent Hashing](http://tom-e-white.com/2007/11/consistent-hashing.html)
- [ ] [Consistent Hashing: Algorithmic Tradeoffs](https://medium.com/@dgryski/consistent-hashing-algorithmic-tradeoffs-ef6b8e2fcae8)
- [ ] [Distributing Content to Open Connect](https://medium.com/netflix-techblog/distributing-content-to-open-connect-3e3e391d4dc9)
- [ ] [Consistent Hashing in Cassandra](https://blog.imaginea.com/consistent-hashing-in-cassandra/)

### Distributed Database
- [ ] [Life Beyond Distributed Transactions](https://queue.acm.org/detail.cfm?id=3025012)
- [ ] [How Sharding Works](https://medium.com/@jeeyoungk/how-sharding-works-b4dec46b3f6)
- [ ] [Why you don’t want to shard](https://www.percona.com/blog/2009/08/06/why-you-dont-want-to-shard/)
- [ ] [How to Scale Big Data Applications.pdf](https://www.percona.com/sites/default/files/presentations/How%20to%20Scale%20Big%20Data%20Applications.pdf)
- [ ] [MySQL Sharding with ProxySQL](https://www.percona.com/blog/2016/08/30/mysql-sharding-with-proxysql/)

### Cache
- [ ] [Cache update routine (CN)](https://coolshell.cn/articles/17416.html)
- [ ] [Design Of A Modern Cache](http://highscalability.com/blog/2016/1/25/design-of-a-modern-cache.html)
- [ ] [Netflix: Caching for a Global Netflix](https://netflixtechblog.com/caching-for-a-global-netflix-7bcc457012f1)
- [ ] [Facebook: An analysis of Facebook photo caching](https://engineering.fb.com/2014/02/20/web/an-analysis-of-facebook-photo-caching/)
- [ ] [How trivago Reduced Memcached Memory Usage by 50%](https://tech.trivago.com/2017/12/19/how-trivago-reduced-memcached-memory-usage-by-50/)
- [ ] [Caching Internal Service Calls at Yelp](https://engineeringblog.yelp.com/2018/03/caching-internal-service-calls-at-yelp.html)

### Message Queue
- [ ] [Understanding When to use RabbitMQ or Apache Kafka](https://tanzu.vmware.com/developer/blog/understanding-the-differences-between-rabbitmq-vs-kafka/)
- [ ] [Trello: Why We Chose Kafka For The Trello Socket Architecture](https://tech.trello.com/why-we-chose-kafka/)
- [ ] [LinkedIn: Running Kafka At Scale](https://engineering.linkedin.com/kafka/running-kafka-scale)
- [ ] [Should You Put Several Event Types in the Same Kafka Topic](https://www.confluent.io/blog/put-several-event-types-kafka-topic/)
- [ ] [Billions of Messages a Day - Yelp’s Real-time Data Pipeline](https://engineeringblog.yelp.com/2016/07/billions-of-messages-a-day-yelps-real-time-data-pipeline.html)
- [ ] [Uber: Building Reliable Reprocessing and Dead Letter Queues with Kafka](https://eng.uber.com/reliable-reprocessing/)
- [ ] [Uber: Introducing Chaperone: How Uber Engineering Audits Kafka End-to-End](https://eng.uber.com/chaperone-audit-kafka-messages/)
- [ ] [Uber: Uber’s Real-Time Push Platform](https://eng.uber.com/real-time-push-platform/)
- [ ] [Publishing with Apache Kafka at The New York Times](https://open.nytimes.com/publishing-with-apache-kafka-at-the-new-york-times-7f0e3b7d2077)
- [ ] [Kafka Streams on Heroku](https://blog.heroku.com/kafka-streams-on-heroku)
- [ ] [Salesforce: How Apache Kafka Inspired Our Platform Events Architecture](https://engineering.salesforce.com/how-apache-kafka-inspired-our-platform-events-architecture-2f351fe4cf63)
- [ ] [Exactly-once Semantics are Possible: Here’s How Kafka Does it](https://www.confluent.io/blog/exactly-once-semantics-are-possible-heres-how-apache-kafka-does-it/)
- [ ] [Delivering billions of messages exactly once](https://segment.com/blog/exactly-once-delivery/)
- [ ] [Benchmarking Streaming Computation Engines at Yahoo!](https://yahooeng.tumblr.com/post/135321837876/benchmarking-streaming-computation-engines-at)

### Log
- [ ] [Using Logs to Build a Solid Data Infrastructure - Martin Kleppmann](https://www.confluent.io/blog/using-logs-to-build-a-solid-data-infrastructure-or-why-dual-writes-are-a-bad-idea/)
- [ ] [Building DistributedLog: High-performance replicated log service](https://blog.twitter.com/engineering/en_us/topics/infrastructure/2015/building-distributedlog-twitter-s-high-performance-replicated-log-servic.html)
- [ ] [LogDevice: a distributed data store for logs](https://engineering.fb.com/2017/08/31/core-data/logdevice-a-distributed-data-store-for-logs/)

### Performance
- [ ] [Understand Latency](http://highscalability.com/latency-everywhere-and-it-costs-you-sales-how-crush-it)
- [ ] [Common Bottlenecks](http://highscalability.com/blog/2012/5/16/big-list-of-20-common-bottlenecks.html)
- [ ] [Performance is a Feature](https://blog.codinghorror.com/performance-is-a-feature/)
- [ ] [Make Performance Part of Your Workflow](https://codeascraft.com/2014/12/11/make-performance-part-of-your-workflow/)  :orange_book: [Designing for Performance](https://learning.oreilly.com/library/view/designing-for-performance/9781491903704/)
- [ ] [CloudFlare: How we built rate limiting capable of scaling to millions of domains](https://blog.cloudflare.com/counting-things-a-lot-of-different-things/)

### Search
- [ ] [Instagram: Search Architecture](https://instagram-engineering.com/search-architecture-eeb34a936d3a)
- [ ] [eBay: The Architecture of eBay Search.pdf](http://www.cs.otago.ac.nz/homepages/andrew/papers/2017-8.pdf)
- [ ] [eBay: Improving Search Engine Efficiency by over 25%](https://tech.ebayinc.com/research/making-e-commerce-search-faster/)
- [ ] [LinkedIn: Introducing LinkedIn’s new search architecture](https://engineering.linkedin.com/search/did-you-mean-galene)
- [ ] [LinkedIn: Search Federation Architecture at LinkedIn](https://engineering.linkedin.com/blog/2018/03/search-federation-architecture-at-linkedin)
- [ ] [Slack: Search at Slack](https://slack.engineering/search-at-slack/)
- [ ] [DoorDash: Search and Recommendations at DoorDash](https://medium.com/@DoorDash/powering-search-recommendations-at-doordash-8310c5cfd88c)
- [ ] [Twitter: Building a complete Tweet index](https://blog.twitter.com/engineering/en_us/a/2014/building-a-complete-tweet-index.html)
- [ ] [Pinterest: Manas: High Performing Customized Search System](https://medium.com/pinterest-engineering/manas-a-high-performing-customized-search-system-cf189f6ca40f)
- [ ] [Sherlock: Near Real Time Search Indexing at Flipkart](https://tech.flipkart.com/sherlock-near-real-time-search-indexing-95519783859d)
- [ ] [Airbnb: Nebula: Storage Platform to Build Search Backends](https://medium.com/airbnb-engineering/nebula-as-a-storage-platform-to-build-airbnbs-search-backends-ecc577b05f06)

### Architecture Practices by Companies
- [ ] [YouTube Architecture](http://highscalability.com/youtube-architecture)
- [ ] [Scaling Pinterest](http://highscalability.com/blog/2013/4/15/scaling-pinterest-from-0-to-10s-of-billions-of-page-views-a.html)
- [ ] [Google Architecture](http://highscalability.com/google-architecture)
- [ ] [Scaling Twitter](http://highscalability.com/scaling-twitter-making-twitter-10000-percent-faster)
- [ ] [The WhatsApp Architecture](http://highscalability.com/blog/2014/2/26/the-whatsapp-architecture-facebook-bought-for-19-billion.html)
- [ ] [Flickr Architecture](http://highscalability.com/flickr-architecture)
- [ ] [Amazon Architecture](http://highscalability.com/amazon-architecture)
- [ ] [Stack Overflow Architecture](http://highscalability.com/blog/2009/8/5/stack-overflow-architecture.html)
- [ ] [Pinterest Architecture](http://highscalability.com/blog/2012/5/21/pinterest-architecture-update-18-million-visitors-10x-growth.html)
- [ ] [Tumblr Architecture](http://highscalability.com/blog/2012/2/13/tumblr-architecture-15-billion-page-views-a-month-and-harder.html)
- [ ] [Instagram Architecture](http://highscalability.com/blog/2011/12/6/instagram-architecture-14-million-users-terabytes-of-photos.html)
- [ ] [TripAdvisor Architecture](http://highscalability.com/blog/2011/6/27/tripadvisor-architecture-40m-visitors-200m-dynamic-page-view.html)
- [ ] [Scaling Mailbox](http://highscalability.com/blog/2013/6/18/scaling-mailbox-from-0-to-one-million-users-in-6-weeks-and-1.html)
- [ ] [Salesforce Architecture](http://highscalability.com/blog/2013/9/23/salesforce-architecture-how-they-handle-13-billion-transacti.html)
- [ ] [ESPN's Architecture At Scale - Operating At 100,000 Duh Nuh Nuhs Per Second](http://highscalability.com/blog/2013/11/4/espns-architecture-at-scale-operating-at-100000-duh-nuh-nuhs.html)
- [ ] [Uber Architecture](http://highscalability.com/blog/2013/9/23/salesforce-architecture-how-they-handle-13-billion-transacti.html)
- [ ] [Dropbox Design](https://www.youtube.com/watch?v=PE4gwstWhmc)
- [ ] [Splunk Architecture](https://www.splunk.com/en_us/software/splunk-enterprise.html)


# Microservice
- [ ] [Martin Fowler: Microservices Guide](https://martinfowler.com/microservices/)
- [ ] [Martin Fowler: Microservice Architecture](https://martinfowler.com/articles/microservices.html)

- [ ] [AWS: What are Microservices?](https://aws.amazon.com/microservices/)
- [ ] [Microsoft: Microservices architecture style](https://docs.microsoft.com/en-us/azure/architecture/guide/architecture-styles/microservices)
- [ ] [Pivotal: Microservices](https://tanzu.vmware.com/microservices)
- [ ] [Uber: Introducing Domain-Oriented Microservice Architecture](https://eng.uber.com/microservice-architecture/)
- [ ] [Uber: Designing Edge Gateway, Uber’s API Lifecycle Management Platform](https://eng.uber.com/gatewayuberapi/)
- [ ] [Microservice Architecture](https://microservices.io)

- [ ] :orange_book: [IBM: Microservices Best Practices for Java.pdf](https://www.redbooks.ibm.com/redbooks/pdfs/sg248357.pdf)
- [ ] :orange_book: [Building MicroService](https://www.amazon.com/Building-Microservices-Designing-Fine-Grained-Systems/dp/1491950358/ref=sr_1_2?crid=LWHLL3P5PIT6&dchild=1&keywords=building+microservices&qid=1610330674&sprefix=building+micros%2Caps%2C390&sr=8-2)

- [ ] [Google: API Improvement Proposals](https://google.aip.dev)

* Nginx
    - [x] [Introduction to Microservices](https://www.nginx.com/blog/introduction-to-microservices/)
    - [x] [Building Microservices: Using an API Gateway](https://www.nginx.com/blog/building-microservices-using-an-api-gateway/)
    - [ ] [Building Microservices: Inter-Process Communication in a Microservices Architecture](https://www.nginx.com/blog/building-microservices-using-an-api-gateway/)
    - [ ] [Service Discovery in a Microservices Architecture](https://www.nginx.com/blog/building-microservices-using-an-api-gateway/)
    - [ ] [Event-Driven Data Management for Microservices](https://www.nginx.com/blog/event-driven-data-management-microservices/)
    - [ ] [Choosing a Microservices Deployment Strategy](https://www.nginx.com/blog/deploying-microservices/)
    - [ ] [Refactoring a Monolith into Microservices](https://www.nginx.com/blog/refactoring-a-monolith-into-microservices/)

* Auto0 Blog
    - [ ] [An Introduction to Microservices, Part 1](https://auth0.com/blog/an-introduction-to-microservices-part-1/)
    - [ ] [API Gateway. An Introduction to Microservices, Part 2](https://auth0.com/blog/an-introduction-to-microservices-part-2-API-gateway/)
    - [ ] [An Introduction to Microservices, Part 3: The Service Registry](https://auth0.com/blog/an-introduction-to-microservices-part-3-the-service-registry/)
    - [ ] [Intro to Microservices, Part 4: Dependencies and Data Sharing](https://auth0.com/blog/apigateway-microservices-superglue/)
    - [ ] [API Gateway: the Microservices Superglue](https://auth0.com/blog/apigateway-microservices-superglue/)

## API Gatway
- [ ] [Kubernetes api gateway](https://k8s-it.medium.com/kubernetes-api-gateway-cac310589f4d)

## Microservice VS SOA, IaaS, Paas, Monolithic
- [ ] :orange_book: [Microservices vs. Service-Oriented Architecture](https://www.nginx.com/resources/library/microservices-vs-soa/)
- [ ] [DZone: Microservices vs. SOA](https://dzone.com/articles/microservices-vs-soa-2)
- [ ] [DZone: Microservices vs. SOA - Is There Any Difference at All?](https://dzone.com/articles/microservices-vs-soa-is-there-any-difference-at-al)
- [ ] [Microservices, SOA, and APIs: Friends or enemies?](https://www.ibm.com/cloud/learn/microservices)

- [ ] [PaaS vs. IaaS for Microservices Architectures: Top 6 Differences](https://www.altoros.com/blog/paas-vs-iaas-for-microservices-architectures-top-6-differences/)
- [ ] [Microservices vs. Monolithic Architectures: Pros, Cons, and How Cloud Foundry (PaaS) Can Help](https://www.slideshare.net/altoros/microservices-vs-monolithic-architectures-pros-and-cons)
- [ ] [Microservices - Not A Free Lunch!](http://highscalability.com/blog/2014/4/8/microservices-not-a-free-lunch.html)
- [ ] [The Hidden Costs Of Microservices](https://www.stackbuilders.com/news/the-hidden-costs-of-microservices)

## Practice
* Mircroservcie with Spring-Boot
    - [ ] [Part 1 - Getting Started with Microservices Architecture](http://www.springboottutorial.com/creating-microservices-with-spring-boot-part-1-getting-started)
    - [ ] [Part 2 - Creating Forex Microservice](http://www.springboottutorial.com/creating-microservices-with-spring-boot-part-2-forex-microservice)
    - [ ] [Part 3 - Creating Currency Conversion Microservice](http://www.springboottutorial.com/creating-microservices-with-spring-boot-part-3-currency-conversion-microservice)
    - [ ] [Part 4 - Using Ribbon for Load Balancing](http://www.springboottutorial.com/microservices-with-spring-boot-part-4-ribbon-for-load-balancing)
    - [ ] [Part 5 - Using Eureka Naming Server](http://www.springboottutorial.com/microservices-with-spring-boot-part-5-eureka-naming-server)

- [ ] [The Hidden Costs Of Microservices](https://www.stackbuilders.com/news/the-hidden-costs-of-microservices)
- [ ] [Microservice Architecture (https://microservices.io)](https://microservices.io)
- [ ] [Microservice Antipatterns and Pitfalls](https://www.oreilly.com/content/microservices-antipatterns-and-pitfalls/)
- [ ] [Microservice Architecture: All The Best Practices You Need To Kno](https://codingsans.com/blog/microservice-architecture-best-practices)
- [ ] [Best Practices for Building a Microservice Architecture](https://www.vinaysahni.com/best-practices-for-building-a-microservice-architecture)
- [ ] [Simplicity by Distributing Complexity](https://engineering.zalando.com/posts/2018/01/simplicity-by-distributing-complexity.html)
- [ ] [Effective Microservices: 10 Best Practices](https://towardsdatascience.com/effective-microservices-10-best-practices-c6e4ba0c6ee2)

## Authentication & Authorization
- [ ] [ForgeRock: Identity Gateway](https://backstage.forgerock.com/docs/ig/7/gateway-guide/index.html#preface)
- [ ] [ForgeRock: Token Validation Microservice](https://backstage.forgerock.com/docs/tvm/1/user-guide/)
- [ ] [Bringing Token state consistency to the Edge](https://charan-mann.medium.com/bringing-token-state-consistency-to-the-edge-eeaffc911b08)

## Design Pattern
- [ ] [Microservice Architecture and its 10 Most Important Design Patterns](https://towardsdatascience.com/microservice-architecture-and-its-10-most-important-design-patterns-824952d7fa41)
    * `Database per Microservice`  `Event Sourcing` `CQRS` `Saga` `BFF` `API Gateway` `Strangler` `Circuit Breaker` `Externalize Configuration` `Consumer-Driven Contract Testing`
- [ ] [Modularity and Information Hiding.pdf](https://www.win.tue.nl/~wstomv/edu/2ip30/references/criteria_for_modularization.pdf)
- [ ] [Separation of Concern](https://www.cs.utexas.edu/users/EWD/transcriptions/EWD04xx/EWD447.html)
- [ ] [Service Oriented Architecture](https://en.wikipedia.org/wiki/Service-oriented_architecture)

# Thanks
This roadmap is highly inspired by course: https://time.geekbang.org/column/intro/48. Thanks [Hao Chen](https://github.com/haoel).