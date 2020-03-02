

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <boost/algorithm/string.hpp>
#include "user.hpp"
#include "item.hpp"
#include "parser.hpp"

class Transaction {
  public:
      bool valid = false;
      std::string transactionCode;
      Transaction(std::string input, User currentUser,
            std::map<std::string, User> &userList, std::map<std::string, Item> &itemList);
      Transaction(std::string input, std::map<std::string, User> &userList);
      void CreateLoginTransaction();
      void CreateLogoutTransaction();
      void CreateBidTransaction();
      void CreateAdvertiseTransaction();
      void CreateAddCreditTransaction();
      void CreateCreateTransaction();
      void CreateRefundTransaction();
      void CreateDeleteTransaction();
      void CreateDisplayTransaction();
      float GetCreditInput();
      User currentUser;
      User targetUser;
      User buyer;
      User seller;
      Item item;
      float credit;
      float minBid;
      int daysToExpiry;
      std::set<std::string> validTypes = {"AA", "FS", "SS", "BS"};
      std::map<std::string, User> userList;
      std::map<std::string, Item> itemList;
      std::string transactionType = "";
};
