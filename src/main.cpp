/*
This c++ file will control the main input loop, and
deal with User input appropriately.
*/

#include <iostream>
#include <vector>
#include "transaction.hpp"
#include "parser.hpp"
#include "fileout.hpp"
#include "item.hpp"
#include "user.hpp"

int main(int argv, char** args) {
    std::cout << "Welcome to TerribleAuction\nBy: Kanban Group™\n" << std::endl;
    std::string outFile = "output.fout";
    std::string usersFile;
    std::string itemsFile;

    if (argv == 4) {
//        if (std::string(args[1]) == "-testmode")
//            outFile = std::string(args[2]);

        outFile = std::string(args[3]);
        usersFile = std::string(args[1]);
        itemsFile = std::string(args[2]);
    } else {
        std::cout << "usage: auction <users file> <items file> <output file>" << std::endl;
    }


    bool loggedIn = false;
    User* currentUser = nullptr;

    //Define empty transaction vector to hold all pending transactions to be
    //written to daily transaction file.
    std::vector<Transaction> transactions;

    //Define parser class, read in user and item list to be passed to
    // each of the transaction instances during a users system use.
    Parser p = Parser();
    std::map<std::string, User> userList = p.ReadCurrentUsers(usersFile);
    std::map<std::string, Item> itemList = p.ReadAvailItems(itemsFile);
    //Continously loop until logout is called, logout is the only break.
    while (true) {
        std::string userInput;

        std::cout << "Please enter a transaction code: ";
        std::cin >> userInput;

        //User is logged in, and requests logout transaction
        if (userInput == "logout" && loggedIn) {
            // User has chose to logout, write transactions to appropriate file(s)
            Fileout f = Fileout(outFile);

            transactions.push_back(Transaction(userInput, *currentUser, userList, itemList));
            f.writeTransactions(transactions);

            return 1;

        }
        //User is logged in, and calls transaction other than logout.
        else if (loggedIn) {
            Transaction t = Transaction(userInput, *currentUser, userList, itemList); // transaction data input lookp

            if (t.valid)
                transactions.push_back(t);
            else
                continue; // transaction failed; class will print error
        }
        //New user into auction system, limits user to only expecting login
        // transaction.
        else {
            if (userInput == "login") {
                Transaction t = Transaction(userInput, userList);

                if (t.valid == true){
                    loggedIn = true;
                    currentUser = &t.currentUser;
                    transactions.push_back(t);
                }

            } else {
                std::cout << "Error: please login before attempting other transaction" << std::endl;
                std::cin.clear();
                std::cin.ignore();
                return -1;
            }

        }
    }

    return 0;
}
