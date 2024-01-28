#include "User.h"
#include "Consol_Input.h"


void User::get_user(){
		Universal_Input<int> enter('0', '9');
		std::cout << " Введите имя пользователя: ";
		std::cin >> _name;
		std::cout << " Введите номер порта сервера: ";
		_port = enter.input();
		enter.clear();
		std::cout << "\n Введите период подключения к серверу в секундах : ";
		_second = enter.input();
		enter.clear();
}


std::string User::user_name() {
	return _name;
}

int User::user_port() {
	return _port;
}

int User::user_sec() {
	return _second;
}


