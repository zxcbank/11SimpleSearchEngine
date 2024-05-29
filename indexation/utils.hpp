//
// Created by Святослав on 29.05.2024.
//
#pragma once

#include <string>
#include <vector>

void correct_term(std::string& term);

bool IsDirCorrect(const std::string& dir);

bool IsExtensionCorrect(const std::string& dir);

std::vector<std::string> ExploringLine(std::string& line);

std::vector<std::string> PasingQ(std::string& line);

bool IsOperand(const std::string& line);