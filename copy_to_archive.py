import os
import datetime

def RunCommands(commands):
    for command in commands:
        print(command)
        os.system(command)

# Start Here
strings =   "del Debug\\*.* /q", \
            "del Debug\\TacticsVictory.tlog\\*.* /s /q", \
            "del *.sdf /s /q"

RunCommands(strings)

date = datetime.datetime.now()

name = 'Archiv\\TacticsVictory\\TacticsVictory' + date.strftime("_%Y_%m_%d_%H_%M_%S") + '.zip .'

strings =   "7z.exe a " + 'c:\\' + name + " -x!.git\\", \
            "7z.exe a " + 'f:\\' + name + " -x!.git\\", \
            "7z.exe a " + 'h:\\' + name + " -x!.git\\", \
            "7z.exe a " + 'i:\\' + name + " -x!.git\\", \
            "7z.exe a " + 'g:\\' + name + " -x!.git\\", \
            "pause"

RunCommands(strings)
