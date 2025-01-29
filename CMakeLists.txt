cmake_minimum_required(VERSION 3.26)
project(MoviesCatalogue)

set(DCMAKE_PREFIX_PATH= "C:/Qt/6.7.0/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6Widgets REQUIRED)

include_directories(controller)
include_directories(domain)
include_directories(repository)
include_directories(ui)

add_executable(MoviesCatalogue
        controller/MovieError.h
        controller/MovieServices.cpp
        controller/MovieServices.h
        domain/Movie.cpp
        domain/Movie.h
        repository/FileRepository.cpp
        repository/Repository.cpp
        repository/Repository.h
        ui/MovieGUI.cpp
        ui/MovieGUI.h
        ui/MovieUI.cpp
        ui/MovieUI.h
        main.cpp
        controller/Action.cpp
        ui/MyTableView.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
