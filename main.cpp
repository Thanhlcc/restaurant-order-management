#include "main.h"
#include "Request.h"

int main() {
    string input;
    vector<string> parsedReq;
    RequestManager manager = RequestManager::getInstance();
    Restaurant res(MAXSIZE);
    ifstream infile;
    infile.open("test.txt");

    if(!infile.is_open()){
        cout << "Open failed\n";
        exit(1);
    }
    while( std::getline(infile, input) ){
        if(!parseRequest(input, parsedReq)){
            cout << "Invalid request\n";
            continue;
        }
        // Define the request before executing
        if(parsedReq.front() == "REG"){
            manager.setRequest( new REG(parsedReq.back()) );
        }
        else if(parsedReq.front() == "CLE"){
            manager.setRequest(new CLE(stoi( parsedReq.back() )));
        }
        else if(parsedReq.front() == "PrintAVL"){
            manager.setRequest( new Print("AVL") );
        }
        else if(parsedReq.front() == "PrintMH"){
            manager.setRequest( new Print("MH") );
        }
        else if(parsedReq.front() == "PrintHT"){
            manager.setRequest( new Print("HT") );
        }
        manager.executeReq(&res);
        parsedReq.clear(); input.clear();
    }
//    ((FIFO*)res.logs[0])->print();
    infile.close();
    return 0;
}
