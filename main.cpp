/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"

// Enumarated Type specifying all of the Tokens
enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}



// Class to hold the Token information
class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

  public:

  // Default to initialize to the ERROR TokenType
  Token()
  {
    type = ERROR;
    op = '$';
    val = -999;
  }

  // Initialize to a specific TokenType
  Token (TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a specific TokenType
  void setToType(TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a OPERATOR TokenType with specific operator value
  void setToOperator(char c)
  {
    type = OPERATOR;
    op = c;
    val = -999;
  }

  // Set to a VALUE TokenType with a specific numeric value
  void setToValue(int v)
  {
    type = VALUE;
    op = '$';
    val = v;
  }

  // return true if the Current Token is of the given TokenType
  bool equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool equalsOperator(char c)
  {
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
  }

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char getOperator ()
  {
    if (type == OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
  }

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int getValue()
  {
    if (type == VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
  }
};


class TokenReader
{
  private:
     char inputline[300];  // this assumes that all input lines are 300 characters or less in length
     bool needline;
     int pos;


  public:

  // initialize the TokenReader class to read from Standard Input
  TokenReader()
  {
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
  }

  // Force the next getNextToken to read in a line of input
  void clearToEoln()
  {
    needline = true;
  }

  // Return the next Token from the input line
  Token getNextToken()
  {
    char* endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets ( inputline, 300, stdin);

      if (endCheck == NULL )
      {
        printf ("Error in reading");
        Token t(EOFILE);
        return t;
      }

      for (int i = 0 ; i < strlen(inputline) ; i++)
          if ('\n' == inputline[i])
              inputline[i] = ' ';
      strcat (inputline , " ");    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while ( pos < strlen(inputline) && isspace(inputline[pos]) )
    {
      pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos]; pos++;

    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return Token (QUIT);
    }

    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return Token (HELP);
    }

    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t;
      t.setToOperator( ch );
      return t;
    }

    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
      int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
      ch = inputline[pos]; pos++;
      while (isdigit(ch))
      {
        number = number * 10 + int (ch) - int('0');
        ch = inputline[pos]; pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t;
      t.setToValue( number );
      return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token (ERROR);
  }

};

    /**************************************************************/
    /*                                                            */
    /*  The Code above this point should NOT need to be modified  */
    /*  for this program.   If you feel you must modify the code  */
    /*  below this point, you are probably trying to solve a      */
    /*  more difficult problem that you are being asked to solve  */
    /*                                                            */
    /**************************************************************/


void processExpression (Token inputToken, TokenReader *tr, int &debug);

int popAndEvaluate(NumStack** Nums, OpStack** Ops, int &debug
);

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    int debug = 0;
    printf("Do you want to run program with Debug Mode (1 for yes/ 0 for no)\n");
    scanf("%d", &debug);
    


    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       //printf("Entering processExpression function\n");
       processExpression(inputToken, &tr, debug);

      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}

int popAndEvaluate(NumStack** Nums, OpStack** Ops, int &debug){
  int result = 0;
  int v1 = top(*Nums);
  pop(&Nums);
  (**Nums).printArr();
  int v2 = top(*Nums);
  pop(&Nums);
  char op1 = top(*Ops);
  pop(&Ops);
  if(debug == 1){
    printf("Value1 is: %d\n", v1);
    printf("Value2 is: %d\n", v2);
    printf("Operator is: %c\n", op1);
  }
  if(op1 == '*'){
    if(debug == 1)
    printf("Multiplying: \n");
    result = (v1 * v2);
  }
  if(op1 == '/'){
     if(debug == 1)
     printf("Dividing: \n");
     result = (v2 / v1);
  }
  if(op1 == '-'){
     if(debug == 1)
     printf("Subtracting: \n");
     result = (v2 - v1);
  }
  if(op1 == '+'){
     if(debug == 1)
     printf("Adding: \n");
     result = (v1) + (v2);
  }
  return result;
}

void processExpression (Token inputToken, TokenReader *tr, int &debug)
{
 /**********************************************/
 /* Declare both stack pointers here      */
 NumStack* nums = new NumStack;
 OpStack* ops = new OpStack;

 clear(&nums);
 clear(&ops);

 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {

     //printf("Inside the while loop\n");
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       if(debug == 1){
          printf ("Val: %d, \n", inputToken.getValue() );
       }
       push(&nums, inputToken.getValue());    
      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      { 
        if(debug == 1){
            printf ("Operator: %c, \n", inputToken.getOperator() );
        }
        if(inputToken.getOperator() == '('){
          push(&ops, inputToken.getOperator());
        }


        if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-'){
          //printf("Entered part 2 operator\n");
            while(!isEmpty(ops) && (top(ops) == '+' || top(ops) == '-' || top(ops) == '*' || top(ops) == '/')){
              //pop and evaluate function calculation
              int result = popAndEvaluate(&nums, &ops, debug);
              push(&nums, result);
              //printf("Had to pop and Evaluate\n");
            }
            push(&ops, inputToken.getOperator());
            
        }


        if(inputToken.getOperator() == '*' || inputToken.getOperator() == '/'){
            //printf("Entered part 3 operator\n");
            while(!isEmpty(ops) && (top(ops) == '*' || top(ops) == '/')){
              //pop and evaluate function calculation
              int result = popAndEvaluate(&nums, &ops, debug);
              push(&nums, result);
            }
            push(&ops, inputToken.getOperator());
        }


        else if(inputToken.getOperator() == ')'){
          //printf("Entered part 4 operator\n");
            while(!isEmpty(ops) && top(ops) != '('){
              //pop and evaluate function calculation
              int result = popAndEvaluate(&nums, &ops, debug);
              push(&nums, result);
            }
            if(isEmpty(ops)){
                printf("Error- Invalid expression because there is no closing parenthesis for an opening one\n");
            }
            else{
              popLastOperator(&ops);
            }
            
        }
        

      }
      if(debug == 1){
          printf("the numbers stack is ");
          (*nums).printArr();
          printf("the operations stack is: ");
          (*ops).printArr();
      }

    /* get next token from input */
     inputToken = tr->getNextToken ();
   }


 /* The expression has reached its end */
 while(!isEmpty(ops)){
   //pop and evaluate function
   int result = popAndEvaluate(&nums, &ops, debug);
   push(&nums, result);
 }
 
 printf("The mathematical result of your expression is %d \n", nums->arr[nums->inUse - 1]);

 if(!isEmpty(ops)){
   printf("Error- Invalid expression because there is an extra operator\n");
 }

 printf ("\n");
}

