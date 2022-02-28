/********************************************************
 * Kernels to be optimized for the Metu Ceng Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "Team",                     /* Team name */

    "Ersel Hengirmen",          /* First member full name */
    "e2468015",                 /* First member id */
 
    "Berfinnur Oktay",          /* Second member full name (leave blank if none) */
    "e2375400",                 /* Second member id (leave blank if none) */
 
    "Alim Bican Çoban",         /* Third member full name (leave blank if none) */
    "e2237196"                  /* Third member id (leave blank if none) */

};

/****************
 * EXPOSURE FUSION KERNEL *
 ****************/

/*******************************************************
 * Your different versions of the exposure fusion kernel go here 
 *******************************************************/

/* 
 * naive_fusion - The naive baseline version of exposure fusion
 */
char naive_fusion_descr[] = "naive_fusion: Naive baseline exposure fusion";
void naive_fusion(int dim, int *img, int *w, int *dst) {
  
    int i, j, k; 
    for(k = 0; k < 4; k++){
        for(i = 0; i < dim; i++) {
            for(j = 0; j < dim; j++) {
                    dst[i*dim+j] += w[k*dim*dim+i*dim+j] * img[k*dim*dim+i*dim+j];
            }
        }
    }
}

/* 
 * fusion - Your current working version of fusion
 * IMPORTANT: This is the version you will be graded on
 */
void erselfusion4(int dim, int *img, int *w, int *dst);
char fusion_descr[] = "fusion: Current working version";
void fusion(int dim, int *img, int *w, int *dst) 
{
    erselfusion4(dim, img, w, dst);
}

char erselfusion4_descr[] = "ersel fusion 4: more loop unrolling ";
void erselfusion4(int dim, int *img, int *w, int *dst){

    int i, j, k;
    for(k = 0; k < 4; k++){
        for(i = 0; i < dim; i+=2) {
            for(j = 0; j < dim; j+=4) {
                dst[i*dim+j    ] += w[k*dim*dim+i*dim+j    ] * img[k*dim*dim+i*dim+j    ];
                dst[i*dim+j+dim] += w[k*dim*dim+i*dim+j+dim] * img[k*dim*dim+i*dim+j+dim];

                dst[i*dim+j+1] += w[k*dim*dim+i*dim+j+1] * img[k*dim*dim+i*dim+j+1];
                dst[i*dim+j+1+dim] += w[k*dim*dim+i*dim+j+1+dim] * img[k*dim*dim+i*dim+j+1+dim];
                
                dst[i*dim+j+2] += w[k*dim*dim+i*dim+j+2] * img[k*dim*dim+i*dim+j+2];
                dst[i*dim+j+2+dim] += w[k*dim*dim+i*dim+j+2+dim] * img[k*dim*dim+i*dim+j+2+dim];

                dst[i*dim+j+3] += w[k*dim*dim+i*dim+j+3] * img[k*dim*dim+i*dim+j+3];
                dst[i*dim+j+3+dim] += w[k*dim*dim+i*dim+j+3+dim] * img[k*dim*dim+i*dim+j+3+dim];

            }
        }
    }
}


/*********************************************************************
 * register_fusion_functions - Register all of your different versions
 *     of the fusion kernel with the driver by calling the
 *     add_fusion_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_fusion_functions() 
{
    add_fusion_function(&naive_fusion, naive_fusion_descr);  
    add_fusion_function(&fusion, fusion_descr);  
    add_fusion_function(&erselfusion4, erselfusion4_descr);  
    /* ... Register additional test functions here */
}

/***************************
 * GAUSSIAN BLUR KERNEL *
 ***************************/

/******************************************************
 * Your different versions of the Gaussian blur functions go here
 ******************************************************/

/* 
 * naive_blur - The naive baseline version of Gussian blur
 */
char naive_blur_descr[] = "naive_blur The naive baseline version of Gaussian blur";
void naive_blur(int dim, float *img, float *flt, float *dst) {
  
    int i, j, k, l;

    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
            for(k = 0; k < 5; k++){
                for(l = 0; l < 5; l++) {
                    dst[i*dim+j] = dst[i*dim+j] + img[(i+k)*dim+j+l] * flt[k*dim+l];
                }
            }
        }
    }
}

/* 
 * blur - Your current working version of Gaussian blur
 * IMPORTANT: This is the version you will be graded on
 */
char blur_descr[] = "blur: Current working version";
void blur(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    int k;
    for(k=0;k<=4;k++)
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-4; j+=4) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
            dst[i*dim+j]+=  
                ((img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1] +
                img[(i+k)*dim+j+2] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]));

            dst[i*dim+j+1]+=  
                ((img[(i+k)*dim+j+1] *   flt2[k*5+0]+
                img[(i+k)*dim+j+2] * flt2[k*5+1] +
                img[(i+k)*dim+j+3] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+4] * flt2[k*5+3] +
                img[(i+k)*dim+j+5] * flt2[k*5+4]));

            dst[i*dim+j+2]+=  
                ((img[(i+k)*dim+j+2] *   flt2[k*5+0]+
                img[(i+k)*dim+j+3] * flt2[k*5+1] +
                img[(i+k)*dim+j+4] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+5] * flt2[k*5+3] +
                img[(i+k)*dim+j+6] * flt2[k*5+4]));

            dst[i*dim+j+3]+=  
                ((img[(i+k)*dim+j+3] *   flt2[k*5+0]+
                img[(i+k)*dim+j+4] * flt2[k*5+1] +
                img[(i+k)*dim+j+5] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+6] * flt2[k*5+3] +
                img[(i+k)*dim+j+7] * flt2[k*5+4]));
        }
    }
}

char blur_descr1[] = "blocks double grouped k/l loops removed";
void blur1(int dim, float *img, float *flt, float *dst) {
  
    int i, j;
    
    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
                dst[i*dim+j]+=  ((img[i*dim+j]  * flt[0]+
                                img[i*dim+j+1] * flt[1] +
                                img[i*dim+j+2] * flt[2]) +
                                (img[i*dim+j+3] * flt[3] +
                                img[i*dim+j+4] * flt[4])) +

                                ((img[(i+1)*dim+j]  * flt[dim+0]+
                                img[(i+1)*dim+j+1] * flt[dim+1] +
                                img[(i+1)*dim+j+2] * flt[dim+2]) +
                                (img[(i+1)*dim+j+3] * flt[dim+3] +
                                img[(i+1)*dim+j+4] * flt[dim+4])) +

                                ((img[(i+2)*dim+j]  * flt[2*dim+0]+
                                img[(i+2)*dim+j+1] * flt[2*dim+1] +
                                img[(i+2)*dim+j+2] * flt[2*dim+2]) +
                                (img[(i+2)*dim+j+3] * flt[2*dim+3] +
                                img[(i+2)*dim+j+4] * flt[2*dim+4])) +

                                ((img[(i+3)*dim+j]  * flt[3*dim+0]+
                                img[(i+3)*dim+j+1] * flt[3*dim+1] +
                                img[(i+3)*dim+j+2] * flt[3*dim+2]) +
                                (img[(i+3)*dim+j+3] * flt[3*dim+3] +
                                img[(i+3)*dim+j+4] * flt[3*dim+4])) +

                                ((img[(i+4)*dim+j]  * flt[4*dim+0]+
                                img[(i+4)*dim+j+1] * flt[4*dim+1] +
                                img[(i+4)*dim+j+2] * flt[4*dim+2]) +
                                (img[(i+4)*dim+j+3] * flt[4*dim+3] +
                                img[(i+4)*dim+j+4] * flt[4*dim+4]))
                                ;
            
        }
    }
}

char blur_descr2[] = "flt grouped(double grouped)";
void blur2(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    /* float flt2_24=flt[24];*/
    
    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
                dst[i*dim+j]+=  ((img[i*dim+j]  * flt2[0]+
                                img[i*dim+j+1] * flt2[1] +
                                img[i*dim+j+2] * flt2[2]) +
                                (img[i*dim+j+3] * flt2[3] +
                                img[i*dim+j+4] * flt2[4])) +

                                ((img[(i+1)*dim+j]  * flt2[5]+
                                img[(i+1)*dim+j+1] * flt2[6] +
                                img[(i+1)*dim+j+2] * flt2[7]) +
                                (img[(i+1)*dim+j+3] * flt2[8] +
                                img[(i+1)*dim+j+4] * flt2[9])) +

                                ((img[(i+2)*dim+j]  * flt2[10]+
                                img[(i+2)*dim+j+1] * flt2[11] +
                                img[(i+2)*dim+j+2] * flt2[12]) +
                                (img[(i+2)*dim+j+3] * flt2[13] +
                                img[(i+2)*dim+j+4] * flt2[14])) +

                                ((img[(i+3)*dim+j]  * flt2[15]+
                                img[(i+3)*dim+j+1] * flt2[16] +
                                img[(i+3)*dim+j+2] * flt2[17]) +
                                (img[(i+3)*dim+j+3] * flt2[18] +
                                img[(i+3)*dim+j+4] * flt2[19])) +

                                ((img[(i+4)*dim+j]  * flt2[20]+
                                img[(i+4)*dim+j+1] * flt2[21] +
                                img[(i+4)*dim+j+2] * flt2[22]) +
                                (img[(i+4)*dim+j+3] * flt2[23] +
                                img[(i+4)*dim+j+4] * flt2[24]))
                                ;
            
        }
    }
}

char blur_descr3[] = "BLflt 3 blocks of 8+ 1 reg(not double grouped)";
void blur3(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[24];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    float flt2_24=flt[4*dim+4];
    /* float flt2_24=flt[24];*/
    
    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
                dst[i*dim+j]+=  (img[i*dim+j] *   flt2[0]+
                                img[i*dim+j+1] * flt2[1] +
                                img[i*dim+j+2] * flt2[2] +
                                img[i*dim+j+3] * flt2[3] +
                                img[i*dim+j+4] * flt2[4]) +

                                (img[(i+1)*dim+j] *   flt2[5]+
                                img[(i+1)*dim+j+1] * flt2[6] +
                                img[(i+1)*dim+j+2] * flt2[7] +
                                img[(i+1)*dim+j+3] * flt2[8] +
                                img[(i+1)*dim+j+4] * flt2[9]) +

                                (img[(i+2)*dim+j] *   flt2[10]+
                                img[(i+2)*dim+j+1] * flt2[11] +
                                img[(i+2)*dim+j+2] * flt2[12] +
                                img[(i+2)*dim+j+3] * flt2[13] +
                                img[(i+2)*dim+j+4] * flt2[14]) +

                                (img[(i+3)*dim+j] *   flt2[15]+
                                img[(i+3)*dim+j+1] * flt2[16] +
                                img[(i+3)*dim+j+2] * flt2[17] +
                                img[(i+3)*dim+j+3] * flt2[18] +
                                img[(i+3)*dim+j+4] * flt2[19]) +

                                (img[(i+4)*dim+j] *   flt2[20]+
                                img[(i+4)*dim+j+1] * flt2[21] +
                                img[(i+4)*dim+j+2] * flt2[22] +
                                img[(i+4)*dim+j+3] * flt2[23] +
                                img[(i+4)*dim+j+4] * flt2_24)
                                ;
            
        }
    }
}



char blur_descr4[] = "flt 3 blocks of 8+ 1 reg(double grouped)";
void blur4(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[24];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    float flt2_24=flt[4*dim+4];
    /* float flt2_24=flt[24];*/
    
    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
                dst[i*dim+j]+=  ((img[i*dim+j] *   flt2[0]+
                                img[i*dim+j+1] * flt2[1] +
                                img[i*dim+j+2] * flt2[2]) +
                                (img[i*dim+j+3] * flt2[3] +
                                img[i*dim+j+4] * flt2[4])) +

                                ((img[(i+1)*dim+j] *   flt2[5]+
                                img[(i+1)*dim+j+1] * flt2[6] +
                                img[(i+1)*dim+j+2] * flt2[7]) +
                                (img[(i+1)*dim+j+3] * flt2[8] +
                                img[(i+1)*dim+j+4] * flt2[9])) +

                                ((img[(i+2)*dim+j] *   flt2[10]+
                                img[(i+2)*dim+j+1] * flt2[11] +
                                img[(i+2)*dim+j+2] * flt2[12]) +
                                (img[(i+2)*dim+j+3] * flt2[13] +
                                img[(i+2)*dim+j+4] * flt2[14])) +

                                ((img[(i+3)*dim+j] *   flt2[15]+
                                img[(i+3)*dim+j+1] * flt2[16] +
                                img[(i+3)*dim+j+2] * flt2[17]) +
                                (img[(i+3)*dim+j+3] * flt2[18] +
                                img[(i+3)*dim+j+4] * flt2[19])) +

                                ((img[(i+4)*dim+j] *   flt2[20]+
                                img[(i+4)*dim+j+1] * flt2[21] +
                                img[(i+4)*dim+j+2] * flt2[22]) +
                                (img[(i+4)*dim+j+3] * flt2[23] +
                                img[(i+4)*dim+j+4] * flt2_24))
                                ;
            
        }
    }
}


char blur_descr5[] = "flt grouped && unrolled[4]";
void blur5(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    
    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j+=2) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead

                float sum1=0,sum2=0;
                // float sum3=0,sum4=0;
                sum1+=  ((img[i*dim+j] *   flt2[0]+         //0-5
                                img[i*dim+j+1] * flt2[1] +
                                img[i*dim+j+2] * flt2[2]) +
                                (img[i*dim+j+3] * flt2[3] +
                                img[i*dim+j+4] * flt2[4]));
                sum2+=  ((img[i*dim+j+1] *   flt2[0]+
                                img[i*dim+j+2] * flt2[1] +
                                img[i*dim+j+3] * flt2[2]) +
                                (img[i*dim+j+4] * flt2[3] +
                                img[i*dim+j+5] * flt2[4]));
                // sum3+=  ((img[i*dim+j+2] *   flt2[0]+
                //                 img[i*dim+j+3] * flt2[1] +
                //                 img[i*dim+j+4] * flt2[2]) +
                //                 (img[i*dim+j+5] * flt2[3] +
                //                 img[i*dim+j+6] * flt2[4]));
                // sum4+=  ((img[i*dim+j+3] *   flt2[0]+
                //                 img[i*dim+j+4] * flt2[1] +
                //                 img[i*dim+j+5] * flt2[2]) +
                //                 (img[i*dim+j+6] * flt2[3] +
                //                 img[i*dim+j+7] * flt2[4]));

                sum1+=  ((img[(i+1)*dim+j] *   flt2[5]+       //5-9
                                img[(i+1)*dim+j+1] * flt2[6] +
                                img[(i+1)*dim+j+2] * flt2[7]) +
                                (img[(i+1)*dim+j+3] * flt2[8] +
                                img[(i+1)*dim+j+4] * flt2[9])) ;
                sum2+=  ((img[(i+1)*dim+j+1] *   flt2[5]+
                                img[(i+1)*dim+j+2] * flt2[6] +
                                img[(i+1)*dim+j+3] * flt2[7]) +
                                (img[(i+1)*dim+j+4] * flt2[8] +
                                img[(i+1)*dim+j+5] * flt2[9])) ;
                // sum3+=  ((img[(i+1)*dim+j+2] *   flt2[5]+
                //                 img[(i+1)*dim+j+3] * flt2[6] +
                //                 img[(i+1)*dim+j+4] * flt2[7]) +
                //                 (img[(i+1)*dim+j+5] * flt2[8] +
                //                 img[(i+1)*dim+j+6] * flt2[9])) ;
                // sum4+=  ((img[(i+1)*dim+j+3] *   flt2[5]+
                //                 img[(i+1)*dim+j+4] * flt2[6] +
                //                 img[(i+1)*dim+j+5] * flt2[7]) +
                //                 (img[(i+1)*dim+j+6] * flt2[8] +
                //                 img[(i+1)*dim+j+7] * flt2[9])) ;

                sum1+=  ((img[(i+2)*dim+j] *   flt2[10]+      //10-14
                                img[(i+2)*dim+j+1] *     flt2[11] +
                                img[(i+2)*dim+j+2] *     flt2[12]) +
                                (img[(i+2)*dim+j+3] *    flt2[13] +
                                img[(i+2)*dim+j+4] *     flt2[14])) ;
                sum2+=  ((img[(i+2)*dim+j+1] * flt2[10]+
                                img[(i+2)*dim+j+2] *     flt2[11] +
                                img[(i+2)*dim+j+3] *     flt2[12]) +
                                (img[(i+2)*dim+j+4] *    flt2[13] +
                                img[(i+2)*dim+j+5] *     flt2[14])) ;
                // sum3+=  ((img[(i+2)*dim+j+2] * flt2[10]+
                //                 img[(i+2)*dim+j+3] *     flt2[11] +
                //                 img[(i+2)*dim+j+4] *     flt2[12]) +
                //                 (img[(i+2)*dim+j+5] *    flt2[13] +
                //                 img[(i+2)*dim+j+6] *     flt2[14])) ;
                // sum4+=  ((img[(i+2)*dim+j+3] * flt2[10]+
                //                 img[(i+2)*dim+j+4] *     flt2[11] +
                //                 img[(i+2)*dim+j+5] *     flt2[12]) +
                //                 (img[(i+2)*dim+j+6] *    flt2[13] +
                //                 img[(i+2)*dim+j+7] *     flt2[14])) ;       





                sum1+=  ((img[(i+3)*dim+j] *   flt2[15]+      //15-19
                                img[(i+3)*dim+j+1] *     flt2[16] +
                                img[(i+3)*dim+j+2] *     flt2[17]) +
                                (img[(i+3)*dim+j+3] *    flt2[18] +
                                img[(i+3)*dim+j+4] *     flt2[19])) ;
                sum2+=  ((img[(i+3)*dim+j+1] * flt2[15]+
                                img[(i+3)*dim+j+2] *     flt2[16] +
                                img[(i+3)*dim+j+3] *     flt2[17]) +
                                (img[(i+3)*dim+j+4] *    flt2[18] +
                                img[(i+3)*dim+j+5] *     flt2[19])) ;
                // sum3+=  ((img[(i+3)*dim+j+2] * flt2[15]+
                //                 img[(i+3)*dim+j+3] *     flt2[16] +
                //                 img[(i+3)*dim+j+4] *     flt2[17]) +
                //                 (img[(i+3)*dim+j+5] *    flt2[18] +
                //                 img[(i+3)*dim+j+6] *     flt2[19])) ;
                // sum4+=  ((img[(i+3)*dim+j+3] * flt2[15]+
                //                 img[(i+3)*dim+j+4] *     flt2[16] +
                //                 img[(i+3)*dim+j+5] *     flt2[17]) +
                //                 (img[(i+3)*dim+j+6] *    flt2[18] +
                //                 img[(i+3)*dim+j+7] *     flt2[19])) ;            

                sum1+=  ((img[(i+4)*dim+j] *   flt2[20]+      //20-24
                                img[(i+4)*dim+j+1] *     flt2[21] +
                                img[(i+4)*dim+j+2] *     flt2[22]) +
                                (img[(i+4)*dim+j+3] *    flt2[23] +
                                img[(i+4)*dim+j+4] *     flt2[24])) ;
                sum2+=  ((img[(i+4)*dim+j+1] * flt2[20]+
                                img[(i+4)*dim+j+2] *     flt2[21] +
                                img[(i+4)*dim+j+3] *     flt2[22]) +
                                (img[(i+4)*dim+j+4] *    flt2[23] +
                                img[(i+4)*dim+j+5] *     flt2[24])) ;
                // sum3+=  ((img[(i+4)*dim+j+2] * flt2[20]+
                //                 img[(i+4)*dim+j+3] *     flt2[21] +
                //                 img[(i+4)*dim+j+4] *     flt2[22]) +
                //                 (img[(i+4)*dim+j+5] *    flt2[23] +
                //                 img[(i+4)*dim+j+6] *     flt2[24])) ;
                // sum4+=  ((img[(i+4)*dim+j+3] * flt2[20]+
                //                 img[(i+4)*dim+j+4] *     flt2[21] +
                //                 img[(i+4)*dim+j+5] *     flt2[22]) +
                //                 (img[(i+4)*dim+j+6] *    flt2[23] +
                //                 img[(i+4)*dim+j+7] *     flt2[24])) ;    

                dst[i*dim+j]=sum1;
                dst[i*dim+j+1]=sum2;
                // dst[i*dim+j+2]=sum3;
                // dst[i*dim+j+3]=sum4;
            
        }
    }

    /*
    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
            for(k = 0; k < 5; k++){
                for(l = 0; l < 5; l++) {
                    dst[i*dim+j] = dst[i*dim+j] + img[(i+k)*dim+j+l] * flt[k*dim+l];
                }
            }
        }
    }
    */
}

char blur_descr6[] = "flt grouped && unrolled[4]V2";
void blur6(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-4; j+=4) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
                
            dst[i*dim+j]+=  ((img[i*dim+j] *   flt2[0]+
                                img[i*dim+j+1] * flt2[1] +
                                img[i*dim+j+2] * flt2[2]) +
                                (img[i*dim+j+3] * flt2[3] +
                                img[i*dim+j+4] * flt2[4])) +

                                ((img[(i+1)*dim+j] *   flt2[5]+
                                img[(i+1)*dim+j+1] * flt2[6] +
                                img[(i+1)*dim+j+2] * flt2[7]) +
                                (img[(i+1)*dim+j+3] * flt2[8] +
                                img[(i+1)*dim+j+4] * flt2[9])) +

                                ((img[(i+2)*dim+j] *   flt2[10]+
                                img[(i+2)*dim+j+1] * flt2[11] +
                                img[(i+2)*dim+j+2] * flt2[12]) +
                                (img[(i+2)*dim+j+3] * flt2[13] +
                                img[(i+2)*dim+j+4] * flt2[14])) +

                                ((img[(i+3)*dim+j] *   flt2[15]+
                                img[(i+3)*dim+j+1] * flt2[16] +
                                img[(i+3)*dim+j+2] * flt2[17]) +
                                (img[(i+3)*dim+j+3] * flt2[18] +
                                img[(i+3)*dim+j+4] * flt2[19])) +

                                ((img[(i+4)*dim+j] *   flt2[20]+
                                img[(i+4)*dim+j+1] * flt2[21] +
                                img[(i+4)*dim+j+2] * flt2[22]) +
                                (img[(i+4)*dim+j+3] * flt2[23] +
                                img[(i+4)*dim+j+4] * flt2[24]))
                                ;



                dst[i*dim+j+1]+=  ((img[i*dim+j+1] *   flt2[0]+
                                img[i*dim+j+2] * flt2[1] +
                                img[i*dim+j+3] * flt2[2]) +
                                (img[i*dim+j+4] * flt2[3] +
                                img[i*dim+j+5] * flt2[4])) +

                                ((img[(i+1)*dim+j+1] *   flt2[5]+
                                img[(i+1)*dim+j+2] * flt2[6] +
                                img[(i+1)*dim+j+3] * flt2[7]) +
                                (img[(i+1)*dim+j+4] * flt2[8] +
                                img[(i+1)*dim+j+5] * flt2[9])) +

                                ((img[(i+2)*dim+j+1] *   flt2[10]+
                                img[(i+2)*dim+j+2] * flt2[11] +
                                img[(i+2)*dim+j+3] * flt2[12]) +
                                (img[(i+2)*dim+j+4] * flt2[13] +
                                img[(i+2)*dim+j+5] * flt2[14])) +

                                ((img[(i+3)*dim+j+1] *   flt2[15]+
                                img[(i+3)*dim+j+2] * flt2[16] +
                                img[(i+3)*dim+j+3] * flt2[17]) +
                                (img[(i+3)*dim+j+4] * flt2[18] +
                                img[(i+3)*dim+j+5] * flt2[19])) +

                                ((img[(i+4)*dim+j+1] *   flt2[20]+
                                img[(i+4)*dim+j+2] * flt2[21] +
                                img[(i+4)*dim+j+3] * flt2[22]) +
                                (img[(i+4)*dim+j+4] * flt2[23] +
                                img[(i+4)*dim+j+5] * flt2[24]))
                                ;
                    dst[i*dim+j+2]+=  ((img[i*dim+j+2] *   flt2[0]+
                                img[i*dim+j+3] * flt2[1] +
                                img[i*dim+j+4] * flt2[2]) +
                                (img[i*dim+j+5] * flt2[3] +
                                img[i*dim+j+6] * flt2[4])) +

                                ((img[(i+1)*dim+j+2] *   flt2[5]+
                                img[(i+1)*dim+j+3] * flt2[6] +
                                img[(i+1)*dim+j+4] * flt2[7]) +
                                (img[(i+1)*dim+j+5] * flt2[8] +
                                img[(i+1)*dim+j+6] * flt2[9])) +

                                ((img[(i+2)*dim+j+2] *   flt2[10]+
                                img[(i+2)*dim+j+3] * flt2[11] +
                                img[(i+2)*dim+j+4] * flt2[12]) +
                                (img[(i+2)*dim+j+5] * flt2[13] +
                                img[(i+2)*dim+j+6] * flt2[14])) +

                                ((img[(i+3)*dim+j+2] *   flt2[15]+
                                img[(i+3)*dim+j+3] * flt2[16] +
                                img[(i+3)*dim+j+4] * flt2[17]) +
                                (img[(i+3)*dim+j+5] * flt2[18] +
                                img[(i+3)*dim+j+6] * flt2[19])) +

                                ((img[(i+4)*dim+j+2] *   flt2[20]+
                                img[(i+4)*dim+j+3] * flt2[21] +
                                img[(i+4)*dim+j+4] * flt2[22]) +
                                (img[(i+4)*dim+j+5] * flt2[23] +
                                img[(i+4)*dim+j+6] * flt2[24]))
                                ;
                    dst[i*dim+j+3]+=  ((img[i*dim+j+3] *   flt2[0]+
                                img[i*dim+j+4] * flt2[1] +
                                img[i*dim+j+5] * flt2[2]) +
                                (img[i*dim+j+6] * flt2[3] +
                                img[i*dim+j+7] * flt2[4])) +

                                ((img[(i+1)*dim+j+3] *   flt2[5]+
                                img[(i+1)*dim+j+4] * flt2[6] +
                                img[(i+1)*dim+j+5] * flt2[7]) +
                                (img[(i+1)*dim+j+6] * flt2[8] +
                                img[(i+1)*dim+j+7] * flt2[9])) +

                                ((img[(i+2)*dim+j+3] *   flt2[10]+
                                img[(i+2)*dim+j+4] * flt2[11] +
                                img[(i+2)*dim+j+5] * flt2[12]) +
                                (img[(i+2)*dim+j+6] * flt2[13] +
                                img[(i+2)*dim+j+7] * flt2[14])) +

                                ((img[(i+3)*dim+j+3] *   flt2[15]+
                                img[(i+3)*dim+j+4] * flt2[16] +
                                img[(i+3)*dim+j+5] * flt2[17]) +
                                (img[(i+3)*dim+j+6] * flt2[18] +
                                img[(i+3)*dim+j+7] * flt2[19])) +

                                ((img[(i+4)*dim+j+3] *   flt2[20]+
                                img[(i+4)*dim+j+4] * flt2[21] +
                                img[(i+4)*dim+j+5] * flt2[22]) +
                                (img[(i+4)*dim+j+6] * flt2[23] +
                                img[(i+4)*dim+j+7] * flt2[24]))
                                ;
        }
    }
}



char blur_descr7[] = "flt grouped && unrolled[8]V2 (worse then unrolled[4]V2 ";
void blur7(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    
    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-8; j+=8) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
                
            dst[i*dim+j]+=  ((img[i*dim+j] *   flt2[0]+
                                img[i*dim+j+1] * flt2[1] +
                                img[i*dim+j+2] * flt2[2]) +
                                (img[i*dim+j+3] * flt2[3] +
                                img[i*dim+j+4] * flt2[4])) +

                                ((img[(i+1)*dim+j] *   flt2[5]+
                                img[(i+1)*dim+j+1] * flt2[6] +
                                img[(i+1)*dim+j+2] * flt2[7]) +
                                (img[(i+1)*dim+j+3] * flt2[8] +
                                img[(i+1)*dim+j+4] * flt2[9])) +

                                ((img[(i+2)*dim+j] *   flt2[10]+
                                img[(i+2)*dim+j+1] * flt2[11] +
                                img[(i+2)*dim+j+2] * flt2[12]) +
                                (img[(i+2)*dim+j+3] * flt2[13] +
                                img[(i+2)*dim+j+4] * flt2[14])) +

                                ((img[(i+3)*dim+j] *   flt2[15]+
                                img[(i+3)*dim+j+1] * flt2[16] +
                                img[(i+3)*dim+j+2] * flt2[17]) +
                                (img[(i+3)*dim+j+3] * flt2[18] +
                                img[(i+3)*dim+j+4] * flt2[19])) +

                                ((img[(i+4)*dim+j] *   flt2[20]+
                                img[(i+4)*dim+j+1] * flt2[21] +
                                img[(i+4)*dim+j+2] * flt2[22]) +
                                (img[(i+4)*dim+j+3] * flt2[23] +
                                img[(i+4)*dim+j+4] * flt2[24]))
                                ;



                dst[i*dim+j+1]+=  ((img[i*dim+j+1] *   flt2[0]+
                                img[i*dim+j+2] * flt2[1] +
                                img[i*dim+j+3] * flt2[2]) +
                                (img[i*dim+j+4] * flt2[3] +
                                img[i*dim+j+5] * flt2[4])) +

                                ((img[(i+1)*dim+j+1] *   flt2[5]+
                                img[(i+1)*dim+j+2] * flt2[6] +
                                img[(i+1)*dim+j+3] * flt2[7]) +
                                (img[(i+1)*dim+j+4] * flt2[8] +
                                img[(i+1)*dim+j+5] * flt2[9])) +

                                ((img[(i+2)*dim+j+1] *   flt2[10]+
                                img[(i+2)*dim+j+2] * flt2[11] +
                                img[(i+2)*dim+j+3] * flt2[12]) +
                                (img[(i+2)*dim+j+4] * flt2[13] +
                                img[(i+2)*dim+j+5] * flt2[14])) +

                                ((img[(i+3)*dim+j+1] *   flt2[15]+
                                img[(i+3)*dim+j+2] * flt2[16] +
                                img[(i+3)*dim+j+3] * flt2[17]) +
                                (img[(i+3)*dim+j+4] * flt2[18] +
                                img[(i+3)*dim+j+5] * flt2[19])) +

                                ((img[(i+4)*dim+j+1] *   flt2[20]+
                                img[(i+4)*dim+j+2] * flt2[21] +
                                img[(i+4)*dim+j+3] * flt2[22]) +
                                (img[(i+4)*dim+j+4] * flt2[23] +
                                img[(i+4)*dim+j+5] * flt2[24]))
                                ;
                    dst[i*dim+j+2]+=  ((img[i*dim+j+2] *   flt2[0]+
                                img[i*dim+j+3] * flt2[1] +
                                img[i*dim+j+4] * flt2[2]) +
                                (img[i*dim+j+5] * flt2[3] +
                                img[i*dim+j+6] * flt2[4])) +

                                ((img[(i+1)*dim+j+2] *   flt2[5]+
                                img[(i+1)*dim+j+3] * flt2[6] +
                                img[(i+1)*dim+j+4] * flt2[7]) +
                                (img[(i+1)*dim+j+5] * flt2[8] +
                                img[(i+1)*dim+j+6] * flt2[9])) +

                                ((img[(i+2)*dim+j+2] *   flt2[10]+
                                img[(i+2)*dim+j+3] * flt2[11] +
                                img[(i+2)*dim+j+4] * flt2[12]) +
                                (img[(i+2)*dim+j+5] * flt2[13] +
                                img[(i+2)*dim+j+6] * flt2[14])) +

                                ((img[(i+3)*dim+j+2] *   flt2[15]+
                                img[(i+3)*dim+j+3] * flt2[16] +
                                img[(i+3)*dim+j+4] * flt2[17]) +
                                (img[(i+3)*dim+j+5] * flt2[18] +
                                img[(i+3)*dim+j+6] * flt2[19])) +

                                ((img[(i+4)*dim+j+2] *   flt2[20]+
                                img[(i+4)*dim+j+3] * flt2[21] +
                                img[(i+4)*dim+j+4] * flt2[22]) +
                                (img[(i+4)*dim+j+5] * flt2[23] +
                                img[(i+4)*dim+j+6] * flt2[24]))
                                ;
                    dst[i*dim+j+3]+=  ((img[i*dim+j+3] *   flt2[0]+
                                img[i*dim+j+4] * flt2[1] +
                                img[i*dim+j+5] * flt2[2]) +
                                (img[i*dim+j+6] * flt2[3] +
                                img[i*dim+j+7] * flt2[4])) +

                                ((img[(i+1)*dim+j+3] *   flt2[5]+
                                img[(i+1)*dim+j+4] * flt2[6] +
                                img[(i+1)*dim+j+5] * flt2[7]) +
                                (img[(i+1)*dim+j+6] * flt2[8] +
                                img[(i+1)*dim+j+7] * flt2[9])) +

                                ((img[(i+2)*dim+j+3] *   flt2[10]+
                                img[(i+2)*dim+j+4] * flt2[11] +
                                img[(i+2)*dim+j+5] * flt2[12]) +
                                (img[(i+2)*dim+j+6] * flt2[13] +
                                img[(i+2)*dim+j+7] * flt2[14])) +

                                ((img[(i+3)*dim+j+3] *   flt2[15]+
                                img[(i+3)*dim+j+4] * flt2[16] +
                                img[(i+3)*dim+j+5] * flt2[17]) +
                                (img[(i+3)*dim+j+6] * flt2[18] +
                                img[(i+3)*dim+j+7] * flt2[19])) +

                                ((img[(i+4)*dim+j+3] *   flt2[20]+
                                img[(i+4)*dim+j+4] * flt2[21] +
                                img[(i+4)*dim+j+5] * flt2[22]) +
                                (img[(i+4)*dim+j+6] * flt2[23] +
                                img[(i+4)*dim+j+7] * flt2[24]))
                                ;





			dst[i*dim+j+4]+=
				((img[i*dim+j+4] *   flt2[0]+
				img[i*dim+j+5] *   flt2[1]+
				img[i*dim+j+6] *   flt2[2])+
				(img[i*dim+j+7] *   flt2[3]+
				img[i*dim+j+8] *   flt2[4]))+
				((img[(i+1)*dim+j+4] *   flt2[5]+
				img[(i+1)*dim+j+5] *   flt2[6]+
				img[(i+1)*dim+j+6] *   flt2[7])+
				(img[(i+1)*dim+j+7] *   flt2[8]+
				img[(i+1)*dim+j+8] *   flt2[9]))+
				((img[(i+2)*dim+j+4] *   flt2[10]+
				img[(i+2)*dim+j+5] *   flt2[11]+
				img[(i+2)*dim+j+6] *   flt2[12])+
				(img[(i+2)*dim+j+7] *   flt2[13]+
				img[(i+2)*dim+j+8] *   flt2[14]))+
				((img[(i+3)*dim+j+4] *   flt2[15]+
				img[(i+3)*dim+j+5] *   flt2[16]+
				img[(i+3)*dim+j+6] *   flt2[17])+
				(img[(i+3)*dim+j+7] *   flt2[18]+
				img[(i+3)*dim+j+8] *   flt2[19]))+
				((img[(i+4)*dim+j+4] *   flt2[20]+
				img[(i+4)*dim+j+5] *   flt2[21]+
				img[(i+4)*dim+j+6] *   flt2[22])+
				(img[(i+4)*dim+j+7] *   flt2[23]+
				img[(i+4)*dim+j+8] *   flt2[24]));

			dst[i*dim+j+5]+=
				((img[i*dim+j+5] *   flt2[0]+
				img[i*dim+j+6] *   flt2[1]+
				img[i*dim+j+7] *   flt2[2])+
				(img[i*dim+j+8] *   flt2[3]+
				img[i*dim+j+9] *   flt2[4]))+
				((img[(i+1)*dim+j+5] *   flt2[5]+
				img[(i+1)*dim+j+6] *   flt2[6]+
				img[(i+1)*dim+j+7] *   flt2[7])+
				(img[(i+1)*dim+j+8] *   flt2[8]+
				img[(i+1)*dim+j+9] *   flt2[9]))+
				((img[(i+2)*dim+j+5] *   flt2[10]+
				img[(i+2)*dim+j+6] *   flt2[11]+
				img[(i+2)*dim+j+7] *   flt2[12])+
				(img[(i+2)*dim+j+8] *   flt2[13]+
				img[(i+2)*dim+j+9] *   flt2[14]))+
				((img[(i+3)*dim+j+5] *   flt2[15]+
				img[(i+3)*dim+j+6] *   flt2[16]+
				img[(i+3)*dim+j+7] *   flt2[17])+
				(img[(i+3)*dim+j+8] *   flt2[18]+
				img[(i+3)*dim+j+9] *   flt2[19]))+
				((img[(i+4)*dim+j+5] *   flt2[20]+
				img[(i+4)*dim+j+6] *   flt2[21]+
				img[(i+4)*dim+j+7] *   flt2[22])+
				(img[(i+4)*dim+j+8] *   flt2[23]+
				img[(i+4)*dim+j+9] *   flt2[24]));

			dst[i*dim+j+6]+=
				((img[i*dim+j+6] *   flt2[0]+
				img[i*dim+j+7] *   flt2[1]+
				img[i*dim+j+8] *   flt2[2])+
				(img[i*dim+j+9] *   flt2[3]+
				img[i*dim+j+10] *   flt2[4]))+
				((img[(i+1)*dim+j+6] *   flt2[5]+
				img[(i+1)*dim+j+7] *   flt2[6]+
				img[(i+1)*dim+j+8] *   flt2[7])+
				(img[(i+1)*dim+j+9] *   flt2[8]+
				img[(i+1)*dim+j+10] *   flt2[9]))+
				((img[(i+2)*dim+j+6] *   flt2[10]+
				img[(i+2)*dim+j+7] *   flt2[11]+
				img[(i+2)*dim+j+8] *   flt2[12])+
				(img[(i+2)*dim+j+9] *   flt2[13]+
				img[(i+2)*dim+j+10] *   flt2[14]))+
				((img[(i+3)*dim+j+6] *   flt2[15]+
				img[(i+3)*dim+j+7] *   flt2[16]+
				img[(i+3)*dim+j+8] *   flt2[17])+
				(img[(i+3)*dim+j+9] *   flt2[18]+
				img[(i+3)*dim+j+10] *   flt2[19]))+
				((img[(i+4)*dim+j+6] *   flt2[20]+
				img[(i+4)*dim+j+7] *   flt2[21]+
				img[(i+4)*dim+j+8] *   flt2[22])+
				(img[(i+4)*dim+j+9] *   flt2[23]+
				img[(i+4)*dim+j+10] *   flt2[24]));

			dst[i*dim+j+7]+=
				((img[i*dim+j+7] *   flt2[0]+
				img[i*dim+j+8] *   flt2[1]+
				img[i*dim+j+9] *   flt2[2])+
				(img[i*dim+j+10] *   flt2[3]+
				img[i*dim+j+11] *   flt2[4]))+
				((img[(i+1)*dim+j+7] *   flt2[5]+
				img[(i+1)*dim+j+8] *   flt2[6]+
				img[(i+1)*dim+j+9] *   flt2[7])+
				(img[(i+1)*dim+j+10] *   flt2[8]+
				img[(i+1)*dim+j+11] *   flt2[9]))+
				((img[(i+2)*dim+j+7] *   flt2[10]+
				img[(i+2)*dim+j+8] *   flt2[11]+
				img[(i+2)*dim+j+9] *   flt2[12])+
				(img[(i+2)*dim+j+10] *   flt2[13]+
				img[(i+2)*dim+j+11] *   flt2[14]))+
				((img[(i+3)*dim+j+7] *   flt2[15]+
				img[(i+3)*dim+j+8] *   flt2[16]+
				img[(i+3)*dim+j+9] *   flt2[17])+
				(img[(i+3)*dim+j+10] *   flt2[18]+
				img[(i+3)*dim+j+11] *   flt2[19]))+
				((img[(i+4)*dim+j+7] *   flt2[20]+
				img[(i+4)*dim+j+8] *   flt2[21]+
				img[(i+4)*dim+j+9] *   flt2[22])+
				(img[(i+4)*dim+j+10] *   flt2[23]+
				img[(i+4)*dim+j+11] *   flt2[24]));


        }
        if(j<dim-4){
            dst[i*dim+j]+=  ((img[i*dim+j] *   flt2[0]+
                                img[i*dim+j+1] * flt2[1] +
                                img[i*dim+j+2] * flt2[2]) +
                                (img[i*dim+j+3] * flt2[3] +
                                img[i*dim+j+4] * flt2[4])) +

                                ((img[(i+1)*dim+j] *   flt2[5]+
                                img[(i+1)*dim+j+1] * flt2[6] +
                                img[(i+1)*dim+j+2] * flt2[7]) +
                                (img[(i+1)*dim+j+3] * flt2[8] +
                                img[(i+1)*dim+j+4] * flt2[9])) +

                                ((img[(i+2)*dim+j] *   flt2[10]+
                                img[(i+2)*dim+j+1] * flt2[11] +
                                img[(i+2)*dim+j+2] * flt2[12]) +
                                (img[(i+2)*dim+j+3] * flt2[13] +
                                img[(i+2)*dim+j+4] * flt2[14])) +

                                ((img[(i+3)*dim+j] *   flt2[15]+
                                img[(i+3)*dim+j+1] * flt2[16] +
                                img[(i+3)*dim+j+2] * flt2[17]) +
                                (img[(i+3)*dim+j+3] * flt2[18] +
                                img[(i+3)*dim+j+4] * flt2[19])) +

                                ((img[(i+4)*dim+j] *   flt2[20]+
                                img[(i+4)*dim+j+1] * flt2[21] +
                                img[(i+4)*dim+j+2] * flt2[22]) +
                                (img[(i+4)*dim+j+3] * flt2[23] +
                                img[(i+4)*dim+j+4] * flt2[24]))
                                ;



                dst[i*dim+j+1]+=  ((img[i*dim+j+1] *   flt2[0]+
                                img[i*dim+j+2] * flt2[1] +
                                img[i*dim+j+3] * flt2[2]) +
                                (img[i*dim+j+4] * flt2[3] +
                                img[i*dim+j+5] * flt2[4])) +

                                ((img[(i+1)*dim+j+1] *   flt2[5]+
                                img[(i+1)*dim+j+2] * flt2[6] +
                                img[(i+1)*dim+j+3] * flt2[7]) +
                                (img[(i+1)*dim+j+4] * flt2[8] +
                                img[(i+1)*dim+j+5] * flt2[9])) +

                                ((img[(i+2)*dim+j+1] *   flt2[10]+
                                img[(i+2)*dim+j+2] * flt2[11] +
                                img[(i+2)*dim+j+3] * flt2[12]) +
                                (img[(i+2)*dim+j+4] * flt2[13] +
                                img[(i+2)*dim+j+5] * flt2[14])) +

                                ((img[(i+3)*dim+j+1] *   flt2[15]+
                                img[(i+3)*dim+j+2] * flt2[16] +
                                img[(i+3)*dim+j+3] * flt2[17]) +
                                (img[(i+3)*dim+j+4] * flt2[18] +
                                img[(i+3)*dim+j+5] * flt2[19])) +

                                ((img[(i+4)*dim+j+1] *   flt2[20]+
                                img[(i+4)*dim+j+2] * flt2[21] +
                                img[(i+4)*dim+j+3] * flt2[22]) +
                                (img[(i+4)*dim+j+4] * flt2[23] +
                                img[(i+4)*dim+j+5] * flt2[24]))
                                ;
                    dst[i*dim+j+2]+=  ((img[i*dim+j+2] *   flt2[0]+
                                img[i*dim+j+3] * flt2[1] +
                                img[i*dim+j+4] * flt2[2]) +
                                (img[i*dim+j+5] * flt2[3] +
                                img[i*dim+j+6] * flt2[4])) +

                                ((img[(i+1)*dim+j+2] *   flt2[5]+
                                img[(i+1)*dim+j+3] * flt2[6] +
                                img[(i+1)*dim+j+4] * flt2[7]) +
                                (img[(i+1)*dim+j+5] * flt2[8] +
                                img[(i+1)*dim+j+6] * flt2[9])) +

                                ((img[(i+2)*dim+j+2] *   flt2[10]+
                                img[(i+2)*dim+j+3] * flt2[11] +
                                img[(i+2)*dim+j+4] * flt2[12]) +
                                (img[(i+2)*dim+j+5] * flt2[13] +
                                img[(i+2)*dim+j+6] * flt2[14])) +

                                ((img[(i+3)*dim+j+2] *   flt2[15]+
                                img[(i+3)*dim+j+3] * flt2[16] +
                                img[(i+3)*dim+j+4] * flt2[17]) +
                                (img[(i+3)*dim+j+5] * flt2[18] +
                                img[(i+3)*dim+j+6] * flt2[19])) +

                                ((img[(i+4)*dim+j+2] *   flt2[20]+
                                img[(i+4)*dim+j+3] * flt2[21] +
                                img[(i+4)*dim+j+4] * flt2[22]) +
                                (img[(i+4)*dim+j+5] * flt2[23] +
                                img[(i+4)*dim+j+6] * flt2[24]))
                                ;
                    dst[i*dim+j+3]+=  ((img[i*dim+j+3] *   flt2[0]+
                                img[i*dim+j+4] * flt2[1] +
                                img[i*dim+j+5] * flt2[2]) +
                                (img[i*dim+j+6] * flt2[3] +
                                img[i*dim+j+7] * flt2[4])) +

                                ((img[(i+1)*dim+j+3] *   flt2[5]+
                                img[(i+1)*dim+j+4] * flt2[6] +
                                img[(i+1)*dim+j+5] * flt2[7]) +
                                (img[(i+1)*dim+j+6] * flt2[8] +
                                img[(i+1)*dim+j+7] * flt2[9])) +

                                ((img[(i+2)*dim+j+3] *   flt2[10]+
                                img[(i+2)*dim+j+4] * flt2[11] +
                                img[(i+2)*dim+j+5] * flt2[12]) +
                                (img[(i+2)*dim+j+6] * flt2[13] +
                                img[(i+2)*dim+j+7] * flt2[14])) +

                                ((img[(i+3)*dim+j+3] *   flt2[15]+
                                img[(i+3)*dim+j+4] * flt2[16] +
                                img[(i+3)*dim+j+5] * flt2[17]) +
                                (img[(i+3)*dim+j+6] * flt2[18] +
                                img[(i+3)*dim+j+7] * flt2[19])) +

                                ((img[(i+4)*dim+j+3] *   flt2[20]+
                                img[(i+4)*dim+j+4] * flt2[21] +
                                img[(i+4)*dim+j+5] * flt2[22]) +
                                (img[(i+4)*dim+j+6] * flt2[23] +
                                img[(i+4)*dim+j+7] * flt2[24]))
                                ;

        }
    }
}

char ALGO2_blur_descr[] = "ALGO2 with 1 load 25 stores unrolling[4]";
void ALGO2_blur(int dim, float *img, float *flt, float *dst) {

    int i, j;
    float current;
    float current1,current2,current3,current4;
    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];

//--------------BASE 00 33---------------
current=img[0];
dst[0]+=current*flt2[0];

current=img[1];
dst[0]+=current*flt2[1];
dst[1]+=current*flt2[0];

current=img[2];
dst[0]+=current*flt2[2];
dst[1]+=current*flt2[1];
dst[2]+=current*flt2[0];

current=img[3];
dst[0]+=current*flt2[3];
dst[1]+=current*flt2[2];
dst[2]+=current*flt2[1];
dst[3]+=current*flt2[0];

current=img[dim+0];
dst[0]+=current*flt2[5];
dst[dim+0]+=current*flt2[0];

current=img[dim+1];
dst[0]+=current*flt2[6];
dst[1]+=current*flt2[5];
dst[dim+0]+=current*flt2[1];
dst[dim+1]+=current*flt2[0];

current=img[dim+2];
dst[0]+=current*flt2[7];
dst[1]+=current*flt2[6];
dst[2]+=current*flt2[5];
dst[dim+0]+=current*flt2[2];
dst[dim+1]+=current*flt2[1];
dst[dim+2]+=current*flt2[0];

current=img[dim+3];
dst[0]+=current*flt2[8];
dst[1]+=current*flt2[7];
dst[2]+=current*flt2[6];
dst[3]+=current*flt2[5];
dst[dim+0]+=current*flt2[3];
dst[dim+1]+=current*flt2[2];
dst[dim+2]+=current*flt2[1];
dst[dim+3]+=current*flt2[0];

current=img[2*dim+0];
dst[0]+=current*flt2[10];
dst[dim+0]+=current*flt2[5];
dst[2*dim+0]+=current*flt2[0];

current=img[2*dim+1];
dst[0]+=current*flt2[11];
dst[1]+=current*flt2[10];
dst[dim+0]+=current*flt2[6];
dst[dim+1]+=current*flt2[5];
dst[2*dim+0]+=current*flt2[1];
dst[2*dim+1]+=current*flt2[0];

current=img[2*dim+2];
dst[0]+=current*flt2[12];
dst[1]+=current*flt2[11];
dst[2]+=current*flt2[10];
dst[dim+0]+=current*flt2[7];
dst[dim+1]+=current*flt2[6];
dst[dim+2]+=current*flt2[5];
dst[2*dim+0]+=current*flt2[2];
dst[2*dim+1]+=current*flt2[1];
dst[2*dim+2]+=current*flt2[0];

current=img[2*dim+3];
dst[0]+=current*flt2[13];
dst[1]+=current*flt2[12];
dst[2]+=current*flt2[11];
dst[3]+=current*flt2[10];
dst[dim+0]+=current*flt2[8];
dst[dim+1]+=current*flt2[7];
dst[dim+2]+=current*flt2[6];
dst[dim+3]+=current*flt2[5];
dst[2*dim+0]+=current*flt2[3];
dst[2*dim+1]+=current*flt2[2];
dst[2*dim+2]+=current*flt2[1];
dst[2*dim+3]+=current*flt2[0];

current=img[3*dim+0];
dst[0]+=current*flt2[15];
dst[dim+0]+=current*flt2[10];
dst[2*dim+0]+=current*flt2[5];
dst[3*dim+0]+=current*flt2[0];

current=img[3*dim+1];
dst[0]+=current*flt2[16];
dst[1]+=current*flt2[15];
dst[dim+0]+=current*flt2[11];
dst[dim+1]+=current*flt2[10];
dst[2*dim+0]+=current*flt2[6];
dst[2*dim+1]+=current*flt2[5];
dst[3*dim+0]+=current*flt2[1];
dst[3*dim+1]+=current*flt2[0];

current=img[3*dim+2];
dst[0]+=current*flt2[17];
dst[1]+=current*flt2[16];
dst[2]+=current*flt2[15];
dst[dim+0]+=current*flt2[12];
dst[dim+1]+=current*flt2[11];
dst[dim+2]+=current*flt2[10];
dst[2*dim+0]+=current*flt2[7];
dst[2*dim+1]+=current*flt2[6];
dst[2*dim+2]+=current*flt2[5];
dst[3*dim+0]+=current*flt2[2];
dst[3*dim+1]+=current*flt2[1];
dst[3*dim+2]+=current*flt2[0];

current=img[3*dim+3];
dst[0]+=current*flt2[18];
dst[1]+=current*flt2[17];
dst[2]+=current*flt2[16];
dst[3]+=current*flt2[15];
dst[dim+0]+=current*flt2[13];
dst[dim+1]+=current*flt2[12];
dst[dim+2]+=current*flt2[11];
dst[dim+3]+=current*flt2[10];
dst[2*dim+0]+=current*flt2[8];
dst[2*dim+1]+=current*flt2[7];
dst[2*dim+2]+=current*flt2[6];
dst[2*dim+3]+=current*flt2[5];
dst[3*dim+0]+=current*flt2[3];
dst[3*dim+1]+=current*flt2[2];
dst[3*dim+2]+=current*flt2[1];
dst[3*dim+3]+=current*flt2[0];




//------------------------

    


//##################BASE COLUMN PLACEMENT##############
    //000000000000000000000000000000000000000000
    for(i = 4; i < dim; i++) {
        current=img[i*dim];
        dst[i*dim] +=current   * flt2[0];

        dst[(i-1)*dim] +=current   * flt2[5];

        dst[(i-2)*dim] +=current   * flt2[10];

        dst[(i-3)*dim] +=current   * flt2[15];

        dst[(i-4)*dim] +=current   * flt2[20];
    }
    //###################2######################
    for(i = 4; i < dim; i++) {
        current=img[i*dim+1];
        dst[i*dim+1] +=current   * flt2[0];
        dst[i*dim] +=current * flt2[1];

        dst[(i-1)*dim+1] +=current   * flt2[5];
        dst[(i-1)*dim] +=current * flt2[6];

        dst[(i-2)*dim+1] +=current   * flt2[10];
        dst[(i-2)*dim] +=current * flt2[11];

        dst[(i-3)*dim+1] +=current   * flt2[15];
        dst[(i-3)*dim] +=current * flt2[16];

        dst[(i-4)*dim+1] +=current   * flt2[20];
        dst[(i-4)*dim] +=current * flt2[21];
    }
    //###################2######################
    for(i = 4; i < dim; i++) {
        current=img[i*dim+2];
        dst[i*dim+2] +=current   * flt2[0];
        dst[i*dim+1] +=current * flt2[1];
        dst[i*dim] +=current * flt2[2];

        dst[(i-1)*dim+2] +=current   * flt2[5];
        dst[(i-1)*dim+1] +=current * flt2[6];
        dst[(i-1)*dim] +=current * flt2[7];

        dst[(i-2)*dim+2] +=current   * flt2[10];
        dst[(i-2)*dim+1] +=current * flt2[11];
        dst[(i-2)*dim] +=current * flt2[12];

        dst[(i-3)*dim+2] +=current   * flt2[15];
        dst[(i-3)*dim+1] +=current * flt2[16];
        dst[(i-3)*dim] +=current * flt2[17];

        dst[(i-4)*dim+2] +=current   * flt2[20];
        dst[(i-4)*dim+1] +=current * flt2[21];
        dst[(i-4)*dim] +=current * flt2[22];
    }
    //###################3######################
    for(i = 4; i < dim; i++) {
        current=img[i*dim+3];
        dst[i*dim+3] +=current   * flt2[0];
        dst[i*dim+2] +=current * flt2[1];
        dst[i*dim+1] +=current * flt2[2];
        dst[i*dim] +=current * flt2[3];

        dst[(i-1)*dim+3] +=current   * flt2[5];
        dst[(i-1)*dim+2] +=current * flt2[6];
        dst[(i-1)*dim+1] +=current * flt2[7];
        dst[(i-1)*dim] +=current * flt2[8];

        dst[(i-2)*dim+3] +=current   * flt2[10];
        dst[(i-2)*dim+2] +=current * flt2[11];
        dst[(i-2)*dim+1] +=current * flt2[12];
        dst[(i-2)*dim] +=current * flt2[13];

        dst[(i-3)*dim+3] +=current   * flt2[15];
        dst[(i-3)*dim+2] +=current * flt2[16];
        dst[(i-3)*dim+1] +=current * flt2[17];
        dst[(i-3)*dim] +=current * flt2[18];

        dst[(i-4)*dim+3] +=current   * flt2[20];
        dst[(i-4)*dim+2] +=current * flt2[21];
        dst[(i-4)*dim+1] +=current * flt2[22];
        dst[(i-4)*dim] +=current * flt2[23];
    }






//#################BASE ROW PLACEMENT#####################
    //000000000000000000000000000000000000000000
    for(j = 4; j < dim; j++) {
        current=img[j];
        dst[j] +=current   * flt2[0];
        dst[j-1] +=current * flt2[1];
        dst[j-2] +=current * flt2[2];
        dst[j-3] +=current * flt2[3];
        dst[j-4] +=current * flt2[4];
    }
    //###################1######################
    for(j = 4; j < dim; j++) {
        current=img[dim+j];
        dst[dim+j] +=current   * flt2[0];
        dst[dim+j-1] +=current * flt2[1];
        dst[dim+j-2] +=current * flt2[2];
        dst[dim+j-3] +=current * flt2[3];
        dst[dim+j-4] +=current * flt2[4];

        dst[j] +=current   * flt2[5];
        dst[j-1] +=current * flt2[6];
        dst[j-2] +=current * flt2[7];
        dst[j-3] +=current * flt2[8];
        dst[j-4] +=current * flt2[9];
    }
    //######################2###################
    for(j = 4; j < dim; j++) {
        current=img[2*dim+j];
        dst[2*dim+j] +=current   * flt2[0];
        dst[2*dim+j-1] +=current * flt2[1];
        dst[2*dim+j-2] +=current * flt2[2];
        dst[2*dim+j-3] +=current * flt2[3];
        dst[2*dim+j-4] +=current * flt2[4];

        dst[1*dim+j] +=current   * flt2[5];
        dst[1*dim+j-1] +=current * flt2[6];
        dst[1*dim+j-2] +=current * flt2[7];
        dst[1*dim+j-3] +=current * flt2[8];
        dst[1*dim+j-4] +=current * flt2[9];

        dst[j] +=current   * flt2[10];
        dst[j-1] +=current * flt2[11];
        dst[j-2] +=current * flt2[12];
        dst[j-3] +=current * flt2[13];
        dst[j-4] +=current * flt2[14];
    }
    //################3#########################
    for(j = 4; j < dim; j++) {
        current=img[3*dim+j];
        dst[3*dim+j] +=current   * flt2[0];
        dst[3*dim+j-1] +=current * flt2[1];
        dst[3*dim+j-2] +=current * flt2[2];
        dst[3*dim+j-3] +=current * flt2[3];
        dst[3*dim+j-4] +=current * flt2[4];

        dst[2*dim+j] +=current   * flt2[5];
        dst[2*dim+j-1] +=current * flt2[6];
        dst[2*dim+j-2] +=current * flt2[7];
        dst[2*dim+j-3] +=current * flt2[8];
        dst[2*dim+j-4] +=current * flt2[9];

        dst[dim+j] +=current   * flt2[10];
        dst[dim+j-1] +=current * flt2[11];
        dst[dim+j-2] +=current * flt2[12];
        dst[dim+j-3] +=current * flt2[13];
        dst[dim+j-4] +=current * flt2[14];

        dst[j] +=current   * flt2[15];
        dst[j-1] +=current * flt2[16];
        dst[j-2] +=current * flt2[17];
        dst[j-3] +=current * flt2[18];
        dst[j-4] +=current * flt2[19];
    }
//##########################################








    for(i = 4; i < dim; i++){
        for(j = 4; j < dim; j+=4) {
            current1=img[i*dim+j];
            current2=img[i*dim+j+1];
            current3=img[i*dim+j+2];
            current4=img[i*dim+j+3];

            dst[i*dim+j+3] +=(current4*flt2[0]);
            dst[i*dim+j+2] +=(current3*flt2[0]+current4*flt2[1]);
            dst[i*dim+j+1] +=(current2*flt2[0]+current3*flt2[1]+current4*flt2[2]);
            dst[i*dim+j] +=(current1*flt2[0]+current2*flt2[1]+current3*flt2[2]+current4*flt2[3]);
            dst[i*dim+j-1] +=(current1*flt2[1]+current2*flt2[2]+current3*flt2[3]+current4*flt2[4]);
            dst[i*dim+j-2] +=(current1*flt2[2]+current2*flt2[3]+current3*flt2[4]);
            dst[i*dim+j-3] +=(current1*flt2[3]+current2*flt2[4]);
            dst[i*dim+j-4] +=(current1*flt2[4]);



            dst[(i-1)*dim+j+3] +=(current4*flt2[5]);
            dst[(i-1)*dim+j+2] +=(current3*flt2[5]+current4*flt2[6]);
            dst[(i-1)*dim+j+1] +=(current2*flt2[5]+current3*flt2[6]+current4*flt2[7]);
            dst[(i-1)*dim+j] +=(current1*flt2[5]+current2*flt2[6]+current3*flt2[7]+current4*flt2[8]);
            dst[(i-1)*dim+j-1] +=(current1*flt2[6]+current2*flt2[7]+current3*flt2[8]+current4*flt2[9]);
            dst[(i-1)*dim+j-2] +=(current1*flt2[7]+current2*flt2[8]+current3*flt2[9]);
            dst[(i-1)*dim+j-3] +=(current1*flt2[8]+current2*flt2[9]);
            dst[(i-1)*dim+j-4] +=(current1*flt2[9]);



            dst[(i-2)*dim+j+3] +=(current4*flt2[10]);
            dst[(i-2)*dim+j+2] +=(current3*flt2[10]+current4*flt2[11]);
            dst[(i-2)*dim+j+1] +=(current2*flt2[10]+current3*flt2[11]+current4*flt2[12]);
            dst[(i-2)*dim+j] +=(current1*flt2[10]+current2*flt2[11]+current3*flt2[12]+current4*flt2[13]);
            dst[(i-2)*dim+j-1] +=(current1*flt2[11]+current2*flt2[12]+current3*flt2[13]+current4*flt2[14]);
            dst[(i-2)*dim+j-2] +=(current1*flt2[12]+current2*flt2[13]+current3*flt2[14]);
            dst[(i-2)*dim+j-3] +=(current1*flt2[13]+current2*flt2[14]);
            dst[(i-2)*dim+j-4] +=(current1*flt2[14]);



            dst[(i-3)*dim+j+3] +=(current4*flt2[15]);
            dst[(i-3)*dim+j+2] +=(current3*flt2[15]+current4*flt2[16]);
            dst[(i-3)*dim+j+1] +=(current2*flt2[15]+current3*flt2[16]+current4*flt2[17]);
            dst[(i-3)*dim+j] +=(current1*flt2[15]+current2*flt2[16]+current3*flt2[17]+current4*flt2[18]);
            dst[(i-3)*dim+j-1] +=(current1*flt2[16]+current2*flt2[17]+current3*flt2[18]+current4*flt2[19]);
            dst[(i-3)*dim+j-2] +=(current1*flt2[17]+current2*flt2[18]+current3*flt2[19]);
            dst[(i-3)*dim+j-3] +=(current1*flt2[18]+current2*flt2[19]);
            dst[(i-3)*dim+j-4] +=(current1*flt2[19]);



            dst[(i-4)*dim+j+3] +=(current4*flt2[20]);
            dst[(i-4)*dim+j+2] +=(current3*flt2[20]+current4*flt2[21]);
            dst[(i-4)*dim+j+1] +=(current2*flt2[20]+current3*flt2[21]+current4*flt2[22]);
            dst[(i-4)*dim+j] +=(current1*flt2[20]+current2*flt2[21]+current3*flt2[22]+current4*flt2[23]);
            dst[(i-4)*dim+j-1] +=(current1*flt2[21]+current2*flt2[22]+current3*flt2[23]+current4*flt2[24]);
            dst[(i-4)*dim+j-2] +=(current1*flt2[22]+current2*flt2[23]+current3*flt2[24]);
            dst[(i-4)*dim+j-3] +=(current1*flt2[23]+current2*flt2[24]);
            dst[(i-4)*dim+j-4] +=(current1*flt2[24]);

                /*img[x][y] is used in
                    
                    dst[x-4][y-4] dst[x-4][y]
                    dst[x][y-4] dst[x][y] 

                    base cases: img[0][0]-img[4][3] img[3][4]
                */
        }
    }
}


/*********************************************************************
 * register_blur_functions - Register all of your different versions
 *     of the gaussian blur kernel with the driver by calling the
 *     add_blur_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/




char blur_descr666[] = "flt grouped && 2Dunrolled[2][4]";
void blur666(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    
    for(i = 0; i < dim-4; i+=2){
        for(j = 0; j < dim-4; j+=4) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
                
            dst[i*dim+j]+=  ((img[i*dim+j] *   flt2[0]+
                                img[i*dim+j+1] * flt2[1] +
                                img[i*dim+j+2] * flt2[2]) +
                                (img[i*dim+j+3] * flt2[3] +
                                img[i*dim+j+4] * flt2[4])) +

                                ((img[(i+1)*dim+j] *   flt2[5]+
                                img[(i+1)*dim+j+1] * flt2[6] +
                                img[(i+1)*dim+j+2] * flt2[7]) +
                                (img[(i+1)*dim+j+3] * flt2[8] +
                                img[(i+1)*dim+j+4] * flt2[9])) +

                                ((img[(i+2)*dim+j] *   flt2[10]+
                                img[(i+2)*dim+j+1] * flt2[11] +
                                img[(i+2)*dim+j+2] * flt2[12]) +
                                (img[(i+2)*dim+j+3] * flt2[13] +
                                img[(i+2)*dim+j+4] * flt2[14])) +

                                ((img[(i+3)*dim+j] *   flt2[15]+
                                img[(i+3)*dim+j+1] * flt2[16] +
                                img[(i+3)*dim+j+2] * flt2[17]) +
                                (img[(i+3)*dim+j+3] * flt2[18] +
                                img[(i+3)*dim+j+4] * flt2[19])) +

                                ((img[(i+4)*dim+j] *   flt2[20]+
                                img[(i+4)*dim+j+1] * flt2[21] +
                                img[(i+4)*dim+j+2] * flt2[22]) +
                                (img[(i+4)*dim+j+3] * flt2[23] +
                                img[(i+4)*dim+j+4] * flt2[24]))
                                ;



                dst[i*dim+j+1]+=  ((img[i*dim+j+1] *   flt2[0]+
                                img[i*dim+j+2] * flt2[1] +
                                img[i*dim+j+3] * flt2[2]) +
                                (img[i*dim+j+4] * flt2[3] +
                                img[i*dim+j+5] * flt2[4])) +

                                ((img[(i+1)*dim+j+1] *   flt2[5]+
                                img[(i+1)*dim+j+2] * flt2[6] +
                                img[(i+1)*dim+j+3] * flt2[7]) +
                                (img[(i+1)*dim+j+4] * flt2[8] +
                                img[(i+1)*dim+j+5] * flt2[9])) +

                                ((img[(i+2)*dim+j+1] *   flt2[10]+
                                img[(i+2)*dim+j+2] * flt2[11] +
                                img[(i+2)*dim+j+3] * flt2[12]) +
                                (img[(i+2)*dim+j+4] * flt2[13] +
                                img[(i+2)*dim+j+5] * flt2[14])) +

                                ((img[(i+3)*dim+j+1] *   flt2[15]+
                                img[(i+3)*dim+j+2] * flt2[16] +
                                img[(i+3)*dim+j+3] * flt2[17]) +
                                (img[(i+3)*dim+j+4] * flt2[18] +
                                img[(i+3)*dim+j+5] * flt2[19])) +

                                ((img[(i+4)*dim+j+1] *   flt2[20]+
                                img[(i+4)*dim+j+2] * flt2[21] +
                                img[(i+4)*dim+j+3] * flt2[22]) +
                                (img[(i+4)*dim+j+4] * flt2[23] +
                                img[(i+4)*dim+j+5] * flt2[24]))
                                ;
                    dst[i*dim+j+2]+=  ((img[i*dim+j+2] *   flt2[0]+
                                img[i*dim+j+3] * flt2[1] +
                                img[i*dim+j+4] * flt2[2]) +
                                (img[i*dim+j+5] * flt2[3] +
                                img[i*dim+j+6] * flt2[4])) +

                                ((img[(i+1)*dim+j+2] *   flt2[5]+
                                img[(i+1)*dim+j+3] * flt2[6] +
                                img[(i+1)*dim+j+4] * flt2[7]) +
                                (img[(i+1)*dim+j+5] * flt2[8] +
                                img[(i+1)*dim+j+6] * flt2[9])) +

                                ((img[(i+2)*dim+j+2] *   flt2[10]+
                                img[(i+2)*dim+j+3] * flt2[11] +
                                img[(i+2)*dim+j+4] * flt2[12]) +
                                (img[(i+2)*dim+j+5] * flt2[13] +
                                img[(i+2)*dim+j+6] * flt2[14])) +

                                ((img[(i+3)*dim+j+2] *   flt2[15]+
                                img[(i+3)*dim+j+3] * flt2[16] +
                                img[(i+3)*dim+j+4] * flt2[17]) +
                                (img[(i+3)*dim+j+5] * flt2[18] +
                                img[(i+3)*dim+j+6] * flt2[19])) +

                                ((img[(i+4)*dim+j+2] *   flt2[20]+
                                img[(i+4)*dim+j+3] * flt2[21] +
                                img[(i+4)*dim+j+4] * flt2[22]) +
                                (img[(i+4)*dim+j+5] * flt2[23] +
                                img[(i+4)*dim+j+6] * flt2[24]))
                                ;
                    dst[i*dim+j+3]+=  ((img[i*dim+j+3] *   flt2[0]+
                                img[i*dim+j+4] * flt2[1] +
                                img[i*dim+j+5] * flt2[2]) +
                                (img[i*dim+j+6] * flt2[3] +
                                img[i*dim+j+7] * flt2[4])) +

                                ((img[(i+1)*dim+j+3] *   flt2[5]+
                                img[(i+1)*dim+j+4] * flt2[6] +
                                img[(i+1)*dim+j+5] * flt2[7]) +
                                (img[(i+1)*dim+j+6] * flt2[8] +
                                img[(i+1)*dim+j+7] * flt2[9])) +

                                ((img[(i+2)*dim+j+3] *   flt2[10]+
                                img[(i+2)*dim+j+4] * flt2[11] +
                                img[(i+2)*dim+j+5] * flt2[12]) +
                                (img[(i+2)*dim+j+6] * flt2[13] +
                                img[(i+2)*dim+j+7] * flt2[14])) +

                                ((img[(i+3)*dim+j+3] *   flt2[15]+
                                img[(i+3)*dim+j+4] * flt2[16] +
                                img[(i+3)*dim+j+5] * flt2[17]) +
                                (img[(i+3)*dim+j+6] * flt2[18] +
                                img[(i+3)*dim+j+7] * flt2[19])) +

                                ((img[(i+4)*dim+j+3] *   flt2[20]+
                                img[(i+4)*dim+j+4] * flt2[21] +
                                img[(i+4)*dim+j+5] * flt2[22]) +
                                (img[(i+4)*dim+j+6] * flt2[23] +
                                img[(i+4)*dim+j+7] * flt2[24]))
                                ;

            dst[dim+i*dim+j]+=  ((img[dim+i*dim+j] *   flt2[0]+
                                img[dim+i*dim+j+1] * flt2[1] +
                                img[dim+i*dim+j+2] * flt2[2]) +
                                (img[dim+i*dim+j+3] * flt2[3] +
                                img[dim+i*dim+j+4] * flt2[4])) +

                                ((img[dim+(i+1)*dim+j] *   flt2[5]+
                                img[dim+(i+1)*dim+j+1] * flt2[6] +
                                img[dim+(i+1)*dim+j+2] * flt2[7]) +
                                (img[dim+(i+1)*dim+j+3] * flt2[8] +
                                img[dim+(i+1)*dim+j+4] * flt2[9])) +

                                ((img[dim+(i+2)*dim+j] *   flt2[10]+
                                img[dim+(i+2)*dim+j+1] * flt2[11] +
                                img[dim+(i+2)*dim+j+2] * flt2[12]) +
                                (img[dim+(i+2)*dim+j+3] * flt2[13] +
                                img[dim+(i+2)*dim+j+4] * flt2[14])) +

                                ((img[dim+(i+3)*dim+j] *   flt2[15]+
                                img[dim+(i+3)*dim+j+1] * flt2[16] +
                                img[dim+(i+3)*dim+j+2] * flt2[17]) +
                                (img[dim+(i+3)*dim+j+3] * flt2[18] +
                                img[dim+(i+3)*dim+j+4] * flt2[19])) +

                                ((img[dim+(i+4)*dim+j] *   flt2[20]+
                                img[dim+(i+4)*dim+j+1] * flt2[21] +
                                img[dim+(i+4)*dim+j+2] * flt2[22]) +
                                (img[dim+(i+4)*dim+j+3] * flt2[23] +
                                img[dim+(i+4)*dim+j+4] * flt2[24]))
                                ;



                dst[dim+i*dim+j+1]+=  ((img[dim+i*dim+j+1] *   flt2[0]+
                                img[dim+i*dim+j+2] * flt2[1] +
                                img[dim+i*dim+j+3] * flt2[2]) +
                                (img[dim+i*dim+j+4] * flt2[3] +
                                img[dim+i*dim+j+5] * flt2[4])) +

                                ((img[dim+(i+1)*dim+j+1] *   flt2[5]+
                                img[dim+(i+1)*dim+j+2] * flt2[6] +
                                img[dim+(i+1)*dim+j+3] * flt2[7]) +
                                (img[dim+(i+1)*dim+j+4] * flt2[8] +
                                img[dim+(i+1)*dim+j+5] * flt2[9])) +

                                ((img[dim+(i+2)*dim+j+1] *   flt2[10]+
                                img[dim+(i+2)*dim+j+2] * flt2[11] +
                                img[dim+(i+2)*dim+j+3] * flt2[12]) +
                                (img[dim+(i+2)*dim+j+4] * flt2[13] +
                                img[dim+(i+2)*dim+j+5] * flt2[14])) +

                                ((img[dim+(i+3)*dim+j+1] *   flt2[15]+
                                img[dim+(i+3)*dim+j+2] * flt2[16] +
                                img[dim+(i+3)*dim+j+3] * flt2[17]) +
                                (img[dim+(i+3)*dim+j+4] * flt2[18] +
                                img[dim+(i+3)*dim+j+5] * flt2[19])) +

                                ((img[dim+(i+4)*dim+j+1] *   flt2[20]+
                                img[dim+(i+4)*dim+j+2] * flt2[21] +
                                img[dim+(i+4)*dim+j+3] * flt2[22]) +
                                (img[dim+(i+4)*dim+j+4] * flt2[23] +
                                img[dim+(i+4)*dim+j+5] * flt2[24]))
                                ;
                    dst[dim+i*dim+j+2]+=  ((img[dim+i*dim+j+2] *   flt2[0]+
                                img[dim+i*dim+j+3] * flt2[1] +
                                img[dim+i*dim+j+4] * flt2[2]) +
                                (img[dim+i*dim+j+5] * flt2[3] +
                                img[dim+i*dim+j+6] * flt2[4])) +

                                ((img[dim+(i+1)*dim+j+2] *   flt2[5]+
                                img[dim+(i+1)*dim+j+3] * flt2[6] +
                                img[dim+(i+1)*dim+j+4] * flt2[7]) +
                                (img[dim+(i+1)*dim+j+5] * flt2[8] +
                                img[dim+(i+1)*dim+j+6] * flt2[9])) +

                                ((img[dim+(i+2)*dim+j+2] *   flt2[10]+
                                img[dim+(i+2)*dim+j+3] * flt2[11] +
                                img[dim+(i+2)*dim+j+4] * flt2[12]) +
                                (img[dim+(i+2)*dim+j+5] * flt2[13] +
                                img[dim+(i+2)*dim+j+6] * flt2[14])) +

                                ((img[dim+(i+3)*dim+j+2] *   flt2[15]+
                                img[dim+(i+3)*dim+j+3] * flt2[16] +
                                img[dim+(i+3)*dim+j+4] * flt2[17]) +
                                (img[dim+(i+3)*dim+j+5] * flt2[18] +
                                img[dim+(i+3)*dim+j+6] * flt2[19])) +

                                ((img[dim+(i+4)*dim+j+2] *   flt2[20]+
                                img[dim+(i+4)*dim+j+3] * flt2[21] +
                                img[dim+(i+4)*dim+j+4] * flt2[22]) +
                                (img[dim+(i+4)*dim+j+5] * flt2[23] +
                                img[dim+(i+4)*dim+j+6] * flt2[24]))
                                ;
                    dst[dim+i*dim+j+3]+=  ((img[dim+i*dim+j+3] *   flt2[0]+
                                img[dim+i*dim+j+4] * flt2[1] +
                                img[dim+i*dim+j+5] * flt2[2]) +
                                (img[dim+i*dim+j+6] * flt2[3] +
                                img[dim+i*dim+j+7] * flt2[4])) +

                                ((img[dim+(i+1)*dim+j+3] *   flt2[5]+
                                img[dim+(i+1)*dim+j+4] * flt2[6] +
                                img[dim+(i+1)*dim+j+5] * flt2[7]) +
                                (img[dim+(i+1)*dim+j+6] * flt2[8] +
                                img[dim+(i+1)*dim+j+7] * flt2[9])) +

                                ((img[dim+(i+2)*dim+j+3] *   flt2[10]+
                                img[dim+(i+2)*dim+j+4] * flt2[11] +
                                img[dim+(i+2)*dim+j+5] * flt2[12]) +
                                (img[dim+(i+2)*dim+j+6] * flt2[13] +
                                img[dim+(i+2)*dim+j+7] * flt2[14])) +

                                ((img[dim+(i+3)*dim+j+3] *   flt2[15]+
                                img[dim+(i+3)*dim+j+4] * flt2[16] +
                                img[dim+(i+3)*dim+j+5] * flt2[17]) +
                                (img[dim+(i+3)*dim+j+6] * flt2[18] +
                                img[dim+(i+3)*dim+j+7] * flt2[19])) +

                                ((img[dim+(i+4)*dim+j+3] *   flt2[20]+
                                img[dim+(i+4)*dim+j+4] * flt2[21] +
                                img[dim+(i+4)*dim+j+5] * flt2[22]) +
                                (img[dim+(i+4)*dim+j+6] * flt2[23] +
                                img[dim+(i+4)*dim+j+7] * flt2[24]))
                                ;

                                

                
        }
    }
}







void blurDENEME1(int dim, float *img, float *flt, float *dst);
void blurDENEME2(int dim, float *img, float *flt, float *dst);
void blurDENEME3(int dim, float *img, float *flt, float *dst);
void blurDENEME4(int dim, float *img, float *flt, float *dst);
void blurDENEME12(int dim, float *img, float *flt, float *dst);
void blurDENEME14(int dim, float *img, float *flt, float *dst);
void blurDENEME18(int dim, float *img, float *flt, float *dst);
void register_blur_functions() 
{
    add_blur_function(&naive_blur, naive_blur_descr); 
    add_blur_function(&blur, blur_descr);
    add_blur_function(&blur1, blur_descr1);
    add_blur_function(&blur2, blur_descr2);
    add_blur_function(&blur3, blur_descr3);
    add_blur_function(&blur4, blur_descr4);
    add_blur_function(&blur5, blur_descr5);
    add_blur_function(&blur6, blur_descr6);     //current best
    add_blur_function(&blur7, blur_descr7);
    // add_blur_function(&ALGO2_blur, ALGO2_blur_descr);
    add_blur_function(&blur666, blur_descr666);
    add_blur_function(&blurDENEME1, "DENEME1");
    add_blur_function(&blurDENEME2, "DENEME2");
    add_blur_function(&blurDENEME3, "DENEME3");
    add_blur_function(&blurDENEME4, "DENEME4");
    add_blur_function(&blurDENEME12, "DENEME12");
    add_blur_function(&blurDENEME14, "DENEME14");
    add_blur_function(&blurDENEME18, "DENEME18");

    /* ... Register additional test functions here */
}


void blurDENEME1(int dim, float *img, float *flt, float *dst) {
  
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    int k;
    for(k=0;k<5;k++){
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-4; j++) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
            dst[i*dim+j]+=  
                (img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1]) +
                img[(i+k)*dim+j+2] * flt2[k*5+2] +
                (img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]);

        }
    }
    }

}

void blurDENEME2(int dim, float *img, float *flt, float *dst) {
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    int k;
    for(k=0;k<5;k++)
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-4; j++) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
            dst[i*dim+j]+=  
                ((img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1]) +
                img[(i+k)*dim+j+2] * flt2[k*5+2] +
                (img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]));
        }
    }
}

void blurDENEME3(int dim, float *img, float *flt, float *dst) {
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    int k;
    for(k=0;k<=4;k++)
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-4; j++) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
            dst[i*dim+j]+=  
                ((img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1]) +
                (img[(i+k)*dim+j+2] * flt2[k*5+2] +
                img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]));
        }
    }
}

void blurDENEME4(int dim, float *img, float *flt, float *dst) {
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    int k;
    for(k=0;k<=4;k++)
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-4; j++) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
            dst[i*dim+j]+=  
                ((img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1] +
                img[(i+k)*dim+j+2] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]));
        }
    }
}

void blurDENEME12(int dim, float *img, float *flt, float *dst) {
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    int k;
    for(k=0;k<=4;k++)
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-4; j+=2) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
            dst[i*dim+j]+=  
                ((img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1] +
                img[(i+k)*dim+j+2] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]));

            dst[i*dim+j+1]+=  
                ((img[(i+k)*dim+j+1] *   flt2[k*5+0]+
                img[(i+k)*dim+j+2] * flt2[k*5+1] +
                img[(i+k)*dim+j+3] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+4] * flt2[k*5+3] +
                img[(i+k)*dim+j+5] * flt2[k*5+4]));
        }
    }
}

void blurDENEME14(int dim, float *img, float *flt, float *dst) {
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    int k;
    for(k=0;k<=4;k++)
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-4; j+=4) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
            dst[i*dim+j]+=  
                ((img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1] +
                img[(i+k)*dim+j+2] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]));

            dst[i*dim+j+1]+=  
                ((img[(i+k)*dim+j+1] *   flt2[k*5+0]+
                img[(i+k)*dim+j+2] * flt2[k*5+1] +
                img[(i+k)*dim+j+3] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+4] * flt2[k*5+3] +
                img[(i+k)*dim+j+5] * flt2[k*5+4]));

            dst[i*dim+j+2]+=  
                ((img[(i+k)*dim+j+2] *   flt2[k*5+0]+
                img[(i+k)*dim+j+3] * flt2[k*5+1] +
                img[(i+k)*dim+j+4] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+5] * flt2[k*5+3] +
                img[(i+k)*dim+j+6] * flt2[k*5+4]));

            dst[i*dim+j+3]+=  
                ((img[(i+k)*dim+j+3] *   flt2[k*5+0]+
                img[(i+k)*dim+j+4] * flt2[k*5+1] +
                img[(i+k)*dim+j+5] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+6] * flt2[k*5+3] +
                img[(i+k)*dim+j+7] * flt2[k*5+4]));
        }
    }
}

void blurDENEME18(int dim, float *img, float *flt, float *dst) {
    int i, j;

    float flt2[25];
    flt2[0]=flt[0];
    flt2[1]=flt[1];
    flt2[2]=flt[2];
    flt2[3]=flt[3];
    flt2[4]=flt[4];
    flt2[5]=flt[dim];
    flt2[6]=flt[dim+1];
    flt2[7]=flt[dim+2];
    flt2[8]=flt[dim+3];
    flt2[9]=flt[dim+4];
    flt2[10]=flt[2*dim];
    flt2[11]=flt[2*dim+1];
    flt2[12]=flt[2*dim+2];
    flt2[13]=flt[2*dim+3];
    flt2[14]=flt[2*dim+4];
    flt2[15]=flt[3*dim];
    flt2[16]=flt[3*dim+1];
    flt2[17]=flt[3*dim+2];
    flt2[18]=flt[3*dim+3];
    flt2[19]=flt[3*dim+4];
    flt2[20]=flt[4*dim];
    flt2[21]=flt[4*dim+1];
    flt2[22]=flt[4*dim+2];
    flt2[23]=flt[4*dim+3];
    flt2[24]=flt[4*dim+4];
    int k;
    for(k=0;k<=4;k++)
    for(i = 0; i < dim-4; i++){
        for(j = 0; j < dim-8; j+=8) {                 //3 or 8 unrolling can be better since 15 sized 40 will be used insead
            dst[i*dim+j]+=  
                ((img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1] +
                img[(i+k)*dim+j+2] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]));

            dst[i*dim+j+1]+=  
                ((img[(i+k)*dim+j+1] *   flt2[k*5+0]+
                img[(i+k)*dim+j+2] * flt2[k*5+1] +
                img[(i+k)*dim+j+3] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+4] * flt2[k*5+3] +
                img[(i+k)*dim+j+5] * flt2[k*5+4]));

            dst[i*dim+j+2]+=  
                ((img[(i+k)*dim+j+2] *   flt2[k*5+0]+
                img[(i+k)*dim+j+3] * flt2[k*5+1] +
                img[(i+k)*dim+j+4] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+5] * flt2[k*5+3] +
                img[(i+k)*dim+j+6] * flt2[k*5+4]));

            dst[i*dim+j+3]+=  
                ((img[(i+k)*dim+j+3] *   flt2[k*5+0]+
                img[(i+k)*dim+j+4] * flt2[k*5+1] +
                img[(i+k)*dim+j+5] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+6] * flt2[k*5+3] +
                img[(i+k)*dim+j+7] * flt2[k*5+4]));

                
                

               




   



            dst[i*dim+j+4]+=  
                ((img[(i+k)*dim+j+4] *   flt2[k*5+0]+
                img[(i+k)*dim+j+5] * flt2[k*5+1] +
                img[(i+k)*dim+j+6] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+7] * flt2[k*5+3] +
                img[(i+k)*dim+j+8] * flt2[k*5+4]));

            dst[i*dim+j+5]+=  
                ((img[(i+k)*dim+j+5] *   flt2[k*5+0]+
                img[(i+k)*dim+j+6] * flt2[k*5+1] +
                img[(i+k)*dim+j+7] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+8] * flt2[k*5+3] +
                img[(i+k)*dim+j+9] * flt2[k*5+4]));

            dst[i*dim+j+6]+=  
                ((img[(i+k)*dim+j+6] *   flt2[k*5+0]+
                img[(i+k)*dim+j+7] * flt2[k*5+1] +
                img[(i+k)*dim+j+8] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+9] * flt2[k*5+3] +
                img[(i+k)*dim+j+10] * flt2[k*5+4]));

            dst[i*dim+j+7]+=  
                ((img[(i+k)*dim+j+7] *   flt2[k*5+0]+
                img[(i+k)*dim+j+8] * flt2[k*5+1] +
                img[(i+k)*dim+j+9] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+10] * flt2[k*5+3] +
                img[(i+k)*dim+j+11] * flt2[k*5+4]));

        
        }
        if(dim-4>j){
            dst[i*dim+j]+=  
                ((img[(i+k)*dim+j] *   flt2[k*5+0]+
                img[(i+k)*dim+j+1] * flt2[k*5+1] +
                img[(i+k)*dim+j+2] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+3] * flt2[k*5+3] +
                img[(i+k)*dim+j+4] * flt2[k*5+4]));

            dst[i*dim+j+1]+=  
                ((img[(i+k)*dim+j+1] *   flt2[k*5+0]+
                img[(i+k)*dim+j+2] * flt2[k*5+1] +
                img[(i+k)*dim+j+3] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+4] * flt2[k*5+3] +
                img[(i+k)*dim+j+5] * flt2[k*5+4]));

            dst[i*dim+j+2]+=  
                ((img[(i+k)*dim+j+2] *   flt2[k*5+0]+
                img[(i+k)*dim+j+3] * flt2[k*5+1] +
                img[(i+k)*dim+j+4] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+5] * flt2[k*5+3] +
                img[(i+k)*dim+j+6] * flt2[k*5+4]));

            dst[i*dim+j+3]+=  
                ((img[(i+k)*dim+j+3] *   flt2[k*5+0]+
                img[(i+k)*dim+j+4] * flt2[k*5+1] +
                img[(i+k)*dim+j+5] * flt2[k*5+2]) +
                (img[(i+k)*dim+j+6] * flt2[k*5+3] +
                img[(i+k)*dim+j+7] * flt2[k*5+4]));
        }
    }
}

