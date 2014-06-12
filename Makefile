udep: comp/main.o comp/c.a comp/Program.o comp/helpers.o
	g++ $^ -O3 -o $@

comp/c.a: comp/csearch_helpers.o comp/csearch_include.o comp/csearch_func.o comp/csearch_enum_struct.o comp/csearch_extern.o comp/c_checker.o comp/c_header_declarations.o comp/c_set.o
	ar cr $@ $^

comp/%.o: source/%.cpp
	g++ -c -std=c++11 -o $@ $<

clean:
	rm -rf comp/*
	rm udep