CC											:= g++
CHEERP									:= /opt/cheerp/bin/clang++
CFLAGS									:= -std=c++17 -g
BUILDDIR								:= build
STATICDIR								:= static
SRCEXT									:= cpp
SRCDIR									:= src

TARGET_NAME							:= mosaic
TARGET									:= "$(BUILDDIR)/$(TARGET_NAME)"
SRCDIR_STANDARD					:= $(SRCDIR)/standard
SOURCES								 	:= $(wildcard $(SRCDIR_STANDARD)/*.$(SRCEXT))
OBJECTS									:= $(patsubst $(SRCDIR_STANDARD)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

SRCDIR_WASM							:= $(SRCDIR)/wasm
SOURCES_WASM						:= $(SRCDIR_WASM)/Image.cpp

$(BUILDDIR)/%.o: $(SRCDIR_STANDARD)/%.$(SRCEXT)
	@printf "\e[33m\e[1mBuilding...\e[0m\n";
	@mkdir -p $(BUILDDIR)
	@echo "  $(notdir $@) from $(notdir $<)"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	@printf "\e[35m\e[1mLinking...\e[0m\n";
	@echo "  $(notdir $(OBJECTS))"
	@$(CC) $(CFLAGS) -o $@ $^

PHONY: clean
clean:
	@printf "\e[31m\e[1mCleaning...\e[0m\n"
	@echo "  /$(BUILDDIR)"
	@echo "  /$(TARGET)"
	@$(RM) -r $(BUILDDIR) $(OBJECTS)
	@$(RM) "./$(TARGET)"

PHONY: r
r:
	@printf "\e[33m\e[1mRunning $(TARGET)\e[0m\n"
	@./$(TARGET)

PHONY: run
run:
	@mkdir -p $(BUILDDIR)
	@for source in $(basename $(notdir $(SOURCES))); do\
		printf "\e[33m\e[1mBuilding...\e[0m\n";\
		echo "  $$source.o from $$source.$(SRCEXT)";\
		$(CC) $(CFLAGS) -c -o $(BUILDDIR)/$$source.o $(SRCDIR_STANDARD)/$$source.$(SRCEXT);\
	done
	@printf "\e[95m\e[1mLinking...\e[0m\n";
	@echo "  $(notdir $(OBJECTS))"
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@printf "\e[33m\e[1mRunning $(TARGET)\e[0m\n"
	@ ./$(TARGET)

PHONY: wasm
wasm:
	@printf "\e[33m\e[1mBuilding wasm...\e[0m\n";
	@mkdir -p $(BUILDDIR)
	$(CHEERP) \
		-target cheerp-wasm \
		$(SRCDIR_WASM)/segmented_sieve.cpp \
		-o $(BUILDDIR)/$(TARGET_NAME).js \
		-O3
	@cp $(STATICDIR)/js-test.html $(BUILDDIR)

PHONY: js
js:
	@printf "\e[33m\e[1mBuilding js...\e[0m\n";
	@mkdir -p $(BUILDDIR)
	$(CHEERP) \
		-target cheerp-wasm \
		$(SOURCES_WASM) \
		-o $(TARGET).js
	@cp $(STATICDIR)/js-test.html $(BUILDDIR)
