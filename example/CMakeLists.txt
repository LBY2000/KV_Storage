set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/example)
include_directories(../src/base)
include_directories(../src/http)
include_directories(../src/logger)
include_directories(../src/storage)
include_directories(../src/timer)
include_directories(../src/network/include)

add_executable(KVServer kv_server.cpp)
target_link_libraries(KVServer storage)
target_link_libraries(KVServer network)

add_executable(Client client.cpp)
target_link_libraries(Client network)


