#pragma once

#include "base.h"

//词牌类型
enum TokenType
{
    //文件结束
    tok_eof,
    //字符串
    tok_string,
    //数字
    tok_number,

    tok_kw_void,  //void
    tok_kw_char, //char
    tok_kw_short, //short
    tok_kw_int, //int
    tok_kw_long, //long
    tok_kw_struct,//struct
    tok_kw_union,//union
    tok_kw_enum, //enum
    tok_kw_static, //static
    tok_kw_extern, //extern
    tok_kw_const, //const
    tok_kw_signed, //signed
    tok_kw_unsigned, //unsigned

    tok_kw_if,  //if
    tok_kw_else, //else
    tok_kw_switch, //switch
    tok_kw_case, //case
    tok_kw_default, //default
    tok_kw_while, //while
    tok_kw_do, //do
    tok_kw_for, //for
    tok_kw_return, //return
    tok_kw_break, //break
    tok_kw_continue, //continue
    tok_kw_goto, //goto
    tok_kw_typedef, //typedef
    tok_kw_import, //import
    tok_kw_sizeof, //sizeof


    tok_op_plus, //+
    tok_op_plus_plus, //++
    tok_op_minus, //-
    tok_op_minus_minus, //--
    tok_op_mul, //*
    tok_op_div, // /
    tok_op_assign , // =
    tok_op_less, // <
    tok_op_greater, // >

	//(
	tok_l_parent,
	//)
	tok_r_parent,
	//{
	tok_l_brace,
	//}
	tok_r_brace,
	//,
	tok_sem,
	//;
	tok_comma,
	//[
	tok_l_square,
	//]
	tok_r_square,
	//.
	tok_period,
    //"
    tok_double_quotes,
    //%
    tok_percent_sign,

    //注释
    tok_comment,
	tok_unkonw
};

class Token
{
public:
    Token();
    Token(string str, TokenType tt);

    string getContext();

    TokenType getType();

private:
    //内容
    string context;
    TokenType type;
};


//是否是参数类型,判断是不是声明
bool isParameterType(TokenType type);

int getOpLevel(TokenType t);