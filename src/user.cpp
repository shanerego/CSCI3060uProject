#include <iostream>
#include "user.hpp"

/*
User - User
Default empty construtor for user class, allows for system to define an empty
	user to hold copied or passed arguements while passing to another class.
@params: None
@return: None
*/
User::User() {}

/*
User - User
General constructor for the user class, stores instance variables.
@params: username current userame, userType current type, credit current credit amount.
@return: None
*/
User::User(std::string username, std::string userType, float credits) {
	this->username = username;
	this->type = userType;
	this->credits = credits;
}
