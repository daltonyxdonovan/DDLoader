#start by importing the necessary modules for downloading from the web
import urllib.request
import os
import zipfile
import shutil
import sys
import subprocess
import time
import json

#get arguments
args = sys.argv



#grab username and save in string
username = os.getlogin()


if (username == "dalto"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/loader/loader.zip', 'loader.zip')
elif (username == "Cal"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/loader/loader.zip', 'loader.zip')
elif (username == "calli"):
    print("downloading the latest version")
    urllib.request.urlretrieve('http://192.168.1.48:8000/loader/loader.zip', 'loader.zip')
else:
    print("downloading the latest version")
    urllib.request.urlretrieve('http://97.88.21.85:8000/loader/loader.zip', 'loader.zip')


#extract all files to the directory that is args
with zipfile.ZipFile('loader.zip', 'r') as zip_ref:
    for file in zip_ref.namelist():
        if file != "update.py":
            if file != "updater.exe":
                zip_ref.extract(file)   
    
    

        
            
print("deleting the loader.zip file")
os.remove('loader.zip')
#remove loader folder
#shutil.rmtree('loader')

print("restarting valheim_loader.exe")
subprocess.Popen('valheim_loader.exe', shell=True)


