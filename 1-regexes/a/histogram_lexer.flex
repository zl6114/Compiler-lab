%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */

#include <string>
#include "histogram.hpp"


/* End the embedded code section. */
%}


%%

[0-9]+         { fprintf(stderr, "Number\n"); 
				yylval.numberValue = atoi(yytext)
		/* TODO: get value out of yytext and into yylval.number */ ;  
				return Number; }

[a-z][A-Z]+         { fprintf(stderr, "Word\n"); 
			std::string s = strdup(yytext); 
			yylval.wordValue = &s
		/*TODO: get value out of yytext and into yylval.wordValue */;  
			return Word; }

\n              { fprintf(stderr, "Newline\n", *yytext); }


%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
