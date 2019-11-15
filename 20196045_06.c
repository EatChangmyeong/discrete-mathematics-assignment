#include <stdio.h>

FILE *in, *out;
int length, perm[6], counter = 0;
char list[6];
void permute(int *p, int len) {
	int occurrence[6] = {0}, i;
	if(len == length) {
		fprintf(out, "[%03d]", ++counter);
		for(i = 0; i < length; i++)
			fprintf(out, " %c", list[p[i]]);
		fprintf(out, "\n");
		return;
	}
	
	for(i = 0; i < len; i++)
		occurrence[p[i]] = 1;
	
	for(i = 0; i < 6; i++)
		if(!occurrence[i]) {
			p[len] = i;
			permute(p, len + 1);
		}
}

int main(int argc, char **argv) {
	int i;
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
		fscanf(in, " %c", &list[i]);
	permute(perm, 0);
	fprintf(out, "[ 20196045 LeeSangmyeong :3 ]\n");
	
	return 0; 
}
