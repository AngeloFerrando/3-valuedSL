grammar StrategyLogic;

slExpr : ('!' | 'not') child=slExpr                                  # Negation
     //temporal operators
     | ('next' | 'X') child=slExpr                                   # Next
     | ('eventually' | 'F') child=slExpr                             # Eventually
     | ('always' | 'G') child=slExpr                                 # Always
     | left=slExpr ('until' | 'U') right=slExpr                      # Until
     | left=slExpr ('release' | 'R') right=slExpr                    # Release
     // boolean operators
     | left=slExpr ('&&' | 'and') right=slExpr                       # Conjunction
     | left=slExpr ('||' | 'or') right=slExpr                        # Disjunction
     | left=slExpr ('->' | 'implies') right=slExpr                   # Implies
     // strategic operators
     | '<<' var=ATOM '>>' child=slExpr                               # Existential
     | '[[' var=ATOM ']]' child=slExpr                               # Universal
     | '(' agent=ATOM ',' var=ATOM ')' child=slExpr                  # Binding
     | '(' slExpr ')'                                                # Grouping
     | child=atomExpr                                                # Evaluation
     ;

atomExpr : ATOM;

ATOM : [_a-zA-Z][_a-zA-Z0-9]*;

WS        : [ \t\r\n\u000C]+ -> skip;

