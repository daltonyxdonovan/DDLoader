import os
import zipfile
print("thanks for using the loader!\n    <3 daltonyx")
print("setting the working directory")
os.chdir(os.path.dirname(os.path.abspath(__file__)))

print("setting the path to the plugins folder\n")

#program files (x86)/steam/steamapps/common/Skyrim Special Edition/Data/
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Havendock Demo')



print("extracting the bepinex.zip to plugins folder\n")
with zipfile.ZipFile('bepinex.zip', 'r') as zip_ref:
    zip_ref.extractall(path)
