#include <iostream>
#include <string>
#include <vector>
#include <map>

struct SearchWord {
    std::string mKey;
    std::string mValue;
    long long mTime;
};

class Search {
public:
    void refresh() {
        // newData = mData.clone(); 
        HashMap newData{mData}; 

        auto updatedData = getSearchWorksFromDB(mLastTime);
        for (auto& word : updatedData) {
            newData.try_emplace(mHash(word.mKey), std::make_shared<SearchWord>(word));
        }

        mData = newData;
    };

private:
    void init() {
        auto words = getSearchWorksFromDB(0);
        for (auto& word : words) {
            if (word.mTime > mLastTime) {
                mLastTime = word.mTime;
            }

            mData.emplace(mHash(word.mKey), std::make_shared<SearchWord>(word));
        }
    }

    std::vector<SearchWord> getSearchWorksFromDB(long long time) {

        return std::vector<SearchWord>{};
    }

private:
    long long mLastTime;
    std::hash<std::string> mHash;
    using HashMap = std::map<std::size_t, std::shared_ptr<SearchWord>>;
    HashMap mData;
};

int main() {
    
    return 0;
}