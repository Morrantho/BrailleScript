I64_I64: return;
I64_F64: node->value.f64 = ( F64 )node->value.i64; return;
I64_STR: return;

F64_I64: node->value.i64 = ( I64 )node->value.f64; return;
F64_F64: return;
F64_STR: return;

STR_I64: return;
STR_F64: return;
STR_STR: return;