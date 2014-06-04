udep: comp/main.o comp/c.a comp/Program.o
	gcc $^ -o $@

comp/c.a: comp/csearch_helpers.o comp/csearch_include.o comp/csearch_func.o comp/csearch_enum_struct.o comp/c_checker.o comp/c_header_declarations.o comp/c_set.o
	ar cr $@ $^

comp/%.o: source/%.cpp
	gcc -c -o $@ $<

clean:
	rm -rf comp/*