#include <unistd.h>  
#include <stdio.h>  
#include <fcntl.h>  
#include <linux/fb.h>  
#include <sys/mman.h>  
#include <stdlib.h>
#include "yellow_face.zif"
int main()  
{  
    int fbfd = 0;  
    struct fb_var_screeninfo vinfo;  
    struct fb_fix_screeninfo finfo;  
    struct fb_cmap cmapinfo;  
    long int screensize = 0;  
    char *fbp = 0;  
    int x = 0, y = 0;  
    long int location = 0;  
    int b,g,r;  
    // Open the file for reading and writing  
    fbfd = open("/dev/graphics/fb0", O_RDWR,0);                    // ��Frame Buffer�豸  
    if (fbfd < 0) {  
                printf("Error: cannot open framebuffer device.%x\n",fbfd);  
                exit(1);  
    }  
    printf("The framebuffer device was opened successfully.\n");  
  
    // Get fixed screen information  
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {            // ��ȡ�豸������Ϣ  
                printf("Error reading fixed information.\n");  
                exit(2);  
    }  
    printf("\ntype:0x%x\n", finfo.type );                            // FrameBuffer ����,��0Ϊ����  
    printf("visual:%d\n", finfo.visual );                        // �Ӿ����ͣ������2��α��3   
    printf("line_length:%d\n", finfo.line_length );        // ÿ�г���  
    printf("\nsmem_start:0x%lx,smem_len:%u\n", finfo.smem_start, finfo.smem_len ); // ӳ��RAM�Ĳ���  
    printf("mmio_start:0x%lx ,mmio_len:%u\n", finfo.mmio_start, finfo.mmio_len );  
      
    // Get variable screen information  
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {            // ��ȡ�豸�ɱ���Ϣ  
                printf("Error reading variable information.\n");  
                exit(3);  
    }  
    printf("%dx%d, %dbpp,xres_virtual=%d,yres_virtual=%dvinfo.xoffset=%d,vinfo.yoffset=%d\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel,vinfo.xres_virtual,vinfo.yres_virtual,vinfo.xoffset,vinfo.yoffset);  

	screensize = finfo.line_length * vinfo.yres_virtual;
    // Map the device to memory ͨ��mmapϵͳ���ý�framebuffer�ڴ�ӳ�䵽�û��ռ�,������ӳ������ʼ��ַ  
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,fbfd, 0);  
    if ((int)fbp == -1) {  
                printf("Error: failed to map framebuffer device to memory.\n");  
                exit(4);  
    }  
    printf("The framebuffer device was mapped to memory successfully.\n");  
/***************exampel 1**********************/
	b = 10;
	g = 100;
	r = 100;
    for ( y = 0; y < 340; y++ )
        for ( x = 0; x < 420; x++ ) { 
      
         location = (x+100) * (vinfo.bits_per_pixel/8) + 
             (y+100) * finfo.line_length; 
      
         if ( vinfo.bits_per_pixel == 32 ) {        //          
                        *(fbp + location) = b; // Some blue  
                        *(fbp + location + 1) = g;             // A little green  
                        *(fbp + location + 2) = r;             // A lot of red  
                        *(fbp + location + 3) = 0;     // No transparency  
         }
      
        }
/*****************exampel 1********************/
/*****************exampel 2********************/		
 	unsigned char *pTemp = (unsigned char *)fbp;
	int i, j;
	//��ʼ����(x,y),�յ�����(right,bottom)
	x = 400;
	y = 400;
	int right = 700;//vinfo.xres;
	int bottom = 1000;//vinfo.yres;
	
	for(i=y; i< bottom; i++)
	{
		for(j=x; j<right; j++)
		{
			unsigned short data = yellow_face_data[(((i-y)  % 128) * 128) + ((j-x) %128)];
			pTemp[i*finfo.line_length + (j*4) + 2] = (unsigned char)((data & 0xF800) >> 11 << 3);
			pTemp[i*finfo.line_length + (j*4) + 1] = (unsigned char)((data & 0x7E0) >> 5 << 2);
			pTemp[i*finfo.line_length + (j*4) + 0] = (unsigned char)((data & 0x1F) << 3);
		}
	} 
/*****************exampel 2********************/	
//note��vinfo.xoffset =0 vinfo.yoffset =0 ����FBIOPAN_DISPLAY���ɹ�
	if (ioctl(fbfd, FBIOPAN_DISPLAY, &vinfo)) {    
                printf("Error FBIOPAN_DISPLAY information.\n");  
                exit(5);  
    }  
	sleep(10);
	munmap(fbp,finfo.smem_len);//finfo.smem_len == screensize == finfo.line_length * vinfo.yres_virtual 
    close(fbfd);  
    return 0;  
}  