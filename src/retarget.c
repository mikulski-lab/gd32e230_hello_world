#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>

#include "gd32e23x_usart.h"
#include "uart.h"

#if !defined(OS_USE_SEMIHOSTING)

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

static const uint32_t USART = USART0;

void retarget_init() {
  uart_setup();
  /* Disable I/O buffering for STDOUT stream, so that
   * chars are sent out as soon as they are printed. */
  setvbuf(stdout, NULL, _IONBF, 0);
}

int _isatty(int fd) {
  if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    return 1;

  errno = EBADF;
  return 0;
}

int _write(int fd, char* ptr, int len) {
  if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
    for (int ii=0; ii<len; ii++) {
      usart_data_transmit(USART, ptr[ii]);
      while(RESET == usart_flag_get(USART, USART_FLAG_TBE));
    }
    return len;
  }
  errno = EBADF;
  return -1;
}

int _close(int fd) {
  if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    return 0;

  errno = EBADF;
  return -1;
}

int _lseek(int fd, int ptr, int dir) {
  (void) fd;
  (void) ptr;
  (void) dir;

  errno = EBADF;
  return -1;
}

int _read(int fd, char* ptr, int len) {
  if (fd == STDIN_FILENO) {
    for(int ii=0; ii<len; ii++) {
      ptr[ii] = usart_data_receive(USART);
    }
    return 0;
  }
  errno = EBADF;
  return -1;
}

int _fstat(int fd, struct stat* st) {
  if (fd >= STDIN_FILENO && fd <= STDERR_FILENO) {
    st->st_mode = S_IFCHR;
    return 0;
  }

  errno = EBADF;
  return 0;
}

#endif //#if !defined(OS_USE_SEMIHOSTING)