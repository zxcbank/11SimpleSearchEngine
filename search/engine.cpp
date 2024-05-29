//
// Created by Святослав on 16.05.2024.
//
#include <fstream>
#include <map>
#include "engine.hpp"
#define AND AND
#define OR OR

bool IsIndexed(const std::string& path) {
    std::string data_path = path + "\\Data\\posting_list.txt";
    std::ifstream ifs(data_path);
    if (!ifs.is_open())  {
        return false;
    }
    return true;
}

Search::Search(int argc, char** argv,std::string&& PROJ_DIR) {
    std::string query;
    project_path = PROJ_DIR;
    if (!IsIndexed(project_path))  {
        std::cerr  <<  "Data file not found! \n";
        exit(1);
    } else {
        std::string data_path = project_path + "\\Data\\posting_list.txt";
        std::ifstream posting_list(data_path);
        std::string line;
        posting_list >> line;
        N = std::stoi(line);
        posting_list >> line;
        all_len = std::stoi(line);
        posting_list >> line;
        avg_len = std::stoi(line);
    }
    
    for (int i = 1; i < argc; i++) {
        query += argv[i]; if (i  <  argc - 1)  query  += " ";
    }
    
    search_query = query;
}
void CalculateTerms(std::vector<std::string>& terms_list, std::map<std::string, term>& scorings, const std::string& data_path, int N) {
    std::string data_path_ = data_path + "\\Data\\posting_list.txt";
    
    std::string line;
    for (auto& word : terms_list) {
        std::ifstream posting_list(data_path_);
        while (!posting_list.eof()) {
            posting_list >> line;
            if (line.find(word) != line.npos) {
                std::vector<std::string> words_in_line = ExploringLine(line);
                term t(word, N);
                for (auto i = words_in_line.begin()++; i != words_in_line.end(); i++) {
                    t.incuded_in_files.push_back(std::stoi(*i));
                }
                
                for (auto i : t.incuded_in_files) {
                    std::string i_datafile_path = data_path + "\\Data\\index" + std::to_string(i) + ".txt";
                    std::ifstream i_datafile(i_datafile_path);
                    std::string dl_line;
                    i_datafile >> dl_line;
                    size_t dl = std::stoi(dl_line);
                    std::string line2;
                    while (!i_datafile.eof()) {
                        i_datafile >> line2;
                        if (line2.find(word) != line2.npos) {
                            std::vector<std::string>
                        }
                    }
                }
                break;
            }
        }
    }
}
void Search::rangingFiles() {
    
    std::vector<std::string> terms_list = ExploringLine(search_query);
    std::map<std::string, term> scorings;
    std::string data_path = project_path + "\\Data\\posting_list.txt";
    CalculateTerms(terms_list, scorings, data_path, N, avg_len, all_len);
    
}
