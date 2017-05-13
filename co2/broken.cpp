#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int main(int argc, char ** argv)
{
	char loopback[7] = {0xFF, 0xFE, 0x04, 0x00, 0x11, 0x22, 0x33};
	int i, j, n = 0;
//	char buf[256];
	char *buf;
	buf = new char[8];
	int fd;
	char input;

	// Open the Port. We want read/write, no "controlling tty" status, and open it no matter what state DCD is in
	fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		perror("open_port: Unable to open /dev/ttyAMA0 - ");
		return(-1);
	}

	while(1)
	{
		usleep(500000);
		std::cout << "Command: ";
		std::cin >> input;

		if (input == 'q')
		 break;

		else
		{
			// Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
			fcntl(fd, F_SETFL, 0);
			struct termios options;
			tcgetattr(fd, &options);
			options.c_cflag = B19200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
			options.c_iflag = IGNPAR;
			options.c_oflag = 0;
			options.c_lflag = 0;
			tcflush(fd, TCIFLUSH);
			tcsetattr(fd, TCSANOW, &options);

			// Write to the port
//			n = write(fd, loopback,7);
			printf("%X\n", loopback[0]);
//			printf("%d\n", n);

//			if (n < 0) 
//			{
//		    	perror("Write failed - ");
//		    	return -1;
//			}

			printf("0");

			usleep(50000);

			printf("1");

			// Read up to 255 characters from the port if they are there
			buf[0] = '\0';

			printf("2");

			n = read(fd, buf, 255);

			printf("3");		

			if (n < 0) 
			{
				perror("Read failed - ");
				return -1;
			} 
			else if (n == 0) 
			{
				printf("No data on port\n");
			}
			else 
			{
				buf[n] = '\0';
				printf("%i bytes read : %s\n", n, buf);
				for (j = 0; j < n; j++)
				{	
					// print shit
					printf("%X ", buf[n]);	
				}
				printf("\n");
			}
		}
	}

	// Don't forget to clean up
	close(fd);
	return 0;
}

