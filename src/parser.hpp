#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "user.hpp"
#include "item.hpp"

class Parser {
	private:
		std::vector<std::string> dailyTrans;
		std::vector<std::string> currentUsers;
		std::vector<std::string> availItems;
	public:
		Parser();
		std::map<std::string, User> ReadCurrentUsers(std::string fileName);
		std::map<std::string, Item> ReadAvailItems(std::string fileName);
};
