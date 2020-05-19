# Gauge是一个可以增大或者减少的值。
import random
import prometheus_client 
from prometheus_client import Gauge
from flask import Response, Flask 

app = Flask(__name__)

random_value = Gauge("dhan_random_value", "Random value of the request. ")

@app.route("/metrics")
def r_value():
    random_value.set(random.randint(0, 10))
    return Response(prometheus_client.generate_latest(random_value), 
                    mimetype="text/plain")

if __name__ == '__main__':
    app.run(host="0.0.0.0", port="5001")