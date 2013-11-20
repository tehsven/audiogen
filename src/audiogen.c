#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tinyAudioLib.h"

// system
#define SAMPLING_RATE 44100
#define PI 3.14159265
#define TABLE_LEN 512

float table[TABLE_LEN];

void outSample(float sample)
{
	outSampleMono(sample);
}

void setup()
{
	tinyInit();

		// fill with sine
	for (int i = 0; i < TABLE_LEN; i++)
	{
		table[i] = (float) sin(2 * PI * i/TABLE_LEN);
	}

	// fill with square
	// for (int i = 0; i < TABLE_LEN; i++)
	// {
	// 	if (i % 2 == 0)
	// 		square_table[i] = 1;
	// 	else
	// 		square_table[i] = -1;
	// }
}

void teardown()
{
	tinyExit();
}

double key_to_freq(double key)
{
	return pow(2, (key / 12)) * 440;
}

void playchord(double duration, int freqs, double freq[])
{
/*----- synthesis engine -----*/
	printf("playchord: dur=%f freqs=%d", duration, freqs);
	double sample_increments[freqs];
	double phases[freqs];
	for (int i = 0; i < freqs; i++)
	{
		printf("freq=%f", freq[i]);
		sample_increments[i] = freq[i] * TABLE_LEN / SAMPLING_RATE;
		phases[i] = sample_increments[i];
		printf("fq=%f smpl_inc=%f\n", freq[i], sample_increments[i]);
	}

	printf("max=%f\n", duration * SAMPLING_RATE);
	for (int i = 0; i < duration * SAMPLING_RATE; i++)
	{
		float sample = 0;
		for (int j = 0; j < freqs; j++)
		{
			sample += table[(long) phases[j]];
		}
		// printf("phase=%f sample=%f\n", phase, sample);
		outSample(sample/freqs);
		for (int j = 0; j < freqs; j++)
		{
			phases[j] += sample_increments[j];
			if (phases[j] > TABLE_LEN)
				phases[j] -= TABLE_LEN;		
		}
		
	}
	/*----- synthesis engine end -----*/	
}

void play(double duration, double frequency)
{
	/*----- synthesis engine -----*/
	double sample_increment = frequency * TABLE_LEN / SAMPLING_RATE;
	printf("fq=%f smpl_inc=%f\n", frequency, sample_increment);
	double phase = sample_increment;
	float sample;

	printf("max=%f\n", duration * SAMPLING_RATE);
	for (int i = 0; i < duration * SAMPLING_RATE; i++)
	{		
		sample = table[(long) phase];
		printf("phase=%f sample=%f\n", phase, sample);
		outSample(sample);
		phase += sample_increment;
		if (phase > TABLE_LEN)
			phase -= TABLE_LEN;
	}
	/*----- synthesis engine end -----*/
}

void debug(char str[])
{
	printf("%s\n", str);
}

int main()
{
	setup();

	int key1, key2;
	float duration;

	while (1)
	{
		// int token
		puts("duration note1 note2 ... note10");

		// setup
		double note[10];
		float duration;
		 
		debug("reading input line");
		char _instr[20];
		fgets(_instr, 20, stdin);
		// copy into local memory
		char instr[20];
		strcpy(instr, _instr);
		puts(instr);

		// tokenize input
		const char delim[2] = " ";

		debug("about to tokenize");
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

		// scanf("%f ", &key1, &key2);
		// printf("key2:%d", key2);
		// if (key1 == 100) break;

		// printf("Enter a duration:");
		// scanf("%f", &duration);

		// play(duration, key_to_freq(key1));	

	}
	
	// user inputs
	// int half_steps = 12;



	// double freqs[3] = {key_to_freq(0), key_to_freq(4), key_to_freq(7)};
	// playchord(duration, 3, freqs);


		// play(duration, key_to_freq(0));	

	// for (int i = 0; i <= half_steps; i++)
	// {
	// 	play(duration, key_to_freq(i));	
	// }

	// for (int i = half_steps-1; i >= 0; i--)
	// {
	// 	play(duration, key_to_freq(i));	
	// }
	
	// play(duration, key_to_freq(1));
	// play(duration, frequency*2);
	// play(duration, frequency*8);
	// play(duration, frequency*16);

	teardown();
	printf("Bye!\n");
}