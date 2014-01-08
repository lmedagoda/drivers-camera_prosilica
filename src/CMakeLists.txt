SET(module_name ${PROJECT_NAME})
add_library(${PROJECT_NAME} SHARED CamGigEProsilica.cpp)
target_link_libraries(${PROJECT_NAME} PvAPI rt camera_interface pthread)

add_executable(${PROJECT_NAME}-show ShowCameras.cpp)
target_link_libraries(${PROJECT_NAME}-show ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-show
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
    )

