/*********************************************************
 * config.h - Configuration data for the driver.c program.
 *********************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/* 
 * CPEs for the baseline (naive) version of the fusion function that
 * was handed out to the students. Fd is the measured CPE for a dxd
 * image. Run the driver.c program on your system to get these
 * numbers.  
 */
#define F64    7.4
#define F128   7.4
#define F256   7.3
#define F512   7.9
#define F1024  9.5

/* 
 * CPEs for the baseline (naive) version of the blur function that
 * was handed out to the students. Bd is the measure CPE for a dxd
 * image. Run the driver.c program on your system to get these
 * numbers.  
 */
#define B64   	43.3 
#define B128  	46.0 
#define B256  	53.3 
#define B512  	67.0 
#define B1024 	69.4 

#endif /* _CONFIG_H_ */
