@echo off
g++ -finput-charset=UTF-8 -Iinclude .\main.cpp .\src\art.cpp .\src\DirectedGraph.cpp -o DirectedGraphImpl.exe
echo Done!