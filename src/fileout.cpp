//Class to write out the daily transaction file


#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include "fileout.hpp"

/*
Fileout - Fileout
Default empty constructor for fileout, used when defined to empty.
@params: None
@return: Void
*/
Fileout::Fileout(){

}

Fileout::Fileout(std::string outDir) {
    this->outDir = outDir;
}

void typeOne(std::ofstream& out, Transaction transaction) {
    std::string username = transaction.currentUser.username;

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << transaction.currentUser.credits << std::flush;
    std::string s = stream.str();

//    std::cout << transaction.currentUser.credits << " " + transaction.currentUser.type << std::endl;

    //Parse transaction code, add filling of spaces and zeroes.
    out << transaction.transactionCode
        << " " << std::left
        << std::setfill(' ') << std::setw(16)
        << username
        << std::setw(2) << transaction.currentUser.type << " " << std::flush
        << std::right << std::setfill('0') << std::setw(9)
        << s << std::endl;

    return;
}

/*
refund
Writes refund transaction to daily transaction file.
  format: XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
@params: out file outstream, transaction current transaction instance being
  written.
@return: Void
*/
void refund(std::ofstream& out, Transaction transaction) {
    std::string username = transaction.currentUser.username;
    std::string seller = transaction.seller.username;
    std::string buyer = transaction.buyer.username;

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << transaction.credit;
    std::string s = stream.str();

    //Parse transaction code, add filling of spaces and zeroes.
    out << transaction.transactionCode
        << " " << std::left << std::setfill(' ') << std::setw(16)
        << buyer << std::setw(16)
        << seller
        << std::right << std::setw(7) << std::setfill('0')
        << s << std::endl;

    return;
}

/*
advertise
Writes advertise transaction to daily transaction file.
  format: XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_DDD_PPPPPP
@params: out file outstream, transaction current transaction instance being
  written.
@return: Void
*/
void advertise(std::ofstream& out, Transaction transaction) {
    std::string username = transaction.currentUser.username;

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << transaction.minBid;
    std::string s = stream.str();

    //Parse transaction code, add filling of spaces and zeroes.
    out << transaction.transactionCode
        << " " << std::left << std::setfill(' ') << std::setw(26)
        << transaction.item.itemName
        << std::setfill(' ') << std::setw(16)
        << username
        << std::setfill('0') << std::setw(3) << transaction.daysToExpiry
        << " "
        << std::right << std::setw(7)
        << s << std::endl;

    return;
}

/*
bid
Writes bid transaction to daily transaction file.
  format: XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
@params: out file outstream, transaction current transaction instance being
  written.
@return: Void
*/
void bid(std::ofstream& out, Transaction transaction) {
    std::string username = transaction.currentUser.username;
    std::string seller = transaction.seller.username;
    std::string buyer = transaction.buyer.username;

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << transaction.minBid;
    std::string s = stream.str();

    //Parse transaction code, add filling of spaces and zeroes.
    out << transaction.transactionCode
        << " " << std::left << std::setfill(' ') << std::setw(26)
        << transaction.item.itemName
        << std::setfill(' ') << std::setw(16)
        << seller << std::setw(16)
        << username
        << std::right << std::setfill('0') << std::setw(7)
        << s << std::endl;

    return;
}

/*
Fileout::writeTransactions
Function called in main to execute writing current pending transactions to the
  daily transaction file. Transactions are split up into different function calls
  to be parsed to the file.
@params: transactions vector list of all pending transactions.
@return: Void
*/
void Fileout::writeTransactions(std::vector<Transaction> transactions) {
    std::cout << outDir << std::endl;
    std::ofstream out(outDir, std::ios_base::app);

    if (!out.is_open()) std::cout << "Error opening output file." << std::endl;

    //Iterate through each of the transactions and pass transaction code to
    // relevant code parser.
    for (auto trans : transactions) {
        if (trans.transactionCode == "10" || trans.transactionCode == "00" ||
            trans.transactionCode == "01" || trans.transactionCode == "02" ||
            trans.transactionCode == "06")
            typeOne(out, trans);

        if (trans.transactionCode == "05")
            refund(out, trans);

        if (trans.transactionCode == "03")
            advertise(out, trans);

        if (trans.transactionCode == "04")
            bid(out, trans);
    }

    return;
}
