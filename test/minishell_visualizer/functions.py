import pexpect
import subprocess
from styles import *

EXEC_DIR = '../../minishell'
PROMPT   = '@minishell> ' 

def execute_valid_cmds(command_list):
    '''Runs elements of the command list in shell and bash and displays the output'''
    for cmd in command_list:
        # Print the command
        print(f"Command: {styles.BOLD}{cmd}{styles.RESET}")

        # Execute command in Bash shell
        bash_process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, 
                                        stderr=subprocess.PIPE, text=True)
        bash_output,_ = bash_process.communicate()
        print(f"{colors.BLUE}Bash Output{colors.RESET}: {bash_output.strip()}")

        # Execute command in minishell using pexpect
        child = pexpect.spawn(EXEC_DIR)
        child.expect(PROMPT)
        child.sendline(cmd)
        child.expect(PROMPT)
        c_output = child.before.decode().strip()
        minishell_out = c_output.split('\r\n')
        minishell_out = minishell_out[1:]
        print(f"{colors.YELLOW}Minishell Output{colors.RESET}: ", end="")
        for line in minishell_out:
            print(f"{line}")
        print("=" * 40, "\n")


def execute_invalid_cmds(command_list):
    for cmd in command_list:
        print(f"Command: {styles.BOLD}{cmd}{styles.RESET}")

        #bash
        proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE)
        stderr = proc.communicate()
        print(f"{colors.BLUE}Bash Output{colors.RESET}: ")
        print(str(stderr[1]).strip("b\'n\\"))

        # Execute command in minishell using pexpect
        child = pexpect.spawn(EXEC_DIR)
        child.expect(PROMPT)
        child.sendline(cmd)
        index = child.expect([pexpect.TIMEOUT, pexpect.EOF, PROMPT])
        if index == 0 or index == 1:
            print(f"{colors.RED}Minishell Error{colors.RESET}: Timeout/EOF occurred")
        else:
            c_output = child.before.decode().strip()
            minishell_out = c_output.split('\r\n')
            minishell_out = minishell_out[1:]
            print(f"{colors.YELLOW}Minishell Output{colors.RESET}: ")
            for line in minishell_out:
                print(f"{line}")
        print("=" * 40, "\n")


def ask_for_input(message):
    user_input = input(message)
    while (user_input):
        if (user_input == "q"):
            exit()
        user_input = input("enter a valid key\n")