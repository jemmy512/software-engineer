#include <iostream>
#include <vector>

struct HttpRequset {

};

struct HttpResponse {

};

class IFilter {
public:
    virtual bool doFilter(HttpRequset& req, HttpResponse& resp) = 0;
    virtual ~IFilter() = default;
};

using FilterPtr = std::shared_ptr<IFilter>;

class FilterChain {
public:
    void registerFilter(const FilterPtr& filter) {
        mFilters.emplace_back(filter);
    }

    void doFilter(HttpRequset& req, HttpResponse& resp) {
        for (const auto& filter : mFilters) {
            filter->doFilter(req, resp);
        }
    }

private:
    std::vector<FilterPtr> mFilters;
};

int main() {

    return 0;
}

/**
 * Avoid coupling the sender of a request to its receiver by giving more than one object
 * a chance to handle the request. Chain the receiving objects and pass the request
 * along the chain until an object handles it. */