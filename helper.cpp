#include "helper.hpp"

template <typename T>
unsigned int sizeofArray(T array)
{
    return sizeof(array) / sizeof(array[0]);
}