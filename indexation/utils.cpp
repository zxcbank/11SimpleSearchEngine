//
// Created by Святослав on 29.05.2024.
//
#include <algorithm>
#include "utils.hpp"

std::vector<char> ignoring_symbols = {' ', '\t', '\r', '\n', '\0', '-', '.', ';', ':', ',', '\'',
                                      '"', '\'', '+', '*', '/', '(', ')', '[', ']', '{', '}',
                                      '&', '|', '<', '>', '=', '?',
                                      '#', '%', '$', '@', '`', '^', '~', '!'};

std::vector<std::string> ignoring_directories = {".git", ".svn", ".hg", ".bzr", "cmake-build-debug", ".idea"};
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