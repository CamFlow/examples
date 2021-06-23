## A. Overview

This directory contains the files used for the example mentioned here: 'https://github.com/ashish-gehani/SPADE/wiki/GetMatch-query#camflow-cross-ipc-namespace-example'

1. `writer.c`: This is the writer program which writes a byte to a temporary file
2. `reader.c`: This is the reader program which reads a byte from the same temporary file

## B. Compile

Command: `make compile`

## C. Execute

Command: `make run`

## D. Post-run

When programs exit then check the CamFlow audit log output in the file `/tmp/audit.log`

## E. Visualize Graph

Set w3c output in `/etc/camflowd.ini` (need reboot to take effect).

Open `https://camflow.org/demo` and click `Start CamFlow MQTT`.

Execute `camtool --publish /tmp/audit.log`
