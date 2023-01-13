
import urllib.request
import os
import zipfile
import shutil




print("setting the working directory")
os.chdir(os.path.dirname(os.path.abspath(__file__)))


print("extracting windows username")
username = os.getlogin()


print("setting the path to the plugins folder\n")

#program files (x86)/steam/steamapps/common/raft/mods
path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Raft', 'mods')





print("\nwiping ONLY the contents of plugins folder")
for filename in os.listdir(path):
    file_path = os.path.join(path, filename)
    try:
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)
    except Exception as e:
        print('Failed to delete %s. Reason: %s' % (file_path, e))


print(username)
if (username == "dalto"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/raft/mods.zip', 'mods.zip')
elif (username == "Cal"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/raft/mods.zip', 'mods.zip')
elif (username == "calli"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/raft/mods.zip', 'mods.zip')
else:
    print("downloading the latest version")
    urllib.request.urlretrieve('http://97.88.21.85:8000/raft/mods.zip', 'mods.zip')



print("extracting the mods.zip file to plugins folder\n")
with zipfile.ZipFile('mods.zip', 'r') as zip_ref:
    zip_ref.extractall(path)


print("deleting the mods.zip file")
os.remove('mods.zip')




print("cleaning up")
#subprocess.call('taskkill /f /im valheim_loader.exe', shell=True)



