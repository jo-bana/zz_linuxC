#ifndef _COMMON_H_
#define _COMMON_H_

#include <time.h>
//normal
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//network
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//file control
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>//需要遍历目录traverse list
#include <sys/stat.h>

#define PORT 1518
#define SRT_LEN 256
#define BUF_SIZE 65535
#define LISTEN_LENGTH 20


void welcomeAndBye(int nSide);
#endif

