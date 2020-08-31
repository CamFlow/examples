all:
	cd ./provenance && $(MAKE) all
	cd ./visicorn && $(MAKE) all

clean:
	cd ./provenance && $(MAKE) clean
	cd ./visicorn && $(MAKE) clean
