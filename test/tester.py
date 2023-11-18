import pexpect
from pexpect import fdpexpect
import subprocess
import os

# List of commands to execute
valid_commands = [
    "ls -l",        # Replace with your desired commands
    "pwd",
    "echo 'Hello, World!'"
]

invalid_commands = [
    "ce",
    "echo\"helloworld\"",
    "| cat"
]

class styles:
    BOLD = '\033[1m'
    RESET = '\033[0m'

class colors:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    RESET = '\033[0m'

def execute_commands(command_list):
    '''Runs elements of the command list in shell and bash and displays the output'''
    outputs = {}
    for cmd in command_list:
        # Print the command
        print(f"Command: {styles.BOLD}{cmd}{styles.RESET}")

        # Execute command in Bash shell
        bash_process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        bash_output, _ = bash_process.communicate()
        print(f"{colors.BLUE}Bash Output{colors.RESET}: {bash_output.strip()}")

        # Execute command in minishell using pexpect
        child = pexpect.spawn('../minishell')
        child.expect('minishell> ')
        child.sendline(cmd)
        child.expect('@minishell> ')
        c_output = child.before.decode()
        print(f"{colors.YELLOW}Minishell Output{colors.RESET}: {c_output.strip()}")
        print("=" * 40, "\n")

def execute_command_with_error(command_list: list, exec):
    prog = command_list.insert(0, exec)
    devNull = open(os.devnull, 'w')
    command = subprocess.Popen(prog, stdout=devNull,
                               stdin=subprocess.PIPE, stderr=subprocess.PIPE)

    child = fdpexpect.fdspawn(command.stderr)
    while True:
        try:
            output = child.readline().decode().strip()
            if (output):
                print(output)
        except pexpect.exceptions.TIMEOUT:
            return f"Command '{command_list}' timed out."
        
def error_cmd(command_list):
    for command in command_list:
        proc = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE)
        stderr = proc.communicate()
        print(stderr)
    
        
# Execute commands and capture their outputs
print(f"\n{colors.GREEN}VALID{colors.RESET}")
execute_commands(valid_commands)
print(f"\n\n{colors.RED}INVALID{colors.RESET}")
error_cmd(invalid_commands)
