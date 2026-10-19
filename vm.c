#include <stdio.h>
#include <assert.h>
#include "stack.c"
#include "vm.h"

enum Vm_error_status
{
    VM_OKAY = 0,
    ERROR_STACKPOP = 1,
    ERROR_STACKPUSH = 2
};

typedef struct
{
    Stack_t* stk;
    int registers[4];
    int* program;
    size_t ip;
    int state;
} SPU;

int GetParametersAmount(int func);
void FunctionCall (SPU* spu, int func, int num, int num_args);
Vm_error_status StackHlt (SPU* spu);
Vm_error_status StackAdd (SPU* spu);
Vm_error_status StackSub (SPU* spu);
Vm_error_status StackMul (SPU* spu);
Vm_error_status StackDiv (SPU* spu);
Vm_error_status StackOut (SPU* spu);

int main ()
{
    FILE* code_file = fopen ("code.txt", "r");
    if (!code_file) {
        printf ("Error: file not found\n");
        return 1;
    }
    SPU* spu = (SPU*)calloc(1, sizeof(SPU));
    spu->stk = (Stack_t*)calloc(1, sizeof(Stack_t));
    StackInit(spu->stk, 1);
    char buffer[256] = {};
    int func = 0;
    int num = 0;
    while ((fgets (buffer, sizeof(buffer), code_file)) != NULL)
    {
        if (spu->state != 0)
            break;
        int num_args = sscanf (buffer, "%d %d", &func, &num);
        FunctionCall (spu, func, num, num_args);
    }

    return 0;
}

int GetParametersAmount(int func)
{
    if (func == PUSH) {
        return 2;
    }
    if (func >= HLT && func <= OUT) {
        return 1;
    }
    return 0;
}

void FunctionCall (SPU* spu, int func, int num, int num_args)
{
    assert (spu);
    if (GetParametersAmount(func) != num_args) {
        printf ("Unnecessary parameter\n");
        return;
    }
    switch (func) {
        case HLT : StackHlt(spu); break;

        case PUSH : StackPush (spu->stk, num); break;

        case ADD : StackAdd (spu); break;

        case SUB : StackSub (spu); break;

        case MUL : StackMul (spu); break;

        case DIV : StackDiv (spu); break;

        case OUT : StackOut (spu); break;
    }
}

Vm_error_status StackHlt (SPU* spu)
{
    assert (spu);
    spu->state = 2;
    return VM_OKAY;
}

Vm_error_status StackAdd (SPU* spu)
{
    int value1 = 0;
    if (StackPop (spu->stk, &value1) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    int value2 = 0;
    if (StackPop (spu->stk, &value2) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    if (StackPush (spu->stk, value1 + value2) != STACK_OKAY) {
        return ERROR_STACKPUSH;
    }
    return VM_OKAY;
}

Vm_error_status StackSub (SPU* spu)
{
    int value1 = 0;
    if (StackPop (spu->stk, &value1) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    int value2 = 0;
    if (StackPop (spu->stk, &value2) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    if (StackPush (spu->stk, value2 - value1) != STACK_OKAY) {
        return ERROR_STACKPUSH;
    }
    return VM_OKAY;
}

Vm_error_status StackMul (SPU* spu)
{
    int value1 = 0;
    if (StackPop (spu->stk, &value1) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    int value2 = 0;
    if (StackPop (spu->stk, &value2) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    if (StackPush (spu->stk, value1 * value2) != STACK_OKAY) {
        return ERROR_STACKPUSH;
    }
    return VM_OKAY;
}

Vm_error_status StackDiv (SPU* spu)
{
    int value1 = 0;
    if (StackPop (spu->stk, &value1) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    int value2 = 0;
    if (StackPop (spu->stk, &value2) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    if (StackPush (spu->stk, value2 / value1) != STACK_OKAY) {
        return ERROR_STACKPUSH;
    }
    return VM_OKAY;
}

Vm_error_status StackOut (SPU* spu)
{
    int value = 0;
    if (StackPop (spu->stk, &value) != STACK_OKAY) {
        return ERROR_STACKPOP;
    }
    printf ("%d\n", value);
    return VM_OKAY;
}
//TODO: STACK_CANARY_BEGIN , убери обход stackverify на и канарейку пофикси пж пж
