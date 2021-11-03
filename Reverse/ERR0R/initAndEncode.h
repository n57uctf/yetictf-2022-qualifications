#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <random>

typedef unsigned int u_int;
typedef std::string str;

u_int keyCreator();

class InitAndEncode {

	u_int key;
	u_int lenght_of_message;
	char* message = new char[128];
	char* encode_string = new char[128];

public:

	InitAndEncode() {
		message = "Hello, its simple c-string!";
		std::cout << "Simple Encoder's instance was created!" << "\n";
		
	}

	InitAndEncode(char* mess) noexcept {
		this->message = mess;
		mess = nullptr; 

	}

	InitAndEncode(InitAndEncode&& instance); 

    InitAndEncode& operator=(const InitAndEncode& instance);

	char* getMyMessage() { return this->message; }

	void MyEncodeAlgorithm();

	~InitAndEncode() {
		message	= nullptr;
		encode_string = nullptr;
	}

};