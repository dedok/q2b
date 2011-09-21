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
