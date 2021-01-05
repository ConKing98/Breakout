OUTPUT = Breakout

OBJDIR = obj
SRCDIR = src
INCDIR = include

CC = gcc
CXX = g++
CFLAGS = -I$(INCDIR) -Wall -g
CXXFLAGS = -I$(INCDIR) -Wall -g
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp

CSRC = $(shell find $(SRCDIR) -type f -name "*.c")
COBJ = $(CSRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

CXXSRC = $(shell find $(SRCDIR) -type f -name "*.cpp")
CXXOBJ = $(CXXSRC:$(SRCDIR)%cpp=$(OBJDIR)%o)

SRC = $(CSRC) $(CXXSRC)
OBJ = $(COBJ) $(CXXOBJ)
DEP = $(OBJ:.o=.d)

$(OUTPUT): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p "$(@D)"
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJDIR)/%.d: $(SRCDIR)/%.c
	@mkdir -p "$(@D)"
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p "$(@D)"
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(shell find $(OBJDIR) -type f -name "*.o") $(OUTPUT)

.PHONY: cleandeps
cleandeps:
	rm -f $(shell find $(OBJDIR) -type f -name "*.d")

.PHONY: cleanall
cleanall:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory cleandeps
	rm -r $(OBJDIR)
