SET(module_name ${PROJECT_NAME})
add_library(${PROJECT_NAME} SHARED CamGigEProsilica.cpp)
target_link_libraries(${PROJECT_NAME} rt PvAPI camera_interface pthread)

install(TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
    )

#SET(TestViewer TestViewer)
#SET(module_name ${TestViewer}) 
add_executable(${PROJECT_NAME}_test test.cpp)  
target_link_libraries(${PROJECT_NAME}_test camera_prosilica_gige)
install(TARGETS ${PROJECT_NAME}_test RUNTIME DESTINATION bin)

