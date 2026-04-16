// wav_utils.h
// Defines the functions for WAV generation, clipping, and playback utilities

#ifndef WAV_UTILS_H
#define WAV_UTILS_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sndfile.h>
#include <portaudio.h>

using namespace std;

#define PI 3.14159265358979323846

const int    SAMPLE_RATE = 48000;
const double FREQUENCY   = 440.0;
const double DURATION    = 1.0;

// Generates a sine wave based on the amplitude provided in the range 0.0 to 1.0
// Default values: 440 Hz, 1 second, 48000 samples/sec
vector<double> generateSine(double amplitude);

// Writes a mono 16-bit PCM WAV file
void writeWav(const string& filename, const vector<double>& samples);

// Hard-clips a sine wave to the -0.25 to +0.25 range
vector<double> clip(const vector<double>& input);

// Plays a generated sine wave through the default audio device via PortAudio
void playAudio(const vector<double>& samples);

#endif // WAV_UTILS_H