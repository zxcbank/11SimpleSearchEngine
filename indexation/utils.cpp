//
// Created by Святослав on 29.05.2024.
//
#include "utils.hpp"

std::vector<char> ignore_symbols = {' ', '\t', '\r', '\n', '\0', '-', '.', ';', ':', ',', '\'',
                                          '"', '\'', '+', '*', '/', '(', ')', '[', ']', '{', '}',
                                          '&', '|',  '<',  '>',  '=',  '?',
                                          '#', '%',  '$',  '@',  '`',  '^',  '~', '!'};

void correct_term(std::string& term) {
    for (int i = 0; i < term.size(); i++)
        term[i] = tolower(term[i]);
}