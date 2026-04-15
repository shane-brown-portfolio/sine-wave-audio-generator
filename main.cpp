/* Sine Wave Audio Generator */

/*
    Sine Wave Parameters:
        Channels per frame: 1 (mono)
        Sample format: 16 bit signed (values in the range -32767..32767)
        Amplitude: ¼ maximum possible 16-bit amplitude (values in the range -8192..8192)
        Duration: one second
        Frequency: 440Hz (440 cycles per second)
        Sample Rate: 48000 samples per second
    
    Clipped Sine Wave Parameters:
        Amplitude: ½ maximum possible 16-bit amplitude (values in the range -16384..16384)
        Clipping threshold: ¼ maximum possible 16-bit amplitude (values in the range -8192..8192)
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <sndfile.h>
#include <portaudio.h>
using namespace std;

const int SAMPLE_RATE = 48000;
const double FREQUENCY = 440.0;
const double DURATION = 1.0;

vector<double> generateSine(double amplitude);
void writeWav(const string& filename, const vector<double>& samples);
vector<double> clip(const vector<double>& input);
void playAudio(const vector<double>& samples);

int main() {
    cout << "Generating sine wave samples...\n";
     // Amplitude is ¼ of the maximum possible 16-bit amplitude (values in the range -8192..8192)
    vector<double> samples = generateSine(0.25);
    cout << "Generated " << samples.size() << " samples\n";

    cout << "\nWriting to sine.wav...\n";
    writeWav("sine.wav", samples);
    cout << "sine.wav written successfully\n";

    cout << "\nGenerating loud sine wave samples...\n";
    // Amplitude is ½ of the maximum possible 16-bit amplitude (values in the range -16384..16384)
    vector<double> loud = generateSine(0.5);
    cout << "Generated " << loud.size() << " loud samples\n";
    
    cout << "\nClipping the loud samples...\n";
    vector<double> clipped = clip(loud);
    
    cout << "Writing to clipped.wav...\n";
    writeWav("clipped.wav", clipped);
    cout << "clipped.wav written successfully\n";
    
    cout << "\nPlaying the clipped audio...\n";
    playAudio(clipped);

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

vector<double> clip(const vector<double>& input) {
    vector<double> output = input;

    for (size_t i = 0; i < output.size(); i++) {
        if (output[i] > 0.25) {
            output[i] = 0.25;
        }
        else if (output[i] < -0.25) {
            output[i] = -0.25;
        }
    }

    return output;
}

void playAudio(const vector<double>& samples) {
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError) {
        cerr << "PortAudio initialization error\n";
        return;
    }

    PaStream * stream;

    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);

    if (err != paNoError) {
        cerr << "Error opening the stream\n";
        return;
    }

    Pa_StartStream(stream);

    vector<float> temp(samples.size());
    for (size_t i = 0; i < samples.size(); i++) {
        temp[i] = static_cast<float>(samples[i]);
    }

    Pa_WriteStream(stream, temp.data(), temp.size());

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}