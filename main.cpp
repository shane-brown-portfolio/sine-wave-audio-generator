/* Sine Wave Audio Generator */

/*
    Sine wave parameters:
        Channels per frame: 1 (mono)
        Sample format: 16 bit signed (values in the range -32767..32767)
        Amplitude: ¼ maximum possible 16-bit amplitude (values in the range -8192..8192)
        Duration: one second
        Frequency: 440Hz (440 cycles per second)
        Sample Rate: 48000 samples per second
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int SAMPLE_RATE = 48000;
const double FREQUENCY = 440.0;
const double DURATION = 1.0;

vector<double> generateSine(double amplitude);

int main() {
    vector<double> samples = generateSine(0.25);
    cout << "Generated " << samples.size() << " samples\n";

    return 0;
}

vector<double> generateSine(double amplitude) {
    int totalSamples = SAMPLE_RATE * DURATION;
    vector<double> samples(totalSamples);

    for (int i = 0; i < totalSamples; i++) {
        double t = static_cast<double>(i) / SAMPLE_RATE;
        samples[i] = amplitude * sin(2 * M_PI * FREQUENCY * t);
    }

    return samples;
}