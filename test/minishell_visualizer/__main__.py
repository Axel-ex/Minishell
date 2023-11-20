import os
from commands import *
from functions import *
from styles import *

def main():
    os.system('clear')
    print(MAIN_BANNER)
    print("Welcome to minishell-visualizer!")
    print('''this program allows you to to visually compare your minishell output with the bash output. Command are separated into VALID commands and INVALID commands, feel free to add your own test commands!''')

    ask_for_input(f"press {colors.GREEN}enter{colors.RESET} to start visualizing, {colors.RED}q+enter{colors.RESET} to quit\n")
    print(f"\n{colors.GREEN}{styles.BOLD}{VALID_BANNER}{colors.RESET}{styles.RESET}")
    execute_valid_cmds(valid_commands)
    ask_for_input(f"press {colors.GREEN}enter{colors.RESET} to keep visualizing, {colors.RED}q+enter{colors.RESET} to quit\n")
    print(f"\n\n{colors.RED}{INVALID_BANNER}{colors.RESET}")
    execute_invalid_cmds(invalid_commands)
    pass

if __name__ == "__main__":
    main()
