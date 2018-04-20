all:
	cd ./provenance && $(MAKE) all
	cd ./provmark && $(MAKE) all

clean:
	cd ./provenance && $(MAKE) clean
