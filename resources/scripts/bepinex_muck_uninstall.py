import os
import shutil
import zipfile

#C drive
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Muck', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Muck C drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Muck C drive steam directory doesn't exist.")

#D drive
path = os.path.join('D:', 'SteamLibrary', 'steamapps', 'common', 'Muck', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Muck D drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Muck D drive steam directory doesn't exist.")

#E drive
path = os.path.join('E:', 'SteamLibrary', 'steamapps', 'common', 'Muck', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Muck E drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Muck E drive steam directory doesn't exist.")

#F drive
path = os.path.join('F:', 'SteamLibrary', 'steamapps', 'common', 'Muck', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Muck F drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Muck F drive steam directory doesn't exist.")

#G drive
path = os.path.join('G:', 'SteamLibrary', 'steamapps', 'common', 'Muck', 'BepInEx')
if os.path.exists(path):
    shutil.rmtree(path)
    print("Muck G drive steam directory found! Removing bepinex6_64_mono...")
else:
    print("The Muck G drive steam directory doesn't exist.")

print("Completed uninstall script! <3 daltonyx")
