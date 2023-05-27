cmake_minimum_required(VERSION 3.14)
project(GAME)

# Pobranie i dodanie biblioteki Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)

set(COMMON_SOURCES 
    Src/FileManager.cpp
    Src/Coordinates.cpp 
    Src/map.cpp
    Src/MapObjects.cpp
    Src/Units.cpp
    Src/Player.cpp
    Src/Time.cpp
    Src/Mediator.cpp
)

set(Testing_SOURCES 
    Tests/ActionTests.cpp 
    Tests/MapTests.cpp 
)

# Kompilacja i dodanie targetów
add_executable(Gra main.cpp ${COMMON_SOURCES})
add_executable(Tests ${Testing_SOURCES} ${COMMON_SOURCES})

# Dodanie flag kompilatora
target_compile_options(Tests PRIVATE -Wall -Wextra)

# Linkowanie z biblioteką Google Test
target_link_libraries(Tests gtest gtest_main)

# Dodanie testów
enable_testing()
include(GoogleTest)
gtest_discover_tests(Tests)
