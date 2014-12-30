# RF24 Python Wrapper (by https://github.com/mz-fuzzy)  
  
Installation:  
  
1. Install the boost libraries:  

    sudo apt-get install libboost1.50-all  

2. Build the library:  

    ./setup.py build  

3. Install the library:install:  

    ./setup.py install  

  
See https://github.com/TMRh20/RF24#connection-info for information on connecting your hardware  
See the included example for usage information. ( https://github.com/TMRh20/RF24/tree/master/examples_RPi )  
  
Running the Example:  
  
1. Edit the pingpair_dyn.py example to configure the appropriate pins per the above documentation:  
    Note: Refer to http://www.airspayce.com/mikem/bcm2835/group__constants.html#ga63c029bd6500167152db4e57736d0939 for RPi version specific pin information  

    nano pingpair_dyn.py  

2. Configure another device, Arduino or RPi with the pingpair_dyn example  
3. Run the example  

    sudo ./pingpair_dyn.py  
  
