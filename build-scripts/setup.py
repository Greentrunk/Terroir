import os
import subprocess

print("Welcome to Terroir!")
print("Building...")

# Go back to root
os.chdir('./../')

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

try:
    subprocess.call(["cmake", "--version"])
    print("\nRunning cmake...")

    # If project built with msvc, don't need compile commands
    if os.name == 'nt':
        subprocess.call(["cmake", "-S.",
                         "-DCMAKE_TOOLCHAIN_FILE=./vendor/vcpkg/scripts/buildsystems/vcpkg.cmake", "-Bbuild"])
    else:
        subprocess.call(["cmake", "-S.", "-DCMAKE_TOOLCHAIN_FILE=./vendor/vcpkg/scripts/buildsystems/vcpkg.cmake",
                         "-DCMAKE_EXPORT_COMPILE_COMMANDS=1", "-Bbuild"])

    print("\nSetup completed")
    print(
        "\nConfigure your IDE to gen/build the project as necessary. If on linux, you need to export compile "
        "commands.  Always set the cmake toolchain file to ./vendor/vcpkg/scripts/buildsystems/vcpkg.cmake")
    print("\nWhile running Sandbox... MAKE SURE TO SET THE WORKING DIRECTORY TO THE ROOT DIR OF THE REPO")
    print("Thank you for checking out Terroir!")


except FileNotFoundError:
    print("Terroir requires CMake to generate project")
