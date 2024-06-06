#include <stdio.h>
#include <stdlib.h>
#include "face.h"

int main()
{
    double face = 0.00;
    face_Init();
    face  = alicloud_Search_Face();
    printf("face = %f\n", face);
    face_Finalize();
    
    return 0;
}