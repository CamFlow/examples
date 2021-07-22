all:
	cd ./provenance && $(MAKE) all
	cd ./visicorn && $(MAKE) all
	cd ./namespaces && $(MAKE) all
	cd ./symlink && $(MAKE) all

clean:
	cd ./provenance && $(MAKE) clean
	cd ./visicorn && $(MAKE) clean
	cd ./namespaces && $(MAKE) clean
	cd ./symlink && $(MAKE) clean
