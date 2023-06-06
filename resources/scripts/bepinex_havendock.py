import os
import zipfile

#C drive
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Havendock Demo')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock Demo C drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock Demo C drive steam directory doesn't exist.")

path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Havendock')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock C drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock C drive steam directory doesn't exist.")

#D drive
path = os.path.join('D:', 'SteamLibrary', 'steamapps', 'common', 'Havendock Demo')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock Demo D drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock Demo D drive steam directory doesn't exist.")

path = os.path.join('D:', 'SteamLibrary', 'steamapps', 'common', 'Havendock')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock D drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock D drive steam directory doesn't exist.")

#E drive
path = os.path.join('E:', 'SteamLibrary', 'steamapps', 'common', 'Havendock Demo')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock Demo E drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock Demo E drive steam directory doesn't exist.")

path = os.path.join('E:', 'SteamLibrary', 'steamapps', 'common', 'Havendock')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock E drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock E drive steam directory doesn't exist.")

#F drive
path = os.path.join('F:', 'SteamLibrary', 'steamapps', 'common', 'Havendock Demo')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock Demo F drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock Demo F drive steam directory doesn't exist.")

path = os.path.join('F:', 'SteamLibrary', 'steamapps', 'common', 'Havendock')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock F drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock F drive steam directory doesn't exist.")

#G drive
path = os.path.join('G:', 'SteamLibrary', 'steamapps', 'common', 'Havendock Demo')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock Demo G drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock Demo G drive steam directory doesn't exist.")

path = os.path.join('G:', 'SteamLibrary', 'steamapps', 'common', 'Havendock')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex6_64_mono.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Havendock G drive steam directory found! Installing bepinex6_64_mono...")
else:
    print("The Havendock G drive steam directory doesn't exist.")

print("Completed install script! <3 daltonyx")
