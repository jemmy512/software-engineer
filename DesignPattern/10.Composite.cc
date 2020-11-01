#include <iostream>
#include <set>
#include <string>

class FileSystemNode {
public:
    FileSystemNode(const std::string& path) : mPath(path) {}

    virtual void ls(const std::string& parentPath = "") = 0;

    virtual ~FileSystemNode() = default;

    std::string getPath() {
        return mPath;
    }

protected:
    std::string mPath;
};

using FileSystemNodeSP = std::shared_ptr<FileSystemNode>;

class File : public FileSystemNode {
public:
    File(const std::string& path) : FileSystemNode(path) {}

    void ls(const std::string& parentPath) override {
        std::cout << parentPath + mPath << std::endl;
    }
};

class Directory : public FileSystemNode {
public:
    Directory(const std::string& path) : FileSystemNode(path) {}

    void addSubDirectory(std::initializer_list<std::string> subDirectories) {
        for (const auto& directory : subDirectories) {
            mSubDirectories.emplace(std::make_shared<Directory>(directory));
        }
    }

    void addSubDirectory(FileSystemNodeSP subDirectory) {
            mSubDirectories.emplace(subDirectory);
    }

    void ls(const std::string& parentPath) override {
        if (mSubDirectories.size() == 0) {
            std::cout << parentPath + mPath << std::endl;
        }

        for (const auto& directory: mSubDirectories) {
            directory->ls(parentPath + mPath);
        }
    }

private:
    std::function<bool(const FileSystemNodeSP&, const FileSystemNodeSP&)> comparator =
    [](const FileSystemNodeSP& lhs, const FileSystemNodeSP& rhs) {
        return lhs->getPath() < rhs->getPath();
    };

    std::set<FileSystemNodeSP, decltype(comparator)> mSubDirectories{comparator};
};

int main() {
    auto usr = std::make_shared<Directory>("/usr");
    auto jemmy = std::make_shared<Directory>("/jemmy");
    auto home = std::make_shared<Directory>("/home");
    auto code = std::make_shared<Directory>("/code");

    auto redis = std::make_shared<File>("/Redis.cc");
    auto ngix = std::make_shared<File>("/Ngix.cc");
    auto tomcat = std::make_shared<File>("/Tomcat.cc");

    code->addSubDirectory(redis);
    code->addSubDirectory(ngix);
    code->addSubDirectory(tomcat);

    home->addSubDirectory(code);
    jemmy->addSubDirectory(home);
    usr->addSubDirectory(jemmy);
    usr->addSubDirectory({"/1", "/2", "/3", "/4"});
    jemmy->addSubDirectory({"/lib", "/bin", "/local", "/share"});

    std::dynamic_pointer_cast<FileSystemNode>(usr)->ls();

    return 0;
}

/**
 * Definition:
 * Compose objects into tree structure to represent the part-whole hirarchies.
 * Composite lets client treat the individual objects and compositions of
 * objects uniformly.
 */