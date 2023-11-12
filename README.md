# Minishell
### init_exit
	* init.c		-> init of shell struct
	* free.c		-> proper free of the program
	* error.c		-> error related functions

### parsing: lexer (tokenization) and synthax analyzer
	* lexer.c		-> function related to tokenization (get_token)
	* parser_util.c	-> subfunctions useful to tokenize and parse

###	execution: execution of commands

### builtins: our built-in functions