grammar Query;

expr : 'True'                                     # True

     | '<:' name=IDENTIFIER ':>'                  # DualAtomic
     | '<:' name=IDENTIFIER                       # RiseAtomic
     | name=IDENTIFIER ':>'                       # FallAtomic
     | name=IDENTIFIER                            # Atomic

     | child=expr '*'                             # Star
     | child=expr '+'                             # Plus
     | child=expr '?'                             # Question
     | '~' child=expr                             # Complementation

     | child=expr '[' (l=NUMBER)? ':' (u=NUMBER)? ']' # Restriction

     | left=expr ';' right=expr                   # Concatenation
     | left=expr '|' right=expr                   # Union
     | left=expr '&' right=expr                   # Intersection
     | left=expr '/' right=expr                   # Difference

     | '<' relation=('A' | 'B' | 'E') (inverse='i')? '>' child=expr     # Diamond
     | '[' relation=('A' | 'B' | 'E') (inverse='i')? ']' child=expr     # Box

     | '(' child=expr ')'                         # Grouping    
     ;


idlist : param=IDENTIFIER (',' param=IDENTIFIER)*;


IDENTIFIER : [_a-zA-Z][_a-zA-Z0-9]*;

LETTER : [_a-zA-Z];

NUMBER: DIGIT | (DIGIT_NOT_ZERO DIGIT+);

WS         : [ \r\n\t]+ -> channel (HIDDEN);

fragment DIGIT: ('0'..'9');
fragment DIGIT_NOT_ZERO: ('1'..'9');
