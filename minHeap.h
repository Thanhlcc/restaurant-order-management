//
// Created by LAPTOP on 4/30/2023.
//

#ifndef HUFFMAN_CODING_TREE_MINHEAP_H
#define HUFFMAN_CODING_TREE_MINHEAP_H
#include <algorithm>
#include <vector>
template <typename T, typename C>
class MinHeap
{
private:
    using node_t = std::pair<T, int>; // store the payload along with an index
    std::vector<node_t> heap;
    int capacity;
    int current_timestamp;
    friend class LFCO;

public:
    explicit MinHeap(int cap = 100)
    {
        capacity = cap;
        current_timestamp = 0;
    }
    void reserve(int &cap)
    {
        heap.reserve(cap);
    }
    MinHeap(const std::vector<T> &samp, const int &cap)
    {
        capacity = cap;
        assert(samp.size() <= cap);
        current_timestamp = 0;
        for (auto item : samp)
        {
            heap.push_back({item, current_timestamp});
        }
        current_timestamp++;
        std::make_heap(heap.begin(), heap.end(), C());
    }
    void add(const T &ele)
    {
        heap.push_back({ele, current_timestamp++});
        std::push_heap(heap.begin(), heap.end(), C());
    }

    // remove root element
    T remove()
    {
        std::pop_heap(heap.begin(), heap.end(), C());
        node_t root = heap.back();
        heap.pop_back();
        return root.first;
    }
    // remove an arbitrary element
    T remove(T sample)
    {
        auto it = heap.begin();
        for (; it != heap.end(); it++)
        {
            if (it->first == sample)
            {
                break;
            }
        }
        assert(it != heap.end());
        T returnValue = it->first;
        *it = heap.back();
        heap.pop_back();
        std::make_heap(heap.begin(), heap.end(), C());
        return returnValue;
    }
    int size() const
    {
        return heap.size();
    }
    void update() {
        std::make_heap(heap.begin(), heap.end(), C());
    }
    T getMin() const {
        return heap.front().first;
    }
};
#endif //HUFFMAN_CODING_TREE_MINHEAP_H
