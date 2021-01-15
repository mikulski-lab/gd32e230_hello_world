#ifndef _RETARGET_H_
#define _RETARGET_H_

#include <sys/stat.h>

void retarget_init();
int _isatty(int fd);
int _write(int fd, char* ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char* ptr, int len);
int _fstat(int fd, struct stat* st);

#endif //#ifndef _RETARGET_H_