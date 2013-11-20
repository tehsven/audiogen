#include <portaudio.h>


PaStream *stream;
int main() {
	PaError  err;
    err = Pa_CloseStream( stream );
}