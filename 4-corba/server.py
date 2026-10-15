# server.py : CORBA server in Python using omniORBpy
#
# Steps (Ubuntu 18.04):
#   sudo apt install python-omniorb omniidl-python
#   omniidl -bpython Calc.idl
#   python server.py

import sys
from omniORB import CORBA
import Demo, Demo__POA

# Implementation of the Calc interface
class Calc_i(Demo__POA.Calc):
    def add(self, a, b):
        print("Client requested: %d + %d" % (a, b))
        return a + b

# Step 1: Initialise the ORB and get the Root POA
orb = CORBA.ORB_init(sys.argv, CORBA.ORB_ID)
poa = orb.resolve_initial_references("RootPOA")

# Step 2: Create the servant and get its object reference
servant = Calc_i()
obj = servant._this()

# Step 3: Write the object reference (IOR) to a file
ior = orb.object_to_string(obj)
f = open("calc.ior", "w")
f.write(ior)
f.close()
print("Calc server is ready. IOR written to calc.ior")

# Step 4: Activate the POA manager and wait for requests
poaManager = poa._get_the_POAManager()
poaManager.activate()
orb.run()
