#include "ConverterJSON.h"
#include "string"
#include "json.hpp"
#include "fstream"
#include "iostream"
using json = nlohmann::json;

namespace std {

    bool checkJson(json& json, fstream& file, const string& path_json) {
        file.open(path_json);

        if (!file.is_open()) {
            file.close();
            return true;
        } else {
            // Если файл существует, то пытаемся получить с него данные
            try {
                json << file;
            }
            catch(...){
                // Если проблемы с файлом, вызываем блок error и очищаем файл
                file.close();
                fstream::trunc;
                file.close();

                return true;
            }
        }
        return false;
    }

    vector<string> ConverterJSON::GetTextDocument() {
        json config;
        string filename = "../json/config";
        fstream file;
        bool error = checkJson(config, file, filename);


        // Если проблемы с файлом, пересобираем его
        if (error) {
            try {
                cout << "Total error configuration files (config.json)! Invalid path to config files, reset config files..." << endl;
                file.open(filename, std::ios::out);
                config["config"]["name"] = "Local File Search Engine";
                config["config"]["version"] = "1.0";
                config["config"]["max_response"] = 0;

                vector<string> empty;
                config["files"] = empty;

                file << config;
                file.close();
                cout << "Done." << endl;
            }
            catch (...) {
                cout << "Failed to reset settings." << endl;
            }
        }


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
                answer.insert(answer.end(), answerLineFile);
            }
            file.close();
        }

        return answer;
    }

    int ConverterJSON::GetResponseLimit() {
        json config;
        string filename = "../json/config";
        fstream file;
        bool error = checkJson(config, file, filename);

        // Если проблемы с файлом, пересобираем его
        if (error) {
            cout << "Total error configuration files (config.json)! Invalid path to config files, reset config files..." << endl;
            try {
                file.open(filename, std::ios::out);
                config["config"]["name"] = "Local File Search Engine";
                config["config"]["version"] = "1.0";
                config["config"]["max_response"] = 0;

                vector<string> empty;
                config["files"] = empty;

                file << config;
                file.close();
                cout << "Done." << endl;
            }
            catch (...) {
                cout << "Failed to reset settings." << endl;
            }
        }

        return config["config"]["max_response"];
    }

    vector<string> ConverterJSON::GetRequests() {
        json requests;
        string filename = "../json/requests.json";
        fstream file;
        bool error = checkJson(requests, file, filename);


        // Если проблемы с файлом, пересобираем его
        if (error) {
            try {
                cout << "Total error configuration files (requests.json)! Invalid path to config files, reset config files..." << endl;
                vector<string> empty;
                file.open(filename, std::ios::out);
                requests["requests"] = empty;
                file << requests;
                file.close();
                cout << "Done." << endl;
                return empty;
            }
            catch (...) {
                cout << "Failed to reset settings." << endl;
            }
        }

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
                        answersJSON["answers"][numberRequest][docid]["document"] = answers.at(i).at(j).first;
                        answersJSON["answers"][numberRequest][docid]["rank"] = answers.at(i).at(j).second;
                    }
                    else {
                        answersJSON["answers"][numberRequest]["relevance"][docid]["document"] = answers.at(i).at(j).first;
                        answersJSON["answers"][numberRequest]["relevance"][docid]["rank"] = answers.at(i).at(j).second;
                    }
                }
            }

            file << answersJSON;
            file.close();
        }
    }

} // std