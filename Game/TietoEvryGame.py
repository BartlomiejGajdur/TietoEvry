import os
import platform
import stat
import subprocess
import sys

default_time_limit = 5  # Default time limit for the mediator

def set_executable_permissions(file_path):
    current_os = platform.system()  # Check the current operating system

    if current_os == 'Linux':
        os.chmod(file_path, stat.S_IRWXU)  # Set executable permissions for the owner (user) on Linux
    elif current_os == 'Windows':
        # Add code for setting executable permissions for the file on Windows if needed
        pass
    else:
        print("Unsupported operating system.")

def run_mediator(file1, file2, file3, file4):
    program_name = "Gra.exe"  # C++ program name
    build_folder = "build"  # Folder where the compiled C++ program is located

    # Path to the C++ program
    program_path = os.path.join(build_folder, program_name)

    # Check if the program file exists
    if os.path.exists(program_path):
        # Run the C++ program as a subprocess
        subprocess.call([program_path, file1, file2, file3, file4])
    else:
        print("C++ program not found.")

if __name__ == "__main__":
    # Set executable permissions for the mediator script
    script_path = os.path.realpath(__file__)  # Get the full path to the mediator script

    if len(sys.argv) < 4:
        print("Please provide at least three text arguments.")
        sys.exit(1)

    arg1 = sys.argv[1]
    arg2 = sys.argv[2]
    arg3 = sys.argv[3]

    if len(sys.argv) >= 5:
        try:
            arg4 = int(sys.argv[4])
        except ValueError:
            print("The fourth argument must be an integer.")
            sys.exit(1)
        run_mediator(arg1, arg2, arg3, str(arg4))
    else:
        run_mediator(arg1, arg2, arg3, str(default_time_limit))
