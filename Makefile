boost_ls: boost_ls.o
	g++ boost_ls.o -lboost_system -lboost_filesystem -o boost_ls

boost_ls.o: boost_ls.cpp
	g++ -c boost_ls.cpp

recursive_boost_ls: recursive_boost_ls.o
	g++ recursive_boost_ls.o -lboost_system -lboost_filesystem -o recursive_boost_ls

recursive_boost_ls.o: recursive_boost_ls.cpp
	g++ -c recursive_boost_ls.cpp

clean:
	\rm *.o boost_ls recursive_boost_ls
