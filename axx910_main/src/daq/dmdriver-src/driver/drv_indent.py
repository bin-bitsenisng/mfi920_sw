"""Run indent on all driver files """
from pathlib import Path
import subprocess
import os
import argparse

indent_cmd_str = 'indent -kr --no-tabs --ignore-profile -l0'
my_dir = Path(__file__).parent

def file_filter(f):
    return (f.endswith('.h') or f.endswith('.c')) and f != 'ADAR690x.h'

def file_finder():
    for dir_name, dirs, files in os.walk(my_dir):
        for f in files:
            if file_filter(f):
                yield os.path.join(dir_name, f)

def run_indent(files):
    cmd = indent_cmd_str + ' ' + ' '.join(files)
    subprocess.run(cmd, shell=True, check=True)

if __name__ == '__main__':
    files = file_finder()
    run_indent(files)

