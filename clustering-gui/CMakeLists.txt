# we need to set 'src' as include directory so the compiler can find the header
# files
include_directories(${DATAMINING_SOURCE_DIR}/src)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
add_executable(clustering-gui kernelkmeansdialog.cpp kmeansdialog.cpp main.cpp mainwindow.cpp pointsarea.cpp)
target_link_libraries(clustering-gui Qt5::Widgets itemsetmining)
