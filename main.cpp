#include <iostream>
#include <stdint.h>
#include <stdlib.h>

/// The memory size.
#define MEMORY_SIZE 32

/// Represents the kind of the opcode.
typedef enum {
    Loadi, // Loadi rx l1
    Addi, // Addi rx ra l1
    Compare, // Compare rx ra rb
    Jump, // Jump l1
    Branch, // Branch ra l1
    Exit // Exit
} opcode_kind_t;

/// Represents an opcode with 3 operands.
class Opcode
{
    public:
        opcode_kind_t kind;
        int64_t op1;
        int64_t op2;
        int64_t op3;
        Opcode(opcode_kind_t kind, int64_t op1 = 0, int64_t op2 = 0, int64_t op3 = 0)
            : kind(kind), op1(op1), op2(op2), op3(op3) {}
};

/// Entry point.
int main() {
    // Program memory (registers)
    int memory[MEMORY_SIZE] = { 0 };
    // Program code to execute.
    const Opcode code[] = {
        Opcode(Loadi, 0, 1000000000), // r0 = 1000000000;
        Opcode(Loadi, 1, 0), // r1 = 0;
        Opcode(Compare, 2, 0, 1), // r2 = r0 == r1;
        Opcode(Branch, 2, 2), // if (r2 == 0) goto +2;
        Opcode(Addi, 1, 1, 1), // r0 = r0 + 1;
        Opcode(Jump, -4), // goto -4;
        Opcode(Exit)
    };
    // Program Counter.
    size_t pc = 0;
    // The VM itself.
    for (;;) {
        const Opcode op = code[pc];
        // printf("(%u) Kind = %u\n\tr0=%d\tr1=%d\tr2=%d\n", pc, op.kind, memory[0], memory[1], memory[2]);
        switch (op.kind) {
            case Loadi: { memory[op.op1] = op.op2; break; }
            case Addi: { memory[op.op1] = memory[op.op2] + op.op3; break; }
            case Compare: { memory[op.op1] = memory[op.op2] == memory[op.op3]; break; }
            case Jump: { pc += op.op1; break; }
            case Branch: { if (memory[op.op1] != 0) pc += op.op1; break; }
            case Exit: { goto end; }
        }
        pc++;
    }
    end: std::cout << "Result: " << memory[1] << std::endl;
    return EXIT_SUCCESS;
}
