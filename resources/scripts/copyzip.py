#a script that takes two arguments, the source zip and the destination folder to extract the zip to
#example: python resources/scripts/copyzip.py resources/scripts/havendock/ConsoleCommands.zip C:\Program Files (x86)\Steam\steamapps\common\Havendock

import os
import zipfile
import sys

os.chdir(os.path.dirname(os.path.abspath(__file__)))

source = sys.argv[1]
destination = sys.argv[2]

print("extracting '" + source + "' to '" + destination + "'\n")

with zipfile.ZipFile(source, 'r') as zip_ref:
    zip_ref.extractall(destination)

