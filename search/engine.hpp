#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "indexation/utils.hpp"

class Search  {
    std::string search_query; //search query
    std::string project_path;
    size_t N; // number of Files
    size_t avg_len;
    size_t all_len;
    
    public:
        Search(int argc, char** argv, std::string&& PROJ_DIR);
        void rangingFiles();
        
};

bool IsIndexed(const std::string& path);

class term {
        std::string word;
        
    public:
        std::vector<int> indexes;
        std::vector<int> incuded_in_files;
        explicit term(std::string term_, int number_of_files) : word(std::move(term_)), indexes(std::vector<int>(number_of_files)) {};
};

void CalculateTerms(std::vector<std::string>& terms_list, std::map<std::string, term>& scorings,
                    const std::string& data_path, size_t N, size_t avg_len, size_t all_len);
