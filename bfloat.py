import ctypes
lib = ctypes.cdll.LoadLibrary('./libbfloat.so')

class Bfloat(object):
    def __init__(self, val):
        lib.bfloat_new.argtypes = [ctypes.c_int]
        lib.bfloat_new.restype = ctypes.c_void_p

        lib.show.argtypes = [ctypes.c_void_p]
        lib.show.restype = ctypes.c_void_p
        self.obj = lib.bfloat_new(val)

    def show(self):
        return lib.show(self.obj)


class BFMat(object):
    def __init__(self, rows, cols, placeholder = False):
        self.rows = rows
        self.cols = cols

        lib.BFMat_new.argtypes = [ctypes.c_int, ctypes.c_int]
        lib.BFMat_new.restype = ctypes.c_void_p

        lib.EW_mul.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        lib.EW_mul.restype = ctypes.c_void_p

        lib.EW_div.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        lib.EW_div.restype = ctypes.c_void_p

        lib.EW_add.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        lib.EW_add.restype = ctypes.c_void_p

        lib.EW_sub.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        lib.EW_sub.restype = ctypes.c_void_p

        lib.dot.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        lib.dot.restype = ctypes.c_void_p
        if not placeholder:
            self.obj = lib.BFMat_new(rows, cols)

    def ew_mul(self, right):
        out = BFMat(self.rows, self.cols, placeholder = True)
        out.obj = lib.EW_mul(self.obj, right.obj)
        return out
    def ew_div(self, right):
        out = BFMat(self.rows, self.cols, placeholder = True)
        out.obj = lib.EW_div(self.obj, right.obj)
        return out

    def ew_add(self, right):
        out = BFMat(self.rows, self.cols, placeholder = True)
        out.obj = lib.EW_add(self.obj, right.obj)
        return out

    def ew_sub(self, right):
        out = BFMat(self.rows, self.cols, placeholder = True)
        out.obj = lib.EW_sub(self.obj, right.obj)
        return out

    def dot(self, right):
        out = BFMat(self.rows, self.cols, placeholder = True)
        out.obj = lib.dot(self.obj, right.obj)
        return out
