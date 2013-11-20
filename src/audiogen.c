#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tinyAudioLib.h"
#include "oscillator_trunc_table_lookup.h"
#include "oscillator_basic.h"

void setup() {
	tinyInit();
	
	// oscillator_trunc_table_lookup
	out_sample_func(&outSampleMono);
	use_sine();

	// oscillator_basic
	oscbasic_out_sample_func(&outSampleMono);
	oscbasic_use_sine();
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
		char *osc;

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

		int i = 0;
		int note_count = 0;
		do {
			if (token == NULL)
				continue;
			if (i == 0)
				osc = token;
			else if (i == 1)
				duration = atof(token);
			else {
				note[note_count] = key_to_freq(atoi(token));
				note_count++;
			}

			puts("grabbing next token");
			token = strtok(NULL, delim);
			puts(token);
			i++;
		}
		while (token != NULL);

		// play the music
		if (strcmp(osc, "ttl") == 0) {
			playchord(duration, note_count, note);
		}
		else if (strcmp(osc, "basic") == 0) {	
			oscbasic_playchord(duration, note_count, note);
		}
	}

	teardown();
	printf("Bye!\n");
}