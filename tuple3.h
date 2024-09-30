#ifndef __TUPLE3_H__
#define __TUPLE3_H__


template<typename T, typename V, typename R>
class Tuple3{
    protected:
        T value1;
        V value2;
        R value3;
    public:
        Tuple3(T value1, V value2, R value3);
        void setValue1(T value1);
        void setValue2(V value2);
        void setValue3(R value3);
        T getValue1();
        V getValue2();
        R getValue3();
};

#include "tuple3.hxx"
#endif