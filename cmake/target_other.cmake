add_executable(${other_name} ${src} ${other_src})
list(APPEND other_link_dependency ${src_link_dependency})
target_link_libraries(${other_name} ${other_link_dependency})

