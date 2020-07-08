#!/usr/bin/env python
import os
files_to_clean = ["./src/main/c/Objects/pyjc3constructor.c","./src/main/c/Objects/pyjc3multimethod.c","./src/main/c/Objects/pyjc3type.c","./src/main/c/Objects/pyjc3object.c", "./src/main/c/Include/pyjc3constructor.h", "./src/main/c/Include/pyjc3multimethod.h", "./src/main/c/Include/pyjc3method.h","./src/main/c/Include/pyjc3type.h","./src/main/c/Include/pyjc3object.h", "./src/main/c/Objects/pyjc3method.c"]
names = ["PyJC3Constructor", "PyJC3Object", "PyJC3Type", "PyJC3Method", "PyJC3MultiMethod"]
name_pairs = {n.replace("PyJC3", "PyJ"):n for n in names}
name_pairs.update({k.lower(): v.lower() for k,v in name_pairs.items()})
for file in files_to_clean:
    if not os.path.isfile(file):
        old_file = file.replace('pyjc3', 'pyj')
        os.mv(old_file, file)
    with open(file, 'r') as f:
        c = f.read()
        for k,v in name_pairs.items():
            print("replacing {} with {}".format(k,v))
            c = c.replace(k, v)
    with open(file, 'w') as f:
        f.write(c)
