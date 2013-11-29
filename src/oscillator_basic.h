/*----- output sample function -----*/
void oscbasic_out_sample_func(void (*func)(float));
/*----- end output sample function -----*/

void oscbasic_use_sine();

void oscbasic_use_square();

void oscbasic_use_saw();

void oscbasic_use_const();

void oscbasic_playchord(double duration, int freqs, double freq[]);

void oscbasic_play(double duration, double frequency);