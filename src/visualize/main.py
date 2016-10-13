"""Ref:
    https://docs.python.org/2/library/simplehttpserver.html
    http://louistiao.me/posts/python-simplehttpserver-recipe-serve-specific-directory/
"""
import posixpath
import argparse
import urllib
import os

from SimpleHTTPServer import SimpleHTTPRequestHandler
from BaseHTTPServer import HTTPServer


class RootedHTTPServer(HTTPServer):

    def __init__(self, base_path, *args, **kwargs):
        HTTPServer.__init__(self, *args, **kwargs)
        self.RequestHandlerClass.base_path = base_path


class RootedHTTPRequestHandler(SimpleHTTPRequestHandler):

    def translate_path(self, path):
        path = posixpath.normpath(urllib.unquote(path))
        words = path.split('/')
        words = filter(None, words)
        path = self.base_path
        for word in words:
            drive, word = os.path.splitdrive(word)
            head, word = os.path.split(word)
            if word in (os.curdir, os.pardir):
                continue
            path = os.path.join(path, word)
        return path


def serve(port):
    dirpath = os.path.join(
        os.path.dirname(os.path.realpath(__file__)),
        'package'
    )
    server_address = ('localhost', port)
    httpd = RootedHTTPServer(dirpath, server_address, RootedHTTPRequestHandler)

    print "Serving package over HTTP on {}:{}".format(
        server_address[0],
        server_address[1]
    )
    httpd.serve_forever()


if __name__ == '__main__':
    serve(8000)
