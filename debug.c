#include <stdio.h>

#include "debug.h"
#include "value.h"


void disassembleChunk(Chunk* chunk, const char* name){
    printf("== %s ==, ==== chunk count %d =====\n", name, chunk->count);


    for(int offset = 0;  offset <  chunk->count;){
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset){
    printf("%s\n", name);
    return offset + 1;
}
static int constantInstruction(const char* name, Chunk* chunk, int offset){
    uint8_t constant = chunk->code[offset + 1];
    printf("name %-16s constant %4d '", name , constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;


}

int disassembleInstruction(Chunk* chunk, int offset){
    printf("%04d ", offset);

    if(offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]){
        printf("  |  %d %d", chunk->lines[offset], chunk->lines[offset - 1] );
    }else {
        printf("%4d  offset  %d ", chunk->lines[offset], offset);
    }
    uint8_t instruction = chunk->code[offset];
    switch(instruction){
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        default: 
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }


}

