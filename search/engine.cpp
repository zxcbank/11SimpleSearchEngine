//
// Created by Святослав on 16.05.2024.
//
#include <fstream>
#include <map>
#include <valarray>
#include "engine.hpp"
#include <chrono>

std::vector<char> ignoring_parse_symbols = {' ', '\t', '\r', '\n', '\0', '-', '.', ';', ',', '\'',
                                            '"', '\'', '+', '*', '/', '[', ']', '{', '}',
                                            '&', '|', '<', '>', '=', '?',
                                            '#', '%', '$', '@', '`', '^', '~', '!'};

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
        
    }
    
    for (int i = 1; i < argc; i++) {
        query += argv[i]; if (i  <  argc - 1)  query  += " ";
    }
    
    search_query = query;
}

term Search::CalculateRela(const std::string& q) {
    std::vector<std::string> expression(3);
    std::string oper;
    term A, B;
    int iter = 0;
    for (int i = 0; i < q.size(); i++) {
        if (q[i] == '(') {
            std::string subline;
            int start = ++i;
            int t = -1;
            while (t != 0) {
                if (q[i] == '(') {
                    t--;
                } else if (q[i] == ')') {
                    t++;
                }
                if (t != 0) {
                    subline += q[i];
                }
                i++;
            }
            if (iter == 0) {
                A = CalculateRela(subline);
                iter++;
            } else if (iter == 1) {
                std::cerr << "must be operator \n";
                exit(1);
            } else if (iter == 2) {
                B = CalculateRela(subline);
            }
        } else {
            if (std::find(ignoring_parse_symbols.begin(), ignoring_parse_symbols.end(), q[i]) == ignoring_parse_symbols.end()) {
                expression[iter] += q[i];
            } else {
                if (iter == 0) {
                    if (IsOperand(expression[iter])) {
                        std::cerr << "left operand cant be OR | AND";
                        exit(1);
                    }
                    A = scorings[expression[iter]];
                    iter++;
                } else if (iter == 1) {
                    if (!IsOperand(expression[iter])) {
                        std::cerr << "left operand must be OR | AND";
                        exit(1);
                    }
                    oper = expression[iter];
                    iter++;
                } else if (iter == 2) {
                    if (IsOperand(expression[iter])) {
                        std::cerr << "right operand cant be OR | AND";
                        exit(1);
                    }
                    B = scorings[expression[iter]];
                    iter++;
                }
                
            }
            if (i == q.size() - 1) {
                if (IsOperand(expression[iter])) {
                    std::cerr << "right operand cant be OR | AND";
                    exit(1);
                }
                B = scorings[expression[iter]];
                iter++;
            }
        }
    }
    
    if (oper == "AND")
        return A * B;
    else
        return A + B;
}

bool cmp(std::pair<int, float> a, std::pair<int, float> b) {
    return a.second > b.second;
}
void Search::showListOfEntry(std::vector<std::string>& term_list, const std::string& fn) {
    std::ifstream file (fn);
    int foundedEntries = 0;
    int line_index = 0;
    std::string line;
    
    while (!file.eof() && (foundedEntries < HowManyEntries)) {
        std::getline(file, line, '\n');
        correct_term(line);
        for (auto& word : term_list) {
            if (line.find(word) != line.npos) {
                std::cout << "    $$ " << word << " in line " << line_index << "...\n";
                foundedEntries++;
            }
        }
        line_index++;
    }
    
}
void Search::show (int topk, std::vector<std::string>& term_list) {
    std::vector<std::pair<int, float>> top;
    for (int i = 0; i < relative_indexes.size(); i++) {
        top.push_back({i, relative_indexes[i]});
    }
    std::sort(top.begin(), top.end(), cmp);
    
    for (int i = 0; i < topk; i++) {
        if (top[i].second == 0)
            break;
        
        std::string fn = project_path + "\\Data\\index" + std::to_string(top[i].first) + ".txt";
        std::ifstream file(fn);
        std::string line;
        file >> line;
        std::cout << i + 1 << ") " << line << "\n";
        showListOfEntry(term_list, line);
        
    }
}

void Search::rangingFiles() {
    auto begin = std::chrono::steady_clock::now();
    std::vector<std::string> terms_list = ExploringLine(search_query);
    
    std::string post_list = project_path + "\\Data\\posting_list.txt";
    remakePostingList(post_list);
    
    scoringTerms(terms_list);
    
    relative_indexes = CalculateRela(search_query).indexes;
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "RELEVANT FILES for " << search_query << " founded in " << elapsed_ms.count()<< "ms \n";
    show(5, terms_list);
}

void Search::remakePostingList(std::string& path_) {
    std::ifstream post_list_file(path_);
    std::string line;
    std::getline(post_list_file, line, '\n');
    N = std::stoi(line);
    std::getline(post_list_file, line, '\n');
    all_len = std::stoi(line);
    std::getline(post_list_file, line, '\n');
    avg_len = std::stoi(line);
    
    while (!post_list_file.eof()) {
        std::getline(post_list_file, line, '\n');
        if (line.empty())
            continue;
        std::vector<std::string> includings = ExploringLine(line);
        std::string term = includings[0];
        for (int i = 1; i < includings.size(); i++)
            posting_list[term].push_back(std::stoi(includings[i]));
    }
}

void Search::scoringTerms(std::vector<std::string>& terms_list) {
    for (auto& term_ : terms_list) {
        if (!(term_ == "OR" || term_ == "AND")) {
            std::vector<int> includings = posting_list[term_];
            std::vector<float> scorings_for_files(N, 0);
            for (auto file_index : includings) {
                std::string fn = project_path + "\\Data\\index" + std::to_string(file_index) + ".txt";
                scorings_for_files[file_index] = scoringFile(term_, fn);
            }
            term t_i(term_, scorings_for_files);
            scorings[term_] = t_i;
        }
    }
}

float Search::scoringFile(const std::string& term, const std::string& fn) {
    std::ifstream file(fn);
    std::string line;
    float tf = 1;
    size_t df = posting_list[term].size();
    std::string real_fn;
    std::getline(file, real_fn, '\n');
    int dl;
    std::getline(file, line, '\n');
    dl = std::stoi(line);
    while (!file.eof()) {
        std::getline(file, line, '\n');
        if (line.empty())
            continue;
        if (line.find(term) != line.npos) {
            tf = std::stoi(ExploringLine(line)[1]);
            break;
        }
    }
    
    float right_log = std::log(static_cast<float>(N) / static_cast<float>(df));
    float leftpart = (tf * (k + 1)) / (tf + k * (1 - b  + b * (static_cast<float>(dl) / static_cast<float>(avg_len))));
    return right_log * leftpart;
}




