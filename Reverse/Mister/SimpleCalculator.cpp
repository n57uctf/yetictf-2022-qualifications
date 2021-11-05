#include "SimpleCalculator.h"
 
template <typename T>
void SimpleCalculator<T>::setNum1(T num) {
    this->m_num1 = num;
}

template <typename T>
void SimpleCalculator<T>::setNum2(T num) {
    this->m_num2 = num;
}

template <typename T>
const T SimpleCalculator<T>::getNum1() {
    return this->m_num1;
}

template <typename T>
const T SimpleCalculator<T>::getNum2() {
    return this->m_num2;
}
