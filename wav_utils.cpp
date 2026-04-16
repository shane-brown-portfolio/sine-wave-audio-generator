// wav_utils.cpp

/*
    Default Sine Wave Parameters:
        Channels per frame: 1 (mono)
        Sample format: 16 bit signed (values in the range -32767..32767)
        Amplitude: ¼ maximum possible 16-bit amplitude (values in the range -8192..8192)
        Duration: one second
        Frequency: 440Hz (440 cycles per second)
        Sample Rate: 48000 samples per second

    Default Clipped Sine Wave Parameters:
        Amplitude: ½ maximum possible 16-bit amplitude (values in the range -16384..16384)
        Clipping threshold: ¼ maximum possible 16-bit amplitude (values in the range -8192..8192)
*/

#include "wav_utils.h"

vector<double> generateSine(double amplitude) {
    // Determine total number of samples for the given duration
    int totalSamples = SAMPLE_RATE * DURATION;
    vector<double> samples(totalSamples);

    for (int i = 0; i < totalSamples; i++) {
        // Calculate time in seconds at sample i
        double t = static_cast<double>(i) / SAMPLE_RATE;
        
        // Calculate sine wave value using formula: amplitude * sin(2 * pi * frequency * t)
        samples[i] = amplitude * sin(2 * PI * FREQUENCY * t);
    }

    return samples;
}

void writeWav(const string& filename, const vector<double>& samples) {
    // Configure the WAV file format: mono, 48000 samples/sec (default), 16-bit PCM
    SF_INFO sfinfo;
    sfinfo.samplerate = SAMPLE_RATE;
    sfinfo.channels   = 1;
    sfinfo.format     = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    // Open the file for writing
    SNDFILE * file = sf_open(filename.c_str(), SFM_WRITE, &sfinfo);

    // Check if the file was opened successfully
    if (file == NULL) {
        cerr << "Error opening the file\n";
        return;
    }

    // libsndfile sf_write_float function expects float values
    vector<float> temp(samples.size());
    for (size_t i = 0; i < samples.size(); i++) {
        temp[i] = static_cast<float>(samples[i]);
    }

    sf_write_float(file, temp.data(), temp.size()); // write all samples at once
    sf_close(file); // flush and close the file
}

vector<double> clip(const vector<double>& input) {
    vector<double> output = input;

    // Hard clip: any sample outside -0.25..0.25 is clamped to the threshold
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

    // Start up the PortAudio library
    err = Pa_Initialize();
    if (err != paNoError) {
        cerr << "PortAudio initialization error\n";
        return;
    }

    PaStream * stream;

    // Open the default output stream: 0 input channels, 1 output channel,
    //     32-bit float samples, 48000 Hz, 256 frames per buffer, no callback (blocking mode)
    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    if (err != paNoError) {
        cerr << "Error opening the stream: " << Pa_GetErrorText(err) << "\n";
        Pa_Terminate();
        return;
    }

    // Begin audio output
    Pa_StartStream(stream);

    // PortAudio expects float, so convert from double before writing
    vector<float> temp(samples.size());
    for (size_t i = 0; i < samples.size(); i++) {
        temp[i] = static_cast<float>(samples[i]);
    }

    Pa_WriteStream(stream, temp.data(), temp.size());

    // Clean up the stream and shut down PortAudio
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}
