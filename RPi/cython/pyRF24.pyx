cdef extern from "RF24.h":
    cdef cppclass CRF24 "RF24":
        CRF24( int, int) except +
        void begin()
        void printDetails()

cdef class RF24:
    cdef CRF24 *wrapper      # hold a C++ instance which we're wrapping
    def __cinit__(self, int _cepin, int _cspin):
        self.wrapper = new CRF24(_cepin, _cspin)
    def __dealloc__(self):
        del self.wrapper
    def begin(self):
        self.wrapper.begin()
    def printDetails(self):
        self.wrapper.printDetails()
   
