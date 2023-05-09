#ifndef HUFFMAN_CODING_TREE_MAIN_H
#define HUFFMAN_CODING_TREE_MAIN_H
#include <bits/stdc++.h>
#include "minHeap.h"
#include "huffmanTree.h"

using namespace std;
using Tree = HuffTree<char>;

#define MAXSIZE 32

/*
 *----------------------------Restaurant-related structures----------------------
 */

class Customer
{
public:
    string original_name;
    int code;
    int table_id;
    int section;
    int slot;
    int noOrders;
    //---------------------------------------------------------
    explicit Customer(string name)
    {
        this->original_name = name;
        code = name.length() > 1 ? getResult(name) : 1;
        table_id = -1;
        slot = -1;
        section = -1;
        noOrders = 1;
    }
    static int encode(std::unordered_map<char, std::string> &lookupTable, const std::string &ref)
    {
        string result;
        for (auto i : ref)
        {
            result += lookupTable[i];
        }
        if (result.size() > 15)
        {
            result = result.substr(result.size() - 15);
        }
        bitset<15> result_int(result);
        return int(result_int.to_ulong());
    }

    static int getResult(const string &name)
    {
//            ofstream outfile("./logHuffman/"+ name + ".txt", std::ios::app);
        std::map<char, int> freqMap;
        for (auto i : name)
        {
            if (freqMap.find(i) != freqMap.end())
            {
                freqMap[i]++;
            }
            else
            {
                freqMap.insert({i, 1});
            }
        }
//            outfile << "Name: " << name << endl;
//            for(auto item : freqMap){
//                outfile << item.first << ": " << item.second << "\n";
//            }
        MinHeap<HuffTree<char> *, HuffTree<char>::GreaterFreq_comp> freqTable;
        for (auto i : freqMap)
        {
            // Create leaf nodes
            freqTable.add(new HuffTree<char>(i.first, i.second));
        }
        HuffTree<char> *codingTree = HuffTree<char>::buildHuff(freqTable);

        std::unordered_map<char, string> codings;
        HuffTree<char>::generate(codingTree->root(), codings, string());
//            outfile << "Code map:\n";
//            for(auto item : codings){
//                outfile << item.first << ": " << item.second << "\n";
//            }
        // Clear the internal content of huffman tree
        HuffTree<char>::clear(codingTree);
        // Clear the tree itself
        delete codingTree;
        int code = encode(codings, name);
//            outfile << "Huffman code: " << code << "\n";
//            outfile.close();
        return code;
    }
};

class Section
{
public:
    virtual ~Section() = default;
    virtual void addCus(Customer *newone) {}
    virtual void removeCus(Customer *tab) {}
    virtual bool isFull() const { return false; }
    virtual void clear() = 0;
    virtual void print() const = 0;
};

class Section1 : public Section
{
private:
    Customer **slots;
    int capacity;
    int size;

public:
    explicit Section1(int _capacity)
    {
        capacity = _capacity;
        slots = new Customer *[capacity];
        for (int i = 0; i < _capacity; i++)
        {
            slots[i] = nullptr;
        }
        size = 0;
    }
    ~Section1()
    {
        delete[] slots;
    }
    void addCus(Customer *newone) override
    {
        // The section must have free slot to start insertion
        assert(size++ < capacity);
        // Define the home slot
        newone->slot = linear_probing(newone->code);
        slots[newone->slot] = newone;
    }

    void removeCus(Customer *customer) override
    {
        // The section must have at least one customer to delete
        assert(size--);
        slots[customer->slot] = nullptr;
    }

    bool isFull() const override
    {
        return (capacity == size);
    }
    void clear() override
    {
        for (int i = 0; i < capacity; i++)
        {
            slots[i] = nullptr;
        }
    }
    void print() const override
    {
        for (int i = 0; i < capacity; i++)
        {
            if (slots[i] != nullptr)
            {
                std::cout << slots[i]->table_id << "-"
                          << slots[i]->code << "-" << slots[i]->noOrders <<"\n";
            }
        }
    }

protected: // Utils
    int linear_probing(const int &code) const
    {
        int slot = code % capacity;
        while (slots[slot] != nullptr)
        {
            slot = (slot + 1) % capacity;
        }
        return slot;
    }
};

class Section2 : public Section
{
public:
    class Node;
    enum BalanceValue
    {
        LH = -1,
        EH = 0,
        RH = 1
    };

private:
    Node *root;
    int size;
    int capacity;

public:
    explicit Section2(int _capacity)
    {
        capacity = _capacity;
        size = 0;
        root = nullptr;
    }
    ~Section2()
    {
        clear(this->root);
    }
    void addCus(Customer *newone) override
    {
        assert(size++ < capacity);
        this->root = insert(this->root, newone);
        newone->slot = -1;
    }

    void removeCus(Customer *tab) override
    {
        assert(size--);
        this->root = remove(this->root, tab);
    }
    bool isFull() const override
    {
        return (size == capacity);
    }
    void clear() override
    {
        clear(this->root);
        root = nullptr;
        size = 0;
    }
    void print() const override
    {
        if (root)
        {
            std::queue<Node *> buffer;
            Node *curr = nullptr;
            buffer.push(root);
            while (!buffer.empty())
            {
                curr = buffer.front();
                cout << curr->data->table_id << "-" << curr->data->code << "-" <<curr->data->noOrders<<"\n";
                if (curr->pLeft)
                    buffer.push(curr->pLeft);
                if (curr->pRight)
                    buffer.push(curr->pRight);
                buffer.pop();
            }
        }
    }

protected:
    int height(Node *node)
    {
        if (node == nullptr)
            return 0;
        int lh = this->height(node->pLeft);
        int rh = this->height(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
    Node *insert(Node *r, Customer *newone)
    {
        if (!r)
        {
            if (!this->root)
            {
                this->root = new Node(newone);
                return this->root;
            }
            return new Node(newone);
        }
        if (newone->code >= r->data->code)
        {
            r->pRight = insert(r->pRight, newone);
        }
        else
        {
            r->pLeft = insert(r->pLeft, newone);
        }
        return rebalance(r);
    }
    Node *left_left_rotate(Node *r)
    {
        Node *tmp = r;
        r = r->pLeft;
        tmp->pLeft = r->pRight;
        r->pRight = tmp;
        return r;
    }

    Node *right_right_rotate(Node *r)
    {
        Node *tmp = r;
        r = r->pRight;
        tmp->pRight = r->pLeft;
        r->pLeft = tmp;
        return r;
    }

    Node *left_right_rotate(Node *r)
    {
        Node *tmp = r;

        r = r->pLeft->pRight;
        tmp->pLeft->pRight = r->pLeft;
        r->pLeft = tmp->pLeft;
        tmp->pLeft = r->pRight;
        r->pRight = tmp;
        return r;
    }

    Node *right_left_rotate(Node *r)
    {
        Node *tmp = r;

        r = r->pRight->pLeft;
        tmp->pRight->pLeft = r->pRight;
        r->pRight = tmp->pRight;
        tmp->pRight = r->pLeft;
        r->pLeft = tmp;
        return r;
    }

    Node *remove(Node *r, Customer *newone)
    {
        if (!r)
        {
            return nullptr;
        }
        int valCode = newone->code;
        int rtCode = r->data->code;
        if (valCode > rtCode)
        {
            r->pRight = remove(r->pRight, newone);
        }
        else if (valCode < rtCode)
        {
            r->pLeft = remove(r->pLeft, newone);
        }
        else
        {
            Node *tmp = r;
            if (!r->pLeft)
            {
                r = r->pRight;
                delete tmp;
            }
            else if (!r->pRight)
            {
                r = r->pLeft;
                delete tmp;
            }
            else
            {
                Node *min = getMin(r->pRight);
                r->data = min->data;
                r->pRight = deleteMin(r->pRight);
                delete min;
            }
        }
        return rebalance(r);
    }

    Node *getMin(Node *r)
    {
        while (r && r->pLeft)
        {
            r = r->pLeft;
        }
        return r;
    }

    Node *deleteMin(Node *r)
    {
        if (!r->pLeft)
        {
            return r->pRight;
        }
        else
        {
            r->pLeft = deleteMin(r->pLeft);
            return r;
        }
    }

    Node *rebalance(Node *r)
    {
        if (!r)
            return nullptr;
        r->pLeft = rebalance(r->pLeft);
        r->pRight = rebalance(r->pRight);
        int bf = height(r->pRight) - height(r->pLeft);
        if (bf < int(LH))
        {
            if (r->pLeft->balance > 0)
            {
                r = left_right_rotate(r);
            }
            else
            {
                r = left_left_rotate(r);
            }
            // Update the balance after rotation
            r->balance = (BalanceValue)(height(r->pRight) - height(r->pLeft));
        }
        else if (bf > int(RH))
        {
            if (r->pRight->balance < 0)
            {
                r = right_left_rotate(r);
            }
            else
            {
                r = right_right_rotate(r);
            }
            // Update the balance after rotation
            r->balance = (BalanceValue)(height(r->pRight) - height(r->pLeft));
        }
        return r;
    }

    Node *clear(Node *r)
    {
        if (r)
        {
            if (r->pLeft)
                clear(r->pLeft);
            if (r->pRight)
                clear(r->pRight);
            delete r;
        }
        return nullptr;
    }

public:
    class Node
    {
    private:
        Customer *data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class Section2;

    public:
        explicit Node(Customer *value) : data(value), pLeft(nullptr), pRight(nullptr), balance(EH) {}
        ~Node() = default;
    };
};

class Log
{
public:
    virtual ~Log() = default;
    virtual void add(Customer *customer) = 0;
    virtual void update(Customer *customer) {}
    virtual void remove(Customer *customer) = 0;
    virtual void removeMany(int section_id) = 0;
    virtual Customer *getReplacedCus() = 0;
};

class FIFO : public Log
{
private:
    deque<Customer *> customers;

public:
    ~FIFO()
    {
        for (int i = 0; i < (int)customers.size(); i++)
        {
            delete customers[i];
        }
    }
    void remove(Customer *customer) override
    {
        std::deque<Customer *>::iterator it;
        for (it = customers.begin(); it != customers.end(); it++)
        {
            if ((*it)->original_name == customer->original_name)
            {
                customers.erase(it);
                break;
            }
        }
    }

    void removeMany(int section_id) override
    {
        for (auto it = customers.begin(); it != customers.end();)
        {
            if ((*it)->section == section_id)
            {
                it = customers.erase(it);
                continue;
            }
            it++;
        }
    }

    Customer *getReplacedCus() override
    {
        return customers.front();
    }

    void add(Customer *customer) override
    {
        customers.push_back(customer);
    }

    Customer *contains(const string &name)
    {
        for (auto &item : customers)
        {
            if (item->original_name == name)
            {
                return item;
            }
        }
        return nullptr;
    }

//        void print() const {
//            ofstream outfile("customerLog.txt");
//            for(auto& item : customers){
//                outfile << item->table_id << "-"<< item->code  << "-" << item->original_name << "\n";
//            }
//            outfile.close();
//        }
};

class LRCO : public Log
{
private:
    std::list<Customer *> log;

public:
    LRCO()
    {
        std::fill(log.begin(), log.end(), nullptr);
    }
    // New customer makes order when they comes to the restaurant
    void add(Customer *customer) override
    {
        log.push_front(customer);
    }

    void remove(Customer *customer) override
    {
        auto it = std::find_if(log.begin(), log.end(), [&](Customer *_cus) -> bool
        { return (_cus == customer); });
        log.erase(it);
    }

    void removeMany(int section_id) override
    {
        for (auto it = log.begin(); it != log.end();)
        {
            if ((*it)->section == section_id)
            {
                it = log.erase(it);
            }
            else
            {
                it++;
            }
        }
    }

    Customer *getReplacedCus() override
    {
        return log.back();
    }

    void update(Customer *cus) override
    {
        auto it = std::find_if(log.begin(), log.end(), [&](Customer *_cus) -> bool
        { return (_cus == cus); });
        Customer *head = *it;
        log.erase(it);		  // remove the element
        log.push_front(head); // push it into the head
    }
};

class LFCO : public Log
{
public:
    class Order_comp;
private:
    MinHeap<Customer*, Order_comp> log;

public:
    explicit LFCO(int _cap)
    {
        log.heap.reserve(_cap);
    }
    void add(Customer *customer) override
    {
        log.add(customer);
    }

    void remove(Customer *customer) override
    {
        log.remove(customer);
    }

    void removeMany(int section_id) override
    {
        auto it = log.heap.begin();
        while (it != log.heap.end())
        {
            if (it->first->section == section_id)
            {
                it = log.heap.erase(it);
                continue;
            }
            it++;
        }
    }

    Customer *getReplacedCus() override
    {
        return log.getMin();
    }

    void update(Customer *cus) override
    {
        for (auto &it : log.heap)
        {
            if (it.first == cus)
            {
                it.first->noOrders++;
            }
        }
        this->log.update();
    }

    void print() const
    {
        _print(log.heap, log.heap.size(), 0);
    }

    void _print(const vector<pair<Customer*, int>> &vec, int size, int i) const
    {
        if (i < 0 || i >= size)
        {
            return;
        }
        cout << vec[i].first->table_id << "-" << vec[i].first->noOrders << "\n";
        _print(vec, size, i * 2 + 1);
        _print(vec, size, i * 2 + 2);
    }

public:
    class Order_comp
    {
    public:
        bool operator()(const pair<Customer*, int> &child, const pair<Customer*, int> &parent)
        {
            if(child.first->noOrders == parent.first->noOrders){
                // Consider arrival time if two customers have the same noOrders
                assert(child.second != parent.second);
                return child.second > parent.second;
            }
            return (child.first->noOrders > parent.first->noOrders);
        }
    };
};

class Restaurant
{
public:
    Section **sections; // section manager
    vector<Customer *> *tables;
    Log **logs;
    int capacity;
    const int NUMBER_LOGS = 3;
    const int NUMBER_SECTIONS = 2;
    /*-------------------------------------------------------*/
    explicit Restaurant(int _capacity)
    {
        capacity = _capacity;
        // Tables init
        tables = new vector<Customer *>(capacity, nullptr);
        // Logs init
        logs = new Log *[NUMBER_LOGS]
                {
                        new FIFO,
                        new LRCO,
                        new LFCO(_capacity)
                };
        // Section init
        sections = new Section *[NUMBER_SECTIONS]
                {
                        new Section1(capacity / 2),
                        new Section2(capacity / 2)
                };
    }
    ~Restaurant()
    {
        for (int i = 0; i < NUMBER_LOGS; i++)
        {
            delete logs[i];
        }
        for (int i = 0; i < NUMBER_SECTIONS; i++)
        {
            delete sections[i];
        }
        delete[] sections;
        delete tables;
        delete[] logs;
    }
    bool isFull() const
    {
        return sections[0]->isFull() && sections[1]->isFull();
    }

    int allotTab(Customer *newone)
    {
        assert(!isFull());
        int slot = (newone->code % capacity);
        int i = slot;
        for (; tables->at(i) != nullptr; i = (i + 1) % capacity)
        {
            if (i + 1 == slot)
                break;
        }
        newone->table_id = i + 1;
        tables->at(i) = newone;
        return (i + 1);
    }

    void log_add(Customer *customer)
    {
        for (int i = 0; i < NUMBER_LOGS; i++)
        {
            logs[i]->add(customer);
        }
    }

    void log_update(Customer *customer)
    {
        for (int i = 0; i < NUMBER_LOGS; i++)
        {
            logs[i]->update(customer);
        }
    }

    void log_remove(Customer *customer)
    {
        for (int i = 0; i < NUMBER_LOGS; i++)
        {
            logs[i]->remove(customer);
        }
    }

    void removeSection(int section_id)
    {
        sections[section_id]->clear();

        for (int i = 0; i < NUMBER_LOGS; i++)
        {
            logs[i]->removeMany(section_id);
        }

        for (int i = 0; i < capacity; i++)
        {
            if (tables->at(i) && tables->at(i)->section == section_id)
            {
                delete tables->at(i);
                tables->at(i) = nullptr;
            }
        }
    }

    void removeCustomerAt(int table_id)
    {
        if (table_id < 1 || table_id > capacity)
            return;
        table_id = table_id - 1;
        Customer *customer = tables->at(table_id);
        if (customer)
        {
            log_remove(customer);
            sections[customer->section]->removeCus(customer);
            delete tables->at(table_id);
            tables->at(table_id) = nullptr;
        }
    }
};

bool parseRequest(string &input, vector<string> &result)
{
    // Check for overall format
    std::regex pattern("[A-Za-z]+|[A-Za-z]+\\s{1}-?[a-zA-Z0-9]+");
    if (!regex_match(input, pattern))
    {
        return false;
    }
    // Check for detail format of each request type
    string delimiter = " "; // because the input is assured to include only words and whitespace
    int endMark = -1, startMark = 0;
    do
    {
        startMark = (int)input.find_first_not_of(delimiter, endMark + 1);
        endMark = (int)input.find_first_of(delimiter, endMark + 1);
        result.push_back(input.substr(startMark, endMark - startMark));
    } while (endMark != (int)string::npos);

    // Check for the leading command
    if (result.front() == "REG")
    {
        regex name_filter("[a-zA-Z]+");
        return regex_match(result[1], name_filter);
    }
    else if (result.front() == "CLE")
    {
        regex number_filter("-?\\d+");
        return regex_match(result[1], number_filter);
    }
    else if (result.front() == "PrintAVL" || result.front() == "PrintHT" || result.front() == "PrintMH")
    {
        return result.size() == 1; // only one word within the input
    }
    return false;
}
#endif //HUFFMAN_CODING_TREE_MAIN_H
