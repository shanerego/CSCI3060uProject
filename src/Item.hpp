

#pragma once
#include <string>

class Item {
  public:
    Item();
    Item(std::string name, std::string sellerName, std::string buyerName, int days, float bid);
    std::string getName();
    std::string getSeller();
    std::string getBuyer();
    std::string getDaysLeft();
    std::string getBid();
    std::string itemName;
    std::string seller;
    std::string buyer;
    int daysToExpiry;
    float currentBid;
};
