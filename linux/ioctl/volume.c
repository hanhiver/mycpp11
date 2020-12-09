#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define  BASE_VALUE 257

int main(int argc,char *argv[])
{
    int mixer_fd=0;
    char *names[SOUND_MIXER_NRDEVICES]=SOUND_DEVICE_LABELS;
    int value,i;

    printf("\nusage:%s dev_no.[0..24] value[0..100]\n\n",argv[0]);
    printf("eg. %s 0 100\n",argv[0]);
    printf("will change the volume to MAX volume.\n\n");
    printf("The dev_no. are as below:\n");

    for (i=0; i<SOUND_MIXER_NRDEVICES; i++)
    {
        if (i%3==0) printf("\n");
        printf("%s:%d\t\t",names[i],i);
    }

    printf("\n\n");

    if (argc<3)  exit(1);

    if ((mixer_fd = open("/dev/mixer",O_RDWR)))
    {
        printf("Mixer opened successfully,working...\n");
        value=BASE_VALUE*atoi(argv[2]);

        if (ioctl(mixer_fd,MIXER_WRITE(atoi(argv[1])),&value)==0)
            printf("successfully.....");
        else
            printf("unsuccessfully.....");

        printf("done.\n");
    }
    else
        printf("can't open /dev/mixer error....\n");

    exit(0);

}