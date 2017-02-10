#!/usr/bin/env python2
import SocketServer
import SimpleHTTPServer
import urllib

PORT = 8080

class Proxy(SimpleHTTPServer.SimpleHTTPRequestHandler):
    def do_GET(self):
        print self.path
        self.copyfile(urllib.urlopen("http://10.5.0.3:8081/"), self.wfile)

httpd = SocketServer.ForkingTCPServer(('10.5.0.2',PORT), Proxy)
print "serving at port",PORT
httpd.serve_forever()
