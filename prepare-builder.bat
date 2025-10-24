@echo off
call .venv\Scripts\activate.bat
conan install . --build=missing && ^
cmake . -G Ninja --preset conan-release
call .venv\Scripts\deactivate.bat
