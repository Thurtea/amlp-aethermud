#include "src/compiler.h"
#include "src/program.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    fprintf(stderr, "Testing compilation of lib/std/player.lpc...\n");
    
    Program *prog = compiler_compile_file("lib/std/player.lpc");
    
    if (!prog) {
        fprintf(stderr, "ERROR: Failed to compile player.lpc\n");
        return 1;
    }
    
    fprintf(stderr, "SUCCESS: player.lpc compiled\n");
    fprintf(stderr, "  Functions: %zu\n", prog->function_count);
    fprintf(stderr, "  Globals: %zu\n", prog->global_count);
    
    // List some key functions
    for (size_t i = 0; i < prog->function_count && i < 10; i++) {
        fprintf(stderr, "  - %s()\n", prog->functions[i].name);
    }
    
    program_free(prog);
    return 0;
}
