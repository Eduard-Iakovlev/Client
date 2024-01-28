#include "Client.h"

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

//---------------- Меню в аккаунте -------------------------------------------------------
void Client::menu_chat() {
	std::cout << "\n Для завершени нажмите \'Esc\'\n";
	_menu = _getch();
	if(_menu == _esc) _work = false;
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

//----------------- Основная функция работы чата -------------------------------------------
void Client::client(){

	greeting();
	User user;
	user.get_user();
	socket_file();
	server_address(user);
	while(_work){
		send_message(user);
	}
	farewell();
	close_socket();
}


