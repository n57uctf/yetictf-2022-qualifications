#include "SimpleCalculator.h"

// Your goal to fix something!
// flag format: YetiCTF{...}


int main() {

    std::cout << "+--- Simple Calc ---+" << std::endl;

    std::cout << "Start items: " << std::endl; 

    int int_num1 = 1234, int_num2 = 5678;

    std::cout << "First integer number: " << int_num1 << "\n" <<
    "Second integer number: " << int_num2 << "\n";

    double double_num1 = 12.5, double_num2 = 21.2;

    std::cout << "First double number: " << int_num1 << "\n" <<
    "Second double number: " << int_num2 << "\n";

    SimpleCalculator<double> obj1(int_num1, int_num2);
    SimpleCalculator<double> obj2(double_num1, double_num2);

    obj1 + obj2;
    std::cout << "Left  res: " << obj1.getNum1() << std::endl;
    std::cout << "Right res: " << obj1.getNum2() << std::endl;

    obj1 / obj2;
    std::cout << "Left  res: " << obj1.getNum1() << std::endl;
    std::cout << "Right res: " << obj1.getNum2() << std::endl;

    std::cout << "Normal exit.." << std::endl;

    return 0;
}