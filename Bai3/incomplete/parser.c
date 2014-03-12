/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>

#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"

Token *currentToken;
Token *lookAhead;

void scan(void) {
  Token* tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType) {
  if (lookAhead->tokenType == tokenType) {
    printToken(lookAhead);
    scan();
  } else missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

void compileProgram(void) {
  assert("Parsing a Program ....");
  eat(KW_PROGRAM);
  eat(TK_IDENT);
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_PERIOD);
  assert("Program parsed!");
}

void compileBlock(void) {
  assert("Parsing a Block ....");
  if (lookAhead->tokenType == KW_CONST) {
    eat(KW_CONST);
    compileConstDecl();
    compileConstDecls();
    compileBlock2();
  } 
  else compileBlock2();
  assert("Block parsed!");
}

void compileBlock2(void) {
  if (lookAhead->tokenType == KW_TYPE) {
    eat(KW_TYPE);
    compileTypeDecl();
    compileTypeDecls();
    compileBlock3();
  } 
  else compileBlock3();
}

void compileBlock3(void) {
  if (lookAhead->tokenType == KW_VAR) {
    eat(KW_VAR);
    compileVarDecl();
    compileVarDecls();
    compileBlock4();
  } 
  else compileBlock4();
}

void compileBlock4(void) {
  compileSubDecls();
  compileBlock5();
}

void compileBlock5(void) {
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileConstDecls(void) {
  // TODO
  if(lookAhead->tokenType == TK_IDENT)
    {
      compileConstDecl();
      compileConstDecls();
    }
  //else 
  //error(ERR_INVALIDCONSTDECL, lookAhead->lineNo, lookAhead->colNo);
}

void compileConstDecl(void) {
  // TODO
  if(lookAhead->tokenType != TK_IDENT)
    error(ERR_INVALIDCONSTDECL, lookAhead->lineNo, lookAhead->colNo);
  eat(TK_IDENT);
  eat(SB_EQ);
  compileConstant();
  eat(SB_SEMICOLON);
}

void compileTypeDecls(void) {
  // TODO
  if(lookAhead->tokenType == TK_IDENT)
    {
      compileTypeDecl();
      compileTypeDecls();
    }
  //else 
  //error(ERR_INVALIDTYPEDECL, lookAhead->lineNo, lookAhead->colNo);
}

void compileTypeDecl(void) {
  // TODO
  if(lookAhead->tokenType != TK_IDENT)
    error(ERR_INVALIDTYPEDECL, lookAhead->lineNo, lookAhead->colNo);
  eat(TK_IDENT);
  eat(SB_EQ);
  compileType();
  eat(SB_SEMICOLON);
}

void compileVarDecls(void) {
  // TODO
  if(lookAhead->tokenType == TK_IDENT)
    {
      compileVarDecl();
      compileVarDecls();
    }
  //else 
  //error(ERR_INVALIDVARDECL, lookAhead->lineNo, lookAhead->colNo);
}

void compileVarDecl(void) {
  // TODO
  if(lookAhead->tokenType != TK_IDENT)
    error(ERR_INVALIDVARDECL, lookAhead->lineNo, lookAhead->colNo);
  eat(TK_IDENT);
  eat(SB_COLON);
  compileType();
  eat(SB_SEMICOLON);
}

void compileSubDecls(void) {
  assert("Parsing subtoutines ....");
  // TODO
  if(lookAhead->tokenType==KW_FUNCTION)
    {
      compileFuncDecl();
      compileSubDecls();
    }
  else if(lookAhead->tokenType==KW_PROCEDURE)
    {
      compileProcDecl();
      compileSubDecls();
    }
  //else 
  //error(ERR_INVALIDSUBDECL, lookAhead->lineNo, lookAhead->colNo);
  assert("Subtoutines parsed ....");
}

void compileFuncDecl(void) {
  assert("Parsing a function ....");
  // TODO
  eat(KW_FUNCTION);
  eat(TK_IDENT);
  compileParams();
  eat(SB_COLON);
  compileBasicType();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Function parsed ....");
}

void compileProcDecl(void) {
  assert("Parsing a procedure ....");
  // TODO
  eat(KW_PROCEDURE);
  eat(TK_IDENT);
  compileParams();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Procedure parsed ....");
}

void compileUnsignedConstant(void) {
  // TODO
  switch(lookAhead->tokenType){
  case TK_NUMBER:
    eat(TK_NUMBER);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    break;
  default:
    error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileConstant(void) {
  // TODO
  switch(lookAhead->tokenType){
  case SB_PLUS:
    eat(SB_PLUS);
    compileConstant2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileConstant2();
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    break;
  default:
    compileConstant2();
    break;
  }

}

void compileConstant2(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case TK_NUMBER:
    eat(TK_NUMBER);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    break;
  default:
    error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileType(void) {
  // TODO
  switch(lookAhead->tokenType){
  case KW_INTEGER:
    eat(KW_INTEGER);
    break;
  case KW_CHAR: 
    eat(KW_CHAR);
    break;
  case TK_IDENT: 
    eat(TK_IDENT);
    break;
  case KW_ARRAY:
    eat(KW_ARRAY);
    eat(SB_LSEL);
    eat(TK_NUMBER);
    eat(SB_RSEL);
    eat(KW_OF);
    compileType();
    break;
  default:
    error(ERR_INVALIDTYPE,lookAhead->lineNo,lookAhead->colNo);
    break;
  }
}

void compileBasicType(void) {
  // TODO
  switch(lookAhead->tokenType){
  case KW_INTEGER: 
    eat(KW_INTEGER);
    break;
  case KW_CHAR: 
    eat(KW_CHAR);
    break;
  default :
    error(ERR_INVALIDBASICTYPE,lookAhead->lineNo,lookAhead->colNo);
    break;
  }
}

void compileParams(void) {
  // TODO
  if(lookAhead->tokenType==SB_LPAR)
    {
      eat(SB_LPAR);
      compileParam();
      compileParams2();
      eat(SB_RPAR);
    }
}

void compileParams2(void) {
  // TODO
  if(lookAhead->tokenType==SB_SEMICOLON)
    {
      eat(SB_SEMICOLON);
      compileParam();
      compileParams2();
    }
}

void compileParam(void) {
  // TODO
  switch(lookAhead->tokenType){
  case TK_IDENT:
    eat(TK_IDENT);
    eat(SB_COLON);
    compileBasicType();
    break;
  case KW_VAR:
    eat(KW_VAR);
    eat(TK_IDENT);
    eat(SB_COLON);
    compileBasicType();
    break;
  default:error(ERR_INVALIDPARAM,lookAhead->lineNo,lookAhead->colNo);break;
  }
}

void compileStatements(void) {
  // TODO
  switch(lookAhead->tokenType){
  case TK_IDENT:
  case KW_CALL:
  case KW_BEGIN:
  case KW_IF:
  case KW_WHILE:
  case KW_FOR:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    compileStatement();
    break;
    //check sau
  default:
    break;
  }
  compileStatements2();
}

void compileStatements2(void) {
  // TODO
  if(lookAhead->tokenType==SB_SEMICOLON)
    {
      eat(SB_SEMICOLON);
      compileStatement();
      compileStatements2();
    }
  else if(lookAhead->tokenType!=KW_END)
    eat(SB_SEMICOLON);
}

void compileStatement(void) {
  switch (lookAhead->tokenType) {
  case TK_IDENT:
    compileAssignSt();
    break;
  case KW_CALL:
    compileCallSt();
    break;
  case KW_BEGIN:
    compileGroupSt();
    break;
  case KW_IF:
    compileIfSt();
    break;
  case KW_WHILE:
    compileWhileSt();
    break;
  case KW_FOR:
    compileForSt();
    break;
    // EmptySt needs to check FOLLOW tokens
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
    // Error occurs
  default:
    error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileAssignSt(void) {
  assert("Parsing an assign statement ....");
  // TODO
  eat(TK_IDENT);
  if(lookAhead->tokenType==SB_LSEL)	
    compileIndexes();	
  eat(SB_ASSIGN);
  compileExpression();
  assert("Assign statement parsed ....");
}

void compileCallSt(void) {
  assert("Parsing a call statement ....");
  // TODO
  eat(KW_CALL);
  eat(TK_IDENT);
  compileArguments();
  assert("Call statement parsed ....");
}

void compileGroupSt(void) {
  assert("Parsing a group statement ....");
  // TODO
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
  assert("Group statement parsed ....");
}

void compileIfSt(void) {
  assert("Parsing an if statement ....");
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE) 
    compileElseSt();
  assert("If statement parsed ....");
}

void compileElseSt(void) {
  eat(KW_ELSE);
  compileStatement();
}

void compileWhileSt(void) {
  assert("Parsing a while statement ....");
  // TODO
  eat(KW_WHILE);
  compileCondition();
  eat(KW_DO);
  compileStatement();
  //chu y check lai cho nay
  assert("While statement pased ....");
}

void compileForSt(void) {
  assert("Parsing a for statement ....");
  // TODO
  eat(KW_FOR);
  eat(TK_IDENT);
  eat(SB_ASSIGN);
  compileExpression();
  eat(KW_TO);
  compileExpression();
  eat(KW_DO);
  compileStatement();
  assert("For statement parsed ....");
}

void compileArguments(void) {
  // TODO
  switch(lookAhead->tokenType)
    {
    case SB_LPAR:      
      eat(SB_LPAR);
      compileExpression();
      compileArguments2();
      eat(SB_RPAR);
      break;
    // Check FOLLOW set 
    case SB_TIMES:
    case SB_SLASH:
    case SB_PLUS:
    case SB_MINUS:
    case KW_TO:
    case KW_DO:
    case SB_RPAR:
    case SB_COMMA:
    case SB_EQ:
    case SB_NEQ:
    case SB_LE:
    case SB_LT:
    case SB_GE:
    case SB_GT:
    case SB_RSEL:
    case SB_SEMICOLON:
    case KW_END:
    case KW_ELSE:
    case KW_THEN:
      break;
    default:
      error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
      break;
    }
}

void compileArguments2(void) {
  // TODO
  if(lookAhead->tokenType==SB_COMMA)
    {
      eat(SB_COMMA);
      compileExpression();
      compileArguments2();
    }
}

void compileCondition(void) {
  // TODO
  switch(lookAhead->tokenType)
    {
    case SB_PLUS:
    case SB_MINUS:
    case TK_IDENT:
    case SB_LPAR:
      compileExpression();
      compileCondition2();
      break;
    default:
      break;
    }
}

void compileCondition2(void) {
  // TODO
  switch (lookAhead->tokenType) 
    {
    case SB_EQ:
      eat(SB_EQ);
      break;
    case SB_NEQ:
      eat(SB_NEQ);
      break;
    case SB_LE:
      eat(SB_LE);
      break;
    case SB_LT:
      eat(SB_LT);
      break;
    case SB_GE:
      eat(SB_GE);
      break;
    case SB_GT:
      eat(SB_GT);
      break;
    default:
      error(ERR_INVALIDCOMPARATOR, lookAhead->lineNo, lookAhead->colNo);
    }
  compileExpression();
}

void compileExpression(void) {
  assert("Parsing an expression");
  // TODO
  switch (lookAhead->tokenType) 
    {
    case SB_PLUS:
      eat(SB_PLUS);
      break;
    case SB_MINUS:
      eat(SB_MINUS);
      break;
    default:
      break;
    }
  compileExpression2();
  assert("Expression parsed");
}

void compileExpression2(void) {
  // TODO
  compileTerm();
  compileExpression3();
}


void compileExpression3(void) {
  // TODO
  switch (lookAhead->tokenType) 
    {
    case SB_PLUS:
      eat(SB_PLUS);
      compileTerm();
      compileExpression3();
      break;
    case SB_MINUS:
      eat(SB_MINUS);
      compileTerm();
      compileExpression3();
      break;
      // check the FOLLOW set
    case KW_TO:
    case KW_DO:
    case SB_RPAR:
    case SB_COMMA:
    case SB_EQ:
    case SB_NEQ:
    case SB_LE:
    case SB_LT:
    case SB_GE:
    case SB_GT:
    case SB_RSEL:
    case SB_SEMICOLON:
    case KW_END:
    case KW_ELSE:
    case KW_THEN:
 
      break;
    default:
      error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
      break;
    }
}

void compileTerm(void) {
  // TODO
  compileFactor();
  compileTerm2();
}

void compileTerm2(void) {
  // TODO
  switch (lookAhead->tokenType) 
    {
    case SB_TIMES:
      eat(SB_TIMES);
      compileFactor();
      compileTerm2();
      break;
    case SB_SLASH:
      eat(SB_SLASH);
      compileFactor();
      compileTerm2();
      break;
    // check the FOLLOW set
    case SB_PLUS:
    case SB_MINUS:
    case KW_TO:
    case KW_DO:
    case SB_RPAR:
    case SB_COMMA:
    case SB_EQ:
    case SB_NEQ:
    case SB_LE:
    case SB_LT:
    case SB_GE:
    case SB_GT:
    case SB_RSEL:
    case SB_SEMICOLON:
    case KW_END:
    case KW_ELSE:
    case KW_THEN:
      break;
    default:
      error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
      break;

    }
}

void compileFactor(void) {
  // TODO
  Token *tmp=lookAhead;
  //de chuyen tiep lookAhead o duoi
  switch(tmp->tokenType)
    {
    case TK_NUMBER:

    case TK_CHAR:
      compileUnsignedConstant();
      break;
    case SB_LPAR:
      eat(SB_LPAR);
      compileExpression();
      eat(SB_RPAR);
      break;
    case TK_IDENT:
      eat(TK_IDENT);
      if(lookAhead->tokenType==SB_LPAR)
	{
	  compileArguments();
	}
      else if(lookAhead->tokenType==SB_LSEL)
	{
	  compileIndexes();
	}
      //else
      //compileUnsignedConstant();      
      break;
    default:
      error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
      break;
    }
  //free(tmp);
}

void compileIndexes(void) {
  // TODO
  if(lookAhead->tokenType==SB_LSEL)
    {
      eat(SB_LSEL);
      compileExpression();
      eat(SB_RSEL);
      compileIndexes();
    }
}

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  currentToken = NULL;
  lookAhead = getValidToken();

  compileProgram();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;

}
