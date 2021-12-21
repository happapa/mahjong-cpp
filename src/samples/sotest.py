from ctypes import *
import pathlib

libname = pathlib.Path().absolute() / "build/src/samples/libmjtools.so"
lib = cdll.LoadLibrary(libname)
print(lib.main())
# for i in range(1,1000):
#     print(lib.main())