#include <iostream>
#include "word_counter.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <num_threads>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    size_t numThreads = std::stoi(argv[2]);

    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Number of threads: " << numThreads << std::endl;

    try {
        WordCounter wordCounter(filename, numThreads);
        wordCounter.countWords();

        const auto& wordFrequencies = wordCounter.getWordFrequencies();
        for (const auto& pair : wordFrequencies) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}