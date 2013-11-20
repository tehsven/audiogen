#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tinyAudioLib.h"
#include "oscillator_trunc_table_lookup.h"

void setup() {
	tinyInit();
	out_sample_func(&outSampleMono);
	use_sine();
}

void teardown() {
	tinyExit();
}

double key_to_freq(double key) {
	return pow(2, (key / 12)) * 440;
}

int main() {
	setup();

	int key1, key2;
	float duration;

	while (1) {
		// int token
		puts("duration note1 note2 ... note10");

		// setup
		double note[10];
		float duration;

		// grab user input		 
		puts("reading input line");
		char _instr[20];
		fgets(_instr, 20, stdin); 
		
		// copy into local memory
		char instr[20];
		strcpy(instr, _instr);
		puts(instr);

		// tokenize input
		const char delim[2] = " ";

		puts("about to tokenize");
		char *token = strtok(instr, delim);
		puts("token grabbed");

		int token_count = 0;
		do {
			if (token == NULL)
				continue;
			if (token_count == 0)
				duration = atof(token);
			else
				note[token_count] = key_to_freq(atoi(token));

			puts("grabbing next token");
			token = strtok(NULL, delim);
			puts(token);
			token_count++;

		}
		while (token != NULL);

		// play the music
		playchord(duration, token_count, note);
	}

	teardown();
	printf("Bye!\n");
}