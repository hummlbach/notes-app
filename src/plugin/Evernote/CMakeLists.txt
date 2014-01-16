include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/3rdParty/libthrift
    ${CMAKE_SOURCE_DIR}/3rdParty/evernote-sdk-cpp/src/
)

set(evernoteplugin_SRCS
    evernoteplugin.cpp
    notesstore.cpp
    userstore.cpp
    notebooks.cpp
    notes.cpp
    note.cpp
    notebook.cpp
    jobs/fetchnotesjob.cpp
    jobs/fetchnotebooksjob.cpp
    jobs/fetchnotejob.cpp
    jobs/createnotejob.cpp
    jobs/evernotejob.cpp
    jobs/savenotejob.cpp
    jobs/deletenotejob.cpp
    evernoteconnection.cpp
    jobs/userstorejob.cpp
    jobs/notesstorejob.cpp
    jobs/fetchusernamejob.cpp
    jobs/createnotebookjob.cpp
    jobs/expungenotebookjob.cpp
    resourceimageprovider.cpp
    utils/enmldocument.cpp
)

add_library(evernoteplugin MODULE
    ${evernoteplugin_SRCS}
)

target_link_libraries(evernoteplugin
    -L${CMAKE_BINARY_DIR}/3rdParty/evernote-sdk-cpp/ -L${CMAKE_BINARY_DIR}/3rdParty/libthrift/ -levernote-sdk-cpp -llibthrift -lssl -lcrypto
)

qt5_use_modules(evernoteplugin Gui Qml Quick)


# Copy qmldir file to build dir for running in QtCreator
add_custom_target(evernoteplugin-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${QMLFILES}
)

# Install plugin file
exec_program(qmake ARGS "-query QT_INSTALL_QML" OUTPUT_VARIABLE QT_IMPORTS_DIR)
install(TARGETS evernoteplugin DESTINATION ${QT_IMPORTS_DIR}/Evernote/)
install(FILES qmldir DESTINATION ${QT_IMPORTS_DIR}/Evernote/)
