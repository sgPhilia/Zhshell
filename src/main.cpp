#include "shell.h"  

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    init_shell();
    shell_loop();
    return 0;
}