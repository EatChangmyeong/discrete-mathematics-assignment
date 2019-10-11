#include <stdio.h>
int main(int argc, char **argv) {
	int n = argc - 2, i, j;
	FILE *out = fopen(argv[1], "w");
	fprintf(out, "\xef\xbb\xbf"); //Ensure UTF-8 Encoding
	for(i = 0; i < 1 << n; i++) {
		fprintf(out, "[%04d]", i + 1);
		if(i) {
			for(j = 0; j < n; j++)
				if(i & 1 << j)
					fprintf(out, " %s", argv[j + 2]);
		} else
			fprintf(out, " \xe2\x88\x85"); //Empty set (U+2205) in UTF-8
		fprintf(out, "\n");
	}
	fprintf(out, "[ 20196045 LeeSangmyeong :3 ]\n");
	fclose(out);
	return 0; 
}
