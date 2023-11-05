#ifndef LOCAL_FILE_SEARCH_ENGINE_INVERTEDINDEX_H
#define LOCAL_FILE_SEARCH_ENGINE_INVERTEDINDEX_H
#include <string>
#include <vector>
#include <map>

namespace std {

    struct Entry {
        size_t doc_id, count;

// Данный оператор необходим для проведения тестовых сценариев
        bool operator==(const Entry &other) const {
            return (doc_id == other.doc_id &&
                    count == other.count);
        }
    };

    class InvertedIndex {
    public:
        InvertedIndex() = default;

/**
* Обновить или заполнить базу документов, по которой будем совершать
поиск
* @param texts_input содержимое документов
*/
        void UpdateDocumentBase(vector<string> input_docs);

/**
* Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
        vector<Entry> GetWordCount(const string &word);
    private:
        vector<string> docs; // список содержимого документов
        map<string, vector<Entry>> freq_dictionary; // частотный словарь
    };

} // std

#endif //LOCAL_FILE_SEARCH_ENGINE_INVERTEDINDEX_H
