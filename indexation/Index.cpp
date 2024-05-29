//
// Created by Святослав on 29.05.2024.
//

#include "Index.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
std::string SPECIAL_LEN_IDENTIFIER = "!!!";

Index::Index(std::string&& path_) {
    path = std::move(path_);
}

void Index::ExploreFiles() {
    std::vector<std::string> paths_;
    const std::string current_path = path;
    recursive_index(paths_, current_path);
    
    
    for (auto& i : paths_)
        std::cout << i << '\n';
    
//    std::string h = CreateDataDirectories(new_dir);
//    std::system("cd Data");
    makeDataFiles(new_dir, paths_);
}

void Index::recursive_index(std::vector<std::string>& paths_, const std::string& current_path) {
    for (const auto& file : std::filesystem::directory_iterator(current_path)) {
        if (std::filesystem::is_directory(file))  {
            std::string fn = file.path().filename().string();
            if (IsDirCorrect(fn)) {
                recursive_index(paths_, file.path().string());
            }
        } else {
            if (IsExtensionCorrect(file.path().extension().string())) {
                paths_.push_back(file.path().string());
            }
        }
    }
    
}

std::string Index::CreateDataDirectories(std::string fn) {
    std::filesystem::create_directory(fn);
}

std::map<std::string, int> Index::readFile(const std::string& pa) {
    size_t len = 0;
    std::ifstream read_file(pa);
    std::map<std::string, int> terms_frequency;
    while (!read_file.eof()) {
        std::string line;
        read_file >> line;
        std::vector<std::string> terms  = ExploringLine(line);
        len += terms.size();
        for (const auto& term : terms) {
            PostingList[term].insert(current_did);
            terms_frequency[term]++;
        }
    }
    terms_frequency[SPECIAL_LEN_IDENTIFIER] = len;
    read_file.close();
    return terms_frequency;
}

void Index::writeFile(const std::string& fn, std::map<std::string, int>& data, std::string&& real_file_name) {
    std::ofstream write_file(fn);
    write_file << real_file_name<< "\n";
    write_file << std::to_string(data[SPECIAL_LEN_IDENTIFIER]) << "\n";
    for (auto i = ++data.begin();i != data.end(); i++)  {
        write_file << i->first;
        write_file << " " << i->second << "\n";
    }
    write_file.close();
}

void Index::makeDataFiles (const std::string& new_path, const std::vector<std::string>& paths_) {
    
    for (const auto& file : paths_) {
        std::map<std::string, int> file_data = readFile(file);
        
        std::string new_file_name = "index" + std::to_string(++current_did) + ".txt";
        std::string new_file_path = new_path  + "\\" + new_file_name;
        writeFile(new_file_path, file_data, std::string(file));
    }
    
}




