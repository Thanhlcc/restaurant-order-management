#ifndef HUFFMAN_CODING_TREE_REQUEST_H
#define HUFFMAN_CODING_TREE_REQUEST_H
#include "main.h"
/*
     *---------------------------Request hierachy-------------------------------
     */
class Restaurant;
class Request
{
public:
    virtual ~Request() = default;
    virtual void execute(Restaurant *res) = 0;
};

class REG : public Request
{
private:
    std::string name;

public:
    REG(std::string _name)
    {
        name = _name;
    }

    void execute(Restaurant *res) override
    {
        /*
         * 1. Encoding the customer name
         *  1.1. Check if the customer is currently in the restaurant or not by Checking log::FIFO
         * 2.case1 Assign the customer to a table (Restaurant object -> the appropriate Section)
         * 2.case2 Update Log::LRCO and Log::LFCO and go to step 4
         * 3. If step two fails to execute, then start off executing Replacement policy
         *  3.1 choose the strategy suit for the customer
         *  3.2 Request replaced table from Log object
         *  3.3 Remove the current customer at that slot
         *  3.4 Assign that table to the new customer
         *  3.5 Add table to the section again
         * 4. Exit
         */
        // Check if the COMMAND is an order or placement
        Customer *customer = ((FIFO *)res->logs[0])->contains(name);
        if (customer != nullptr)
        { // An order
            res->log_update(customer);
        }
        else
        { // placement
            // Add to either section
            if (!res->isFull())
            {
                customer = new Customer(name);
                // Chose the section on basis of customer code
                int section_id = int(customer->code % 2 == 0); // 0 or 1
                customer->section = section_id;
                // Assign a table to the customer
                res->allotTab(customer);

                // Starting insertion in the computed section
                if (!res->sections[section_id]->isFull())
                {
                    res->sections[section_id]->addCus(customer);
                }
                else
                {
                    res->sections[!section_id]->addCus(customer);
                }
                // Add new customer to the log system
                res->log_add(customer);
            }
            else
            { // Do replacement policy
                int code = name.length() > 1 ? Customer::getResult(name) : 1;
                Customer* oldCustomer = res->logs[code % 3]->getReplacedCus();
                // Update the customer holding the table
                oldCustomer->code = code;
                oldCustomer->original_name = name;
                // Remove the old customer info from and add new customer to the log system
                res->log_remove(oldCustomer);
                res->log_add(oldCustomer);
            }
            //            std::cout << "REG called with " << name << std::endl;
        }
    }
};

class CLE : public Request
{
public:
private:
    int table_id;

public:
    CLE(int _number)
    {
        table_id = _number;
    }
    void execute(Restaurant *res) override
    {
        /*
         * table_id < 1 => clear whole section 1
         * table_id > maxsize => clear whole section 2
         * otherwise
         *  - find the customer sitting in that table
         *  - find the section where the table is currently in
         *  - Update whole system ( Log, Section, Restaurant )
         *  -
         */
        if (table_id < MAXSIZE && table_id > 0)
        {
            res->removeCustomerAt(table_id);
        }
        else if (table_id < 1)
        {
            res->removeSection(0);
        }
        else
        {
            res->removeSection(1);
        }
        // std::cout << "CLE called with " << table_id << std::endl;
    }
};

class Print : public Request
{
private:
    std::string mode;

public:
    Print(const std::string _mode)
    {
        mode = _mode;
    }
    void execute(Restaurant *res) override
    {
        if (this->mode == "HT")
        {
            res->sections[0]->print();
        }
        else if (this->mode == "AVL")
        {
            res->sections[1]->print();
        }
        else if (this->mode == "MH")
        {
            ((LFCO *)(res->logs[2]))->print();
        }
    }
};

class RequestManager
{
private:
    RequestManager() {}
    Request *req = nullptr;

public:
    ~RequestManager()
    {
        if (this->req)
            delete this->req;
    }
    static RequestManager &getInstance()
    {
        static RequestManager instance;
        return instance;
    }
    void setRequest(Request *request)
    {
        if (this->req)
            delete this->req;
        this->req = request;
    }

    void executeReq(Restaurant *res)
    {
        assert(this->req);
        this->req->execute(res);
    }
};

#endif //HUFFMAN_CODING_TREE_REQUEST_H
