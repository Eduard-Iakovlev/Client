#pragma once

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

#include <thread>
#include <chrono>

#include "User.h"
#include "Consol_Input.h"

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
//#define PORT 7777 // Будем использовать этот номер порта


class Client{
public:
	Client() = default;
	void socket_file();// создаем сокет
	void close_socket(); // Закрытие сокета
	void server_address(User& user);// Настройка связи с сервером
	std::string message();// Перевод сообщения в стринг
	void transmitting(const std::string& mess); //отправка данных

	void greeting();
	void farewell();
	void menu();
	void send_message(User& user);

	void clean_console();
	void system_pause(int second);

	void client();
private:

	int _socket_file_descriptor, _connection;
	struct sockaddr_in _server_address, _client;
	char _message[MESSAGE_LENGTH];

	char _menu{ 0 };

	bool _work{ true };
	const char _esc{ 27 };
	const char _enter{ 10 };
};
