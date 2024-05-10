#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "../include/so_utils.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSGDATA_MAX_SIZE 8192

/**
 *  KEY to be used on all Linux IPC get operations
 */
#define IPC_KEY 0xcedc      // Suggestion: Replace with your student number

#endif // __DEFINES_H__