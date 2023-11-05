#include "SearchServer.h"
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

bool compare(const RelativeIndex& a, const RelativeIndex& b) {
    return a.rank > b.rank;
}

vector<vector<RelativeIndex>> SearchServer::search(const vector<string> &queries_input) {

    // Разобьем полученные предложения на отдельные слова
    vector<vector<string>> words_input;
    for (int i = 0; i < queries_input.size(); i++) {
        istringstream iss(queries_input.at(i));
        vector<string> words;
        string word;

        while (getline(iss, word, ' ')) words.push_back(word);

        // Необходимо избавиться от дубликатов
        set<string> set_words = set<string>(words.begin(), words.end());
        vector<string> unique_words = vector<string>(set_words.begin(), set_words.end());

        // Заполняем вектор полученными словами из предложения
        words_input.push_back(unique_words);
    }

    // Получим относительные величины, для каждого запроса
    vector<vector<RelativeIndex>> answer;
    // Цикл для всех запросов
    for (int i = 0; i < words_input.size(); i++) {

        vector<map<int, float>> table;
        vector<string> words = words_input.at(i);
        set<size_t> list_doc_id;
        // Цикл определенного запроса
        for (int j = 0; j < words.size(); j++) {
            vector<Entry> entries = _index.GetWordCount(words.at(j));
            map<int, float> entry;
            // Цикл определенного слова
            for (int k = 0; k < entries.size(); k++) {
                entry[entries.at(k).doc_id] = entry[entries.at(k).doc_id] + entries.at(k).count;
                list_doc_id.insert(entries.at(k).doc_id);
            }
            table.push_back(entry);
        }

        // Цикл для определения абсолютных величин
        map<int, float> absoluteIndex;
        map<int, float> maximumAbsoluteIndexes;

        for (auto &doc_id: list_doc_id) {
            maximumAbsoluteIndexes[doc_id] = 0;
            for (auto &column_table: table) {
                absoluteIndex[doc_id] = absoluteIndex[doc_id] + column_table[doc_id];
                if (absoluteIndex[doc_id] > maximumAbsoluteIndexes[doc_id])
                    maximumAbsoluteIndexes[doc_id] = absoluteIndex[doc_id];
            }
        }

        float maximumAbsoluteIndex = 0;
        for (const auto &[key, value]: maximumAbsoluteIndexes) {
            if (value > maximumAbsoluteIndex) maximumAbsoluteIndex = value;
        }

        vector<RelativeIndex> relativeIndexes;
        for (auto &index: absoluteIndex) {
            RelativeIndex relativeIndex;
            relativeIndex.doc_id = index.first;
            relativeIndex.rank = index.second / maximumAbsoluteIndex;
            relativeIndexes.push_back(relativeIndex);
        }

        sort(relativeIndexes.begin(), relativeIndexes.end(), compare);
        answer.push_back(relativeIndexes);
    }
    return answer;
}
