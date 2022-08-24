* [C++](#c)
   * [OOP](#oop)
      * [VTable Layout](#layout)

* [STL](#stl)
   * [Build Commands](#build-commands)
   * [shared_ptr](#sharedptr)
   * [malloc](#gcc)

* [IPC](#ipc)

# C++
## OOP
### Layout
```c++
g++ -fdump-class-hierarchy layout.cc
clang -Xclang -fdump-record-layouts -stdlib=libc++ -std=c++17 -c layout.cc
clang -Xclang -fdump-vtable-layouts -stdlib=libc++ -std=c++17 -c layout.cc
```

```c++
// layout.cc
struct Base {
   virtual ~Base() = default;

   virtual void FnBase() {  }

   int a;
   int b;
};

struct BaseA : virtual public Base {
   virtual void FnBaseA() {  }

   int a;
   int b;
};

struct BaseB : virtual public Base {
   virtual void FnBaseB() {  }

   int a;
   int b;
};

struct Derive : public BaseB, public BaseA {
   void FnBase() override {  }
   void FnBaseA() override {  }
   void FnBaseB() override {  }
};

int main() {
   Derive d;
   return 0;
}
```
```c++
Vtable for 'Derive' (21 entries).
   0 | vbase_offset (32)
   1 | offset_to_top (0)
   2 | Derive RTTI
       -- (BaseB, 0) vtable address --
       -- (Derive, 0) vtable address --
   3 | void Derive::FnBaseB()
   4 | Derive::~Derive() [complete]
   5 | Derive::~Derive() [deleting]
   6 | void Derive::FnBase()
   7 | void Derive::FnBaseA()
   8 | vbase_offset (16)
   9 | offset_to_top (-16)
  10 | Derive RTTI
       -- (BaseA, 16) vtable address --
  11 | void Derive::FnBaseA()
       [this adjustment: -16 non-virtual] method: void BaseA::FnBaseA()
  12 | Derive::~Derive() [complete]
       [this adjustment: -16 non-virtual] method: BaseA::~BaseA()
  13 | Derive::~Derive() [deleting]
       [this adjustment: -16 non-virtual] method: BaseA::~BaseA()
  14 | vcall_offset (-32)
  15 | vcall_offset (-32)
  16 | offset_to_top (-32)
  17 | Derive RTTI
       -- (Base, 32) vtable address --
  18 | Derive::~Derive() [complete]
       [this adjustment: 0 non-virtual, -24 vcall offset offset] method: Base::~Base()
  19 | Derive::~Derive() [deleting]
       [this adjustment: 0 non-virtual, -24 vcall offset offset] method: Base::~Base()
  20 | void Derive::FnBase()
       [this adjustment: 0 non-virtual, -32 vcall offset offset] method: void Base::FnBase()

Virtual base offset offsets for 'Derive' (1 entry).
   Base | -24

Thunks for 'Derive::~Derive()' (2 entries).
   0 | this adjustment: -16 non-virtual
   1 | this adjustment: 0 non-virtual, -24 vcall offset offset

Thunks for 'void Derive::FnBase()' (1 entry).
   0 | this adjustment: 0 non-virtual, -32 vcall offset offset

Thunks for 'void Derive::FnBaseA()' (1 entry).
   0 | this adjustment: -16 non-virtual

VTable indices for 'Derive' (5 entries).
   0 | void Derive::FnBaseB()
   1 | Derive::~Derive() [complete]
   2 | Derive::~Derive() [deleting]
   3 | void Derive::FnBase()
   4 | void Derive::FnBaseA()
```

```c++
*** Dumping AST Record Layout
         0 | struct Derive
         0 |   struct BaseB (primary base)
         0 |     (BaseB vtable pointer)
         8 |     int a
        12 |     int b
        16 |   struct BaseA (base)
        16 |     (BaseA vtable pointer)
        24 |     int a
        28 |     int b
        32 |   struct Base (virtual base)
        32 |     (Base vtable pointer)
        40 |     int a
        44 |     int b
           | [sizeof=48, dsize=48, align=8,
           |  nvsize=32, nvalign=8]
```
![](https://github.com/Jemmy512/book-notes/blob/master/Images/cpp-virtual-inheritance.png)
     * BaseA has its own virtual `FunB`, Derive overrides it and adds it into vtable of both BaseA and BaseB.

```c++
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $64, %rsp
        movl    $0, -4(%rbp)
        leaq    -56(%rbp), %rdi
        callq   Derive::Derive() [complete object constructor]
        movl    $0, -4(%rbp)
        leaq    -56(%rbp), %rdi
        callq   Derive::~Derive() [complete object destructor]
        movl    -4(%rbp), %eax
        addq    $64, %rsp
        popq    %rbp
        retq
Derive::Derive() [complete object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -16(%rbp)         # 8-byte Spill derive_this
        addq    $32, %rdi               # base_this = derive_this + 32
        callq   Base::Base() [base object constructor]
        movq    -16(%rbp), %rdi         # 8-byte Reload derive_this
        movabsq $VTT for Derive, %rsi
        addq    $8, %rsi
        callq   BaseB::BaseB() [base object constructor]
        movq    -16(%rbp), %rdi
        addq    $16, %rdi               # baseA_this = derive_this + 16
        movabsq $VTT for Derive, %rsi
        addq    $24, %rsi
        callq   BaseA::BaseA() [base object constructor]
        movq    -16(%rbp), %rax
        movabsq $vtable for Derive, %rcx
        addq    $24, %rcx
        movq    %rcx, (%rax)            # derive_vptr = vtable + 24
        movabsq $vtable for Derive, %rcx
        addq    $144, %rcx
        movq    %rcx, 32(%rax)          # base_vptr = vtable + 144
        movabsq $vtable for Derive, %rcx
        addq    $88, %rcx
        movq    %rcx, 16(%rax)          # baseA_vptr = vtable + 88
        addq    $16, %rsp
        popq    %rbp
        retq
Derive::~Derive() [complete object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -16(%rbp)
        movabsq $VTT for Derive, %rsi
        callq   Derive::~Derive() [base object destructor]
        movq    -16(%rbp), %rdi
        addq    $32, %rdi
        callq   Base::~Base() [base object destructor]
        addq    $16, %rsp
        popq    %rbp
        retq
Base::Base() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movabsq $vtable for Base, %rcx
        addq    $16, %rcx
        movq    %rcx, (%rax)
        popq    %rbp
        retq
BaseB::BaseB() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    %rsi, -16(%rbp)
        movq    -8(%rbp), %rax
        movq    -16(%rbp), %rcx
        movq    (%rcx), %rdx
        movq    %rdx, (%rax)
        movq    8(%rcx), %rdx
        movq    (%rax), %rcx
        movq    -24(%rcx), %rcx
        movq    %rdx, (%rax,%rcx)
        popq    %rbp
        retq
BaseA::BaseA() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    %rsi, -16(%rbp)
        movq    -8(%rbp), %rax
        movq    -16(%rbp), %rcx
        movq    (%rcx), %rdx
        movq    %rdx, (%rax)
        movq    8(%rcx), %rdx
        movq    (%rax), %rcx
        movq    -24(%rcx), %rcx
        movq    %rdx, (%rax,%rcx)
        popq    %rbp
        retq
BaseB::FnBaseB():
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        popq    %rbp
        retq
BaseB::~BaseB() [complete object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -16(%rbp)
        movabsq $VTT for BaseB, %rsi
        callq   BaseB::~BaseB() [base object destructor]
        movq    -16(%rbp), %rdi
        addq    $16, %rdi
        callq   Base::~Base() [base object destructor]
        addq    $16, %rsp
        popq    %rbp
        retq
BaseB::~BaseB() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -16(%rbp)
        callq   BaseB::~BaseB() [complete object destructor]
        movq    -16(%rbp), %rdi
        callq   operator delete(void*)
        addq    $16, %rsp
        popq    %rbp
        retq
virtual thunk to BaseB::~BaseB() [complete object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    (%rdi), %rax
        movq    -24(%rax), %rax
        addq    %rax, %rdi
        popq    %rbp
        jmp     BaseB::~BaseB() [complete object destructor]
virtual thunk to BaseB::~BaseB() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    (%rdi), %rax
        movq    -24(%rax), %rax
        addq    %rax, %rdi
        popq    %rbp
        jmp     BaseB::~BaseB() [deleting destructor]
Base::FnBase():
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        popq    %rbp
        retq
BaseA::FnBaseA():
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        popq    %rbp
        retq
BaseA::~BaseA() [complete object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -16(%rbp)
        movabsq $VTT for BaseA, %rsi
        callq   BaseA::~BaseA() [base object destructor]
        movq    -16(%rbp), %rdi
        addq    $16, %rdi
        callq   Base::~Base() [base object destructor]
        addq    $16, %rsp
        popq    %rbp
        retq
BaseA::~BaseA() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -16(%rbp)
        callq   BaseA::~BaseA() [complete object destructor]
        movq    -16(%rbp), %rdi
        callq   operator delete(void*)
        addq    $16, %rsp
        popq    %rbp
        retq
virtual thunk to BaseA::~BaseA() [complete object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    (%rdi), %rax
        movq    -24(%rax), %rax
        addq    %rax, %rdi
        popq    %rbp
        jmp     BaseA::~BaseA() [complete object destructor]
virtual thunk to BaseA::~BaseA() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    (%rdi), %rax
        movq    -24(%rax), %rax
        addq    %rax, %rdi
        popq    %rbp
        jmp     BaseA::~BaseA() [deleting destructor]
Derive::FnBaseB():
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        popq    %rbp
        retq
Derive::~Derive() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -16(%rbp)
        callq   Derive::~Derive() [complete object destructor]
        movq    -16(%rbp), %rdi
        callq   operator delete(void*)
        addq    $16, %rsp
        popq    %rbp
        retq
Derive::FnBase():
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        popq    %rbp
        retq
Derive::FnBaseA():
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        popq    %rbp
        retq
non-virtual thunk to Derive::FnBaseA():
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        addq    $-16, %rdi
        popq    %rbp
        jmp     Derive::FnBaseA()
non-virtual thunk to Derive::~Derive() [complete object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        addq    $-16, %rdi
        popq    %rbp
        jmp     Derive::~Derive() [complete object destructor]
non-virtual thunk to Derive::~Derive() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        addq    $-16, %rdi
        popq    %rbp
        jmp     Derive::~Derive() [deleting destructor]
virtual thunk to Derive::~Derive() [complete object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    (%rdi), %rax
        movq    -24(%rax), %rax
        addq    %rax, %rdi
        popq    %rbp
        jmp     Derive::~Derive() [complete object destructor]
virtual thunk to Derive::~Derive() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    (%rdi), %rax
        movq    -24(%rax), %rax
        addq    %rax, %rdi
        popq    %rbp
        jmp     Derive::~Derive() [deleting destructor]
virtual thunk to Derive::FnBase():
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    (%rdi), %rax
        movq    -32(%rax), %rax
        addq    %rax, %rdi
        popq    %rbp
        jmp     Derive::FnBase()
Base::~Base() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        popq    %rbp
        retq
Base::~Base() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -16(%rbp)
        callq   Base::~Base() [base object destructor]
        movq    -16(%rbp), %rdi
        callq   operator delete(void*)
        addq    $16, %rsp
        popq    %rbp
        retq
BaseB::~BaseB() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    %rsi, -16(%rbp)
        popq    %rbp
        retq
BaseA::~BaseA() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movq    %rsi, -16(%rbp)
        popq    %rbp
        retq
Derive::~Derive() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $32, %rsp
        movq    %rdi, -8(%rbp)
        movq    %rsi, -16(%rbp)
        movq    -8(%rbp), %rdi
        movq    %rdi, -32(%rbp)
        movq    -16(%rbp), %rsi
        movq    %rsi, -24(%rbp)
        addq    $16, %rdi
        addq    $24, %rsi
        callq   BaseA::~BaseA() [base object destructor]
        movq    -32(%rbp), %rdi
        movq    -24(%rbp), %rsi
        addq    $8, %rsi
        callq   BaseB::~BaseB() [base object destructor]
        addq    $32, %rsp
        popq    %rbp
        retq
vtable for Derive:
        .quad   32
        .quad   0
        .quad   typeinfo for Derive
        .quad   Derive::FnBaseB()
        .quad   Derive::~Derive() [complete object destructor]
        .quad   Derive::~Derive() [deleting destructor]
        .quad   Derive::FnBase()
        .quad   Derive::FnBaseA()
        .quad   16
        .quad   -16
        .quad   typeinfo for Derive
        .quad   non-virtual thunk to Derive::FnBaseA()
        .quad   non-virtual thunk to Derive::~Derive() [complete object destructor]
        .quad   non-virtual thunk to Derive::~Derive() [deleting destructor]
        .quad   -32
        .quad   -32
        .quad   -32
        .quad   typeinfo for Derive
        .quad   virtual thunk to Derive::~Derive() [complete object destructor]
        .quad   virtual thunk to Derive::~Derive() [deleting destructor]
        .quad   virtual thunk to Derive::FnBase()

VTT for Derive:
        .quad   vtable for Derive+24
        .quad   construction vtable for BaseB-in-Derive+24
        .quad   construction vtable for BaseB-in-Derive+80
        .quad   construction vtable for BaseA-in-Derive+24
        .quad   construction vtable for BaseA-in-Derive+80
        .quad   vtable for Derive+144
        .quad   vtable for Derive+88

construction vtable for BaseB-in-Derive:
        .quad   32
        .quad   0
        .quad   typeinfo for BaseB
        .quad   BaseB::FnBaseB()
        .quad   BaseB::~BaseB() [complete object destructor]
        .quad   BaseB::~BaseB() [deleting destructor]
        .quad   0
        .quad   -32
        .quad   -32
        .quad   typeinfo for BaseB
        .quad   virtual thunk to BaseB::~BaseB() [complete object destructor]
        .quad   virtual thunk to BaseB::~BaseB() [deleting destructor]
        .quad   Base::FnBase()

typeinfo name for BaseB:
        .asciz  "5BaseB"

typeinfo name for Base:
        .asciz  "4Base"

typeinfo for Base:
        .quad   vtable for __cxxabiv1::__class_type_info+16
        .quad   typeinfo name for Base

typeinfo for BaseB:
        .quad   vtable for __cxxabiv1::__vmi_class_type_info+16
        .quad   typeinfo name for BaseB
        .long   0                               # 0x0
        .long   1                               # 0x1
        .quad   typeinfo for Base
        .quad   -6141                           # 0xffffffffffffe803

construction vtable for BaseA-in-Derive:
        .quad   16
        .quad   0
        .quad   typeinfo for BaseA
        .quad   BaseA::FnBaseA()
        .quad   BaseA::~BaseA() [complete object destructor]
        .quad   BaseA::~BaseA() [deleting destructor]
        .quad   0
        .quad   -16
        .quad   -16
        .quad   typeinfo for BaseA
        .quad   virtual thunk to BaseA::~BaseA() [complete object destructor]
        .quad   virtual thunk to BaseA::~BaseA() [deleting destructor]
        .quad   Base::FnBase()

typeinfo name for BaseA:
        .asciz  "5BaseA"

typeinfo for BaseA:
        .quad   vtable for __cxxabiv1::__vmi_class_type_info+16
        .quad   typeinfo name for BaseA
        .long   0                               # 0x0
        .long   1                               # 0x1
        .quad   typeinfo for Base
        .quad   -6141                           # 0xffffffffffffe803

typeinfo name for Derive:
        .asciz  "6Derive"

typeinfo for Derive:
        .quad   vtable for __cxxabiv1::__vmi_class_type_info+16
        .quad   typeinfo name for Derive
        .long   2                               # 0x2
        .long   2                               # 0x2
        .quad   typeinfo for BaseB
        .quad   2                               # 0x2
        .quad   typeinfo for BaseA
        .quad   4098                            # 0x1002

vtable for Base:
        .quad   0
        .quad   typeinfo for Base
        .quad   Base::~Base() [base object destructor]
        .quad   Base::~Base() [deleting destructor]
        .quad   Base::FnBase()

vtable for BaseB:
        .quad   16
        .quad   0
        .quad   typeinfo for BaseB
        .quad   BaseB::FnBaseB()
        .quad   BaseB::~BaseB() [complete object destructor]
        .quad   BaseB::~BaseB() [deleting destructor]
        .quad   0
        .quad   -16
        .quad   -16
        .quad   typeinfo for BaseB
        .quad   virtual thunk to BaseB::~BaseB() [complete object destructor]
        .quad   virtual thunk to BaseB::~BaseB() [deleting destructor]
        .quad   Base::FnBase()

VTT for BaseB:
        .quad   vtable for BaseB+24
        .quad   vtable for BaseB+80

vtable for BaseA:
        .quad   16
        .quad   0
        .quad   typeinfo for BaseA
        .quad   BaseA::FnBaseA()
        .quad   BaseA::~BaseA() [complete object destructor]
        .quad   BaseA::~BaseA() [deleting destructor]
        .quad   0
        .quad   -16
        .quad   -16
        .quad   typeinfo for BaseA
        .quad   virtual thunk to BaseA::~BaseA() [complete object destructor]
        .quad   virtual thunk to BaseA::~BaseA() [deleting destructor]
        .quad   Base::FnBase()

VTT for BaseA:
        .quad   vtable for BaseA+24
        .quad   vtable for BaseA+80
```

# STL

## Build Commands
```c++
/* 1. Preprocess
 * runs the C preprocessor (cpp),
 * which translates the C source file main.c into an ASCII intermediate file main.i: */

cpp [other arguments] main.c /tmp/main.i


/* 2. Compile
 * runs the C compiler (cc1), which translates main.i into an ASCII assembly language file main.s. */

cc1 /tmp/main.i main.c -O2 [other arguments] -o /tmp/main.s


/* 3. Assembly
 * runs the assembler (as), which translates main.s into a relocatable object file main.o: */

as [other arguments] -o /tmp/main.o /tmp/main.s

/* 4. Link
 * it runs the linker program ld, which combines main.o and swap.o,
 * along with the necessary system object files, to create the executable object file p: */

ld -o p [system object files and args] /tmp/main.o /tmp/swap.o
```

```c++
// static link
gcc -c addvec.c multvec.c
ar rcs libvector.a addvec.o multvec.o
gcc -O2 -c main2.c
gcc -static -o p2 main2.o ./libvector.a
```

```c++
// dynamic link
gcc -shared -fPIC -o libvector.so addvec.c multvec.c
gcc -o p2 main2.c ./libvector.so
```

## shared_ptr
* ![gcc-shared-ptr.png](./STL/gcc-shared-ptr.png)
* [Gcc source code](./STL/shared-ptr-gcc.md)

## GCC
* [GCC: new allocator malloc](../OpenSource/new-allocator-malloc.md)

# IPC

![](./Images/ipc.png)