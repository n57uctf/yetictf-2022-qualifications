#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void getFlag() {

    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen("hardest_v_release" ,"rb");
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (pFile , 0 , SEEK_END);
    lSize = ftell(pFile);
    rewind (pFile);

    buffer = (char*) malloc (sizeof(char)*lSize);

    if (buffer == NULL) {
        fputs("Memory error",stderr); 
        exit(2);
    }

    result = fread(buffer,1,lSize,pFile);
    if (result != lSize) {
        fputs("Reading error",stderr);
        exit(3);
    }

    for (long i=0; i<lSize; i++)
        printf("%c ", buffer[i]);

    fclose(pFile);
    free(buffer);
}

void helper(char& data) {
    printf("%s", "Welcome to the help function!\n");
    printf("%s","Here you can change the value of your password entry!\n");

    printf("Give me your password: ");
    std::cin.getline(&data, 38, '\n');
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767,'\n');
    }
    else {
        std::cout << "Your input has changed successfully\n";
    }

}


int main() {
    int help = 0;
    char* user_input = new char[38];
    char* password = new char[38]; 


    while (true) {    
        short counter{0};

        srand(static_cast<unsigned int>(time(0)));

        for (int i{0}; i<38; i++) {
            password[i] = static_cast<char>(getRandomNumber(32,126));
        }

        printf("Hello, welcome to YetiCTF !\nI hope, that u remember your password,\ncoz him is very HARD!\n");
        printf("Good luck, have fun!\n");

        printf("Give me your HARD password: ");
        std::cin.getline(user_input, 38, '\n');

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767,'\n');
            printf("%s","Its not pwn!\nJust try again!\n\n");
            continue;
        }
        else 
            printf("%s", "Successfully input!\n");

        for (int k(0); k<38; k++) {
            if ((int)user_input[k] > 32 && (int)user_input[k] < 126) {
                password[k] ^= user_input[k];
                if ((int)password[k] > 32 && (int)password[k] < 126)
                    password[k] ^= user_input[k];    
            }
            else
                break;
        }
        for (int i(0); i<38; i++) {
            if ((int)user_input[i] > 32 && (int)user_input[i] < 126) 
                password[i] ^= user_input[i];
            else
                continue;
        }

        if (help) {
            helper(*user_input);
        }

        for (int res(0); res<38; res++)
            if (password[res] == user_input[res])
                counter++;
            else break;

        if (counter != 37) {
            char choise;

            printf("Try again?\n");
            printf("Press F, to exit or another symbol to continue..\n");
            printf("Your input: ");

            std::cin >> choise;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(32767,'\n');
                std::cout << "Failed choise!\nContinuing..\n";
                continue;
            }

            if (choise == 'F' || choise == 'f')
                break;
            continue;
        }
        else if (counter == 37 && password==user_input) {
            getFlag();
            break;
        }
    }

    delete[] user_input;
    delete[] password;

    return 0;
}
