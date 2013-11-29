#include <stdio.h>
#include <math.h>

#define SAMPLING_RATE 44100
#define TABLE_LEN 512
#define PI 3.14159265

/*----- output sample function -----*/
void (*oscbasic_outSample)(float);

void oscbasic_out_sample_func(void (*func)(float)) {
	oscbasic_outSample = func;
}
/*----- end output sample function -----*/

double (*oscbasic_wave_func)(double);

double constant_wave_func(double phase) {
	return 0.25;
}

double saw_wave_func(double phase) {
	return 1 - (phase / PI);
}

double square_wave_func(double phase) {
	return phase = PI ? 1 : -1;
}

void oscbasic_use_sine() {
	oscbasic_wave_func = &sin;
}

void oscbasic_use_square() {
	oscbasic_wave_func = &square_wave_func;
}

void oscbasic_use_saw() {
	oscbasic_wave_func = &saw_wave_func;
}

void oscbasic_use_const() {
	oscbasic_wave_func = &constant_wave_func;
}

void oscbasic_playchord(double duration, int freqs, double freq[]) {
	printf("playchord: dur=%f freqs=%d", duration, freqs);

	// calculate sample increments and initial phases for each freq
	double sample_increments[freqs];
	double phases[freqs];
	for (int i = 0; i < freqs; i++) {
		printf("freq=%f", freq[i]);
		sample_increments[i] = freq[i] * 2*PI / SAMPLING_RATE;
		phases[i] = sample_increments[i];
		printf("fq=%f smpl_inc=%f\n", freq[i], sample_increments[i]);
	}

	printf("max=%f\n", duration * SAMPLING_RATE);

	// play samples for the specified duration
	for (int i = 0; i < duration * SAMPLING_RATE; i++) {
		float sample = 0;
		// sum the samples for each freq at each freq's phase
		for (int j = 0; j < freqs; j++) {
			sample += oscbasic_wave_func(phases[j]);
		}
		// update the phases for the next pass
		for (int j = 0; j < freqs; j++) {
			phases[j] += sample_increments[j];
			if (phases[j] > 2*PI)
				phases[j] -= 2*PI;
		}
		// output the sample
		oscbasic_outSample(sample/freqs);
	}
}

void oscbasic_play(double duration, double frequency) {
	oscbasic_playchord(duration, 1, (double []){frequency});
}