#!/bin/bash
gcc audiogen.c tinyAudioLib.c oscillator_trunc_table_lookup.c oscillator_basic.c -o audiogen.o -lportaudio && ./audiogen.o 