#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <signal.h>

void sig_handler(int sig);
int ctrl_c_pressed = 0;

int main(int argc, char ** argv) {
  int fd;
  // Open the Port. We want read/write, no "controlling tty" status, and open it no matter what state DCD is in
  fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("open_port: Unable to open /dev/ttyAMA0 - ");
    return(-1);
  }

  // Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
  fcntl(fd, F_SETFL, 0);

	struct termios options;
	tcgetattr(fd, &options);
	options.c_cflag = B19200; // | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
//	options.c_oflag = 0;
//	options.c_lflag = 0;
//	tcflush(fd, TCIFLUSH);
//	tcsetattr(fd, TCSANOW, &options);

  // Read up to 255 characters from the port if they are there
	char buf[256];
	int n = 0;

	while (n==0)
	{
		n = read(fd, (void*)buf, 255);
		if (n < 0) 
		{
    		perror("Read failed - ");
    		return -1;
		} 
		else if (n == 0)
		{
		}
        else if(ctrl_c_pressed)
		{
			printf("aborting...");
			break;
		}
		else 
		{
    		buf[n] = '\0';
    		printf("%i bytes read : %s", n, buf);
			break;
  		}
	}

  // Don't forget to clean up
  close(fd);
  return 0;
}

void sig_handler(int sig)
{
    write(0,"nCtrl^C pressed in sig handlern",32);
    ctrl_c_pressed = 1;
}
