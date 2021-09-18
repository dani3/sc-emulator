# Baldwin library

This folder contains a small library used by the integration tests. `Baldwin` implements a target class that is able to communicate with the emulator via TCP/IP.

To use the target you just need to do the following:

```py
from baldwin.target import Target

with Target() as target:
    target.reset()

    # Your tests here.
```

