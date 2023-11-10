#include "../../includes/minishell.h"

// tested with CMD type. needs further testing will do it when OTHER is implemented

int syntax_checker(t_token *token)
{
    t_token *temp;
    t_token *next;

    temp = token;

    //check the type of first node if not command return error.
    if(temp->type != OTHER) //it will be replace by OTHER)
        print_error("Sintax Error : First token should be a command",20);
    while(temp && temp->next)
    {
        next = temp->next;
        //if the current is not Other meas the following has to be Other. so if bot are not it returns and error
        if(temp->type != OTHER && next->type != OTHER) //it will be replace by OTHER
            print_error("Syntax Error : unexpect sequence of tokens",20);
    temp = temp -> next;        
    }
    // if last token is separator return error.
    if(temp->type == PIPE ||temp -> type == REDIR_IN || temp ->type == REDIR_OUT )
        print_error("Sintax Error: Prompt should not be ended by a separator",20);  
    return (EXIT_SUCCESS);  
}
