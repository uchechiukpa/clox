#include <stdio.h>
#include "memory.h"
#include "value.h"



void initValueArray(ValueArray* array){

    //Remember the count and capacity is used to dynamically expand the array
    array->values = NULL; //The values pointer is initiallized 
    array->capacity = 0; //The capacity of the array is initialized and set to 0
    array->count = 0; //The count of the array is initialized and set to 0
}

void writeValueArray(ValueArray* array, Value value){
    if(array->capacity < array->count + 1){
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values,oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array){
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}


void printValue(Value value){
    printf("%g", value);
}