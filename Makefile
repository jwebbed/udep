udep: comp/udep.o comp/sets.o comp/c.a
	gcc $^ -o $@

comp/c.a: comp/csearch.a comp/c_checker.o comp/c_header_declarations.o
	ar cr $@ $^

comp/csearch.a: comp/csearch_helpers.o comp/csearch_include.o comp/csearch_func.o comp/csearch_enum.o comp/csearch_struct.o comp/csearch_define.o
	ar cr $@ $^

comp/%.o: source/%.c
	gcc -c -o $@ $<

comp/sets.o:
	gcc -c -o $@ source/sets/sets.c

clean:
	rm -rf comp/*