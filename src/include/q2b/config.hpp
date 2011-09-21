// q2b is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// q2b is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with q2b.  If not, see <http://www.gnu.org/licenses/>.

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
