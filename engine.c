#include <stdio.h>
#include "head.h"

void execute_commands(const Rule rule) {
    for (int i = 0; i < rule.command_count; i++) {
        printf("Executing command: %s\n", rule.commands[i]);
        system(rule.commands[i]);
    }
}
