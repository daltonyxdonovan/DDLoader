import os
import zipfile

#C drive
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Regions Of Ruin')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex5_86.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Regions Of Ruin C drive steam directory found! Installing bepinex5_86...")
else:
    print("The Regions Of Ruin C drive steam directory doesn't exist.")

#D drive
path = os.path.join('D:', 'SteamLibrary', 'steamapps', 'common', 'Regions Of Ruin')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex5_86.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Regions Of Ruin D drive steam directory found! Installing bepinex5_86...")
else:
    print("The Regions Of Ruin D drive steam directory doesn't exist.")

#E drive
path = os.path.join('E:', 'SteamLibrary', 'steamapps', 'common', 'Regions Of Ruin')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex5_86.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Regions Of Ruin E drive steam directory found! Installing bepinex5_86...")
else:
    print("The Regions Of Ruin E drive steam directory doesn't exist.")

#F drive
path = os.path.join('F:', 'SteamLibrary', 'steamapps', 'common', 'Regions Of Ruin')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex5_86.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Regions Of Ruin F drive steam directory found! Installing bepinex5_86...")
else:
    print("The Regions Of Ruin F drive steam directory doesn't exist.")

#G drive
path = os.path.join('G:', 'SteamLibrary', 'steamapps', 'common', 'Regions Of Ruin')
if os.path.exists(path):
    with zipfile.ZipFile('resources/scripts/bepinex/bepinex5_86.zip', 'r') as zip_ref:
        zip_ref.extractall(path)
    print("Regions Of Ruin G drive steam directory found! Installing bepinex5_86...")
else:
    print("The Regions Of Ruin G drive steam directory doesn't exist.")

print("Completed install script! <3 daltonyx")
