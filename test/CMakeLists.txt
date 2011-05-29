SET(TestViewer TestViewer)
SET(module_name ${TestViewer}) 
add_executable(${PROJECT_NAME}_test test.cpp)  
target_link_libraries(${PROJECT_NAME}_test camera_prosilica_gige)
install(TARGETS ${PROJECT_NAME}_test RUNTIME DESTINATION bin)

