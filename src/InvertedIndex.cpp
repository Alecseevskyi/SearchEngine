#include "InvertedIndex.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <sstream>

    std::mutex mtx;

    void SearchWord(const std::vector<std::string>& sentences, const std::string& word_to_find, int start, int end, std::vector<std::Entry>& results) {
        for (int i = start; i < end; ++i) {
            std::istringstream iss(sentences[i]);
            std::string word;
            int count = 0;
            while (iss >> word) {
                if (word == word_to_find) {
                    ++count;
                }
            }
            if (count > 0) {
                mtx.lock();
                results.push_back({(size_t) i, (size_t) count});
                mtx.unlock();
            }
        }
    }
namespace std {
    void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
        InvertedIndex::docs.clear();
        for (int i = 0; i < input_docs.size(); i++) InvertedIndex::docs.insert(docs.end(), input_docs.at(i));
    }

    vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
        // Получаем слова со всех файлов
        vector<string> files = docs;

        // Создаем многопоточный режим
        int num_threads = std::thread::hardware_concurrency();
        int sentences_per_thread = files.size() / num_threads;

        vector<thread> threads;
        vector<Entry> results;
        for (int i = 0; i < num_threads; ++i) {
            int start = i * sentences_per_thread;
            int end = (i == num_threads - 1) ? files.size() : start + sentences_per_thread;
            threads.push_back(thread(SearchWord, ref(files), ref(word), start, end, ref(results)));
        }

        for (auto& t : threads) {
            t.join();
        }

        freq_dictionary[word] = results;

        return results;
    }
} // std