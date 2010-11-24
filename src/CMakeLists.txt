SET(module_name ${PROJECT_NAME})
add_library(${PROJECT_NAME} SHARED CamGigEProsilica.cpp)
target_link_libraries(${PROJECT_NAME} rt PvAPI camera_interface pthread)

install(TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
    )

#SET(TestViewer TestViewer)
#SET(module_name ${TestViewer}) 
add_executable(test_exec test.cpp)  
target_link_libraries(test_exec camera_prosilica_gige)
#install(TARGETS ${TestViewer} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/test)

