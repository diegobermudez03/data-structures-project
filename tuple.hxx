#include "tuple.h"


template<typename T, typename  V>
Tuple<T, V>::Tuple(T value1, V value2){
    this->value1 = value1;
    this->value2 = value2;
}

template<typename T, typename  V>
void Tuple<T, V>::setValue1(T value1){
    this->value1 = value1;
}

template<typename T, typename  V>
void Tuple<T, V>::setValue1(T value1){
    this->value2 = value2;
}

template<typename T, typename  V>
T Tuple<T, V>::getValue1(){
    return this->value1;
}

template<typename T, typename  V>
V Tuple<T, V>::getValue2(){
    return this->value2;
}