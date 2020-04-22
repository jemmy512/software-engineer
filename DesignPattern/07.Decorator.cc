#include <iostream>

class InputStream {
public:
    virtual void read() {

    }

    virtual ~InputStream() = default;
};

class FileInputStream : public InputStream {
public:
    void read() override {

    }
};


class BufferedInputStream : public InputStream {
public:
    BufferedInputStream(InputStream&& istream)
    :   mInputStream(istream)
    {}

    void read() override {
        mInputStream.read();

        // do something about buffered input stream
    }

private:
    InputStream mInputStream;
};

class DataInputStream : public InputStream {
public:
    DataInputStream(InputStream&& istream)
    : mInputStream(istream)
    {}

    void read() override {
        mInputStream.read();

        // do something about data input stream
    }

private:
    InputStream mInputStream;
};

int main() {

    return 0;
}

/**
 * The decorator pattern maily solves the complication problem of the inheritance relationship,
 * and replaces inheritance through combination. It's main role is to add enhancements to the original class.
 *
 * You can nest mutiple decorator classes to the original class, this requires the decorator classes need to
 * inherit the same interface with the original class. */