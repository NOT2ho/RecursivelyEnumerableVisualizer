cmake_minimum_required(VERSION 3.16)

project(infinitelyLazy VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appinfinitelyLazy
    main.cpp
)

qt_add_qml_module(appinfinitelyLazy
    URI infinitelyLazy
    QML_FILES

        SOURCES valuearray2d.h valuearray2d.cpp
        SOURCES
        SOURCES view.h view.cpp
        SOURCES visualize2d.h visualize2d.cpp
        SOURCES
        SOURCES drawpixel.h drawpixel.cpp
        RESOURCES drawpixel.pro
        SOURCES
        SOURCES linetextframe.h linetextframe.cpp
        SOURCES mainwindow.h mainwindow.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appinfinitelyLazy PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appinfinitelyLazy
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appinfinitelyLazy
    PRIVATE Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

install(TARGETS appinfinitelyLazy
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
