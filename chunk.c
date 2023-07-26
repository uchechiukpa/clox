#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

//chuck is use to refer to a sequence of bytecode

/* bytecodes explained, let's say you had a information you wanted to pass across and you wanted people to get the message, translating the message to every different form of language will be crazy and time consuming, 
 so you transform the lanaguge into instruction that are clear, so anyone can pick it and transform it into thier native language.
*/
void initChunk(Chunk* chunk){
    chunk->count = 0; //count of count:  on initialization we set count to zero 
    chunk->capacity = 0; // capacity of chunk: on initailization we set count to zero
    chunk->code = NULL; // code is a pointer, so we set it to NULL to initialize it 
    // chunk->lines = NULL; // like is a pointer as well and is set to null to initailize it


    //constants its a struct called ValueArray
    //     typedef struct {
    //     int capacity;
    //     int count;
    //     Value* values;
    // } ValueArray;
    // the count and capacity is used to grow the values array dynamically

    initValueArray(&chunk->constants); // initValueArray recieves the address of struct 
    // initLineArray()
}

void freeChunk(Chunk* chunk){
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}
void writeChunk(Chunk* chunk, uint8_t byte, int line){
    // if capacity is less than count + 1, that means the capacity is full and we need to increase the capacity
    if(chunk->capacity < chunk->count + 1){
        // assign capacity  to a variable called capacity
        int oldCapacity = chunk->capacity;
        // then we grow the capacity
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        /* we grow the size of the code Array to make sure it can contain our code
         a compile time this will be (uint8_t*)reallocate(chunk->code, sizeof(uint8_t) * (oldCapacity),  sizeof(uint8_t)* (chunk->capacity))
         we use type casting so the pointer is pointing to the correct type 
        */
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);

        // this grows the array of line as the code grows
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
        
    }
    // if the capacity is still sufficient, we assign the code[count] the code
    chunk->code[chunk->count] = byte;
    // if the capacity is still sufficient, we assign the lines[count] the line
    chunk->lines[chunk->count] = line;
    //we increase count
    chunk->count++;
}
// takes in a pointer to the struct, to be able to access constant, and the value to be added 
int addConstant(Chunk* chunk, Value value){ 
    writeValueArray(&chunk->constants, value); // we write the value to the constant to the value
    return chunk->constants.count - 1;
}

