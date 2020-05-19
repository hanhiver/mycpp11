from prometheus_client import Counter

c = Counter('requests_total', 'HTTP requests total', ['method', 'clientip'])

c.labels('get', '127.0.0.1').inc()
c.labels('post', '192.168.0.1').inc(3)
c.labels(method="get", clientip="192.168.0.1").inc()

from prometheus_client import Counter, Gauge
from prometheus_client.core import CollectorRegistry

REGISTRY = CollectorRegistry(auto_describe=False)

requests_total = Counter("request_count", "Total request cout of the host", registry=REGISTRY)
random_value = Gauge("random_value", "Random value of the request", registry=REGISTRY)



