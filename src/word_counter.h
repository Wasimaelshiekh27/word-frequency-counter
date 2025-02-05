#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

extern std::mutex mtx;

class WordCounter {
public:
    WordCounter(const std::string& filename, size_t numThreads);
    void countWords();
    const std::unordered_map<std::string, size_t>& getWordFrequencies() const;

private:
    void processSegment(size_t start, size_t end);
    void readFile();
    
    std::string filename;
    size_t numThreads;
    std::vector<std::string> words;
    std::unordered_map<std::string, size_t> wordFrequencies;
};

#endif // WORD_COUNTER_H