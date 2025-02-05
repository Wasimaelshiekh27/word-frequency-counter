#include "word_counter.h"
#include <fstream>
#include <sstream>
#include <thread>

std::mutex mtx;

WordCounter::WordCounter(const std::string& filename, size_t numThreads)
    : filename(filename), numThreads(numThreads) {}

void WordCounter::readFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
}

void WordCounter::processSegment(size_t start, size_t end) {
    std::unordered_map<std::string, size_t> localCount;
    for (size_t i = start; i < end; ++i) {
        ++localCount[words[i]];
    }

    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& pair : localCount) {
        wordFrequencies[pair.first] += pair.second;
    }
}

void WordCounter::countWords() {
    readFile();
    std::vector<std::thread> threads;
    size_t segmentSize = words.size() / numThreads;

    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * segmentSize;
        size_t end = (i == numThreads - 1) ? words.size() : (i + 1) * segmentSize;
        threads.emplace_back(&WordCounter::processSegment, this, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

const std::unordered_map<std::string, size_t>& WordCounter::getWordFrequencies() const {
    return wordFrequencies;
}