import ctypes

# Load the shared library
square_lib = ctypes.CDLL('./calculation_software/square.so')

# Declare the function signature
square_lib.square.argtypes = [ctypes.c_int]
square_lib.square.restype = ctypes.c_int

# Call the C++ function
result = square_lib.square(5)
print(result)  # Output: 25