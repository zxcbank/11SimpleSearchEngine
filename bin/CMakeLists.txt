add_executable(${PROJECT_NAME} main.cpp
        ../indexation/Index.hpp
        ../indexation/Index.cpp
        ../indexation/utils.hpp
        ../indexation/utils.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE 11SearchEngineT)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})