#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>

#define SYS_kernel_2d_memcpy 449

int main(int argc, char** argv){
    float myArr[4][4] = {
        {5.020, 2.123, 8.010, 4.100},
        {6.080, 3.001, 9.020, 6.200},
        {7.050, 4.002, 7.030, 7.300},
        {8.409, 6.003, 3.040, 8.400},
    };

    float arrcopy[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", myArr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int ret_val = syscall(SYS_kernel_2d_memcpy, myArr, arrcopy, 80);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", arrcopy[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("\nReturn value: %d\n", ret_val); 

    return 0;
}