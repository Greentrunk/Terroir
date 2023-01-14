import os
import subprocess

print("Welcome to Terroir!")
print("Building...")

os.chdir('./../') # Change from devtools/scripts directory to root


print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

try: 
    subprocess.call(["cmake", "--version"])
    print("\nRunning cmake...")
    subprocess.call(["cmake", "-S." "-DCMAKE_TOOLCHAIN_FILE=./vendor/vcpkg/scripts/buildsystems/vcpkg.cmake", "DCMAKE_EXPORT_COMPILE_COMMANDS=1", "-Bbuild"])
    print("\nSetup completed")
    print("Thank you for checking out Terroir!")

        
except FileNotFoundError:
    print("Terroir requires CMake to generate project")
   
