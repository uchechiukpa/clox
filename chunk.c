#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

//chuck is use to refer to a sequence of bytecode

void initChunk(Chunk* chunk){
    chunk->count = 0; //count of count:  on initialization we set count to zero 
    chunk->capacity = 0; // capacity of chunk: on initailization we set count to zero
    chunk->code = NULL; // code is a pointer, so we set it to NULL to initialize it 
    chunk->lines = NULL; // like is a pointer as well and is set to null to initailize it


    //constants its a struct called ValueArray
    //     typedef struct {
    //     int capacity;
    //     int count;
    //     Value* values;
    // } ValueArray;
    // the count and capacity is used to grow the values array dynamically

    initValueArray(&chunk->constants); // initValueArray recieves the address of struct 
};

void freeChunk(Chunk* chunk){
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}
void writeChunk(Chunk* chunk, uint8_t byte, int line){
    if(chunk->capacity < chunk->count + 1){
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
        
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value){
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

