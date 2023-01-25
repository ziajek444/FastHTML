# FastHTML

------------------------------------------------------------------------------------------------
Gigant (53MB), Huge (26MB), Big (13MB), Small (6.5MB), Tiny (3.3MB)
12 threads vs sequentional
type		GIGANT		HUGE		BIG			SMALL			TINY
Threading	5963		3462		2449		1734			1611	(ms)
no thread	15548		7788		3965		2112			1095	(ms)

6 threads vs sequentional
type		GIGANT		HUGE		BIG			SMALL			TINY
Threading	5963		3419		1984		1347			1069	(ms)
no thread	16178		8092		4159		2172			1123	(ms)

4 threads vs sequentional
type		GIGANT		HUGE		BIG			SMALL			TINY
Threading	6151		3441		1822		1094			889		(ms)
no thread	15434		7756		3933		2076			1099	(ms)

2 threads vs sequentional
type		GIGANT		HUGE		BIG			SMALL			TINY
Threading	9385		4769		2710		1496			953		(ms)
no thread	15637		7850		3990		2123			1112	(ms)

Threading is better for response bigger than 3MB.
------------------------------------------------------------------------------------------------
25.01.2034
https://stackoverflow.com/a/64719718/9473237

# Configure the build
cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Debug

# Actually build the binaries
cmake --build build/

# Configure a release build
cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Release

# Build release binaries
cmake --build build/


For multi-configuration generators it's slightly different (Ninja Multi-Config, Visual Studio)

# Configure the build
cmake -S . -B build

# Build debug binaries
cmake --build build --config Debug

# Build release binaries
cmake --build build --config Release
------------------------------------------------------------------------------------------------