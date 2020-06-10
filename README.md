Many users ask how they can get their ip. I found a nice site, that returns IP and info about it in json format.
I parsed a returned json and put information into my struct. Btw, it's not API, just example for your projects.
I present 2 ways: WinInet & WinSocket. Use that you like.
Library is used for JSON parsing: https://github.com/DaveGamble/cJSON.


Compilation into *.exe on Windows (for test):
1. WinInet: ```gcc *.c ../cJSON/cJSON.c -lwininet```
2. WinSocket: ```gcc *.c ../cJSON/cJSON.c -lws2_32```