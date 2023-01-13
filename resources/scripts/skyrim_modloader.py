
import urllib.request
import os
import zipfile
import shutil




print("setting the working directory")
os.chdir(os.path.dirname(os.path.abspath(__file__)))


print("extracting windows username")
username = os.getlogin()


print("setting the path to the plugins folder\n")

#program files (x86)/steam/steamapps/common/Skyrim Special Edition/Data/
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Skyrim Special Edition', 'Data')








print(username)
if (username == "dalto"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/skyrim/mods.zip', 'mods.zip')
elif (username == "Cal"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/skyrim/mods.zip', 'mods.zip')
elif (username == "calli"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/skyrim/mods.zip', 'mods.zip')
else:
    print("downloading the latest version")
    urllib.request.urlretrieve('http://97.88.21.85:8000/skyrim/mods.zip', 'mods.zip')



print("extracting the mods.zip file to plugins folder\n")
with zipfile.ZipFile('mods.zip', 'r') as zip_ref:
    zip_ref.extractall(path)


print("deleting the mods.zip file")
os.remove('mods.zip')




print("cleaning up")





