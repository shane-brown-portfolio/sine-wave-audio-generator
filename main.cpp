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
#include <sndfile.h>
using namespace std;

const int SAMPLE_RATE = 48000;
const double FREQUENCY = 440.0;
const double DURATION = 1.0;

vector<double> generateSine(double amplitude);
void writeWav(const string& filename, const vector<double>& samples);

int main() {
    vector<double> samples = generateSine(0.25);
    cout << "Generated " << samples.size() << " samples\n";

    cout << "Writing to sine.wav...\n";
    writeWav("sine.wav", samples);
    cout << "sine.wav written successfully\n";

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

void writeWav(const string& filename, const vector<double>& samples) {
    SF_INFO sfinfo;
    sfinfo.samplerate = SAMPLE_RATE;
    sfinfo.channels = 1;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE * file = sf_open(filename.c_str(), SFM_WRITE, &sfinfo);

    if (file == NULL) {
        cerr << "Error opening the file\n";
        return;
    }

    vector<float> temp(samples.size());
    for (size_t i = 0; i < samples.size(); i++) {
        temp[i] = static_cast<float>(samples[i]);
    }

    sf_write_float(file, temp.data(), temp.size());
    sf_close(file);
}