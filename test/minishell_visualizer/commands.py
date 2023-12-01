# List of commands to execute
valid_commands = [
    "ls | ls | ls | ls | ls",        # Replace with your desired commands
    "pwd",
	"echo $USER $PWD",
	"ls | grep minishell | wc",
	"cat README.md >> outfile | cat outfile | wc -l"
]

invalid_commands = [
    "ce",
    "echo\"helloworld\"",
    "| cat",
	"echo $GUIOK"
]
