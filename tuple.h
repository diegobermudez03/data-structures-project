#ifndef __TUPLE_H__
#define __TUPLE_H__


template<typename T, typename V>
class Tuple{
    protected:
        T value1;
        V value2;
    public:
        Tuple(T value1, V value2);
        void setValue1(T value1);
        void setValue2(T value1);
        T getValue1();
        V getValue2();
};

#include "tuple.hxx"
#endif