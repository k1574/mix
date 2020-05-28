#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 32
#define SIZEL(x) (sizeof(x[0]))
#define NUMEL(x) (sizeof(x/sizeof(x[0])))

char *argv0;

static void
usage(void)
{
	printf("Usage: %s [files]\n", argv0);
	exit(1);
}

static float
sum(float a[], unsigned int n)
{
	int i;
	float f=0 ;
	for( i=0 ; i<n ; ++i )
	 	f += a[i] ;
	return f ;
}

unsigned int
afeof(FILE *a[], unsigned int n)
{
	int i;
	for( i=0 ; i<n ; ++i )
		if( !feof(a[i]) ) return 0 ;
	return  1 ;
}

static void
mix(unsigned int n, char *paths[])
{
	int i, j, e;
	float f;
	float buf[MAX_FILES];
	FILE *files[MAX_FILES];
	for( i=0 ; i<n ; ++i ){
		if( !(files[i] = fopen(paths[i], "rb")) ){
			perror("open");
			exit(1);
		}
	}
	
	for(;;){
		for( i=0 ; i<n ; ++i ){
			if(!feof(files[i])){
				fread(buf+i, SIZEL(buf), 1, files[i]);
			}else{
				buf[i] = 0 ;
			}
		}
		f = sum(buf, n) ;
		fwrite(&f, sizeof(f), 1, stdout);

		if(afeof(files, n))
			break;
	}

	for( i=0 ; i<n ; ++i )
		fclose(files[i]);
}

void
main(int argc, char *argv[])
{
	argv0 = argv[0] ;
	if(argc<2)
		usage();
	
	mix(argc-1, argv+1);

	exit(0);
}
