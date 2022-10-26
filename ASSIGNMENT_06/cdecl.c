struct token 
{ 
  char type;
  char string[MAXTOKENLEN];
};

// holds tokens we read before reaching first identifier
struct token stack[MAXTOKENS];

int top = -1;

// holds the token just read
struct token;

enum string_class
{
  type,
  qualifier,
  identifier
} 

enum string_class classify_string(void);

void gettoken(void);

read_to_first_identifier();

deal_with_function_args();

deal_with_arrays();

deal_with_any_pointers();

deal_with_declarator();

int main()
{
  // read_to_first_identifier
  read_to_first_identifier();
  // deal_with_declarator
  deal_with_declarator();
  printf("\n");
  return 0;
}

enum string_class classify_string(void)
{
  // look at the current token and 
  char *token = this.string;
  // return a value of "type", "qualifier", or "identifier" in this.type
  if(!strcmp(token, "char"))
    return type;
  if(!strcmp(token, "unsigned"))
    return type;
  if(!strcmp(token, "signed"))
    return type;
  if(!strcmp(token, "int"))
    return type;
  if(!strcmp(token, "short"))
    return type;
  if(!strcmp(token, "long"))
    return type;
  if(!strcmp(token, "float"))
    return type;
  if(!strcmp(token, "double"))
    return type;
  if(!strcmp(token, "void"))
    return type;
  if(!strcmp(token, "struct"))
    return type;
  if(!strcmp(token, "union"))
    return type;
  if(!strcmp(token, "enum"))
    return type;
  if(!strcmp(token, "const"))
    return qualifier;
  if(!strcmp(token, "volatile"))
    return qualifier;
  if(!strcmp(token, "restrict"))
    return qualifier;
  return identifier;
}

void gettoken(void)
{
  // read the next token into this.string
  char *next_token = this.string;
  // if it is alphanumeric, classify_string
  if(isalnum(*next_token))
  {
    this.type = classify_string();
    return;
  }
  // else it must be a single character token
  // this.type = the token itself; terminate this.string with a nul
  this.type = *next_token;
  this.string[1] = '\0';
  return;
}

read_to_first_identifier()
{
  // gettoken and push it onto the stack until the first identifer is read
  gettoken();
  while(this.type != identifier) 
  {
    stack[++top] = this;
    gettoken(); 
  }
  // Print "identifier is", this.string
  printf("identifier is %s ", this.string);
  // gettoken
  gettoken();
}

deal_with_function_args()
{
  // read past closing ')' print out "function returning"
  while(this.type != ')')
  {
    gettoken();
  }
  gettoken();
  printf("function returning ");
}

deal_with_arrays()
{
  // while you've got "[size]" print it out and read past it
  while(this.type == '[')
  {
    printf("array ");
    gettoken();
    if(isdigit(*this.string))
    {
      printf("with size %s ", this.string);
      gettoken();
    }
    printf("of ");
    gettoken();
  }
}

deal_with_any_pointers()
{
  // while you've got "*" on the stack print "pointer to" and pop it
  while(stack[top].type == '*')
  {
    printf("pointer to ")
    stack[top--];
  }
}

deal_with_declarator()
{
  // if this.type is '[' deal_with_arrays
  if(this.type == '[')
    deal_with_arrays();
  // if this.type is '(' deal_with_function_args
  if(this.type == '(')
    deal_with_function_args();
  // deal_with_any_pointers
  deal_with_any_pointers();
  // while there's stuff on the stack
  while(top >= 0)
  {
  // if it's a '('
    if(stack[top].type == '(')
    {
  // pop it and gettoken; it should be the closing ')'
      stack[top--];
      gettoken();
  // deal_with_declarator
     deal_with_delcarator();
    }
  // else pop it and print it
    else
      printf("%s ", stack[top--].string);
  }
}
