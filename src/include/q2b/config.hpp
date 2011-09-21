/*
 * Copyright 2011 Soshnikov Vasiliy <dedok.mad@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaim all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 */

#ifndef QTB_CONFIG_HPP
#define QTB_CONFIG_HPP

#if defined(DEBUG)
 	
#include <stdio.h>	

#define DEBUG_TRACE(...) fprintf(stdout, "TRACE %s",__FUNCTION__);	\
								 fprintf(stdout, " ");								\
				   	  		 fprintf(stdout, __VA_ARGS__); 					\
								 fprintf(stdout, "\n");
#define DEBUG_WARNING(...) fprintf(stderr, "WARNING %s",__FUNCTION__);	\
									fprintf(stderr, " ");								\
		       					fprintf(stderr, __VA_ARGS__); 					\
									fprintf(stderr, " error code %i, sys message %s\n", errno, strerror(errno));
#else

#define DEBUG_TRACE(...)
#define DEBUG_WARNING(...)

#endif

#endif
