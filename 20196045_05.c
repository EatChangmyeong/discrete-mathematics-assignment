#include <stdio.h>

FILE *in, *out;
int length;
int sum(int list[], int size) {
	if(size) {
		int s = list[0] + sum(list + 1, --size);
		fprintf(out, "[%03d] %d\n", length - size, s);
		return s;
	} else return 0;
}
int main(int argc, char **argv) {
	int list[100], i;
	if((in = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ERROR: failed to open %s for reading", argv[1]);
		return 0;
	}
	if((out = fopen(argv[2], "w")) == NULL) {
		fprintf(stderr, "ERROR: failed to open %s for writing", argv[2]);
		return 0;
	}
	
	fscanf(in, "%d", &length);
	for(i = 0; i < length; i++)
		fscanf(in, "%d", &list[i]);
	sum(list, length);
	fprintf(out, "[ 20196045 LeeSangmyeong :3 ]\n");
	
	return 0; 
}
