#include "tuple2.h"


template<typename T, typename  V>
Tuple2<T, V>::Tuple2(T value1, V value2){
    this->value1 = value1;
    this->value2 = value2;
}

template<typename T, typename  V>
void Tuple2<T, V>::setValue1(T value1){
    this->value1 = value1;
}

template<typename T, typename  V>
void Tuple2<T, V>::setValue2(V value2){
    this->value2 = value2;
}

template<typename T, typename  V>
T Tuple2<T, V>::getValue1(){
    return this->value1;
}

template<typename T, typename  V>
V Tuple2<T, V>::getValue2(){
    return this->value2;
}