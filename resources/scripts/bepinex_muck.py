import os
import zipfile

#C drive
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Muck')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Muck C drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Muck C drive steam directory doesn't exist.")

#D drive
path = os.path.join('D:', 'SteamLibrary', 'steamapps', 'common', 'Muck')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Muck D drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Muck D drive steam directory doesn't exist.")

#E drive
path = os.path.join('E:', 'SteamLibrary', 'steamapps', 'common', 'Muck')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Muck E drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Muck E drive steam directory doesn't exist.")

#F drive
path = os.path.join('F:', 'SteamLibrary', 'steamapps', 'common', 'Muck')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Muck F drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Muck F drive steam directory doesn't exist.")

#G drive
path = os.path.join('G:', 'SteamLibrary', 'steamapps', 'common', 'Muck')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Muck G drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Muck G drive steam directory doesn't exist.")

print("Completed install script! <3 daltonyx")
