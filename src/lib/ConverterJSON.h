#ifndef LOCAL_FILE_SEARCH_ENGINE_CONVERTERJSON_H
#define LOCAL_FILE_SEARCH_ENGINE_CONVERTERJSON_H

#include <vector>
#include <string>

namespace std {

    /**
        * Класс для работы с JSON-файлами
    */

    class ConverterJSON {
    public:
        ConverterJSON() = default;

        /**
            * Метод получения содержимого файлов
            * @return Возвращает список с содержимым файлов перечисленных
            * в config.json
        */
        vector<string> GetTextDocument();

        /**
            * Метод считывает поле max_responses для определения предельного
            * количества ответов на один запрос
            * @return
        */
        int GetResponseLimit();

        /**
            * Метод получения запросов из файла requests.json
            * @return возвращает список запросов из файла requests.json
        */
        vector<string> GetRequests();

        /**
            * Положить в файл answers.json результаты поисковых запросов
        */
        void putAnswers(vector<vector<pair<int, float>>> answers);
    };

} // std

#endif
