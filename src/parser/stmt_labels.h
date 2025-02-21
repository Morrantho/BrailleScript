EXPR: return ParseExpr( parser, PREC_NONE );
IF: return ParseIf( parser );
FOR: return ParseFor( parser );
DO: return ParseDo( parser );
WHILE: return ParseWhile( parser );
ID: return ParseId( parser );