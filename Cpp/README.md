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
    virtual ~Base() = defaul`t;

    virtual void FuncB() {  }

    int a;
    int b;
};

struct BaseA : virtual public Base {
    virtual ~BaseA() = default;

    virtual void FuncB() {  }

    int a;
    int b;
};

struct BaseB : virtual public Base {
    virtual ~BaseB() = default;

    virtual void FuncC() {  }

    int a;
    int b;
};

struct Derive : public BaseB, public BaseA {
    void FuncB() override {  }
    void FuncC() override {  }
};

int main() {
    BaseA a;
    Derive d;
    return 0;
}
```
```c++
Vtable for 'Derive' (20 entries).
   0 | vbase_offset (32)
   1 | offset_to_top (0)
   2 | Derive RTTI
       -- (BaseB, 0) vtable address --
       -- (Derive, 0) vtable address --
   3 | Derive::~Derive() [complete]
   4 | Derive::~Derive() [deleting]
   5 | void Derive::FuncC()
   6 | void Derive::FuncB()
   7 | vbase_offset (16)
   8 | offset_to_top (-16)
   9 | Derive RTTI
       -- (BaseA, 16) vtable address --
  10 | Derive::~Derive() [complete]
       [this adjustment: -16 non-virtual] method: BaseA::~BaseA()
  11 | Derive::~Derive() [deleting]
       [this adjustment: -16 non-virtual] method: BaseA::~BaseA()
  12 | void Derive::FuncB()
       [this adjustment: -16 non-virtual] method: void BaseA::FuncB()
  13 | vcall_offset (-32)
  14 | vcall_offset (-32)
  15 | offset_to_top (-32)
  16 | Derive RTTI
       -- (Base, 32) vtable address --
  17 | Derive::~Derive() [complete]
       [this adjustment: 0 non-virtual, -24 vcall offset offset] method: Base::~Base()
  18 | Derive::~Derive() [deleting]
       [this adjustment: 0 non-virtual, -24 vcall offset offset] method: Base::~Base()
  19 | void Derive::FuncB()
       [this adjustment: 0 non-virtual, -32 vcall offset offset] method: void Base::FuncB()

Virtual base offset offsets for 'Derive' (1 entry).
   Base | -24

Thunks for 'Derive::~Derive()' (2 entries).
   0 | this adjustment: -16 non-virtual
   1 | this adjustment: 0 non-virtual, -24 vcall offset offset

Thunks for 'void Derive::FuncB()' (2 entries).
   0 | this adjustment: -16 non-virtual
   1 | this adjustment: 0 non-virtual, -32 vcall offset offset

VTable indices for 'Derive' (4 entries).
   0 | Derive::~Derive() [complete]
   1 | Derive::~Derive() [deleting]
   2 | void Derive::FuncC()
   3 | void Derive::FuncB()
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