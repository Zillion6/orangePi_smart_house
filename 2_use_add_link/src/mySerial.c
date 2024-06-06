#include "mySerial.h"

int my_serialOpen (const char *device, const int baud)
{
	struct termios options ;
	speed_t myBaud ;
	int     status, fd ;

  	switch (baud)
  	{
    	case    9600:	myBaud =    B9600 ; break ;
    	case  115200:	myBaud =  B115200 ; break ;

    	default:
      	return -2 ;
  	}

  	if ((fd = open (device, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1)
    return -1 ;

  	fcntl (fd, F_SETFL, O_RDWR) ;

// Get and modify current options:

  	tcgetattr (fd, &options) ;

    cfmakeraw   (&options) ;
    cfsetispeed (&options, myBaud) ;
    cfsetospeed (&options, myBaud) ;

    options.c_cflag |= (CLOCAL | CREAD) ;
    options.c_cflag &= ~PARENB ;
    options.c_cflag &= ~CSTOPB ;
    options.c_cflag &= ~CSIZE ;
    options.c_cflag |= CS8 ;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG) ;
    options.c_oflag &= ~OPOST ;

    options.c_cc [VMIN]  =   0 ;
    options.c_cc [VTIME] = 100 ;	// Ten seconds (100 deciseconds)

  	tcsetattr (fd, TCSANOW, &options) ;

  	ioctl (fd, TIOCMGET, &status);

  	status |= TIOCM_DTR ;
  	status |= TIOCM_RTS ;

  	ioctl (fd, TIOCMSET, &status);

  	usleep (10000) ;	// 10mS

 	return fd ;
}

void my_serialPuts(const int fd, const char *s, int len)
{
	printf("%s|%s|%d:s = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", __FILE__, __FUNCTION__, __LINE__, s[0], s[1], s[2], s[3], s[4], s[5]);
	
	int n_write = write(fd, s, len);

	printf("%s|%s|%d:n_write = %d\n", __FILE__, __FUNCTION__, __LINE__, n_write);

	if(n_write == -1)
	{
		perror("write");

		exit(-1);
	}

}

int my_serialGets(const int fd, unsigned char *buffer)
{
	int n_read = read(fd, buffer, 32);
	if(n_read == -1)
	{
		perror("read");

		exit(-1);
	}

	return n_read;
}

char* serialGetchar(const int fd)
{
	char *x;

  	if (read (fd, x, 1) != 1)
    exit(-1);

  	return x;
}