#include <initAndEncode.h>



int main()
{
	char* user_input = new char[128];

	std::cout << "Welcome to YetiCTF, my dear friend!" << std::endl;
	std::cout << "Keep calm and follow the instruction!" << std::endl;
	std::cout << std::endl;

	std::cout << "Hint: Don't try to break or crash something!\nYour goal is to FIX something!\n" << std::endl;
	std::cout << "Give me some data with characters: " << std::endl;

	std::cin.getline(user_input, 128, '\n');
	
	if (std::cin.fail()) {
		std::cin.clear();
    	std::cin.ignore(32767,'\n');
	}

	if (!std::strlen(user_input)) {
		std::cout << "Ooops! Your input is empty string..";
		std::cout << "Exiting..\n"; 
		return -1;
	}

	InitAndEncode first(user_input);
	first.MyEncodeAlgorithm();
	
	InitAndEncode second(std::move(first));

	std::cout << "\n" << "Final check !" << "\n"; 

	std::cout << "My second message:" << second.getMyMessage() << "\n\n";
	str string = static_cast<str>(second.getMyMessage());

	std::cout << "Lenght of my message: " << string.length() << "\n\n";

	if (user_input != nullptr)
		user_input = nullptr;

	if (string.empty())
		return -1;
	else
		return 0;
}