
class BitMap {
public:
    BitMap(int size) : Size(size), Bytes(new char[size/8 + 1]) { }

    ~BitMap() {
        if (Bytes) {
            delete[] Bytes;
        }
    }

    void set(int k) {
        if (k < Size) {
            int byteIndex = k / 8;
            int bitIndex = k % 8;

            Bytes[byteIndex] |= (1 << bitIndex);
        }
    }

    bool get (int k) const {
        if (k > Size)
            return false;

        int byteIndex = k / 8;
        int bitIndex = k % 8;

        return (Bytes[byteIndex] & (1 << bitIndex));
    }

private:
    char* const Bytes;
    const int Size;
};