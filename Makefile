udep : comp/udep.o comp/c.a comp/sets.o
	gcc $^ -o $@

comp/c.a : comp/c_checker.o comp/c_find_declarations.o comp/c_header_declarations.o
	ar cr $@ $^
	rm $^

comp/%.o : source/%.c
	gcc -c -o $@ $<