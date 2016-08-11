all:
	cd ./ifc && $(MAKE) all
	cd ./provenance && $(MAKE) all

clean:
	cd ./ifc && $(MAKE) clean
	cd ./provenance && $(MAKE) clean
