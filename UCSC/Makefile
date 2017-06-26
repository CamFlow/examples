build:
	cd proxy && sudo docker build -t proxypy .
	cd server && sudo docker build -t serverpy .

network:
	sudo docker network create --subnet 10.5.0.0/16 demo

camflow:
	sudo camflow --track-ipv4-ingress 10.5.0.0/16:0 propagate
	camflow -s

run:
	sudo docker run -p 49165:8080 --net=demo --ip='10.5.0.2' --name=proxy proxypy &
	sudo docker run -p 49166:8081 --net=demo --ip='10.5.0.3' --name=server serverpy &

test:
	echo 'is provenance generated talking to proxy'
	wget 10.5.0.2:8080

stop:
	sudo docker rm -f proxy
	sudo docker rm -f server
	sudo docker network rm demo
