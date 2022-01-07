/* Created by Jemmy on 2018/8/20.
 * https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170 */

#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

class String{
    friend ostream& operator<<(ostream&, const String&);
    friend istream& operator>>(istream&, const String&);

public:
    String() = default;

    String(const char* str) {
        if (str) {
            Size = strlen(str);
            Buf = new char[Size + 1];
            strcpy(Buf, str);
        }
    }

    String(const String& other) {
        if (other.Buf) {
            Size = other.size();
            Buf = new char[Size + 1];
            strcpy(Buf, other.Buf);
        }
    }

    String(String&& other) noexcept {
        Size = other.size();
        Buf = other.Buf;

        other.reset();
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] Buf;
            if (other.Buf) {
                Size = other.size();
                Buf = new char[Size + 1];
                strcpy(Buf, other.Buf);
            } else {
                reset();
            }
        }

        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] Buf;

            Size = other.size();
            Buf = other.Buf;

            other.reset();
        }

        return *this;
    }

    String operator+(const String& other) {
        String newString;

        if (!other.Buf) {
            newString = *this;
        } else if (!Buf) {
            newString = other;
        } else {
            newString.Size = size() + other.size();
            newString.Buf = new char[newString.size() + 1];
            strcpy(newString.Buf, Buf);
            strcat(newString.Buf, other.Buf);
        }

        return newString;
    }

    char& operator[](unsigned int pos) {
        if (pos >= 0 && pos <= size()) {
            return Buf[pos];
        }

        throw std::out_of_range(std::to_string(pos) + " out of range [0, " + std::to_string(size()) + "}");
    }

    bool operator==(const String& other) {
        if (size() != other.size())
            return false;
        return strcmp(Buf, other.Buf) ? false : true;
    }

    size_t size() const {
        return Size;
    }

    ~String() {
        if (Buf != nullptr) {
            delete[] Buf;
            reset();
        }
    }

private:
    void reset() {
        Size = 0;
        Buf = nullptr;
    }

private:
    std::size_t Size = 0;
    char *Buf = nullptr;
};

ostream& operator<<(ostream &os, const String& str) {
    os << str.Buf;
    return os;
}

istream& operator>>(istream &is, const String& str) {
    is >> str.Buf;
    return is;
}

int main() {
    String str("hello world");
    cout << str << endl;
    String ss;
    ss = str;
    ss = ss + " Ni hao";
    ss[0] = 'A';
    ss = std::move(ss);
    str = std::move(str);
    cout << str << endl;
}