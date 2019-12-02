/**
 * 20196045_07.c: (c) 2019 EatChangmyeong
 * 
 * This C program reads a file, scans every word contained in it
 * (delimited by non-alphanumeric characters) and writes occurrence of
 * each of them into a given file.
 * 
 * In this implementation, I stored dictionary words in a linked list
 * to work with unknown and hard-to-predict number of different words.
 * Original content is written in a dynamically allocated char array,
 * since its size (in bytes) can easily be calculated from its filesize.
 * This program can take a long time to complete with very large input,
 * so I decided to print its progress to stdout every 100K words.
 * The first, naive implementation takes approximately 30~70 seconds
 * to scan a 6+MB input with ~1.12M words.
 * 
 * Then, I tried sorting the dictionary by their occurrences in descending order
 * every 100K words, so that frequently used words are more quickly found
 * in linked list search. and the result is also neatly sorted.
 * This implementation takes approximately ~85 seconds, so I decided to
 * scrap that feature, except for the last sort just before outputting.
 * The final result of running time is approximately 25~35 seconds now.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// A dictionary word element, in a linked list format
struct _dictElem;
struct _dictElem {
	char *word;
	int count;
	struct _dictElem *next;
};
typedef struct _dictElem dictElem;

FILE *in, *out;
dictElem *dict;
int dictSize = 0;

clock_t clk; // to keep track of running time

char* strtok_alphanumeric(char *str) { // strtok by non-alphanumeric
	static char *p;
	char *wf;
	if(str)
		p = --str;
	
	while(!isalnum(*++p))
		if(!*p)
			return NULL;
	wf = p;
	while(isalnum(*++p));
	*p = '\0';
	return wf;
}

void pushWord(char *str) { // Push a word into the dictionary
	dictElem *dp = dict, *dprev = NULL, *dn;
	while(dp) { // Look for a matching string
		if(!strcmp(dp->word, str)) {
			dp->count++;
			return;
		}
		dprev = dp;
		dp = dp->next;
	}
	
	// Append a new element
	dn = malloc(sizeof(dictElem));
	dn->word = str;
	dn->count = 1;
	if(dprev) {
		dprev->next = dn;
		dn->next = dp;
	} else {
		dn->next = dict;
		dict = dn;
	}
	dictSize++;
}

int sorter(const void *a, const void *b) {
	return (*(dictElem**)b)->count - (*(dictElem**)a)->count;
}
void sortDict() { // Sort by occurrences
	dictElem **lst = malloc(dictSize*sizeof(dictElem*)), *dp = dict;
	int i;
	for(i = 0; i < dictSize; i++) { // Map the linked list into an array
		lst[i] = dp;
		dp = dp->next;
	}
	qsort(lst, dictSize, sizeof(dictElem*), sorter);
	for(i = 0; i < dictSize; i++) // Relink the list
		lst[i]->next = i == dictSize - 1 ? NULL : lst[i + 1];
	dict = lst[0];
}

void enumerateWord(FILE *f) { // Write word count statistics
	int n = dictSize, l = 0;
	dictElem *dp = dict;
	while(n) {
		n /= 10;
		l++;
	}
	l = l ? l : 1;
	
	while(dp) {
		fprintf(f, "[%0*d] %s (%d)\n", l, ++n, dp->word, dp->count);
		dp = dp->next;
	}
}

int main(int argc, char **argv) {
	char *text, *tok;
	int p = -1, fsz, c = 0;
	
	// Open file
	if((in = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ERROR: failed to open %s for reading", argv[1]);
		return 0;
	}
	if((out = fopen(argv[2], "w")) == NULL) {
		fprintf(stderr, "ERROR: failed to open %s for writing", argv[2]);
		return 0;
	}
	
	clk = clock();
	
	// Get filesize
	fseek(in, 0l, SEEK_END);
	fsz = ftell(in);
	fseek(in, 0l, SEEK_SET);
	text = malloc((fsz + 1)*sizeof(char));
	
	// Read file
	while((text[++p] = fgetc(in)) != EOF)
		text[p] = tolower(text[p]);
	text[p] = '\0';
	
	fclose(in);
	
	// Tokenize & construct dictionary
	tok = strtok_alphanumeric(text);
	while(tok) {
		pushWord(tok);
		if(!(++c % 100000))
			printf("Constructing dictionary: %d words\n", c);
		tok = strtok_alphanumeric(NULL);
	}
	
	// Output to file
	sortDict();
	enumerateWord(out);
	fprintf(out, "[total] %d\n", c);
	fprintf(out, "[ 20196045 LeeSangmyeong :3 ]\n");
	
	printf("Done. Scanned %d words in %f second(s); check the file %s for result.\n", c, (double)(clock() - clk)/CLOCKS_PER_SEC, argv[2]);
	fclose(out);
	
	return 0;
}
