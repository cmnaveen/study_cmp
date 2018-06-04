#ifndef QUERY_IOCTL_H
#define QUERY_IOCTL_H
#include <linux/ioctl.h>
typedef struct {

int status , dignity,ego;
}qurey_arg_t;

#define QUERY_GET_VARIABLES_IOR('q',1,query_arg_t *)
#define QUERY_CLR_VARIABLES_IO('q',2)
#define QUERY_SET_VARIABLES_IOW('q',3,query_arg_t *)
#endif

