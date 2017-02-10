# Docker containers demo for UCSC

Thanks to Peter Alvaro's team for the python scripts.

Architecture is simple as follow:
client <- proxy <- server

To run the demo (we assume docker and camflow are running correctly on the machine):
```
make build
make network
make camflow
make run
make test
```

To stop and delete the container simply:
```
make stop
```
