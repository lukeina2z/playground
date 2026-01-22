

## Application configuration (single endpoint)

Your app sends both metrics & traces to the collector:

```bash
OTEL_EXPORTER_OTLP_ENDPOINT=http://localhost:4318
OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf
```
Docker-to-Docker:

```bash
OTEL_EXPORTER_OTLP_ENDPOINT=http://otel-collector:4318
```

No backend-specific config in your app anymore

## Access UIs

| Component   | URL                                              |
| ----------- | ------------------------------------------------ |
| Prometheus  | [http://localhost:9090](http://localhost:9090)   |
| Grafana     | [http://localhost:3000](http://localhost:3000)   |
| Tempo (API) | [http://localhost:3200](http://localhost:3200)   |
| Jaeger UI   | [http://localhost:16686](http://localhost:16686) |


## Grafana trace setup (quick)

In Grafana → Datasources:
- Add Tempo
- URL: http://tempo:3200
- Enable Trace to Metrics
- Enable Exemplars

Now you can:
- Click from metrics → traces
- Search traces by service name
- Correlate RED metrics with spans


## Want next?
I can:

- Enable exemplars (metrics ↔ traces)
- Add SpanMetrics + dashboards
- Add logs → Loki
- Add service graph metrics
- Tune sampling strategies




