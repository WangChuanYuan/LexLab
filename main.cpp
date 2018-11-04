#include <iostream>
#include <vector>
#include "include/RECompiler.h"

int main() {
    RECompiler re;
    RECompiler alphabet("(a|b)*", "alphabet");
    RECompiler num("12", "num");
    if(alphabet.isLegal() && num.isLegal()){
        vector<NFA> nfas;
        nfas.push_back(alphabet.toNFA());
        nfas.push_back(num.toNFA());
        NFA nfa = re.merge(nfas);
        DFA dfa = nfa.toDFA();
        DFA dfao = dfa.minimize();
        cout << "over" << endl;
    }
    return 0;
}