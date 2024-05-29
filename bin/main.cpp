//
// Created by Святослав on 15.05.2024.
//
#include "search/engine.hpp"
#include "indexation/index.hpp"
#include "indexation/utils.hpp"
#define PROJECTS_DIR "C:\\itmo\\OP"


int main( int argc, char** argv) {
     Index Indexator(PROJECTS_DIR);
     Indexator.ExploreFiles();

     return 0;
}
