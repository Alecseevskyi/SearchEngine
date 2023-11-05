# About Local File Search Engine

Local File Search Engine is a tool that allows users to quickly and efficiently find files on their local systems. It can be especially useful in the following situations:

Working with a large amount of data: Imagine that you work in a large company where a huge number of files are created every day. Instead of manually going through each folder and each file, you can use the Local File Search Engine to quickly find the document you need.

Cloud Storage Search: If you use cloud services such as Dropbox, Google Drive or Microsoft OneDrive to store files, Local File Search Engine can help you quickly find the files you need, no matter where they are found.

Legal Field: Law firms and legal departments can use search engines to manage and search for cases, contracts and other legal documents.
## Documentation

### Engine architecture

The architecture is based on the JSON Convertator, using the JSON for [Modern C++ library](https://github.com/nlohmann/json?ysclid=lohqpsiym1209861604), authored by nlohmann.

The project also supports various model tests, which are allocated to a separate source, using its own cmake file. Unit tests are based on the [Google Test library](https://github.com/google/googletest?ysclid=lohr7skmnr774464427).

### Libraries project

#### Json Converter:
Json Converter allows you to upload responses to a specially prepared file for this purpose. To do this, it is enough for the method to transmit only the prepared information.

Json Converter allows you to receive user requests from a specific file, as well as read and transmit information from files specified in the configuration file.

Example:
```cpp
ConverterJSON converterJson;
InvertedIndex idx;

vector<vector<RelativeIndex>> result = srv.search(converterJson.GetRequests());

// Convert the answers into the desired form
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

// We send it to answer.json
converterJson.putAnswers(transformed_indices);
```

You must have a "json" directory in the root folder of the project, which is created when building the project. Files in this directory may not be located, when trying to convert files, the program will independently make the first files for itself that you can configure. There are no exceptions about the absence of a directory, there are no json files, so be careful.

#### Inverted Index

This library is used for indexing files in multithreaded mode. Indexing of files is necessary so that in the future we can give the user, first of all, more similar, possible answers to his requests.

Example:
```cpp
ConverterJSON converterJson;
InvertedIndex idx;

// We load resources and update the database using config.json
idx.UpdateDocumentBase(converterJson.GetTextDocument());
```

#### Search Server
The main library that will perform a relevant search, then returning answers that we can use in the future, or write to a json file. The calculated initial indexes are obtained from the Inverted Index library, which were described in the sections above.

Example:
```cpp
SearchServer srv(idx);

// Sending requests from requests.json
int max_response = converterJson.GetResponseLimit();

// If the request limit is exceeded, the response is "100"
if (converterJson.GetRequests().size() > max_response) 
    return 100;

vector<vector<RelativeIndex>> result = srv.search(converterJson.GetRequests());
```
## 🚀 About Me
I am a software developer undergoing training on the SkillBox platform. This project was for me the first and full-fledged project that I made on my own. For me, this project was a small step into the world of developers, perhaps in the future I will be able to achieve much more, but this project will remain in my memory for many years. During the execution of this project, I was able to feel the very charm of programming, which I aspired to during the entire training on SkillBox. Perhaps in the future, this project will continue its development...


## Badges

#### Licenses

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

#### Engine architecture

| ![Static Badge](https://img.shields.io/badge/Google_Test-purple?link=https%3A%2F%2Fgithub.com%2Fgoogle%2Fgoogletest%3Fysclid%3Dlohr7skmnr774464427) | ![Static Badge](https://img.shields.io/badge/JSON_for_Modern_C%2B%2B-orange?link=https%3A%2F%2Fgithub.com%2Fnlohmann%2Fjson%3Fysclid%3Dlohqpsiym1209861604) |
|----------|----------|