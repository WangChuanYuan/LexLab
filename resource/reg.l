digit (1|2|3|4|5|6|7|8|9)
letter (a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)
%%
identifier (letter)(letter)*(digit)*
num digit*
decimal (digit)(digit)*.(digit)(digit)*
keyword int|float|double|public|main