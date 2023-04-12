
import urllib.request
import os
import zipfile
import shutil




print("setting the working directory")
os.chdir(os.path.dirname(os.path.abspath(__file__)))


print("extracting windows username")
username = os.getlogin()


print("setting the path to the dinkum folder\n")

#program files (x86)/steam/steamapps/common/raft/mods
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Dinkum')








print(username)
if (username == "dalto"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/dinkum/bepinex.zip', 'bepinex.zip')
elif (username == "Cal"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/dinkum/bepinex.zip', 'bepinex.zip')
elif (username == "calli"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/dinkum/bepinex.zip', 'bepinex.zip')
else:
    print("downloading the latest version")
    urllib.request.urlretrieve('http://97.88.21.85:8000/dinkum/bepinex.zip', 'bepinex.zip')



print("extracting the mods.zip file to dinkum folder\n")
with zipfile.ZipFile('bepinex.zip', 'r') as zip_ref:
    zip_ref.extractall(path)


print("deleting the mods.zip file")
os.remove('bepinex.zip')




print("cleaning up")
#subprocess.call('taskkill /f /im valheim_loader.exe', shell=True)



