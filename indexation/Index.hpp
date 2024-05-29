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
        std::string new_dir = R"(C:\itmo\OP\11SimpleSearchEngine\Data)";
        std::string posting_list_filename = R"(C:\itmo\OP\11SimpleSearchEngine\Data\posting_list.txt)";
        std::map<std::string, std::set<int>> PostingList;
        std::string path;
        std::string CreateDataDirectories(std::string fn);
        void recursive_index(std::vector<std::string>& paths_, const std::string&  current_path);
        void makeDataFiles (const std::string& new_path, const std::vector<std::string>& paths_);
        void makePostingListFile();
        std::map<std::string, int> readFile(const std::string& pa);
        void writeFile(const std::string& fn, std::map<std::string, int>& data, std::string&& real_file_name);
    public:
        [[maybe_unused]] explicit Index(std::string&& path_);
        
        [[maybe_unused]] void ExploreFiles();
};

