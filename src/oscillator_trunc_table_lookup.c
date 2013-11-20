#include <stdio.h>
#include <math.h>

#define SAMPLING_RATE 44100
#define TABLE_LEN 512
#define PI 3.14159265

/*----- output sample function -----*/
void (*outSample)(float);

void out_sample_func(void (*func)(float)) {
	outSample = func;
}
/*----- end output sample function -----*/

float table[TABLE_LEN];

void use_sine() {
	// fill with sine
	for (int i = 0; i < TABLE_LEN; i++) {
		table[i] = (float) sin(2 * PI * i/TABLE_LEN);
	}
}

void use_square() {
	// fill with square
	for (int i = 0; i < TABLE_LEN; i++) {
		if (i % 2 == 0)
			table[i] = 1;
		else
			table[i] = -1;
	}
}

void playchord(double duration, int freqs, double freq[]) {
	printf("playchord: dur=%f freqs=%d", duration, freqs);

	// calculate sample increments and initial phases for each freq
	double sample_increments[freqs];
	double phases[freqs];
	for (int i = 0; i < freqs; i++) {
		printf("freq=%f", freq[i]);
		sample_increments[i] = freq[i] * TABLE_LEN / SAMPLING_RATE;
		phases[i] = sample_increments[i];
		printf("fq=%f smpl_inc=%f\n", freq[i], sample_increments[i]);
	}

	printf("max=%f\n", duration * SAMPLING_RATE);

	// play samples for the specified duration
	for (int i = 0; i < duration * SAMPLING_RATE; i++) {
		float sample = 0;
		// sum the samples for each freq at each freq's phase
		for (int j = 0; j < freqs; j++) {
			sample += table[(long) phases[j]];
		}
		// update the phases for the next pass
		for (int j = 0; j < freqs; j++) {
			phases[j] += sample_increments[j];
			if (phases[j] > TABLE_LEN)
				phases[j] -= TABLE_LEN;		
		}
		// output the sample
		outSample(sample/freqs);
	}
}

void play(double duration, double frequency) {
	playchord(duration, 1, (double []){frequency});
}