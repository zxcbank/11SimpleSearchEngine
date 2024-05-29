#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "indexation/utils.hpp"

class term {
        std::string word;
    
    public:
        std::vector<float> indexes;
        
        explicit term(std::string term_, std::vector<float>& scores) : word(std::move(term_)), indexes(scores) {};
        term() = default;
        
        term operator + (const term& B) {
            term res;
            for (int i = 0; i < B.indexes.size(); i++) {
                res.indexes.push_back(indexes[i] + B.indexes[i]);
            }
            return res;
        }
        
        term operator * (const term& B) {
            term res;
            for (int i = 0; i < B.indexes.size(); i++) {
                float val = static_cast<float>((indexes[i] * B.indexes[i]) != 0) * (indexes[i] + B.indexes[i]);
                res.indexes.push_back(val);
            }
            return res;
        }
};

class Search {
    std::string search_query; //search query
    std::string project_path;
    float k = 10; // коэфф хз чего так и не понял
    float b = 0.1; // коээффициетн влияния длинны файла на релеватность
    size_t N; // number of Files
    size_t avg_len;
    size_t all_len;
    std::map<std::string, std::vector<int>> posting_list;
    std::map<std::string, term> scorings;
    std::vector<float> relative_indexes;
    public:
        
        Search(int argc, char** argv, std::string&& PROJ_DIR);
        void rangingFiles();
        void remakePostingList(std::string& path_);
        void scoringTerms(std::vector<std::string>& terms_list);
        void show(int topk);
        float scoringFile(const std::string& term, const std::string& fn);
        term CalculateRela(const std::string& q);
        void showListOfEntry(const std::string& word, const std::string& fn);
        
};

bool IsIndexed(const std::string& path);



