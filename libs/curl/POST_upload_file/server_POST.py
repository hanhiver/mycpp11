from http.server import BaseHTTPRequestHandler, HTTPServer 
import logging 
import json

class S(BaseHTTPRequestHandler):
    def do_HEAD(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        paths = {
            '/foo': {'status': 200}, 
            '/bar': {'status': 302}, 
            '/baz': {'status': 404}, 
            '/qux': {'status': 500}
        }

        if self.path in paths:
            self.respond(paths[self.path])
        else:
            self.respond({'status': 500})
        
        logging.info("GET Request, \nPath: %s\nHeaders:\n%s\n", 
                        str(self.path), str(self.headers))
        self.wfile.write("GET request for {}".format(self.path).encode('utf-8'))

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        logging.info("POST request,\nPath: %s\nHeaders:\n%s\n\nBody:\n%s\n",
                        str(self.path), str(self.headers), post_data.decode('utf-8'))
        res = post_data.decode('utf-8')
        
        request = json.loads(res)
        _ = request.pop('cipherText')
        orig_report = json.JSONEncoder(separators=(',', ':')).encode(request)
        print(orig_report)
        
        
        self.do_HEAD()
        self.wfile.write("{}".format(res).encode('utf-8'))

    def respond(self, opts):
        response = self.handle_http(opts['status'], self.path)
        self.wfile.write(response)

    def handle_http(self, status_code, path):
        self.send_response(status_code)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        content = '''
           <html><head><title>Title goes here.</title></head>
           <body><p>This is a test.</p>
           <p>You accessed path: {}</p>
           </body></html>
           '''.format(path)
        return bytes(content, 'UTF-8')

def run(server_class=HTTPServer, handler_class=S, port=8288):
    print("run()")
    logging.basicConfig(level=logging.INFO)
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    logging.info('Starting httpd... \n')
    
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass 
    
    httpd.server_close()
    print("httpd.server_close()")
    logging.info('Stopping httpd... \n')

if __name__ == "__main__":
    run()
