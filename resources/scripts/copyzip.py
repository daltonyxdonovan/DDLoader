#a script that takes two arguments, the source zip and the destination folder to extract the zip to
#example: python resources/scripts/copyzip.py resources/scripts/havendock/ConsoleCommands.zip C:\Program Files (x86)\Steam\steamapps\common\Havendock

import os
import zipfile
import sys

os.chdir(os.path.dirname(os.path.abspath(__file__)))

source = sys.argv[1]
destination = sys.argv[2]

#if there is a third argument, it is the game name as a string
game_name = None
if len(sys.argv) > 3:
    game_name = sys.argv[3]
if game_name == "Hollow":
    game_name = "Hollow Knight"
elif game_name == "Regions":
    game_name = "Regions Of Ruin"
elif game_name == "HavendockD":
    game_name = "Havendock Demo"
    
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', game_name, 'BepInEx', 'plugins')

if destination == "-C":
    destination = path

#make source folder a full path if it isn't already
if not os.path.isabs(source):
    source = os.path.join(os.getcwd(), source)

print("extracting '" + source + "' to '" + destination + "'\n")

with zipfile.ZipFile(source, 'r') as zip_ref:
    zip_ref.extractall(destination)

