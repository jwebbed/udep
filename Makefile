udep: comp/udep.o comp/sets.o comp/c.a comp/cfulib_hash.a
	gcc $^ -o $@

comp/c.a: comp/csearch_helpers.o comp/csearch_include.o comp/csearch_func.o comp/csearch_enum_struct.o comp/csearch_define.o comp/c_checker.o comp/c_header_declarations.o comp/cset.o comp/cmap.o
	ar cr $@ $^

comp/cfulib_hash.a: comp/cfu.o comp/cfuhash.o comp/cfustring.o
	ar cr $@ $^

comp/%.o: source/%.c
	gcc -c -o $@ $<

comp/sets.o:
	gcc -c -o $@ source/sets/sets.c

clean:
	rm -rf comp/*