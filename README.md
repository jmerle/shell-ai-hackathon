# Shell.ai Hackathon

This repository contains my solution for the [Shell.ai Hackathon](https://www.hackerearth.com/challenges/competitive/shell-hackathon/) competition on HackerEarth.

## Development

Every time you create a new .cpp file or if you `git pull` new .cpp files into your local repository you'll need to manually reload the CMake project for the file to be discovered in future builds. In CLion this can be done by clicking `Tools > CMake > Reload CMake Project` or by pressing `Ctrl+Shift+A` and searching for `Reload CMake Project` in the Find Actions pop-up triggered by the shortcut.

If you are using CLion and you're getting a "Conan executable not found!" error when trying to load the CMake project, make sure Conan is installed system-wide. On Linux this can be achieved by running ``sudo ln -s `which conan` /usr/local/bin/conan``.
