#pragma once
#include <iostream>
#include <vector>
    
    class Search  {
        public:
            Search();
            std::string name;
            Search(std::string& name) : name(name){};
            ~Search() = default;
            Search& operator=( Search& X)=default;
            Search& operator=( Search&& X)=default;
            Search(std::string&& name) : name(std::move(name)){};
            void run();
            
    };