﻿#include "Client.h"
#include <future>

//----------- Создание сокета ---------------------------
void Client::socket_file() {
	_socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_file_descriptor == -1) {
		std::cout << " Не удалось создать сокет!" << std::endl;
		exit(1);
	} std::cout << "\n Сокет создан" << std::endl;
}

//----------- Закрытие сокета ------------------------------
void Client::close_socket() {
	close(_socket_file_descriptor);
}


//------------ Настройка связи с сервером ---------------------
void Client::server_address(User& user) {
	_server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	_server_address.sin_port = htons(user.user_port());
	_server_address.sin_family = AF_INET;
	_connection = connect(_socket_file_descriptor, (struct sockaddr*)&_server_address, sizeof(_server_address));
	if (_connection == 0) {
        std::cout << " Соединение установлено" << std::endl;
    } else {
        std::cerr << " Error: нет соединения с сервером" << std::endl;
		exit(1);
    }
}

//--------------- Перевод сообщения в стринг -----------------------------
std::string Client::message() {
	return std::string(_message);
}

//-------------- Отправка данных -----------------------------------
void Client::transmitting(const std::string& mess) {
	memset(_message, 0, sizeof(_message));
	strcpy(_message, mess.c_str());
	ssize_t bytes = write(_socket_file_descriptor, _message, sizeof(_message));
}


//---------------- Приветствие ------------------------------------------------------------
void Client::greeting() {
	clean_console();
	std::cout << "\n          Добро пожаловать!\n\n";
}

//----------------- Прощание --------------------------------------------------------------
void Client::farewell() {
	std::cout << "\n\n          Всего хорошего.\n";
}

//-------------------- Меню -------------------------------------------------------------
void Client::menu() {
	std::cout << "\n Для завершения нажмите \'Esc\'\n";
	_menu = _getch();
	if(_menu == _esc) {
		transmitting("exit");
		farewell();
		close_socket();
		exit(0);
	}
}

//------------- Создание и отправка сообщения ---------------------------------------
void Client::send_message(User& user){
	transmitting(user.user_name());
	system_pause(user.user_sec());
}

//----------------- Очистка консоли -------------------------------------------------------
void Client::clean_console(){
	std::system("clear");  
}

//----------------- Пауза -----------------------------------------------------------------
void Client::system_pause(int second){
	std::this_thread::sleep_for(std::chrono::seconds(second));

}

//----------------- Запуск -----------------------------------------------------------
void Client::client_start(){

	greeting();
	User user;
	user.get_user();
	socket_file();
	server_address(user);
	std::future<void> m = std::async(std::launch::async, &Client::menu, this);
	while(_work){
		send_message(user);
	}
	m.wait();
	farewell();
	close_socket();
}


