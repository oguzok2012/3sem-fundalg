#ifndef __TEXTMENU__
#define __TEXTMENU__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define COMMAND_LENGTH 40
#define DESCRIPTION_LENGTH 200

typedef void (*CommandHandler)(void*);
// Codestyle for handler names: handler_<handler-name-in-snake-case>
// Example: handler_print, handler_set_list
// Codestyle for creator/destroyer names: <creator/destroyer>_<name-of-data-structure>
// Default handlers
void handler_undefined();

typedef struct {
    char name[COMMAND_LENGTH];
    char description[DESCRIPTION_LENGTH];
    CommandHandler handler;
} Command;

typedef struct {
    Command *commands;
    int size, capacity;
} CommandStorage;

// CommandStorage interface ====

Command commandCreate(char *name, char *description, void (*handler)(void*));
CommandStorage *commandStorageCreate();
void commandStorageDestroy(CommandStorage *commandStorage);
void commandStoragePush(CommandStorage *commandStorage, Command binding);
void commandStorageClear(CommandStorage *commandStorage);

// \CommandStorage interface ===

// TextMenu interface ====

void textMenuDescript(CommandStorage *storage);
void textMenuMatch(CommandStorage *storage, void *obj, char *name);
void textMenuStart(CommandStorage *storage, void *obj);

// \TextMenu interface ===

// ===================== ||
// Wrapper               ||
// ===================== ||
// ! Use only if you have only one textMenu in your program.
// You also need initialize creator and destroyer functions.

// Order: name, description, handler
void textMenuFastInitialize(int commandCount, ...);
void textMenuFastStart(void *(*creator)(void), void (*destroyer)(void*));
void textMenuFastClose();

#endif