#ifndef __TUPLE2_H__
#define __TUPLE2_H__


template<typename T, typename V>
class Tuple2{
    protected:
        T value1;
        V value2;
    public:
        Tuple2(T value1, V value2);
        void setValue1(T value1);
        void setValue2(V value2);
        T getValue1();
        V getValue2();
};

#include "tuple2.hxx"
#endif