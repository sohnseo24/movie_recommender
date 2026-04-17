# Makefile — Movie Recommender 
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g

#movie_recommender로 변경
TARGET   = movie_recommender
OBJS     = main.o Movie.o User.o Rating.o MovieManager.o UserManager.o RatingManager.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^


main.o: main.cpp Movie.h User.h Rating.h MovieManager.h UserManager.h RatingManager.h
	$(CXX) $(CXXFLAGS) -c $<

Movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c $<

User.o: User.cpp User.h
	$(CXX) $(CXXFLAGS) -c $<

Rating.o: Rating.cpp Rating.h
	$(CXX) $(CXXFLAGS) -c $<

MovieManager.o: MovieManager.cpp MovieManager.h Movie.h
	$(CXX) $(CXXFLAGS) -c $<

UserManager.o: UserManager.cpp UserManager.h User.h
	$(CXX) $(CXXFLAGS) -c $<


RatingManager.o: RatingManager.cpp RatingManager.h Rating.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean run


clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)