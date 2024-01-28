#include <iostream>
#include <string>


class User {
public:
	User() = default;

	void get_user();

	std::string user_name();
	int user_port();
	int user_sec();

private:
	std::string _name;
	int _port;
	int _second;
};
