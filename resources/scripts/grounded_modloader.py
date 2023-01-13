
import urllib.request
import os
import zipfile
import shutil




print("setting the working directory")
os.chdir(os.path.dirname(os.path.abspath(__file__)))


print("extracting windows username")
username = os.getlogin()


print("setting the path to the plugins folder\n")

#C:\Program Files (x86)\Steam\steamapps\common\Grounded\Maine\Content\Paks
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Grounded', 'Maine', 'Content', 'Paks')


#delete any file that is named either Hauling_P.pak, Hauling_P.ucas, or Hauling_P.utoc
print("deleting any old files")
for file in os.listdir(path):
    if file.startswith("Hauling_P"):
        os.remove(os.path.join(path, file))



print(username)
if (username == "dalto"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/grounded/mods.zip', 'mods.zip')
elif (username == "Cal"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/grounded/mods.zip', 'mods.zip')
elif (username == "calli"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/grounded/mods.zip', 'mods.zip')
else:
    print("downloading the latest version")
    urllib.request.urlretrieve('http://97.88.21.85:8000/grounded/mods.zip', 'mods.zip')



print("extracting the mods.zip file to plugins folder\n")
with zipfile.ZipFile('mods.zip', 'r') as zip_ref:
    zip_ref.extractall(path)


print("deleting the mods.zip file")
os.remove('mods.zip')



print("setting the path to the Win64 folder\n")

#C:\Program Files (x86)\Steam\steamapps\common\Grounded\Maine\Content\Paks
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Grounded', 'Maine', 'Binaries', 'Win64')

if (username == "dalto"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/grounded/ue4ss.zip', 'ue4ss.zip')
elif (username == "Cal"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/grounded/ue4ss.zip', 'ue4ss.zip')
elif (username == "calli"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/grounded/ue4ss.zip', 'ue4ss.zip')
else:
    print("downloading the latest version")
    urllib.request.urlretrieve('http://97.88.21.85:8000/grounded/ue4ss.zip', 'ue4ss.zip')




print("extracting the ue4ss.zip file to Win64 folder\n")
with zipfile.ZipFile('ue4ss.zip', 'r') as zip_ref:
    zip_ref.extractall(path)


print("deleting the ue4ss.zip file")
os.remove('ue4ss.zip')




print("cleaning up")
#subprocess.call('taskkill /f /im valheim_loader.exe', shell=True)



