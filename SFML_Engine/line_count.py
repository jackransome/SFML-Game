import os
import glob

def count_lines_in_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        return sum(1 for _ in file)

def count_lines_in_folder(folder_path):
    os.chdir(folder_path)
    file_extensions = ['*.h', '*.cpp']
    total_lines = 0

    for file_ext in file_extensions:
        for file_path in glob.glob('**/' + file_ext, recursive=True):
            lines = count_lines_in_file(file_path)
            print(f'{file_path}: {lines} lines')
            total_lines += lines

    print(f'Total lines in .h and .cpp files: {total_lines}')

# Get the folder where the script is located
folder_path = os.path.dirname(os.path.abspath(__file__))
count_lines_in_folder(folder_path)