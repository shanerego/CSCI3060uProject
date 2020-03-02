/*
Container for each item in the item list file.
Also used as a container to be passed during a transaction write if multiple
users or items must be used for a transaction write.
*/
#include "item.hpp"

/*
Item - Item
Default empty construtor for item class, allows for system to define an empty
	item to hold copied or passed arguements while passing to another class.
@params: None
@return: None
*/
Item::Item() {}

/*
Item - Item
General constructor for the item class, stores instance variables.
@params: name current item name, sellserName seller name of ite, buyerName
  buyer name of item, days days left to expiry, bid item's current bid amount.
@return: None
*/
Item::Item(std::string name, std::string sellerName, std::string buyerName, int days, float bid) {
  this->itemName = name;
  this->seller = sellerName;
  this->buyer = buyerName;
  this->daysToExpiry = days;
  this->currentBid = bid;
}
