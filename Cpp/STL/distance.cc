#include<iostream>
#include<iterator>
#include<array>
#include<vector>
#include<algorithm>

using namespace std;

template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
_distance(Iterator pos1, Iterator pos2, std::output_iterator_tag) {
    return pos2 - pos1;
}

template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
_distance(Iterator pos1, Iterator pos2, std::input_iterator_tag) {
    return pos2 - pos1;
}

template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
_distance(Iterator pos1, Iterator pos2, std::bidirectional_iterator_tag) {
    return pos2 - pos1;
}

template<typename Iterator>
typename std::iterator_traits<Iterator>::differece_type
_distance(Iterator pos1, Iterator pos2, std::forward_iterator_tag) {
    return pos2 - pos1;
}

template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
_distance(Iterator pos1, Iterator pos2, std::random_access_iterator_tag) {
    return pos2 - pos1;
}

template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
_distance(Iterator pos1, Iterator pos2) {
    return _distance(pos1 ,pos2, typename std::iterator_traits<Iterator>::iterator_category());
}

int main(void) {
    
    vector<int> arr = {1, 2, 3, 4, 5};
    auto pos = find(arr.begin(), arr.end(), 4);
    cout << "distance of arr: " << _distance(arr.begin(), pos) << endl;
   
    return 0;
}
