#include "tuple3.h"


template<typename T, typename  V, typename R>
Tuple3<T, V, R>::Tuple3(T value1, V value2, R value3){
    this->value1 = value1;
    this->value2 = value2;
    this->value3 = value3;
}

template<typename T, typename  V, typename R>
void Tuple3<T, V, R>::setValue1(T value1){
    this->value1 = value1;
}

template<typename T, typename  V, typename R>
void Tuple3<T, V, R>::setValue2(V value2){
    this->value2 = value2;
}

template<typename T, typename  V, typename R>
void Tuple3<T, V, R>::setValue3(R value3){
    this->value3 = value3;
}


template<typename T, typename  V, typename R>
T Tuple3<T, V, R>::getValue1(){
    return this->value1;
}

template<typename T, typename  V, typename R>
V Tuple3<T, V, R>::getValue2(){
    return this->value2;
}

template<typename T, typename  V, typename R>
R Tuple3<T, V, R>::getValue3(){
    return this->value3;
}