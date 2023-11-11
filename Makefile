# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
CXX := /usr/bin/g++

TARGET_EXEC := main

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP -std=c++17

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) $(BUILD_DIR)/res
	echo "Building"
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) ./lib/*

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/res:
	cp -r src/res $(BUILD_DIR)/res


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)/*

.PHONY: rclean
rclean:
	rm -r $(BUILD_DIR)/FallingCrates.app

.PHONY: run
run:
	@$(BUILD_DIR)/main

.PHONY: release
release: $(BUILD_DIR)/$(TARGET_EXEC) rclean
	mkdir $(BUILD_DIR)/FallingCrates.app
	mkdir $(BUILD_DIR)/FallingCrates.app/contents
	mkdir $(BUILD_DIR)/FallingCrates.app/contents/MacOS

	cp -r macos/Frameworks $(BUILD_DIR)/FallingCrates.app/contents/Frameworks
	cp -r macos/Resources $(BUILD_DIR)/FallingCrates.app/contents/Resources
	cp -r $(BUILD_DIR)/res $(BUILD_DIR)/FallingCrates.app/contents/MacOS/res

	cp $(BUILD_DIR)/$(TARGET_EXEC) $(BUILD_DIR)/FallingCrates.app/contents/MacOS/main
	cp macos/Info.plist $(BUILD_DIR)/FallingCrates.app/contents/Info.plist

	install_name_tool -change @rpath/libsfml-audio.2.5.dylib @executable_path/../Frameworks/libsfml-audio.2.5.1.dylib $(BUILD_DIR)/FallingCrates.app/contents/MacOS/main
	install_name_tool -change @rpath/libsfml-graphics.2.5.dylib @executable_path/../Frameworks/libsfml-graphics.2.5.1.dylib $(BUILD_DIR)/FallingCrates.app/contents/MacOS/main
	install_name_tool -change @rpath/libsfml-network.2.5.dylib @executable_path/../Frameworks/libsfml-network.2.5.1.dylib $(BUILD_DIR)/FallingCrates.app/contents/MacOS/main
	install_name_tool -change @rpath/libsfml-system.2.5.dylib @executable_path/../Frameworks/libsfml-system.2.5.1.dylib $(BUILD_DIR)/FallingCrates.app/contents/MacOS/main
	install_name_tool -change @rpath/libsfml-window.2.5.dylib @executable_path/../Frameworks/libsfml-window.2.5.1.dylib $(BUILD_DIR)/FallingCrates.app/contents/MacOS/main

	install_name_tool -change @rpath/../Frameworks/OpenAL.framework/Versions/A/OpenAL @executable_path/../Frameworks/OpenAL.framework/Versions/A/OpenAL $(BUILD_DIR)/FallingCrates.app/contents/Frameworks/libsfml-audio.2.5.1.dylib;
	install_name_tool -change @rpath/../Frameworks/vorbisenc.framework/Versions/A/vorbisenc @executable_path/../Frameworks/vorbisenc.framework/Versions/A/vorbisenc $(BUILD_DIR)/FallingCrates.app/contents/Frameworks/libsfml-audio.2.5.1.dylib;
	install_name_tool -change @rpath/../Frameworks/vorbisfile.framework/Versions/A/vorbisfile @executable_path/../Frameworks/vorbisfile.framework/Versions/A/vorbisfile $(BUILD_DIR)/FallingCrates.app/contents/Frameworks/libsfml-audio.2.5.1.dylib;
	install_name_tool -change @rpath/../Frameworks/vorbis.framework/Versions/A/vorbis @executable_path/../Frameworks/vorbis.framework/Versions/A/vorbis $(BUILD_DIR)/FallingCrates.app/contents/Frameworks/libsfml-audio.2.5.1.dylib;
	install_name_tool -change @rpath/../Frameworks/ogg.framework/Versions/A/ogg @executable_path/../Frameworks/ogg.framework/Versions/A/ogg $(BUILD_DIR)/FallingCrates.app/contents/Frameworks/libsfml-audio.2.5.1.dylib;
	install_name_tool -change @rpath/../Frameworks/FLAC.framework/Versions/A/FLAC @executable_path/../Frameworks/FLAC.framework/Versions/A/FLAC $(BUILD_DIR)/FallingCrates.app/contents/Frameworks/libsfml-audio.2.5.1.dylib;

	install_name_tool -change @rpath/../Frameworks/freetype.framework/Versions/A/freetype @executable_path/../Frameworks/freetype.framework/Versions/A/freetype $(BUILD_DIR)/FallingCrates.app/contents/Frameworks/libsfml-graphics.2.5.1.dylib

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)