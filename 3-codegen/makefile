CXXFLAGS += -std=c++11 -w -Wall -g
CXXFLAGS += -I include

bin/% : src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

bin/interpreter : src/ast_parse.o src/ast_pretty_print.o src/ast_interpret.o

bin/compiler : src/ast_parse.o src/ast_pretty_print.o src/ast_compile.o

bin/pretty_print : src/ast_parse.o src/ast_pretty_print.o

bin/constant_fold : src/ast_parse.o  src/ast_pretty_print.o src/ast_constant_fold.o

bin/dead_branches_removal : src/ast_parse.o  src/ast_pretty_print.o src/ast_dead_branches_removal.o

bin/constant_propagation : src/ast_parse.o  src/ast_pretty_print.o src/ast_constant_propagation.o

bin/generate_mips : src/ast_parse.o  src/ast_pretty_print.o

clean :
	-rm bin/*
	-rm src/*.o
	-rm working/*/*.txt
