import os
import shutil
import zipfile

#C drive
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Hollow Knight', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Hollow Knight C drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Hollow Knight C drive steam directory doesn't exist.")

#D drive
path = os.path.join('D:', 'SteamLibrary', 'steamapps', 'common', 'Hollow Knight', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Hollow Knight D drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Hollow Knight D drive steam directory doesn't exist.")

#E drive
path = os.path.join('E:', 'SteamLibrary', 'steamapps', 'common', 'Hollow Knight', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Hollow Knight E drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Hollow Knight E drive steam directory doesn't exist.")

#F drive
path = os.path.join('F:', 'SteamLibrary', 'steamapps', 'common', 'Hollow Knight', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Hollow Knight F drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Hollow Knight F drive steam directory doesn't exist.")

#G drive
path = os.path.join('G:', 'SteamLibrary', 'steamapps', 'common', 'Hollow Knight', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Hollow Knight G drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Hollow Knight G drive steam directory doesn't exist.")

print("Completed uninstall script! <3 daltonyx")
