# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ooo/aa2/aa

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ooo/aa2/aa/build

# Include any dependencies generated for this target.
include CMakeFiles/armor_detect.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/armor_detect.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/armor_detect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/armor_detect.dir/flags.make

CMakeFiles/armor_detect.dir/main.cpp.o: CMakeFiles/armor_detect.dir/flags.make
CMakeFiles/armor_detect.dir/main.cpp.o: /home/ooo/aa2/aa/main.cpp
CMakeFiles/armor_detect.dir/main.cpp.o: CMakeFiles/armor_detect.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ooo/aa2/aa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/armor_detect.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/armor_detect.dir/main.cpp.o -MF CMakeFiles/armor_detect.dir/main.cpp.o.d -o CMakeFiles/armor_detect.dir/main.cpp.o -c /home/ooo/aa2/aa/main.cpp

CMakeFiles/armor_detect.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/armor_detect.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ooo/aa2/aa/main.cpp > CMakeFiles/armor_detect.dir/main.cpp.i

CMakeFiles/armor_detect.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/armor_detect.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ooo/aa2/aa/main.cpp -o CMakeFiles/armor_detect.dir/main.cpp.s

CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o: CMakeFiles/armor_detect.dir/flags.make
CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o: /home/ooo/aa2/aa/src/LightBarDetector.cpp
CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o: CMakeFiles/armor_detect.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ooo/aa2/aa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o -MF CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o.d -o CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o -c /home/ooo/aa2/aa/src/LightBarDetector.cpp

CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ooo/aa2/aa/src/LightBarDetector.cpp > CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.i

CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ooo/aa2/aa/src/LightBarDetector.cpp -o CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.s

CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o: CMakeFiles/armor_detect.dir/flags.make
CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o: /home/ooo/aa2/aa/src/cameraConnect.cpp
CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o: CMakeFiles/armor_detect.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ooo/aa2/aa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o -MF CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o.d -o CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o -c /home/ooo/aa2/aa/src/cameraConnect.cpp

CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ooo/aa2/aa/src/cameraConnect.cpp > CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.i

CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ooo/aa2/aa/src/cameraConnect.cpp -o CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.s

# Object files for target armor_detect
armor_detect_OBJECTS = \
"CMakeFiles/armor_detect.dir/main.cpp.o" \
"CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o" \
"CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o"

# External object files for target armor_detect
armor_detect_EXTERNAL_OBJECTS =

/home/ooo/aa2/aa/bin/armor_detect: CMakeFiles/armor_detect.dir/main.cpp.o
/home/ooo/aa2/aa/bin/armor_detect: CMakeFiles/armor_detect.dir/src/LightBarDetector.cpp.o
/home/ooo/aa2/aa/bin/armor_detect: CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o
/home/ooo/aa2/aa/bin/armor_detect: CMakeFiles/armor_detect.dir/build.make
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_gapi.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_highgui.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_ml.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_objdetect.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_photo.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_stitching.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_video.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_videoio.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /opt/MVS/lib/64/libMvCameraControl.so
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_imgcodecs.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_dnn.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_calib3d.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_features2d.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_flann.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_imgproc.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: /usr/local/lib/libopencv_core.so.4.10.0
/home/ooo/aa2/aa/bin/armor_detect: CMakeFiles/armor_detect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ooo/aa2/aa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable /home/ooo/aa2/aa/bin/armor_detect"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/armor_detect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/armor_detect.dir/build: /home/ooo/aa2/aa/bin/armor_detect
.PHONY : CMakeFiles/armor_detect.dir/build

CMakeFiles/armor_detect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/armor_detect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/armor_detect.dir/clean

CMakeFiles/armor_detect.dir/depend:
	cd /home/ooo/aa2/aa/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ooo/aa2/aa /home/ooo/aa2/aa /home/ooo/aa2/aa/build /home/ooo/aa2/aa/build /home/ooo/aa2/aa/build/CMakeFiles/armor_detect.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/armor_detect.dir/depend

