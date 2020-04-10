#include <iostream>
#include <string>

class ResourcePoolConfig;

class ResourcePoolBuilder {
public:
    using Ptr = std::shared_ptr<ResourcePoolBuilder>;

    friend class ResourcePoolConfig;

    std::shared_ptr<ResourcePoolConfig> build() {
        if (mMaxIdle > mMaxTotal || mMinIdle > mMaxIdle) {
            throw std::invalid_argument("Max Idle < Max Total");
        }

        return std::make_shared<ResourcePoolConfig>(*this);
    }

    ResourcePoolBuilder& setName(const std::string& name) {
        if (name.empty()) {
            throw std::invalid_argument("Name is invalid");
        }

        mName = name;

        return *this;
    }

    ResourcePoolBuilder& setMaxTotal(int total) {
        if (total < 1) {
            throw std::invalid_argument("Max Total > 0");
        }

        mMaxTotal = total;

        return *this;
    }

    ResourcePoolBuilder& setMaxIdle(int idle) {
        if (idle < 1) {
            throw std::invalid_argument("Max Idle > 0");
        }

        mMaxIdle = idle;

        return *this;
    }

    ResourcePoolBuilder& setMinIdle(int idle) {
        if (idle < 0) {
            throw std::invalid_argument("Min Idle >= 0");
        }

        mMinIdle = idle;

        return *this;
    }

private:
    constexpr static int DefaultMaxTotal = 8;
    constexpr static int DefaultMaxIdle = 8;
    constexpr static int DefaultMinIdle = 0;

    std::string mName;
    int mMaxTotal{DefaultMaxTotal};
    int mMaxIdle{DefaultMaxIdle};
    int mMinIdle{DefaultMinIdle};
};

class ResourcePoolConfig {
public:
    ResourcePoolConfig(const ResourcePoolBuilder& builder)
    :   mName(builder.mName),
        mMaxTotal(builder.mMaxTotal),
        mMaxIdle(builder.mMaxIdle),
        mMinIdle(builder.mMinIdle)
    { }

    void toString() {
        std::cout << "Config Name: " << mName << "\nMax Total: " << mMaxTotal << "\nMax Idle: " << mMaxIdle << "\nMin Idle: " << mMinIdle << std::endl;  
    }

private:
    std::string mName;
    int mMaxTotal;
    int mMaxIdle;
    int mMinIdle;
};

int main() {
    auto builder = std::make_shared<ResourcePoolBuilder>();
    auto config = builder->setName(std::string("DbPoolConfig"))
        .setMaxTotal(10)
        .setMaxIdle(9)
        .setMinIdle(3)
        .build();

    config->toString();

    return 0;
}

/*
Use:
1. There are many paramters in the contrcutor. Some are mandatory, some are optional. 
    It's error-prone to use the constructor with many parameters.
2. The parameters has some relationship. With set method, relationship can't validate.
3. We hope to new a const object

Difference with Factory pattern:
1. Factory create different but related types of objects dentermined by given parameters.
2. Builder create the same type but complex object which is customized by different parameters.
*/