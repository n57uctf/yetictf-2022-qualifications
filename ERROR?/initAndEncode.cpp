#include <initAndEncode.h>


u_int keyCreator() {
 	u_int key;
	std::random_device rd; 
    std::mt19937 mersenne(rd());
    
    for (int count = 0;;++count) {
        key = mersenne();

		if (key)
			break;

		continue;
	}
	return (key - (key%5)) / 100000000;
}

void InitAndEncode::MyEncodeAlgorithm() {

		str simple_string = static_cast<str>(message);

		this->lenght_of_message = static_cast<u_int>(simple_string.length());
		std::cout << "Lenght of string: " << lenght_of_message  << std::endl; 

		std::cout << "\n+=== Start of encode your string ===+" << std::endl;

		this->key = keyCreator();
		
		try {
			char* result = new char[lenght_of_message];

			for (u_int ind{0}; ind < lenght_of_message; ind++) {
				if (ind % 2)
					result[ind] = static_cast<char>((int)message[ind]+key);
				else 
					result[ind] = static_cast<char>((int)message[ind]-key);
			}
			strncpy(this->encode_string, result, sizeof(result));
			delete[] result;
		}
        catch(const std::exception& e)
		{
			std::cout << "[-] Something went wrong !\n";
			std::cerr << e.what() << '\n';
		}

		std::cout << "\n[+] Complete" << std::endl;
		std::cout << "Your encoded string: " << this->encode_string << std::endl;
}

InitAndEncode::InitAndEncode(InitAndEncode&& instance) noexcept: lenght_of_message{ instance.lenght_of_message }, 
		encode_string{ instance.encode_string }, key{ instance.key } {
		instance.lenght_of_message = 0;
		instance.key = 0;
		instance.encode_string = nullptr;
} 

InitAndEncode& InitAndEncode::operator=(const InitAndEncode& instance) {
    if (this == &instance) return *this;

    lenght_of_message = instance.lenght_of_message;

    char* new_encode = new char[lenght_of_message];
    delete[] encode_string;
    encode_string = new_encode;

    char* new_message = new char[lenght_of_message];
    delete[] message;
    message = new_message;

    std::strncpy(message, instance.message, lenght_of_message);

    std::strncpy(encode_string, instance.encode_string, lenght_of_message);

    return *this;
}
