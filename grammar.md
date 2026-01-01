expression -> literal | unary_expression | binary_expression | grouping_expression ;

literal -> NUMBER | STRING | "true" | "false" | "nil" ;

unary_expression -> ("-" | "!") expression ;

binary_expression -> expression operator expression ;

grouping_expression ->  "(" expression ")" ;

operator -> "==" | "!=" | "<" | "<=" | ">" | ">="
               | "+"  | "-"  | "*" | "/" ;
