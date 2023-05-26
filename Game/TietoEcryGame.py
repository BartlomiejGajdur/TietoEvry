import os
import platform
import stat
import sys
import subprocess

def set_executable_permissions(file_path):
    current_os = platform.system()  # Sprawdzenie bieżącego systemu operacyjnego

    if current_os == 'Linux':
        os.chmod(file_path, stat.S_IRWXU)  # Ustawienie praw wykonania dla właściciela (użytkownika) na Linuxie
    elif current_os == 'Windows':
        # Dodaj kod ustawiania praw wykonania dla pliku na Windowsie (jeśli jest potrzebny)
        pass
    else:
        print("Nieobsługiwany system operacyjny.")

def run_mediator(file1, file2, file3,file4):
    program_name = "Gra.exe"  # Nazwa programu C++
    build_folder = "build"  # Nazwa folderu, w którym znajduje się skompilowany program C++

    # Ścieżka do programu C++
    program_path = os.path.join(build_folder, program_name)

    # Sprawdź czy plik programu istnieje
    if os.path.exists(program_path):
        # Uruchom program C++ jako proces
        subprocess.call([program_path, file1, file2, file3, file4])
    else:
        print("Program C++ nie został znaleziony.")



if __name__ == "__main__":
    # Ustawienie praw wykonania dla pliku mediatora
    script_path = os.path.realpath(__file__)  # Pobranie pełnej ścieżki do skryptu mediatora

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
    run_mediator(arg1, arg2, arg3, '5')

