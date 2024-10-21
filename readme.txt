
WSL INSTALLATION _______________

Install Windows Subsystem for Linux (WSL) Installation 

1. Open PowerShell as an Administrator.
2. Run the following command to enable the WSL feature: wsl --install
3. After the installation is complete, restart your computer if prompted.
4. Once restarted, open the Microsoft Store and search for a Linux distribution (e.g., Ubuntu).
5. Install the desired Linux distribution.
6. After installation, launch the Linux distribution from the Start menu and complete the setup process (create a user account and password).

DEPENDENCIES __________________

Run the following commands in linux terminal ->
sudo apt-get update
sudo apt install build-essential
sudo apt install libgl1-mesa-dev 
sudo apt install libglu1-mesa-dev
sudo apt install assimp libassimp-dev
sudo apt install libglm libglm-dev
sudo apt install libglfw libglfw3-dev
sudo apt install libstb-dev


Verify that all header files and libs for these installations are in /usr/include to avoid include directive errors

	Install GLAD - OpenGL Function Loading Library
	Visit https://glad.dav1d.de/
	Configure Settings ->
	Language -> C/C++
	Specification -> OpenGL
	Profile -> Core
	API -> gl -> Version 3.0
	Generate a loader -> True
	-> Generate
	Place glad.c in /ysw/src/ if not already present
	Place glad/glad.h in usr/include
	Place KHR/khrplatform.h in usr/include
NOTES __________________________

If installation did not result in header files being automatically added to /usr/include, the include statements with <> syntax will throw errors. 

COMPILATION ____________________

Naviagate to directory with main.cpp using cd command (ysw/src/main.cpp)
In terminal enter the following commands
g++ main.cpp glad.c -o run -lGL -lglfw -lm -lassimp
./run

NAVIGATION _____________________

Naviagate scene with WASD and mouse 
Enter ESC to exit



