#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include<stdlib.h>
#include <time.h>

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int main(){

   int fd; /* File descriptor for the port */

   fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
   if (fd == -1){
   /* Could not open the port. */
    perror("open_port: Unable to open /dev/ttyACMO - ");
   }
   else{
     fcntl(fd, F_SETFL, 0);
   }
   int *rcve;
   int tmp;
   int i;
   while(1){;
      tmp = fcntl(fd, F_SETFL, 0);
      printf("%d\n", tmp); //
      //delay(250);
      printf("-----------------------------\n");
   }

   close(fd);

   /*
   n = write(fd, "ATZ\r", 4);
   if (n < 0)
      fputs("write() of 4 bytes failed!\n", stderr); */


   /*
   n = write(fd, "ATZ\r", 4);
   if (n < 0){
     fputs("write() of 4 bytes failed!\n", stderr);
  }*/

   return 0;
}
