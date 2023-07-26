#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]){
    Chunk chunk;
    initChunk(&chunk); // set chunk to beginning values

    int constant = addConstant(&chunk, 1.2); // add a constant to our constant array
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);
    writeChunk(&chunk, OP_RETURN, 123);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}