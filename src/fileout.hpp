

//This class will handle file output given a list of valid transactions.


#pragma once
#include "transaction.hpp"
#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string.hpp>
#include <iomanip>

class Fileout {
private:
    std::string outDir;
public:
    Fileout();
    Fileout(std::string outDir);
    void writeTransactions(std::vector<Transaction> transactions);
};
