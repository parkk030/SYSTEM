#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
	void *handle;
	int (*add)(int, int), (*subtract)(int,int),(*multiply)(int,int),(*divide)(int,int);
	char *error;

	handle = dlopen("./lib/libtest.so", RTLD_LAZY);
	if(!handle){
		fputs(dlerror(), stderr);
		exit(1);
	}

	add  = dlsym(handle, "add");
	if((error=dlerror()) !=NULL){
		fprintf(stderr,"%s", error);
		exit(1);
	}
	subtract  = dlsym(handle, "add");
        if((error=dlerror()) !=NULL){
                fprintf(stderr,"%s", error);
                exit(1);
        }       
	multiply  = dlsym(handle, "add");
        if((error=dlerror()) !=NULL){
                fprintf(stderr,"%s", error);
                exit(1);
        }       
	divide  = dlsym(handle, "add");
        if((error=dlerror()) !=NULL){
                fprintf(stderr,"%s", error);
                exit(1);
        }     

    printf("add(4,2) = %d\n",add(4,2));
    printf("subtract(4,2) = %d\n",subtract(4,2));
    printf("multiply(4,2) = %d\n",multiply(4,2));
    printf("divide(4,2) = %d\n",divide(4,2));   	
}
