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
CMAKE_SOURCE_DIR = /home/ooo/桌面/te

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ooo/桌面/te/build

# Include any dependencies generated for this target.
include CMakeFiles/armor_detect.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/armor_detect.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/armor_detect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/armor_detect.dir/flags.make

CMakeFiles/armor_detect.dir/main.cpp.o: CMakeFiles/armor_detect.dir/flags.make
CMakeFiles/armor_detect.dir/main.cpp.o: /home/ooo/桌面/te/main.cpp
CMakeFiles/armor_detect.dir/main.cpp.o: CMakeFiles/armor_detect.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ooo/桌面/te/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/armor_detect.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/armor_detect.dir/main.cpp.o -MF CMakeFiles/armor_detect.dir/main.cpp.o.d -o CMakeFiles/armor_detect.dir/main.cpp.o -c /home/ooo/桌面/te/main.cpp

CMakeFiles/armor_detect.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/armor_detect.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ooo/桌面/te/main.cpp > CMakeFiles/armor_detect.dir/main.cpp.i

CMakeFiles/armor_detect.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/armor_detect.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ooo/桌面/te/main.cpp -o CMakeFiles/armor_detect.dir/main.cpp.s

CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o: CMakeFiles/armor_detect.dir/flags.make
CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o: /home/ooo/桌面/te/src/cameraConnect.cpp
CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o: CMakeFiles/armor_detect.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ooo/桌面/te/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o -MF CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o.d -o CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o -c /home/ooo/桌面/te/src/cameraConnect.cpp

CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ooo/桌面/te/src/cameraConnect.cpp > CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.i

CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ooo/桌面/te/src/cameraConnect.cpp -o CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.s

# Object files for target armor_detect
armor_detect_OBJECTS = \
"CMakeFiles/armor_detect.dir/main.cpp.o" \
"CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o"

# External object files for target armor_detect
armor_detect_EXTERNAL_OBJECTS =

/home/ooo/桌面/te/bin/armor_detect: CMakeFiles/armor_detect.dir/main.cpp.o
/home/ooo/桌面/te/bin/armor_detect: CMakeFiles/armor_detect.dir/src/cameraConnect.cpp.o
/home/ooo/桌面/te/bin/armor_detect: CMakeFiles/armor_detect.dir/build.make
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_gapi.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_highgui.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_ml.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_objdetect.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_photo.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_stitching.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_video.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_videoio.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /opt/MVS/lib/64/libMvCameraControl.so
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libceres.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_base.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_imgcodecs.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_dnn.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_calib3d.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_features2d.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_flann.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_imgproc.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libopencv_core.so.4.10.0
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_check_op.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_conditions.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_message.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_nullguard.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_examine_stack.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_format.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_proto.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_log_sink_set.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_globals.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_sink.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_entry.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_strerror.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_flags.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_globals.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_flags_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_flags_reflection.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_flags_config.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_flags_program_name.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_flags_private_handle_accessor.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_flags_commandlineflag.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_flags_commandlineflag_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_raw_hash_set.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_hash.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_city.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_bad_variant_access.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_low_level_hash.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_cord.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_cordz_info.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_cord_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_cordz_functions.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_cordz_handle.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_crc_cord_state.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_crc32c.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_crc_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_crc_cpu_detect.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_hashtablez_sampler.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_exponential_biased.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_flags_marshalling.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_str_format_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_vlog_config_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_bad_optional_access.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_internal_fnmatch.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_synchronization.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_stacktrace.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_symbolize.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_debugging_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_demangle_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_demangle_rust.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_decode_rust_punycode.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_utf8_for_code_point.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_graphcycles_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_kernel_timeout_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_malloc_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_tracing_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_time.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_strings.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_strings_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_string_view.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_throw_delegate.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_base.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_spinlock_wait.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_raw_logging_internal.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_log_severity.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_int128.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_civil_time.a
/home/ooo/桌面/te/bin/armor_detect: /usr/local/lib/libabsl_time_zone.a
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libspqr.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libcholmod.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libamd.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libcamd.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libccolamd.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libcolamd.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libtbb.so.12.5
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/liblapack.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libblas.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libf77blas.so
/home/ooo/桌面/te/bin/armor_detect: /usr/lib/x86_64-linux-gnu/libatlas.so
/home/ooo/桌面/te/bin/armor_detect: CMakeFiles/armor_detect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ooo/桌面/te/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/ooo/桌面/te/bin/armor_detect"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/armor_detect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/armor_detect.dir/build: /home/ooo/桌面/te/bin/armor_detect
.PHONY : CMakeFiles/armor_detect.dir/build

CMakeFiles/armor_detect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/armor_detect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/armor_detect.dir/clean

CMakeFiles/armor_detect.dir/depend:
	cd /home/ooo/桌面/te/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ooo/桌面/te /home/ooo/桌面/te /home/ooo/桌面/te/build /home/ooo/桌面/te/build /home/ooo/桌面/te/build/CMakeFiles/armor_detect.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/armor_detect.dir/depend

