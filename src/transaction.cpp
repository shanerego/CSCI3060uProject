
#include "transaction.hpp"

/*
Transaction - Transaction
General constructor for transaction instance when user is not logged in.
@params: input transaction request, userList username list
@return: Void
*/
Transaction::Transaction(std::string input, std::map<std::string, User> &userList) {
    this->userList = userList;
    this->itemList = itemList;
    if (input == "login"){
        this->transactionCode = "10";
        CreateLoginTransaction();
    } else{
        std::cout << "\t\t\tnot a transaction l0ser" << std::endl;
    }
}

/*
Transaction - Transaction
General constructor for transaction instance when user is logged in. Checks
 to see if input is valid, if it is call CreateTransaction for input.
@params: input transaction request, currentUser instance of existing login
          userList username list, itemList item list
@return: Void
*/
Transaction::Transaction(std::string input, User currentUser,
            std::map<std::string, User> &userList, std::map<std::string, Item> &itemList) {

    // check and see if transaction input is valid
    // if it is, call respective transaction function to gather input
    this->currentUser = currentUser;
    this->userList = userList;
    this->itemList = itemList;

    if (input == "logout"){
        this->transactionCode = "00";
        CreateLogoutTransaction();
    }
    else if (input == "bid"){
        this->transactionCode = "04";
        CreateBidTransaction();
    }
    else if (input == "advertise"){
        this->transactionCode = "03";
        CreateAdvertiseTransaction();
    }
    else if (input == "addcredit"){
        this->transactionCode = "06";
        CreateAddCreditTransaction();
    }
    else if (input == "create"){
        this->transactionCode = "01";
        CreateCreateTransaction();
    }
    else if (input == "refund"){
        this->transactionCode = "05";
        CreateRefundTransaction();
    }
    else if (input == "delete"){
        this->transactionCode = "02";
        CreateDeleteTransaction();
    } else if (input == "display"){
        CreateDisplayTransaction();
    }
    else{
        std::cout << "Please input a valid transaction." << std::endl;
    }
}

/*
Transaction - CreateLoginTransaction
Function used for login input request, sets valid to T/F depending on Function
  interation, stores all relevant input to currentUser instance for write.
  Transaction Code: 10
@params: None
@return: Void
*/
void Transaction::CreateLoginTransaction(){
    std::string username;
    std::cout << "Username: ";
    std::cin >>  username;

    if (username.length() > 15){
        std::cout << "ERROR: Username above limit (15 characters)" << std::endl;
        this->valid = false;
    }
    else {
        // Check if username exists in userList
        if (this->userList.count(username) == 0){
        std::cout << "ERROR: Entered username does not exist." << std::endl;
        this->valid = false;
        }
        else{
        //Create valid transaction here
            this->currentUser = this->userList[username];
            this->valid = true;
        }
    }

    return;
}

/*
Transaction - CreateLogoutTransaction
Function used for logout input request, closes transaction stream for current
  login
  Transaction Code: 00
@params: None
@return: Void
*/
void Transaction::CreateLogoutTransaction(){
  std::cout << "Logging out." << std::endl;
  this->valid = true;
  //Create valid transaction here

  return;
}

/*
Transaction - CreateBidTransaction
Function used for bid input request, sets valid to T/F depending on Function
  interation, stores all relevant input to seller and item instance for write.
  Transaction Code: 04
@params: None
@return: Void
*/
void Transaction::CreateBidTransaction(){
  std::string itemName, numDays, sellerName;
  float bidAmount;
  std::cout << "Item Name: ";
	std::cin >>  itemName;

  std::cout << "Number of Days Remaining: ";
  std::cin >> numDays;

	std::cout << "Seller Name: ";
	std::cin  >>  sellerName;

  if(this->currentUser.username != sellerName){
    if (this->currentUser.type != "SS"){
      //Check if item & seller name's exists
      if(this->itemList.count(itemName) > 0){
        if(this->userList.count(sellerName) > 0){
          float currentBid = this->itemList[itemName].currentBid;
          std::cout << "Highest bid: " << currentBid << std::endl;

          std::cout << "Bid Amount: ";
          bidAmount = GetCreditInput();

          if (this->currentUser.type == "AA" && bidAmount > currentBid){
            std::cout << "Bid made on " << itemName << std::endl;
            this->valid = true;
            this->seller = User(sellerName, "", 0);
            this->item = Item(itemName, sellerName, "", stoi(numDays), bidAmount);

          } else if (this->currentUser.type == "AA" && bidAmount <= currentBid){
            std::cout << "Error: Bid is not greater than current highest bid." <<std::endl;
            this->valid = false;
          } else{
            float minBid = currentBid * 1.05;
            if (bidAmount > minBid){
              std::cout << "Bid made on " << itemName << std::endl;
              this->valid = true;
              this->seller = User(sellerName, "", 0);
              this->item = Item(itemName, sellerName, "", stoi(numDays), bidAmount);
            } else{
              std::cout << "Error: Bid is not 5%% greater than current highest bid." << std::endl;
              this->valid = false;
            }
          }
        } else{
          std::cout << "Error: Seller does not exist" << std::endl;
          this->valid = false;
        }
      } else{
        std::cout << "Error: Item name does not exist" << std::endl;
        this->valid = false;
      }
    } else{
      std::cout << "Error: " << this->currentUser.username << " does not have privilege to buy." << std::endl;
      this->valid = false;
    }
  } else{
    std::cout << "Error: Can't bid on your own items." << std::endl;
    this->valid = false;

  }
  return;
}

/*
Transaction - CreateAdvertiseTransaction
Function used for advertise input request, sets valid to T/F depending on
  Function interation, stores all relevant input to  item instance for write.
  Transaction Code: 03
@params: None
@return: Void
*/
void Transaction::CreateAdvertiseTransaction(){
    std::string itemName;
    int auctionLength;
    float minBid;
    std::cout << "Item Name: ";
	std::cin >>  itemName;

	//FillItemName used for Exists function

	std::cout << "Minimum Bid: ";
	std::cin >>  minBid;

	std::cout << "Auction Length (Days): ";
	std::cin >>  auctionLength;

    if (this->currentUser.type != "BS"){
        if (itemName.length() <= 25){
            if (minBid < 1000.00){
                if (auctionLength <= 100){
                    if (this->itemList.count(itemName) == 0){
                    this->item = Item(itemName, this->currentUser.username, "", auctionLength, minBid);
                    std::cout << itemName << " is up for auction!" << std::endl;
                    this->valid = true;
                    } else{
                    std::cout << "Error: " << itemName << " is already up for auction." << std::endl;
                    this->valid = false;
                    }
                } else{
                    std::cout << "Error: Item cannot be up for over 100 days" << std::endl;
                    this->valid = false;
                }
                } else{
                std::cout << "Error: Cannot put items up for over 999.99 credits." << std::endl;
                this->valid = false;
                }
        } else{
            std::cout << "Error: Item name cannot exceed 25 characters." << std::endl;
            this->valid = false;
        }
    } else{
    std::cout << "Error: Buy-standard user cannot put items up for auction." << std::endl;
    this->valid = false;
    }
    return;
}

/*
Transaction - CreateAddCreditTransaction
Function used for add credit input request, sets valid to T/F depending on
  Function interation, stores all relevant input to currentUser and targetUser
  instance for write.
  Transaction Code: 06
@params: None
@return: Void
*/
void Transaction::CreateAddCreditTransaction(){
  std::string username;
  float credit;



  if (this->currentUser.type == "AA"){

    std::cout << "Username: ";
    std::cin >>  username;

    credit = GetCreditInput();

    //Check if user exists
    if (this->userList.count(username) > 0){
      float newCredit = this->userList[username].credits + credit;

      //Check if new credit amount exceeds limit
      if (newCredit > 999999.00){
        std::cout << "ERROR: New credit amount exceeds limit." << std::endl;
        this->valid = false;
      } else if (credit > 1000.00){
      //Check if user is adding more than 1000 credits
        std::cout << "ERROR: Cannot add more than 1000 credits in one session." << std::endl;
        this->valid = false;
      }else{
        //Create valid transaction here
        std::cout << "Credit of " << credit << " added to " << username << std::endl;
        this->currentUser = this->userList[username];
        this->credit = credit;
        this->valid = true;
      }
    } else{
      std::cout << "ERROR: Entered username does not exist." << std::endl;
      this->valid = false;
    }
  }

  //Standard user attempts to add credit.
  else{
    credit = GetCreditInput();
    float newCredit = this->userList[username].credits + credit;
    //Check if new credit amount exceeds limit
      if (newCredit > 999999.00){
        std::cout << "ERROR: New credit amount exceeds limit." << std::endl;
        this->valid = false;
      } else if (credit > 1000.00){
        //Check if user is adding more than 1000 credits
        std::cout << "ERROR: Cannot add more than 1000 credits in one session." << std::endl;
        this->valid = false;
      } else{
        //Create valid transaction here
        std::cout << "Credit of " << credit << " added to " << username << std::endl;
        this->targetUser = this->userList[username];
        this->credit = credit;
        this->valid = true;
      }

  }

  return;
}

/*
Transaction - CreateCreateTransaction
Function used for advertise input request, sets valid to T/F depending on
  Function interation, stores all relevant input to currentUser instance for
  write.
  Transaction Code: 03
@params: None
@return: Void
*/
void Transaction::CreateCreateTransaction(){
  std::string username, type;
  float credit;
  std::cout << "Username: ";
  std::cin >> username;
  std::cout << "Account Type: ";
  std::cin >> type;
  credit = GetCreditInput();
  //Checks if user is admin to proceed
  if (this->currentUser.type == "AA"){
    if (username.length() > 15){
    //Rejects overly long username
      std::cout << "ERROR: New username cannot exceed 15 characters." << std::endl;
      this->valid = false;
    } else if(this->userList.find(username) != this->userList.end()){
    //Rejects existing username
      std::cout << "ERROR: "<< username << " already exists." << std::endl;
      this->valid = false;
    } else{
      if (credit > 999999.00){
      //Rejects credit value over max
        std::cout << "ERROR: User cannot have more than the 999,999 credit limit." << std::endl;
        this->valid = false;
      } else{
        if (validTypes.count(type) > 0){
          //Create valid transaction here
          std::cout << username << " created by " << this->currentUser.username << std::endl;
          this->currentUser = User(username, type, credit);
          this->valid = true;
        } else{
            std::cout << "ERROR: Not a valid user type." << std::endl;
          this->valid = false;
        }

        }
    }
  } else{
    std::cout << "ERROR: Standard user cannot use CREATE." << std::endl;
    this->valid = false;
  }
  return;
}

/*
Transaction - CreateRefundTransaction
Function used for refund input request, sets valid to T/F depending on
  Function interation, stores all relevant input to buyer and seller instance
  for write.
  Transaction Code: 05
@params: None
@return: Void
*/
void Transaction::CreateRefundTransaction(){
  std::string buyer, seller;
  float credit;
  std::cout << "Buyer Name: ";
  std::cin >> buyer;
  std::cout << "Seller Name: ";
  std::cin  >> seller;
  credit = GetCreditInput();

  if (this->currentUser.type == "AA"){
    //Check if user is admin

    //Checks that buyer exists
    if (this->userList.find(buyer) != this->userList.end()){

      //Checks that seller exists
      if (this->userList.find(seller) != this->userList.end()){

        User sellerUser = this->userList[seller];

        //Checks if seller has enough credits to refund
        if (sellerUser.credits < credit){
          std::cout << "ERROR: Seller does not have enough credits." << std::endl;
          this->valid = false;
        } else{
          this->buyer = this->userList[buyer];
          this->seller = this->userList[seller];
          this->credit = credit;

          this->valid = true;
        }

      } else{
        std::cout << "ERROR: Seller does not exist." << std::endl;
        this->valid = false;
      }
    } else{
      std::cout << "ERROR: Buyer does not exist." << std::endl;
      this->valid = false;
    }

  } else{
    std::cout << "ERROR: " << this->currentUser.username
        << " does not have privilege to refund." << std::endl;
    this->valid = false;
  }
  return;
}

/*
Transaction - CreateDeleteTransaction
Function used for delete input request, sets valid to T/F depending on
  Function interation, stores all relevant input to targetUser instance for write.
  Transaction Code: 02
@params: None
@return: Void
*/
void Transaction::CreateDeleteTransaction(){
  std::string username;
  std::cout << "Username: " << std::endl;
  std::cin >> username;

  //Checks that user is admin
  if (this->currentUser.type == "AA"){
      if (this->userList[username].type != "AA"){
        //Checks that user is not deleting itself
        if (this->currentUser.username == username){
        //Checks that user to be deleted exists
        if (this->userList.count(username) > 0){
            //Designate deleted user here
            this->targetUser = this->userList[username];
            std::cout << username  << " deleted by " << this->currentUser.username << "." << std::endl;
            this->valid = true;
        } else{
            std::cout << "ERROR: "<< username <<" does not exist." << std::endl;
            this->valid = false;
        }

        } else{
        std::cout << "ERROR: User cannot delete itself." << std::endl;
        this->valid = false;
        }
      } else{
          std::cout << "ERROR: Admins cannot delete other admins" << std::endl;
          this->valid = false;
      }
  } else{
    std::cout << "ERROR: Standard users cannot delete other standard users." << std::endl;
    this->valid = false;
  }

  return;

}

/*
Transaction - CreateDisplayTransaction
Function used for display input request, outputs item list
@params: None
@return: Void
*/
void Transaction::CreateDisplayTransaction(){
    for (std::map<std::string, Item>::iterator it=itemList.begin(); it!=itemList.end(); ++it){
        item = it->second;
        std::cout << "Item: " << item.itemName << std::endl
        << "\tSeller: " << item.seller << std::endl
        << "\tCurrent Buyer: " << item.buyer << std::endl
        << "\tDays Left: " << item.daysToExpiry << std::endl
        << "\tCurrent Bid:" << item.currentBid << std::endl << std::endl;
    }
}


/*
Transaction - GetCreditInput
Function used for float input for credits, user must be prompted prior to
  calling this function for 'what' the input required is for. Continuous input
  until valid input given.
@params: None
@return: float
*/
float Transaction::GetCreditInput(){
  float credit;
  bool validFloat = false;
  while(!validFloat){
  //Checks that user input is a valid value for credits
    std::cin >> credit;

    if (!std::cin.good()){
      std::cout << "Please enter a number." <<std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      return credit;
    }
  }
}
