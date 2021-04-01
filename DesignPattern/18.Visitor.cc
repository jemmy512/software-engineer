/* Author: Jemmy
 * Date: 2020-04-08 */

#include <iostream>
#include <vector>
#include <string>

class PdfFile;
using PdfFilePtr = std::shared_ptr<PdfFile>;

class PptFile;
using PptFilePtr = std::shared_ptr<PptFile>;

class WordFile;
using WordFilePtr = std::shared_ptr<WordFile>;

#define Pln(x) std::cout << x << std::endl;

class Visitor {
public:
    virtual void visit(const PdfFilePtr& file) { }

    virtual void visit(const PptFilePtr& file) { }

    virtual void visit(const WordFilePtr& file) { }

    virtual ~Visitor() = default;
};

using VisitorPtr = std::shared_ptr<Visitor>;


class Compressor : public Visitor {
public:
    void visit(const PdfFilePtr& file) override {
        Pln("compress pdf file");
    }

    void visit(const PptFilePtr& file) override {
        Pln("compress ppt file");
    }

    void visit(const WordFilePtr& file) override {
        Pln("compress word file");
    }
};

class Extractor : public Visitor {
public:
    void visit(const PdfFilePtr& file) override {
        Pln("extract pdf file");
    }

    void visit(const PptFilePtr& file) override {
        Pln("extract ppt file");
    }

    void visit(const WordFilePtr& file) override {
        Pln("extract word file");
    }
};




class File {
public:
    File(const std::string& filePath) : mFilePath(filePath) {}

    virtual void accept(VisitorPtr visitor) = 0;
    virtual ~File() = default;

private:
    std::string mFilePath;
};

using FilePtr = std::shared_ptr<File>;

class PdfFile : public File, public std::enable_shared_from_this<PdfFile> {
public:
    PdfFile(const std::string& file) : File(file) { }

    void accept(VisitorPtr visitor) override {
        visitor->visit(shared_from_this());
    }
};

class PptFile : public File, public std::enable_shared_from_this<PptFile>  {
public:
    PptFile(const std::string& file) : File(file) { }

    void accept(VisitorPtr visitor) override {
        visitor->visit(shared_from_this());
    }
};

class WordFile : public File, public std::enable_shared_from_this<WordFile>  {
public:
    WordFile(const std::string& file) : File(file) { }

    void accept(VisitorPtr visitor) override {
        visitor->visit(shared_from_this());
    }
};

int main() {
    std::vector<FilePtr> vec {
        std::make_shared<PdfFile>("a.pdf"),
        std::make_shared<PptFile>("b.ppt"),
        std::make_shared<WordFile>("c.word")
    };

    auto extractor = std::make_shared<Extractor>();
    auto compressor = std::make_shared<Compressor>();

    for (const auto& file : vec) {
        file->accept(extractor);
        file->accept(compressor);
    }

    return 0;
}

/**
 * Allows for one or more operation to be applied to a set of objects at runtime,
 * decoupling the operations from the object structure. */

/**
 * The visitor pattern aims at a group of objects inherited the same parent class,
 * or implement the same interface.
 *
 * In different application scenarios, we need to perform a group of unrelated operations on this group of objects,
 * to avoid frequent code changes and classes are not single responsibility, we decouple the objects and
 * operations, extract those operations into separate subdivided classes. */