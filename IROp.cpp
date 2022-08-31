
#include "IROp.h"

string FormatOp(string op, bool isSigned)
{
    if (op=="+")
        return "add";
    if (op == "-")
        return "sub";
    if (op == "*")
        return "mul";
    if (op == "/")
        return "div";
    if (op == "%")
        return "mod";
    if (op == "&")
        return "and";
    if (op == "|")
        return "and";
    if (op == "^")
        return "xor";
    if (op == "<<")
        return "bit_lshift";
    if (op == ">>")
        return "bit_rshift";
    if (op == "==")
        return "eq";
    if (op == "!=")
        return "neq";
    if (op == "<")
        return "slt";
    if (op == "<=")
        return "slteq";
    if (op == ">")
        return "sgt";
    if (op == ">=")
        return "sgteq";

    assert(0 && "FormatOp Error");

    return "";
}
