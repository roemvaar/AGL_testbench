cmake_minimum_required(VERSION 3.5)
project(src)
set(CMAKE_CXX_STANDARD 17)

# add_executable(${PROJECT_NAME}
#     can_transmit.c
#     can_receive.c
#     can_continuous_tx.c
#     can_continuous_rx.c
# )

add_executable(can_transmit
    can_transmit.c
)

add_executable(can_receive
    can_receive.c
)

add_executable(can_continuous_tx
    can_continuous_tx.c
)

add_executable(can_continuous_rx
    can_continuous_rx.c
)

# Libraries
# when running g++ these will be included as -static LIB or -lLIB
# target_link_libraries(${PROJECT_NAME}
#     pthread
# )
