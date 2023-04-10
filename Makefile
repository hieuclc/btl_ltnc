all:
	g++ *.cpp -o bin/debug/gaem.exe \
	-I"C:\Users\hieu1\OneDrive\Desktop\sdl_final\x86_64-w64-mingw32\include\SDL2" \
	-L"C:\Users\hieu1\OneDrive\Desktop\sdl_final\x86_64-w64-mingw32\lib" \
	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
