#pragma once

class User {
	public:
		User();
		User(std::string username, std::string userType, float credits);
		std::string username;
		std::string type;
		float credits;
};
