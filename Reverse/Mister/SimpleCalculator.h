#ifndef SIMPLECALCULATOR_H
#define SIMPLECALCULATOR_H

#include <iostream>

template <class T>
class SimpleCalculator {

    T m_num1;
    T m_num2;
    T m_result;
    char* object_name = new char[256];

public:

    SimpleCalculator() {
        std::cout << "Simple constructor" << std::endl;
        this->object_name = "Simple object";
        m_num1 = 0, m_num2 = 0;
    }

    SimpleCalculator(T num1, T num2) {
        this->m_num1 = num1;
        this->m_num2 = num2;

        size_t size_num1 = sizeof(num1);
        size_t size_num2 = sizeof(num2);

        if (size_num1 == size_num2 && size_num1 == 4) {
            this->object_name = "simple integer object";
        }
        else if (size_num1 == size_num2 && size_num1 == 8) {
            this->object_name = "simple double object";
        }
        else if (size_num1 == 4 && size_num2 == 8) {
            this->object_name = "int and double object";
        }
        else if (size_num1 == 8 && size_num2 == 4) {
            this->object_name = "double and int object";
        }
        else {
            this->object_name = "unknown object ?!";
        }
    }

    const T getNum1();

    const T getNum2();

    void setNum1(T num); 

    void setNum2(T num); 

    SimpleCalculator& operator+(SimpleCalculator<T>& operand1)
    {
        this->setNum1(this->getNum1()+operand1.getNum1());
        this->setNum2(this->getNum2()+operand1.getNum2());

        return *this;
    }

    SimpleCalculator& operator-(SimpleCalculator<T>& operand1)
    {
        this->setNum1(this->getNum1()-operand1.getNum1());
        this->setNum2(this->getNum2()-operand1.getNum2());

        return *this;
    }

    SimpleCalculator& operator/(SimpleCalculator<T>& operand1)
    {
        this->setNum1(this->getNum1()/operand1.getNum1());
        this->setNum2(this->getNum2()/operand1.getNum2());

        return *this;
    }

    SimpleCalculator& operator*(SimpleCalculator<T>& operand1)
    {
        this->setNum1(this->getNum1()*operand1.getNum1());
        this->setNum2(this->getNum2()*operand1.getNum2());

        return *this;
    }

    ~SimpleCalculator() {
        std::cout << "Destruct object with name: " << object_name << std::endl;
        object_name = nullptr;
    }

};

#endif