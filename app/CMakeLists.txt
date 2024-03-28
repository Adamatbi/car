# Build the app, using the HAL

include_directories(include)
file(GLOB MY_SOURCES "src/*.c")
add_executable(driver ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(driver LINK_PRIVATE hal)

# Copy executable to final location (change `driver` to project name as needed)
add_custom_command(TARGET driver POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:driver>"
     "~/cmpt433/public/myApps/driver" 
  COMMENT "Copying ARM executable to public NFS directory")
