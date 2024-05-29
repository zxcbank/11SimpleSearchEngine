//
// Created by Святослав on 29.05.2024.
//
#include <algorithm>
#include "utils.hpp"

std::vector<char> ignoring_symbols = {' ', '\t', '\r', '\n', '\0', '-', '.', ';', ':', ',', '\'',
                                      '"', '\'', '+', '*', '/', '(', ')', '[', ']', '{', '}',
                                      '&', '|', '<', '>', '=', '?',
                                      '#', '%', '$', '@', '`', '^', '~', '!'};

std::vector<std::string> ignoring_directories = {".git", ".svn", ".hg", ".bzr", "cmake-build-debug", ".idea", "11SimpleSearchEngine"};
std::vector<std::string> ignoring_extensions = {".cmake"};

void correct_term(std::string& term) {
    for (int i = 0; i < term.size(); i++)
        term[i] = tolower(term[i]);
}

bool IsDirCorrect(const std::string& dir) {
    return !(std::find(ignoring_directories.begin(), ignoring_directories.end(), dir) != ignoring_directories.end());
}

bool IsExtensionCorrect(const std::string& dir) {
    return!(std::find(ignoring_extensions.begin(), ignoring_extensions.end(), dir)!= ignoring_extensions.end());
}

std::vector<std::string> ExploringLine(std::string& line) {
    std::string t;
    std::vector<std::string> terms;
    for (const auto& c : line) {
        if (std::find(ignoring_symbols.begin(), ignoring_symbols.end(), c) != ignoring_symbols.end()) {
            if (!t.empty()) {
                correct_term(t);
                terms.push_back(t);
            }
            
            t.clear();
        } else {
            t += c;
        }
    }
    if (!t.empty()) {
        correct_term(t);
        terms.push_back(t);
    }
    return terms;
}