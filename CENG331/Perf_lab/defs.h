/*
 * driver.h - Various definitions for the Performance Lab.
 * 
 * DO NOT MODIFY ANYTHING IN THIS FILE
 */
#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdlib.h>

#define RIDX(i,j,n) ((i)*(n)+(j))

typedef struct {
  char *team;
  char *name1, *id1;
  char *name2, *id2;
  char *name3, *id3;
} team_t;

extern team_t team;


typedef void (*lab_test_func1) (int, int*, int*, int*);
typedef void (*lab_test_func2) (int, float*, float*, float*);

void fusion(int, int *, int *, int *);
void blur(int, float *, float *, float *);

void register_fusion_functions(void);
void register_blur_functions(void);
void add_fusion_function(lab_test_func1, char*);
void add_blur_function(lab_test_func2, char*);

#endif /* _DEFS_H_ */

