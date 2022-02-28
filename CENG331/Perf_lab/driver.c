/*******************************************************************
 * 
 * driver.c - Driver program for CS:APP Performance Lab
 * 
 * In kernels.c, students generate an arbitrary number of fusion and
 * blur test functions, which they then register with the driver
 * program using the add_fusion_function() and add_blur_function()
 * functions.
 * 
 * The driver program runs and measures the registered test functions
 * and reports their performance.
 * 
 * Copyright (c) 2002, R. Bryant and D. O'Hallaron, All rights
 * reserved.  May not be used, modified, or copied without permission.
 *
 ********************************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "fcyc.h"
#include "defs.h"
#include "config.h"

/* Team structure that identifies the students */
extern team_t team; 
int seed;

/* Keep track of a number of different test functions */
#define MAX_BENCHMARKS 100
#define DIM_CNT 5

/* Misc constants */
#define BSIZE 32     /* cache block size in bytes */     
#define MAX_DIM 1280 /* 1024 + 256 */
#define ODD_DIM 96   /* not a power of 2 */

/* fast versions of min and max */
#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)

#define PI 3.14159265358979323846

/* This struct characterizes the results for one benchmark test */
typedef struct {
    lab_test_func1 tfunct; /* The test function */
    double cpes[DIM_CNT]; /* One CPE result for each dimension */
    char *description;    /* ASCII description of the test function */
    unsigned short valid; /* The function is tested if this is non zero */
} bench_fusion_t;

/* This struct characterizes the results for one benchmark test */
typedef struct {
    lab_test_func2 tfunct; /* The test function */
    double cpes[DIM_CNT]; /* One CPE result for each dimension */
    char *description;    /* ASCII description of the test function */
    unsigned short valid; /* The function is tested if this is non zero */
} bench_blur_t;

/* The range of image dimensions that we will be testing */
static int test_dim_fusion[] = {64, 128, 256, 512, 1024};
static int test_dim_blur[] = {64, 128, 256, 512, 1024};

/* Baseline CPEs (see config.h) */
static double fusion_baseline_cpes[] = {F64, F128, F256, F512, F1024};
static double blur_baseline_cpes[] = {B64, B128, B256, B512, B1024};

/* These hold the results for all benchmarks */
static bench_fusion_t benchmarks_fusion[MAX_BENCHMARKS];
static bench_blur_t benchmarks_blur[MAX_BENCHMARKS];

/* These give the sizes of the above lists */
static int fusion_benchmark_count = 0;
static int blur_benchmark_count = 0;

/* 
 * An image is a dimxdim matrix of pixels stored in a 1D array.  The
 * data array holds three images (the input original, a copy of the original, 
 * and the output result array. There is also an additional BSIZE bytes
 * of padding for alignment to cache block boundaries.
 */
static int images_data[(9*MAX_DIM*MAX_DIM) + (BSIZE/sizeof(int))];
static int weight_data[(8*MAX_DIM*MAX_DIM) + (BSIZE/sizeof(int))];

static float image_data[(3*MAX_DIM*MAX_DIM) + (BSIZE/sizeof(float))];
static float filter_data[(2*MAX_DIM*MAX_DIM) + (BSIZE/sizeof(float))];

/* Various image pointers */
static int *orig_imgs = NULL;         		/* original image */
static int *copy_of_orig_imgs = NULL; 		/* copy of original image for checking result */
static int *orig_weight = NULL;	   		    /* original weight matrix */
static int *copy_of_orig_weight = NULL;	    /* copy of original weight matrix for checking result */
static int *result_img = NULL;       		/* result image */

/* Various matrix pointers */
static float *orig_img = NULL; 				/* original image */
static float *orig_filter = NULL; 			/* original Gaussian filter */
static float *copy_of_orig_img = NULL;		/* copy original image for checking result */
static float *copy_of_orig_filter = NULL;		/* copy original Gaussian filter for checking result */
static float *blur_img = NULL;				/* blurred image */

/* Keep track of the best fusion and blur score for grading */
double fusion_maxmean = 0.0;
char *fusion_maxmean_desc = NULL;

double blur_maxmean = 0.0;
char *blur_maxmean_desc = NULL;


/******************** Functions begin *************************/

void add_fusion_function(lab_test_func1 f, char *description) 
{
    benchmarks_fusion[fusion_benchmark_count].tfunct = f;
    benchmarks_fusion[fusion_benchmark_count].description = description;
    benchmarks_fusion[fusion_benchmark_count].valid = 0;
    fusion_benchmark_count++;
}

void add_blur_function(lab_test_func2 f, char *description) 
{
    benchmarks_blur[blur_benchmark_count].tfunct = f;
    benchmarks_blur[blur_benchmark_count].description = description;
    benchmarks_blur[blur_benchmark_count].valid = 0;  
    blur_benchmark_count++;
}

/* 
 * random_in_interval - Returns random integer in interval [low, high) 
 */
static float random_in_interval(int low, int high) 
{
    int size = high - low;
    return (float)(rand()% size) + low;
}

/*
 * create_images_and_weight - creates 4 dimxdim images and their weights aligned to a BSIZE byte boundary
 */
static void create_images_and_weight(int dim)
{
    int i, j, k, offset;
    
    srand(seed);
    /* Align the images to BSIZE byte boundaries */
    orig_imgs = images_data;
    
    while ((unsigned)orig_imgs % BSIZE)
		orig_imgs++;
    result_img = orig_imgs + 4*dim*dim;
    copy_of_orig_imgs = result_img + dim*dim;

    /* Align the weights to the BSIZE byte boundary */
    orig_weight = weight_data;
    while ((unsigned)orig_weight % BSIZE)
    	orig_weight++;
    copy_of_orig_weight = orig_weight + 4*dim*dim;
    
    
    for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			for (k = 0; k < 4; k++){
				offset = k*dim*dim;
			    /* Original image initialized to random grayscale colors */
			    orig_imgs[offset+RIDX(i,j,dim)] = random_in_interval(0, 20000);

			    /* Copy of original image for checking result */
			    copy_of_orig_imgs[offset+RIDX(i,j,dim)] = orig_imgs[offset+RIDX(i,j,dim)];

			    /* Weight is created with fully focused at the beginning */
			    orig_weight[offset+RIDX(i,j,dim)] = random_in_interval(0,3);

			    /* Copy of original weight for checking result */
			    copy_of_orig_weight[offset+RIDX(i,j,dim)] = orig_weight[offset+RIDX(i,j,dim)];
			}

		    /* Result image initialized to all black */
		    result_img[RIDX(i,j,dim)] = 0;
		}
    }

    return;
}

static void gaussian_filter(int dim, int size){
	int i, j;
	float value;
	int grid = (size-1)/2;

	for (i = -grid; i <= grid; i++){
		for (j = -grid; j <= grid; j++){
			value = expf(-((float)(i*i+j*j)) / 2) / (2*PI);

			orig_filter[RIDX(i+grid,j+grid,dim)] = value;
			copy_of_orig_filter[RIDX(i+grid,j+grid,dim)] = value;
		}
	}
}


/*
 * create_image_and_filter - creates two dimxdim matrices aligned to a BSIZE byte boundary
 */
static void create_image_and_filter(int dim)
{
    int i, j;
    srand(seed);
    /* Align the images to BSIZE byte boundaries */
    orig_img = image_data;
    
    while ((unsigned)orig_img % BSIZE)
		orig_img++;
    blur_img = orig_img + dim*dim;
    copy_of_orig_img = blur_img + dim*dim;

    /* Align the weights to the BSIZE byte boundary */
    orig_filter = filter_data;
    while ((unsigned)orig_filter % BSIZE)
    	orig_filter++;
    copy_of_orig_filter = orig_filter + dim*dim;

    for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
		    /* Original matrices initialized to random integers */
		    orig_img[RIDX(i,j,dim)]	 		= random_in_interval(0, 65536);
		    orig_filter[RIDX(i,j,dim)] 		= 0;

		    /* Copy of original matrices for checking result */
		    copy_of_orig_img[RIDX(i,j,dim)] 	= orig_img[RIDX(i,j,dim)];
		    copy_of_orig_filter[RIDX(i,j,dim)]	= 0;
		   
		    /* Result image initialized to all 0 */
		    blur_img[RIDX(i,j,dim)] = 0;
		}
    }
    gaussian_filter(dim,5);
    return;
}


/* Make sure the orig images and weights is unchanged */
static int check_orig_imgs_and_weight(int dim) 
{
    int i, j, k, offset;

    for (k = 0; k < 4; k++){
    	offset = k*dim*dim;
	    for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++) { 
			    if (orig_imgs[offset+RIDX(i,j,dim)] != copy_of_orig_imgs[offset+RIDX(i,j,dim)]) {
					printf("\n");
					printf("Error: Original images have been changed!\n");
					return 1;
			    }
			    if (orig_weight[offset+RIDX(i,j,dim)] != copy_of_orig_weight[offset+RIDX(i,j,dim)]) {
					printf("\n");
					printf("Error: Original weights have been changed!\n");
					return 1;
			    }
			}
		}
	}
    return 0;
}

/* Make sure the orig array is unchanged */
static int check_orig_img_and_filter(int dim) 
{
    int i, j;

    for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
		    if ( orig_img[RIDX(i,j,dim)] != copy_of_orig_img[RIDX(i,j,dim)] ) {
				printf("\n");
				printf("Error: Original image has been changed!\n");
				return 1;
		    }
		    if ( orig_filter[RIDX(i,j,dim)] != copy_of_orig_filter[RIDX(i,j,dim)] ) {
				printf("\n");
				printf("Error: Original Gaussian filter has been changed!\n");
				return 1;
		    }
		}
    }

    return 0;
}

static int fused_value(int dim, int i, int j) {
    int k, result;
 
    result = 0;
    for(k = 0; k < 4; k++)
	    result += orig_imgs[dim*dim*k+RIDX(i,j,dim)] * orig_weight[dim*dim*k+RIDX(i,j,dim)];
 
    return result;
}


/* 
 * check_fusion - Make sure the fusion function actually works.  The
 * orig array should not have been tampered with!  
 */
static int check_fusion(int dim) {
    int err = 0;
    int i, j;
    int badi = 0;
    int badj = 0;
    int right, wrong;

    /* return 1 if original image has been changed */
    if (check_orig_imgs_and_weight(dim)) 
		return 1; 

    for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			int fused = fused_value(dim, i, j);
		    if (result_img[RIDX(i,j,dim)] != fused) {
				err++;
				badi = i;
				badj = j;
				wrong = result_img[RIDX(i,j,dim)];
				right = fused;
				break;
		    }
		}
		if (err) break;
    }

    if (err) {
		printf("\n");
		printf("ERROR: Dimension=%d, %d errors\n", dim, err);    
		printf("E.g., \n");
		printf("You have dst[%d][%d] = %d\n",
		       badi, badj, wrong);
		printf("It should be dst[%d][%d] = %d\n",
		       badi, badj, right);
    }

    return err;
}


static int compare_floats(float f1, float f2){
	float eps = 0.01;
	return ((f1 < (f2-eps)) || (f1 > (f2+eps)));
}

/* 
 * check_blur - Make sure the blur actually works. 
 * The orig array should not  have been tampered with! 
 */
static int check_blur(int dim) 
{
    int err = 0;
    int i, j, k, l;
    int badi = 0;
    int badj = 0;
    float res_bad;
    float blurred;

    /* return 1 if the original image has been  changed */
    if (check_orig_img_and_filter(dim)) 
		return 1; 

	for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
        	blurred = 0;
            for(k = 0; k < 5; k++)
                for(l = 0; l < 5; l++) {
                    blurred = blurred + orig_img[(i+k)*dim+(j+l)]*orig_filter[k*dim+l];
                }
            if(compare_floats(blurred, blur_img[RIDX(i,j,dim)])){
            	err++;
				badi = i;
				badj = j;
				res_bad = blur_img[RIDX(i,j,dim)];
				break;
            }
   
		}
		if (err) break;

    }

    if (err) {
		printf("\n");
		printf("ERROR: Dimension=%d, %d errors\n", dim, err);    
		printf("E.g., The following blurred pixel  to the wrong result:\n");
		printf("You have dst[%d][%d] = %f and it should be dst[%d][%d] = %f\n",
		       badi, badj, res_bad, badi, badj, blurred);
    }

    return err;
}




void func_wrapper_fusion(void *arglist[]) 
{
    int *img, *w, *dst;
    int mydim;
    lab_test_func1 f;

    f = (lab_test_func1) arglist[0];
    mydim = *((int *) arglist[1]);
    img = (int *) arglist[2];
    w = (int *) arglist[3];
    dst = (int *) arglist[4];

    (*f)(mydim, img, w, dst);

    return;
}

void func_wrapper_blur(void *arglist[]) 
{
    float *img, *flt, *dst;
    int mydim;
    lab_test_func2 f;

    f = (lab_test_func2) arglist[0];
    mydim = *((int *) arglist[1]);
    img = (float *) arglist[2];
    flt = (float *) arglist[3];
    dst = (float *) arglist[4];

    (*f)(mydim, img, flt, dst);

    return;
}

void run_fusion_benchmark(int idx, int dim) 
{
    benchmarks_fusion[idx].tfunct(dim, orig_imgs, orig_weight, result_img);
}

void test_fusion(int bench_index) 
{
    int i;
    int test_num;
    char *description = benchmarks_fusion[bench_index].description;
  
    for(test_num=0; test_num < DIM_CNT; test_num++) {
	int dim;

	/* Check correctness for odd (non power of two dimensions */
	create_images_and_weight(ODD_DIM);
	run_fusion_benchmark(bench_index, ODD_DIM);
	if (check_fusion(ODD_DIM)) {
	    printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
		   benchmarks_fusion[bench_index].description, ODD_DIM);
	    return;
	}

	/* Create a test image of the required dimension */
	dim = test_dim_fusion[test_num];
	create_images_and_weight(dim);

#ifdef DEBUG
	printf("DEBUG: Running benchmark \"%s\"\n", benchmarks_fusion[bench_index].description);
#endif
	/* Check that the code works */
	run_fusion_benchmark(bench_index, dim);
	if (check_fusion(dim)) {
	    printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
		   benchmarks_fusion[bench_index].description, dim);
	    return;
	}

	/* Measure CPE */
	{
	    double num_cycles, cpe;
	    int tmpdim = dim;
	    void *arglist[5];
	    double dimension = (double) dim;
	    double work = dimension*dimension;
#ifdef DEBUG
	    printf("DEBUG: dimension=%.1f\n",dimension);
	    printf("DEBUG: work=%.1f\n",work);
#endif
	    arglist[0] = (void *) benchmarks_fusion[bench_index].tfunct;
	    arglist[1] = (void *) &tmpdim;
	    arglist[2] = (void *) orig_imgs;
	    arglist[3] = (void *) orig_weight;
	    arglist[4] = (void *) result_img;
        
	    create_images_and_weight(dim);
	    num_cycles = fcyc_v((test_funct_v)&func_wrapper_fusion, arglist); 
	    cpe = num_cycles/work;
	    benchmarks_fusion[bench_index].cpes[test_num] = cpe;
	}
    }

    /* Print results as a table */
    printf("fusion: Version = %s:\n", description);
    printf("Dim\t");
    for (i = 0; i < DIM_CNT; i++)
	printf("\t%d", test_dim_fusion[i]);
    printf("\tMean\n");
  
    printf("Your CPEs");
    for (i = 0; i < DIM_CNT; i++) {
	printf("\t%.1f", benchmarks_fusion[bench_index].cpes[i]);
    }
    printf("\n");

    printf("Baseline CPEs");
    for (i = 0; i < DIM_CNT; i++) {
	printf("\t%.1f", fusion_baseline_cpes[i]);
    }
    printf("\n");

    /* Compute speedup */
    {
	double prod, ratio, mean;
	prod = 1.0; /* Geometric mean */
	printf("Speedup\t");
	for (i = 0; i < DIM_CNT; i++) {
	    if (benchmarks_fusion[bench_index].cpes[i] > 0.0) {
		ratio = fusion_baseline_cpes[i]/
		    benchmarks_fusion[bench_index].cpes[i];
	    }
	    else {
		printf("Fatal Error: Non-positive CPE value...\n");
		exit(EXIT_FAILURE);
	    }
	    prod *= ratio;
	    printf("\t%.1f", ratio);
	}
	/* Geometric mean */
	mean = pow(prod, 1.0/(double) DIM_CNT);
	printf("\t%.1f", mean);
	printf("\n\n");
	if (mean > fusion_maxmean) {
	    fusion_maxmean = mean;
	    fusion_maxmean_desc = benchmarks_fusion[bench_index].description;
	}
    }

    return;  
}

void run_blur_benchmark(int idx, int dim) 
{
    benchmarks_blur[idx].tfunct(dim, orig_img, orig_filter, blur_img);
}

void test_blur(int bench_index) 
{
    int i;
    int test_num;
    char *description = benchmarks_blur[bench_index].description;
  
    for (test_num = 0; test_num < DIM_CNT; test_num++) {
	int dim;

	/* Check for odd dimension */
	create_image_and_filter(ODD_DIM);
	run_blur_benchmark(bench_index, ODD_DIM);
	if (check_blur(ODD_DIM)) {
	    printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
		   benchmarks_blur[bench_index].description, ODD_DIM);
	    return;
	}

	/* Create a test image of the required dimension */
	dim = test_dim_blur[test_num];
	create_image_and_filter(dim);
#ifdef DEBUG
	printf("DEBUG: Running benchmark \"%s\"\n", benchmarks_blur[bench_index].description);
#endif

	/* Check that the code works */
	run_blur_benchmark(bench_index, dim);
	if (check_blur(dim)) {
	    printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
		   benchmarks_blur[bench_index].description, dim);
	    return;
	}

	/* Measure CPE */
	{
	    double num_cycles, cpe;
	    int tmpdim = dim;
	    void *arglist[5];
	    double dimension = (double) dim;
	    double work = dimension*dimension;
#ifdef DEBUG
	    printf("DEBUG: dimension=%.1f\n",dimension);
	    printf("DEBUG: work=%.1f\n",work);
#endif
	    arglist[0] = (void *) benchmarks_blur[bench_index].tfunct;
	    arglist[1] = (void *) &tmpdim;
	    arglist[2] = (void *) orig_img;
	    arglist[3] = (void *) orig_filter;
	    arglist[4] = (void *) blur_img;

	    create_image_and_filter(dim);
	    num_cycles = fcyc_v((test_funct_v)&func_wrapper_blur, arglist); 
	    cpe = num_cycles/work;
	    benchmarks_blur[bench_index].cpes[test_num] = cpe;
	}
    }

    /* 
     * Print results as a table 
     */
    printf("blur: Version = %s:\n", description);
    printf("Dim\t");
    for (i = 0; i < DIM_CNT; i++)
	printf("\t%d", test_dim_blur[i]);
    printf("\tMean\n");
  
    printf("Your CPEs");
    for (i = 0; i < DIM_CNT; i++) {
	printf("\t%.1f", benchmarks_blur[bench_index].cpes[i]);
    }
    printf("\n");

    printf("Baseline CPEs");
    for (i = 0; i < DIM_CNT; i++) {
	printf("\t%.1f", blur_baseline_cpes[i]);
    }
    printf("\n");

    /* Compute Speedup */
    {
	double prod, ratio, mean;
	prod = 1.0; /* Geometric mean */
	printf("Speedup\t");
	for (i = 0; i < DIM_CNT; i++) {
	    if (benchmarks_blur[bench_index].cpes[i] > 0.0) {
		ratio = blur_baseline_cpes[i]/
		    benchmarks_blur[bench_index].cpes[i];
	    }
	    else {
		printf("Fatal Error: Non-positive CPE value...\n");
		exit(EXIT_FAILURE);
	    }
	    prod *= ratio;
	    printf("\t%.1f", ratio);
	}

	/* Geometric mean */
	mean = pow(prod, 1.0/(double) DIM_CNT);
	printf("\t%.1f", mean);
	printf("\n\n");
	if (mean > blur_maxmean) {
	    blur_maxmean = mean;
	    blur_maxmean_desc = benchmarks_blur[bench_index].description;
	}
    }


#ifdef DEBUG
    fflush(stdout);
#endif
    return;  
}




void usage(char *progname) 
{
    fprintf(stderr, "Usage: %s [-hqg] [-f <func_file>] [-d <dump_file>]\n", progname);    
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -h         Print this message\n");
    fprintf(stderr, "  -q         Quit after dumping (use with -d )\n");
    fprintf(stderr, "  -g         Autograder mode: checks only fusion() and blur()\n");
    fprintf(stderr, "  -f <file>  Get test function names from dump file <file>\n");
    fprintf(stderr, "  -d <file>  Emit a dump file <file> for later use with -f\n");
    exit(EXIT_FAILURE);
}



int main(int argc, char *argv[])
{
    int i;
    int quit_after_dump = 0;
    int skip_teamname_check = 0;
    int autograder = 0;
    seed = 1729;
    char c = '0';
    char *bench_func_file = NULL;
    char *func_dump_file = NULL;

    /* register all the defined functions */
    register_fusion_functions();
    register_blur_functions();

    /* parse command line args */
    while ((c = getopt(argc, argv, "tgqf:d:s:h")) != -1)
	switch (c) {

	case 't': /* skip team name check (hidden flag) */
	    skip_teamname_check = 1;
	    break;

	case 's': /* seed for random number generator (hidden flag) */
	    seed = atoi(optarg);
	    break;

	case 'g': /* autograder mode (checks only fusion() and blur()) */
	    autograder = 1;
	    break;

	case 'q':
	    quit_after_dump = 1;
	    break;

	case 'f': /* get names of benchmark functions from this file */
	    bench_func_file = strdup(optarg);
	    break;

	case 'd': /* dump names of benchmark functions to this file */
	    func_dump_file = strdup(optarg);
	    {
		int i;
		FILE *fp = fopen(func_dump_file, "w");	

		if (fp == NULL) {
		    printf("Can't open file %s\n",func_dump_file);
		    exit(-5);
		}

		for(i = 0; i < fusion_benchmark_count; i++) {
		    fprintf(fp, "R:%s\n", benchmarks_fusion[i].description); 
		}
		for(i = 0; i < blur_benchmark_count; i++) {
		    fprintf(fp, "S:%s\n", benchmarks_blur[i].description); 
		}
		fclose(fp);
	    }
	    break;

	case 'h': /* print help message */
	    usage(argv[0]);

	default: /* unrecognized argument */
	    usage(argv[0]);
	}

    if (quit_after_dump) 
	exit(EXIT_SUCCESS);


    /* Print team info */
    if (!skip_teamname_check) {
	if (strcmp("bovik", team.team) == 0) {
	    printf("%s: Please fill in the team struct in kernels.c.\n", argv[0]);
	    exit(1);
	}
	printf("Teamname: %s\n", team.team);
	printf("Member 1: %s\n", team.name1);
	printf("ID 1: %s\n", team.id1);
	if (*team.name2 || *team.id2) {
	    printf("Member 2: %s\n", team.name2);
	    printf("ID 2: %s\n", team.id2);
	}
	if (*team.name3 || *team.id3) {
	    printf("Member 3: %s\n", team.name3);
	    printf("ID 3: %s\n", team.id3);
	}
	printf("\n");
    }

    //srand(seed);

    /* 
     * If we are running in autograder mode, we will only test
     * the fusion() and blur() functions.
     */
    if (autograder) {
	fusion_benchmark_count = 1;
	blur_benchmark_count = 1;

	benchmarks_fusion[0].tfunct = fusion;
	benchmarks_fusion[0].description = "fusion() function";
	benchmarks_fusion[0].valid = 1;

	benchmarks_blur[0].tfunct = blur;
	benchmarks_blur[0].description = "blur() function";
	benchmarks_blur[0].valid = 1;
    }

    /* 
     * If the user specified a file name using -f, then use
     * the file to determine the versions of fusion and blur to test
     */
    else if (bench_func_file != NULL) {
	char flag;
	char func_line[256];
	FILE *fp = fopen(bench_func_file, "r");

	if (fp == NULL) {
	    printf("Can't open file %s\n",bench_func_file);
	    exit(-5);
	}
    
	while(func_line == fgets(func_line, 256, fp)) {
	    char *func_name = func_line;
	    char **strptr = &func_name;
	    char *token = strsep(strptr, ":");
	    flag = token[0];
	    func_name = strsep(strptr, "\n");
#ifdef DEBUG
	    printf("Function Description is %s\n",func_name);
#endif

	    if (flag == 'R') {
		for(i=0; i<fusion_benchmark_count; i++) {
		    if (strcmp(benchmarks_fusion[i].description, func_name) == 0)
			benchmarks_fusion[i].valid = 1;
		}
	    }
	    else if (flag == 'S') {
		for(i=0; i<blur_benchmark_count; i++) {
		    if (strcmp(benchmarks_blur[i].description, func_name) == 0)
			benchmarks_blur[i].valid = 1;
		}
	    }      
	}

	fclose(fp);
    }

    /* 
     * If the user didn't specify a dump file using -f, then 
     * test all of the functions
     */
    else { /* set all valid flags to 1 */
	for (i = 0; i < fusion_benchmark_count; i++)
	    benchmarks_fusion[i].valid = 1;
	for (i = 0; i < blur_benchmark_count; i++)
	    benchmarks_blur[i].valid = 1;
    }

    /* Set measurement (fcyc) parameters */
    set_fcyc_cache_size(1 << 14); /* 16 KB cache size */
    set_fcyc_clear_cache(1); /* clear the cache before each measurement */
    set_fcyc_compensate(1); /* try to compensate for timer overhead */
 
    for (i = 0; i < fusion_benchmark_count; i++) {
	if (benchmarks_fusion[i].valid)
	    test_fusion(i);
    
}
    for (i = 0; i < blur_benchmark_count; i++) {
	if (benchmarks_blur[i].valid)
	    test_blur(i);
    }


    if (autograder) {
	printf("\nbestscores:%.1f:%.1f:\n", fusion_maxmean, blur_maxmean);
    }
    else {
	printf("Summary of Your Best Scores:\n");
	printf("  fusion: %3.1f (%s)\n", fusion_maxmean, fusion_maxmean_desc);
	printf("  blur: %3.1f (%s)\n", blur_maxmean, blur_maxmean_desc);
    }

    return 0;
}












