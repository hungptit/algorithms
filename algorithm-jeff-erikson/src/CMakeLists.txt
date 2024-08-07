set(SOLUTIONS 01-tower-of-hanoi)
foreach(SRC_FILE ${SOLUTIONS})
  add_executable(${SRC_FILE} ${SRC_FILE}.cpp)
  target_link_libraries(${SRC_FILE} Catch2::Catch2WithMain fmt::fmt)
  add_test(${SRC_FILE} ${SRC_FILE})
endforeach(SRC_FILE)

enable_testing()
