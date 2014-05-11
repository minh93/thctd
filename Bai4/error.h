/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __ERROR_H__
#define __ERROR_H__
#include "token.h"

typedef enum {
  ERR_END_OF_COMMENT,
  ERR_IDENT_TOO_LONG,
  ERR_INVALID_CONSTANT_CHAR,
  ERR_INVALID_SYMBOL,
  ERR_INVALID_IDENT,
  ERR_INVALID_CONSTANT,
  ERR_INVALID_TYPE,
  ERR_INVALID_BASICTYPE,
  ERR_INVALID_VARIABLE,
  ERR_INVALID_FUNCTION,
  ERR_INVALID_PROCEDURE,
  ERR_INVALID_PARAMETER,
  ERR_INVALID_STATEMENT,
  ERR_INVALID_COMPARATOR,
  ERR_INVALID_EXPRESSION,
  ERR_INVALID_TERM,
  ERR_INVALID_FACTOR,
  ERR_INVALID_LVALUE,
  ERR_INVALID_ARGUMENTS,
  ERR_UNDECLARED_IDENT,
  ERR_UNDECLARED_CONSTANT,
  ERR_UNDECLARED_INT_CONSTANT,
  ERR_UNDECLARED_TYPE,
  ERR_UNDECLARED_VARIABLE,
  ERR_UNDECLARED_FUNCTION,
  ERR_UNDECLARED_PROCEDURE,
  ERR_DUPLICATE_IDENT,
  ERR_TYPE_INCONSISTENCY,
  ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY
} ErrorCode;


#define ERM_END_OF_COMMENT "End of comment expected!"
#define ERM_IDENT_TOO_LONG "Identification too long!"
#define ERM_INVALID_CHAR_CONSTANT "Invalid const char!"
#define ERM_INVALID_SYMBOL "Invalid symbol!"
#define ERM_INVALID_CONSTANT "Invalid constant!"
#define ERM_INVALID_TYPE "Invalid type!"
#define ERM_INVALID_BASIC_TYPE "Invalid basic type!"
#define ERM_INVALID_PARAM "Invalid parameter!"
#define ERM_INVALID_STATEMENT "Invalid statement!"
#define ERM_INVALID_ARGUMENTS "Invalid arguments!"
#define ERM_INVALID_COMPARATOR "Invalid comparator!"
#define ERM_INVALID_EXPRESSION "Invalid expression!"
#define ERR_INVALID_TERM "Invalid term"
#define ERR_INVALID_FACTOR "Invalid factor"
#define ERR_INVALID_LVALUE "Invalid LValue"
#define ERR_INVALID_ARGUMENTS "Invalid arguments"
#define ERR_UNDECLARED_IDENT "Undeclared ident"
#define ERR_UNDECLARED_CONSTANT "Undeclared constant"
#define ERR_UNDECLARED_INT_CONSTANT "Undeclared int constant"
#define ERR_UNDECLARED_TYPE "Undeclared type"
#define ERR_UNDECLARED_VARIABLE "Undeclared variable"
#define ERR_UNDECLARED_FUNCTION "Undeclared function"
#define ERR_UNDECLARED_PROCEDURE "Undeclared procedure"
#define ERR_DUPLICATE_IDENT "Error duplicate ident"
#define ERR_TYPE_INCONSISTENCY "Error type inconsistency"
#define ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY "parameters arguments inconsistency"

void error(ErrorCode err, int lineNo, int colNo);
void missingToken(TokenType tokenType, int lineNo, int colNo);
void assert(char *msg);

#endif
