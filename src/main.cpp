#include <string>
#include <vector>
#include "lib/SearchServer.h"
#include "lib/ConverterJSON.h"

using namespace std;
int main() {
    ConverterJSON converterJson;

    InvertedIndex idx;

    // Загружаем ресурсы и обновляем базу, с помощью config.json
    idx.UpdateDocumentBase(converterJson.GetTextDocument());
    SearchServer srv(idx);

    // Отправляем запросы из requests.json
    int max_response = converterJson.GetResponseLimit();

    // Если превышен лимит запросов - ответ "100"
    if (converterJson.GetRequests().size() > max_response) return 100;

    vector<vector<RelativeIndex>> result = srv.search(converterJson.GetRequests());

    // Преобразуем ответы в нужную форму
    vector<vector<pair<int, float>>> transformed_indices;
    transformed_indices.reserve(result.size());

    for (const auto& inner_vector : result) {
        std::vector<std::pair<int, float>> temp_vector;
        temp_vector.reserve(inner_vector.size());

        for (const auto& index : inner_vector) {
            temp_vector.emplace_back(index.doc_id, index.rank);
        }

        transformed_indices.push_back(std::move(temp_vector));
    }

    // Отправляем в answer.json
    converterJson.putAnswers(transformed_indices);

    return 0;
}