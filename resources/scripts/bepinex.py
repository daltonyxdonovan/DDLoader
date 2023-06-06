import os
import zipfile
os.chdir(os.path.dirname(os.path.abspath(__file__)))

path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Havendock Demo')

print("extracting the bepinex.zip to plugins folder\n")
with zipfile.ZipFile('bepinex.zip', 'r') as zip_ref:
    zip_ref.extractall(path)
