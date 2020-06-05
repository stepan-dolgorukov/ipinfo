# Get-IP-WinApi
Many users ask how they can get their ip. I found a nice site, that can return need information in json format.
I parsed a returned json and put information into my struct. Btw, it's not API, just example for your projects.
Library is used for JSON parsing: https://github.com/DaveGamble/cJSON.
Compilation into .exe file on Windows (in project folder): ```gcc gcc *.c cJSON/cJSON.c -o app.exe -lwininet```
