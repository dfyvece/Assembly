
/*
 * Large Number Support using Inline Assembly Demo
 * @author Kevin Vece
 *
 * To compile on linux:
 * gcc -m32 -masm=intel -w gen.c -o gen
 *
 * If you're on a 64-bit machine, you may need gcc-multilib:
 * sudo apt-get install gcc-multilib
 * or
 * sudo apt-get install gcc-*-multilib
 *
 * To run:
 * ./gen
 */

// THIS IS THE BYTE WIDTH OF YOUR NUMBER (must be > 1)
const int SIZE = 4;


int p(int** m, int s) {
    const char* f = "";
    const char* x = "%08x";
    const char* n = "\n";
    asm(
        "push esi\n"
        "push edi\n"
        "push dword ptr [ebp-12]\n"
        "call printf\n"
        "add esp, 4\n"
        "mov esi, [ebp+8]\n"
        "mov ecx, [ebp+12]\n"
        "sub ecx, 1\n"        
        "f:\n"
            "add esi, 4\n"
        "loop f\n"
        "mov edi, [ebp+12]\n"
        "push dword ptr [esi]\n"
        "push dword ptr [ebp-8]\n"
        "do:\n"
            "call printf\n"
            "sub esi, 4\n"
            "mov eax, [esi]\n"
            "mov [esp+4], eax\n"
            "sub edi, 1\n"
        "jnz do\n"
        "push dword ptr [ebp-4]\n"
        "call printf\n"
        "add esp, 12\n"
        "pop edi\n"
        "pop esi\n"
        "mov eax, 1\n"
    );
}

int a(int** m, int s) {
    asm(
        "mov ecx, [ebp+12]\n" 
        "mov eax, [ebp+8]\n"
        "sub eax, 4\n"
        "da:\n"
            "cmp eax, [ebp+8]\n"
            "jl s\n"
                "mov [eax], ebx\n"
            "s:\n"
            "add eax, 4\n"
            "sub ecx, 1\n"
            "jz dn\n"
            "mov ebx, [eax]\n"
            "add ebx, 1\n"
        "jz da\n"
        "mov [eax], ebx\n"
        "mov eax, 1\n"
        "leave\n"
        "ret\n"

        "dn:\n"
        "mov eax, 0\n"
    );
}


int c(int** m, int s) {
    asm(
        "push edi\n"
        "mov edi, [ebp+8]\n"
        "mov ecx, [ebp+12]\n"
        "xor eax, eax\n"
        "rep stosd\n"
        "pop edi\n"
        "mov al, 1\n"
    );
}

int main() {
    int n[SIZE];
    c(&n, SIZE);
    while (p(&n, SIZE) && a(&n, SIZE));
    return 0;
}
