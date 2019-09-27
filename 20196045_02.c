#include <stdio.h>
int main(int argc, char **argv) {
	int sum = 0, sign, t, i;
	for(i = 1; i < argc; i++) {
		if(i & 1)
			sign = argv[i][0] == '+';
		else {
			sscanf(argv[i], "%d", &t);
			sum += sign ? t : -t;
		}
	}
	printf("= %d\n", sum);
	printf("[ 20196045 LeeSangmyeong :3 ]");
	return 0; 
}
