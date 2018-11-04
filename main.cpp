#include <iostream>
#include "include/RECompiler.h"

int main() {
    RECompiler reCompiler("(a|b)*");
    if(reCompiler.isLegal()){
        NFA nfa = reCompiler.toNFA();
        DFA dfa = nfa.toDFA();
        DFA dfao = dfa.minimize();
        cout << "over" << endl;
    }
    return 0;
}