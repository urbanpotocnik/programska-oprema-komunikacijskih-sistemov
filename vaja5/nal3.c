#include <fcntl.h>       
#include <sys/ioctl.h>  
#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#define DEVICE_FILE_NAME "/dev/mydevice"

int main(){
  int file_desc, ret_val;
  char msg[100];
  char msgSend[100]="Text from Application\n";
  printf("Open device file: %s\n", DEVICE_FILE_NAME); 
  file_desc = open(DEVICE_FILE_NAME, 2);
  if (file_desc < 0) {
    printf ("Can't open device file: %s\n", DEVICE_FILE_NAME);
    exit(-1);
  }

  read(file_desc, msg, 100);
  printf("Read from kernel modul : %s \n", msg);
  if (ret_val < 0) 
  {
    printf ("Read from kernel failed:%d\n", ret_val);
    exit(-1);
  }

  write(file_desc, msgSend, strlen(msgSend));
  printf("Write to kernel modul: %s \n", msgSend);
  if (ret_val < 0) 
  {
    printf ("Write to kernel failed:%d\n", ret_val);
    exit(-1);
  }

  sleep(1);
  close(file_desc); 
  printf("Close device file: %s\n", DEVICE_FILE_NAME); 
}