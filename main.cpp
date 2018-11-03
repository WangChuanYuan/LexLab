#include <iostream>
#include "include/RECompiler.h"

int main() {
    RECompiler reCompiler("(a|b)*");
    if(reCompiler.isLegal()){
        NFA nfa = reCompiler.toNFA();
        DFA dfa = nfa.toDFA();
        dfa.minimize();
        cout << "over" << endl;
    }
    return 0;
}