Python Wrapper for RF24
See http://tmrh20.github.io/RF24 for more information

To compile for python 3
python3 setup.py build
sudo python3 setup.py install

On Raspbian jessie, boost_python3 is missing
you need to manually create the link
ln -s /usr/lib/arm-linux-gnueabihf/libboost_python-py34.so.1.55.0 /usr/lib/arm-linux-gnueabihf/libboost_python3.so
