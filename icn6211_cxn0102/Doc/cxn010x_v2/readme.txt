add /dev/input/uevent2 cxn010x
add /dev/cxn010x file node for i2c read write interface 

�ڴ���/dev/cxn010x ,��Ϊi2c��д�豸�Ľӿڣ�ר���ڶ�дi2c0 cxn0102,���ɶ�д32���ֽڣ�����д��һ���򵥵Ĳ��Դ����������

�۴���/dev/input/event2 ����cxn0102����notify����ʱ��ͨ��uevent�ϱ���֪ͨӦ�ó����ȡcxn0102�����ݡ�
  �����ϱ����¼����¼��룬�¼�ֵ���£�
        
�ܴ���/sys/class/i2c-dev/i2c-0/device/0-0077/cxn_ctl�����ڿ���cxn0102�����ߣ�����״̬������������
     echo 0 >/sys/class/i2c-dev/i2c-0/device/0-0077/cxn_ctl
    echo 1 >/sys/class/i2c-dev/i2c-0/device/0-0077/cxn_ctl

test progarm:
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define DEVICE_NAME "/dev/cxn010x"
int main(int argc, char** argv)
{
    int fd = -1;
    int tt[3]={0};
    char xx[3]={0};
    fd = open(DEVICE_NAME, O_RDWR);
    if(fd == -1) {
        printf("Failed to open device %s\n", DEVICE_NAME);
        return -1;
    }
    read(fd,xx,3);
    printf("read value %d,%d,%d\n",xx[0],xx[1],xx[2]);
    
		tt[0] = 2 ;
		tt[1] = 1 ;
 
    write(fd, tt, 2);//shutdown input
    
    close(fd);
    return 0;
}