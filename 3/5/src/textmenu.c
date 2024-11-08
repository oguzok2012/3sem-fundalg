#include "textmenu.h"

void handler_undefined() {
    printf("Undefined command\n");
}

// CommandStorage interface ====

Command commandCreate(char *name, char *description, void (*handler)(void*)) {
    Command command;
    strcpy(command.name, name);
    strcpy(command.description, description);
    command.handler = handler;
    return command;
}

CommandStorage *commandStorageCreate() {
    CommandStorage *storage = malloc(sizeof(CommandStorage));
    storage->capacity = 1;
    storage->size = 0;
    storage->commands = malloc(sizeof(Command));
    return storage;
}

void commandStorageDestroy(CommandStorage *commandStorage) {
    assert(commandStorage != NULL);
    free(commandStorage->commands);
    free(commandStorage);
}

void commandStoragePush(CommandStorage *storage, Command command) {
    assert (storage != NULL);
    storage->size++;
    if (storage->size > storage->capacity) {
        storage->capacity *= 2;
        storage->commands = realloc(storage->commands, storage->capacity * sizeof(Command));
    }
    storage->commands[storage->size - 1] = command;
}

// \CommandStorage interface ===


// TextMenu interface ====

void textMenuDescript(CommandStorage *storage) {
    assert (storage != NULL);
    for (int i = 0; i < storage->size; i++) {
        char *line = storage->commands[i].description;
        printf("    %s\n", line);
    }
    printf("---------------\n    help - view the list of commands.\n");
    printf("    exit - exit program.\n");
}

void textMenuMatch(CommandStorage *storage, void *obj, char *name) {
    assert (storage != NULL);
    for (int i = 0; i < storage->size; i++) {
        if (strcmp(name, storage->commands[i].name) == 0) {
            (*(storage->commands[i].handler))(obj);
            return;
        }
    }
    handler_undefined();
}


void textMenuStart(CommandStorage *storage, void *obj) {
    assert(storage != NULL && obj != NULL);

    printf("Hello! You are in interactive mode. Here's the list of commands:\n");
    textMenuDescript(storage);

    char command_input[COMMAND_LENGTH];

    while (true) {

        printf("> ");
        
        if (scanf("%s", command_input) == EOF) {
            printf("Goodbye!\n");
            return;
        } 
        
        if (strcmp(command_input, "exit") == 0) {
            printf("Goodbye!\n");
            return;
        }
        if (strcmp(command_input, "help") == 0) {
            textMenuDescript(storage);
            continue;
        }
        textMenuMatch(storage, obj, command_input);
    }
}

// \TextMenu interface ===


// ===================== ||
// Macro Wrapper         ||
// ===================== ||

CommandStorage *GLOBAL_STORAGE;

void textMenuFastInitialize(int commandCount, ...) {
    GLOBAL_STORAGE = commandStorageCreate();

    va_list args;
    va_start(args, commandCount);

    for (int i = 0; i < commandCount; i++) {

        char *name = va_arg(args, char*);
        char *description = va_arg(args, char*);
        CommandHandler handler = va_arg(args, CommandHandler);

        Command command = commandCreate(name, description, handler);
        commandStoragePush(GLOBAL_STORAGE, command);

    }

    va_end(args);
}

void textMenuFastStart(void *(*creator)(void), void (*destroyer)(void*)) {
    assert(GLOBAL_STORAGE != NULL && (creator != NULL) && (destroyer != NULL));
    void *obj = (*creator)();
    textMenuStart(GLOBAL_STORAGE, obj);
    (*destroyer)(obj);
}

void textMenuFastClose() {
    commandStorageDestroy(GLOBAL_STORAGE);
    GLOBAL_STORAGE = NULL;
}