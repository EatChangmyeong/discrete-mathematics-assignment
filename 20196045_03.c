#include <stdio.h>
int main(int argc, char **argv) {
	int n = argc - 1, i, j;
	for(i = 0; i < 1 << n; i++) {
		printf("[%04d]", i + 1);
		if(i) {
			for(j = 0; j < n; j++)
				if(i & 1 << j)
					printf(" %s", argv[j + 1]);
		} else
			printf(" (/)"); //Failed to print the empty set symbol...
		printf("\n");
	}
	printf("[ 20196045 LeeSangmyeong :3 ]\n");
	return 0; 
}
