# ET Legacy Development Setup for macOS and Visual Studio Code

This guide will help you set up ET Legacy for development on macOS with Visual Studio Code.

## Prerequisites

### Required Software

1. **Xcode Command Line Tools**
   ```bash
   xcode-select --install
   ```

2. **Homebrew** (https://brew.sh/)
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

3. **Visual Studio Code** with these extensions installed:
   - C/C++ Extension Pack
   - CMake Tools
   - CMake Language Support

### Dependencies

Install the required build dependencies:
```bash
brew bundle install
```

This installs:
- cmake
- nasm
- automake
- autoconf
- libtool

## Project Structure

```
etlegacy/
├── .vscode/                 # VS Code configuration
│   ├── settings.json        # Editor settings and IntelliSense
│   ├── tasks.json          # Build and run tasks
│   └── launch.json         # Debug configurations
├── build/                   # Build output directory
│   ├── ET Legacy.app/       # macOS application bundle
│   └── etlded              # Dedicated server binary
├── src/                     # Source code
│   ├── cgame/              # Client-side game logic
│   ├── client/             # Client engine
│   ├── game/               # Server-side game logic
│   ├── renderer/           # OpenGL renderer
│   ├── renderer_metal/     # Metal renderer (macOS)
│   └── server/             # Server engine
├── etmain/                 # Game assets directory
├── cmake/                  # CMake modules
└── easybuild.sh           # Build script
```

## Building ET Legacy

### Using VS Code (Recommended)

1. **Open the workspace**: Open `etlegacy.code-workspace` in VS Code
2. **Build**: Use `Ctrl+Shift+P` and run "Tasks: Run Task" → "Build ET Legacy (64-bit)"
3. **Run**: Use the task "Run ET Legacy Client" or "Run ET Legacy Dedicated Server"

### Using Command Line

```bash
# Clean build
./easybuild.sh clean

# Build 64-bit version for macOS
./easybuild.sh -64 build

# Generate project files only
./easybuild.sh -64 generate

# Create distribution package
./easybuild.sh -64 package
```

### Build Options

Common build flags for `easybuild.sh`:
- `-64`: Build 64-bit version (required for macOS 10.15+)
- `-debug`: Build with debug symbols
- `-clang`: Use Clang compiler (default on macOS)
- `--osx=10.15`: Set minimum macOS version
- `-systemlibs`: Use system libraries instead of bundled ones

## Running ET Legacy

### Game Assets Required

ET Legacy requires original Wolfenstein: Enemy Territory assets:

1. Download the original game from [Splash Damage](https://www.splashdamage.com/games/wolfenstein-enemy-territory/)
2. Copy `pak0.pk3` from the original game to `build/etmain/`
3. Optionally copy `pak1.pk3` and `pak2.pk3` for full mod compatibility

**Automatic Download:**
```bash
./easybuild.sh download
```

### Launch Options

**Client:**
```bash
# Launch via application bundle
open "build/ET Legacy.app"

# Or via command line with options
"build/ET Legacy.app/Contents/MacOS/ET Legacy" +set r_fullscreen 0 +set developer 1
```

**Dedicated Server:**
```bash
./build/etlded +set dedicated 1 +set fs_basepath ./etmain
```

## Development

### VS Code Tasks

Available tasks (Ctrl+Shift+P → "Tasks: Run Task"):
- **Build ET Legacy (64-bit)**: Full build (default build task)
- **Clean Build**: Clean the build directory
- **Generate Project Files**: Generate CMake files
- **Run ET Legacy Client**: Launch the game client
- **Run ET Legacy Dedicated Server**: Run dedicated server
- **Package ET Legacy**: Create distribution package
- **Download Game Assets**: Download required pak files

### Debugging

Two debug configurations are available:
1. **Debug ET Legacy Client**: Debug the game client with developer settings
2. **Debug ET Legacy Server**: Debug the dedicated server

To debug:
1. Set breakpoints in the source code
2. Press F5 or use "Run and Debug" panel
3. Select the appropriate debug configuration

### Code Structure

**Key directories for development:**

- `src/cgame/`: Client-side game logic (UI, effects, prediction)
- `src/game/`: Server-side game logic (physics, AI, rules)
- `src/client/`: Client engine (rendering, input, sound)
- `src/server/`: Server engine (networking, world simulation)
- `src/qcommon/`: Shared code between client and server
- `src/renderer/`: OpenGL 1/2 renderer
- `src/renderer2/`: OpenGL 3+ renderer
- `src/renderer_metal/`: Metal renderer (macOS-specific)

### CMake Configuration

Key CMake options (set in CMakeLists.txt or via command line):

```cmake
# Renderer options
-DFEATURE_RENDERER1=ON          # OpenGL 1/2 renderer
-DFEATURE_RENDERER2=OFF         # OpenGL 3+ renderer
-DFEATURE_RENDERER_METAL=ON     # Metal renderer (experimental)

# Feature options
-DFEATURE_CURL=ON               # HTTP downloads
-DFEATURE_SSL=ON                # SSL support
-DFEATURE_LUA=ON                # Lua scripting
-DFEATURE_OPENAL=ON             # OpenAL audio
-DFEATURE_OGG_VORBIS=ON         # OGG/Vorbis audio

# Build options
-DBUNDLED_LIBS=ON               # Use bundled libraries
-DCROSS_COMPILE32=OFF           # 32-bit build (not recommended on modern macOS)
```

### Metal Renderer (Experimental - Currently Disabled)

ET Legacy includes an experimental Metal renderer, but it's currently disabled due to compilation issues:

- **Location**: `src/renderer_metal/`
- **Status**: Disabled in CMakeLists.txt due to Objective-C compilation errors
- **Issue**: Metal renderer files have .c extensions but contain Objective-C code
- **Fix Applied**: Commented out `add_subdirectory(src/renderer_metal)` in main CMakeLists.txt

**To re-enable Metal renderer** (not recommended until fixed):
```cmake
# In CMakeLists.txt, uncomment:
if(APPLE)
    add_subdirectory(src/renderer_metal)
endif()
```

**Note**: The current implementation tries to compile Objective-C Foundation framework code as C, causing build failures on Apple Silicon. Use OpenGL renderer for stable development.

## Troubleshooting

### Common Issues

**Build fails with missing dependencies:**
```bash
brew bundle install
```

**"Cannot find pak0.pk3" error:**
- Download original Wolfenstein: Enemy Territory
- Copy pak0.pk3 to `build/etmain/` directory
- Or run `./easybuild.sh download`

**CMake configuration fails:**
```bash
rm -rf build/
./easybuild.sh generate
```

**Application won't launch:**
```bash
# Check if executable exists and has permissions
ls -la "build/ET Legacy.app/Contents/MacOS/"
chmod +x "build/ET Legacy.app/Contents/MacOS/ET Legacy"
```

### Getting Help

- **Documentation**: [ET Legacy Wiki](https://github.com/etlegacy/etlegacy/wiki)
- **Issues**: [GitHub Issues](https://github.com/etlegacy/etlegacy/issues)
- **Discord**: [ET Legacy Community](https://discord.gg/UBAZFys)
- **IRC**: #etlegacy on irc.libera.chat

## Performance Tips

1. **Use Release builds** for better performance (default with easybuild.sh)
2. **Enable Metal renderer** for better GPU utilization on modern Macs
3. **Adjust graphics settings** in-game for your hardware
4. **Use bundled libraries** for better compatibility

## Mod Development

ET Legacy supports Lua scripting for server-side modifications:

- Lua scripts go in `legacy/` directory
- Examples in `src/game/` directory
- API documentation: [ET Legacy Lua API](https://etlegacy-lua-docs.readthedocs.io)

---

Happy coding! 🎮