all:
	g++ src/*.cpp -o gaem.exe \
	-I"include\SDL2" \
	-I"include\Headers" \
	-L"lib" \
	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
