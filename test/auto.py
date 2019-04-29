import time
import os
import subprocess

COR_DIR = "champs/cor/"

os.system("./auto/auto_compile")
os.system("./auto/auto_config")

max_children = int(subprocess.getoutput("cat auto/auto.conf | grep NUM_PROCESSES | cut -d '=' -f 2"))

dir = os.listdir(COR_DIR)

total = 0
for i in range(0, len(dir)):
    for j in range(i + 1, len(dir)):
        total += 1

os.system("echo " + str(total) + " > ./auto/total.out")

num_children = 0
for i in range(0, len(dir)):
    for j in range(i + 1, len(dir)):
        while num_children >= max_children:
            time.sleep(10)
            num_children = int(subprocess.getoutput("ps -ef | grep auto_corewar | grep -v grep | wc -l"))
        os.system("./auto/auto_corewar " + COR_DIR + dir[i] + " " + COR_DIR + dir[j] + " &")
        num_children = int(subprocess.getoutput("ps -ef | grep auto_corewar | grep -v grep | wc -l"))
