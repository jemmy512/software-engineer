#include <iostream>

class InputStream {
public:
    virtual void read() {

    }
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