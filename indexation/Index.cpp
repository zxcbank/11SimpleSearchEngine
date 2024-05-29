//
// Created by Святослав on 29.05.2024.
//

#include "Index.hpp"
#include <filesystem>
#include <iostream>

Index::Index(std::string&& path_) {
    path = std::move(path_);
}

void Index::ExploreFiles() {
    std::vector<std::string> paths_;
    const std::string current_path = path;
    recursive_index(paths_, current_path);
    
    
    for (auto& i : paths_)
        std::cout << i << '\n';
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