//
// Created by Святослав on 29.05.2024.
//
#pragma once

#include <cstdint>
#include <string>
#include <set>
#include <map>
#include "utils.hpp"

class Index {
    private:
        size_t current_did = 0; // N
        size_t length_of_files = 0; // dl(all)
        size_t avg_length = 0; // d_avg в формуле
        std::map<std::string, std::set<int>> PostingList;
        std::string path;
        
        void recursive_index(std::vector<std::string>& paths_, const std::string&  current_path);
    public:
        [[maybe_unused]] explicit Index(std::string&& path_);
        
        [[maybe_unused]] void ExploreFiles();
};

