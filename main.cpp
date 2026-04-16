// Sine Wave Audio Generator
// main.cpp

#include <filesystem>
#include "wav_utils.h"

namespace fs = std::filesystem;

const string WAV_DIR = "wavs";

int main() {
    fs::create_directories(WAV_DIR);

    cout << "Generating sine wave samples...\n";

    // Amplitude is ¼ of the maximum possible 16-bit amplitude (values in the range -8192..8192)
    vector<double> samples = generateSine(0.25);
    cout << "Generated " << samples.size() << " samples\n";

    cout << "\nWriting to " << WAV_DIR << "/sine.wav...\n";
    writeWav(WAV_DIR + "/sine.wav", samples);
    cout << "sine.wav written successfully\n";

    cout << "\nGenerating loud sine wave samples...\n";

    // Amplitude is ½ of the maximum possible 16-bit amplitude (values in the range -16384..16384)
    vector<double> loud = generateSine(0.5);
    cout << "Generated " << loud.size() << " loud samples\n";

    cout << "\nClipping the loud samples...\n";
    vector<double> clipped = clip(loud);

    cout << "Writing to " << WAV_DIR << "/clipped.wav...\n";
    writeWav(WAV_DIR + "/clipped.wav", clipped);
    cout << "clipped.wav written successfully\n";

    cout << "\nPlaying the clipped audio...\n";
    playAudio(clipped);

    return 0;
}