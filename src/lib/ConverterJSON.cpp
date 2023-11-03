#include "ConverterJSON.h"
#include "string"
#include "include/nlohmann/json.hpp"
#include "fstream"
#include "iostream"
using json = nlohmann::json;

namespace std {

    vector<string> ConverterJSON::GetTextDocument() {
        json config;

        // Парсим данные
        ifstream file("../json/config.json"); // Путь идет от Build
        file >> config;
        file.close();

        // Получаем пути всех файлов из ресурсов
        vector<string> files = config["files"];

        // Читаем и записываем информацию из файлов в отдельный vector
        vector<string> answer;

        for (int i = 0; i < files.size(); i++) {
            file.open(files.at(i));
            string answerLineFile;
            if (file.is_open()) {
                getline(file, answerLineFile);

                // Удаляем все лишние пробелы
                istringstream ss(answerLineFile);
                string word;
                string output;

                while (ss >> word) {
                    output += word + " ";
                }

                // Удаляем последний пробел
                if (!output.empty()) {
                    output.pop_back();
                }
                answerLineFile = output;
            }
            answer.insert(answer.end(), answerLineFile);
            file.close();
        }

        return answer;
    }

    int ConverterJSON::GetResponseLimit() {
        json config;

        // Парсим данные
        ifstream file("../json/config.json"); // Путь идет от Build
        file >> config;
        file.close();

        return config["config"]["max_response"];
    }

    vector<string> ConverterJSON::GetRequests() {
        json requests;

        // Парсим данные
        ifstream file("../json/requests.json"); // Путь идет от Build
        file >> requests;
        file.close();

        return requests["requests"];
    }

    void ConverterJSON::putAnswers(vector<vector<pair<int, float>>> answers) {
        // Создание файла
        string filename = "../json/answer.json";
        std::fstream file;

        // Открываем файл в режиме чтения и записи
        file.open(filename, std::ios::in | std::ios::out);

        // Если файл не открылся (то есть не существует), создаем его
        if (!file.is_open()) {
            file.open(filename, std::ios::out);
        } else {
            // Если файл существует, очищаем его
            file.close();
            file.open(filename, std::ios::out | std::ios::trunc);

        }

        // Создаем json
        json answersJSON;
        answersJSON["answers"] = {};

        // Загрузка данных в json
        {

            for (int i = 0; i < answers.size(); i++) {
                // Делаем нумерацию
                string numberRequest = "request";
                ostringstream oss;
                oss << setw(3) << setfill('0') << i;
                numberRequest = numberRequest + oss.str();

                // Создаем объект в json
                answersJSON["answers"][numberRequest] = {};
                if (answers.at(i).empty()) answersJSON["answers"][numberRequest]["result"] = false;
                else answersJSON["answers"][numberRequest]["result"] = true;

                for (int j = 0; j < answers.at(i).size(); j++) {
                    string docid = "docid" + to_string(j);
                    if(answers.at(i).size() == 1) {
                        answersJSON["answers"][numberRequest][docid] = answers.at(i).at(j).first;
                        answersJSON["answers"][numberRequest][docid] = answers.at(i).at(j).second;
                    }
                    else {
                        answersJSON["answers"][numberRequest]["relevance"][docid] = answers.at(i).at(j).first;
                        answersJSON["answers"][numberRequest]["relevance"][docid] = answers.at(i).at(j).second;
                    }
                }
            }

            file << answersJSON;
            file.close();
        }
    }

} // std