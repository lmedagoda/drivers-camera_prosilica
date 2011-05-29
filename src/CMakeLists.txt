SET(module_name ${PROJECT_NAME})
add_library(${PROJECT_NAME} SHARED CamGigEProsilica.cpp)
target_link_libraries(${PROJECT_NAME} rt PvAPI camera_interface pthread)

install(TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
    )

