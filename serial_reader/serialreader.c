#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
  int fd, n, i;
  char buf = '\0';
  struct termios toptions;

  char response[1024];
  memset(response, '\0', sizeof(response));
  i=0; n=0; fd=0;

  /* open serial port */
  if(argc==1)
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
  else
    fd = open(argv[1], O_RDWR | O_NOCTTY);

  if(fd<0)
  {
    printf("error open()\n");
    return 1;
  }
  printf("fd %i\n", fd);

  /* wait for the Arduino to reboot */
  printf("waiting for the Arduino to reboot...");
  fflush(stdout);
  usleep(3500000);
  printf(" DONE\n");

  /* get current serial port settings */
  tcgetattr(fd, &toptions);
  /* set 9600 baud both ways */
  cfsetispeed(&toptions, B9600);
  cfsetospeed(&toptions, B9600);
  /* 8 bits, no parity, no stop bits */
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  /* Canonical mode */
  toptions.c_lflag |= ICANON;
  /* commit the serial port settings */
  tcsetattr(fd, TCSANOW, &toptions);


  while(1)
  {
    i=0;
    do
    {
      n = read( fd, &buf, 1 );
      if(n>0)
      {
        //printf("%c\n",buf);
        response[i]=buf;
        //i += n;
        i++;
      }
    }
    while( buf != '\r');

    response[i]=0;

    printf("%s", response);
  }

  return 0;
}
