CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
TARGET   = movie_recommender
SRCDIR   = src
OBJDIR   = obj

OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/Movie.o \
       $(OBJDIR)/User.o \
       $(OBJDIR)/Rating.o \
       $(OBJDIR)/MovieManager.o \
       $(OBJDIR)/UserManager.o \
       $(OBJDIR)/RatingManager.o \
       $(OBJDIR)/SimilarityCalculator.o \
       $(OBJDIR)/Recommender.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run