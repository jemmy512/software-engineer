#include <iostream>

/* Approach 1: traditional decorator */
namespace std {
class IStream {
public:
    virtual void read() {

    }

    virtual ~IStream() = default;
};

class FileInputStream : public IStream {
public:
    void read() override {

    }
};


class BufferedInputStream : public IStream {
public:
    BufferedInputStream(IStream&& istream)
    :   mInputStream(istream)
    {}

    void read() override {
        mInputStream.read();

        // do something about buffered input stream
    }

private:
    IStream mInputStream;
};

class DataInputStream : public IStream {
public:
    DataInputStream(IStream&& istream)
    : mInputStream(istream)
    {}

    void read() override {
        mInputStream.read();

        // do something about data input stream
    }

private:
    IStream mInputStream;
};
} // namespace std;


/* Approach 2: decorator with CRTP, mixin classe
 * advantage: compile time polymorphism, avoid overhead of virtual function calls */
namespace crtp {
template<typename Stream> // Stream must be a derived class type
class FileInputStream : public Stream {
public:
    FileInputStream(cosnt Stream& stream) : Stream(stream) {}

    void read() {
        static_cast<Stream*>(this)->read();
        // do something about file input stream
    }
};

template<typename Stream>
class BufferedInputStream : public Stream {
public:
    BufferedInputStream(const Stream& stream) : Stream(stream) {}

    void read() {
        static_cast<Stream*>(this)->read();
        // do something about buffered input stream
    }
};
} // namespace crtp

int main() {

    return 0;
}

/**
 * The decorator pattern maily reduces the complexity of the inheritance relationship,
 * and replaces inheritance through combination. It's main role is to add enhancements to the original class.
 *
 * You can nest mutiple decorator classes to the original class, this requires the decorator classes need to
 * inherit the same interface with the original class. */