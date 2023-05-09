//
// Created by LAPTOP on 4/23/2023.
//

#ifndef HUFFMAN_CODING_TREE_HUFFMANTREE_H
#define HUFFMAN_CODING_TREE_HUFFMANTREE_H
#include "main.h"

template <typename T>
class HuffNode
{
public:
    virtual ~HuffNode() = default;
    virtual int weight() = 0;
    virtual bool isLeaf() = 0;
};

template <typename T>
class LeafNode : public HuffNode<T>
{
private:
    int wgt;
    char letter;

public:
    LeafNode(char ltr, int _weight){
        wgt = _weight;
        letter = ltr;
    }
    bool isLeaf() override { return true; }
    int weight() override { return wgt; }
    char val() const { return letter; }
};

template <typename T>
class IntlNode : public HuffNode<T>
{
private:
    int wgt;
    HuffNode<T> *lc;
    HuffNode<T> *rc;

public:
    explicit IntlNode(HuffNode<T> *left, HuffNode<T> *right)
    {
        lc = left;
        rc = right;
        wgt = lc->weight() + rc->weight();
    }
    ~IntlNode()
    {
        if (lc)
        {
            delete lc;
            lc = nullptr;
        }
        if (rc)
        {
            delete rc;
            rc = nullptr;
        }
    }
    bool isLeaf() override { return (!lc && !rc); }
    int weight() override { return wgt; }
    HuffNode<T> *left() { return lc; }
    HuffNode<T> *right() { return rc; }
    void setLeft(HuffNode<T> *leftChild) { lc = leftChild; }
    void setRight(HuffNode<T> *rightChild) { rc = rightChild; }
};

template <typename T>
class HuffTree
{
public:
    class GreaterFreq_comp;

private:
    HuffNode<T> *rt;

public:
    HuffTree(T val, int freq)
    {
        rt = new LeafNode<T>(val, freq);
    }
    HuffTree(HuffTree<T> *left, HuffTree<T> *right)
    {
        rt = new IntlNode<T>(left->root(), right->root());
    }
    HuffNode<T> *root() const { return rt; }
    int weight() const { return rt->weight(); }
    static void generate(HuffNode<T> *_root, std::unordered_map<T, std::string> &codec, std::string _code)
    {
        if (_root == nullptr)
            return;

        if (_root->isLeaf())
        {

            codec.insert({((LeafNode<char> *)_root)->val(), _code});
        }
        else
        {
            generate(((IntlNode<T> *)_root)->left(), codec, _code + '0');
            generate(((IntlNode<T> *)_root)->right(), codec, _code + '1');
        }
    }

    static HuffTree<T> *buildHuff(MinHeap<HuffTree<T> *, typename HuffTree<T>::GreaterFreq_comp> &freqHeap)
    {
//            ofstream outfile("./logHuffman/poppedHeap.txt");
        HuffTree<char> *fst, *snd, *thrd = nullptr;
        while (freqHeap.size() > 1)
        {
            fst = freqHeap.remove();
            snd = freqHeap.remove();
//                outfile << (fst->root()->isLeaf() ? ((LeafNode<char>*)fst->root())->val() : ' ') << fst->root()->weight() <<"\t";
//                outfile << (snd->root()->isLeaf() ? ((LeafNode<char>*)snd->root())->val() : ' ') << snd->root()->weight() <<"\n";
            thrd = new HuffTree<char>(fst, snd);
            delete fst;
            delete snd;
            freqHeap.add(thrd);
        }
//            outfile.close();
        return thrd;
    }
    static void clear(HuffTree<T> *r)
    {
        clearTree(r->rt);
        r->rt = nullptr;
    }
    // Util to clear the tree after encoding a name
    static HuffNode<T> *clearTree(HuffNode<T> *r)
    {
        if (r == nullptr)
            return nullptr;
        if (!r->isLeaf())
        {
            ((IntlNode<T> *)r)->setLeft(clearTree(((IntlNode<T> *)r)->left()));
            ((IntlNode<T> *)r)->setRight(clearTree(((IntlNode<T> *)r)->right()));
        }
        delete r;
        return nullptr;
    }

public:
    class GreaterFreq_comp
    {
    public:
        using node_t = std::pair<HuffTree *, int>;
        bool operator()(const node_t &fst, const node_t &snd)
        {
            HuffTree<T> *fstVal = fst.first;
            HuffTree<T> *sndVal = snd.first;
            if (fstVal->weight() == sndVal->weight())
            {
                if (fstVal->root()->isLeaf() && sndVal->root()->isLeaf())
                {
                    return ((LeafNode<T> *)fstVal->root())->val() > ((LeafNode<T> *)sndVal->root())->val();
                }
                else
                {
                    // The second para should come before its child if it came before
                    return fst.second > snd.second;
                }
            }
            return fstVal->weight() > sndVal->weight();
        }
    };
};
#endif //HUFFMAN_CODING_TREE_HUFFMANTREE_H
