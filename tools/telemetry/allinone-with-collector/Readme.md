

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




```test
C. Grafana: link metrics → traces

In Grafana → Data Sources → Prometheus:

Enable Exemplars

Set Internal link:

Data source: Tempo

Label name: trace_id

Grafana now knows how to jump from metrics → traces.

2️⃣ Add SpanMetrics (RED metrics from traces)

You now automatically get golden signals:

Metric	Meaning
traces_spanmetrics_latency_bucket	Request latency
traces_spanmetrics_calls_total	Throughput
traces_spanmetrics_errors_total	Error rate

All derived from spans, not manual metrics.

3️⃣ Recommended Dashboards (Import IDs)
🔥 MUST-HAVE dashboards

Import these directly in Grafana.

A. OpenTelemetry SpanMetrics (RED)

Dashboard ID: 18265
📌 Shows:

Latency (P50 / P90 / P99)

Requests/sec

Errors/sec

By service, operation, HTTP status

B. Service Overview (Tempo-native)

Dashboard ID: 19475
📌 Shows:

Service-to-service latency

Error hotspots

Trace volume

C. Prometheus Exemplars Test

Dashboard ID: 17506
📌 Lets you:

Click histogram bars

Jump straight to a trace

4️⃣ Verify Everything Works
A. Generate traffic

Hit your app endpoints.

B. Check Prometheus

Query:

traces_spanmetrics_latency_bucket


You should see labels like:

service.name
span.name
http.method

C. Click metric → trace

Open SpanMetrics dashboard

Click a latency spike

Click View trace

Grafana opens Tempo trace view

🎯 This confirms exemplars are working

5️⃣ What You Have Now (Big Picture)

You now have:

✔ Auto-generated RED metrics
✔ Zero manual instrumentation for latency
✔ One-click metric → trace navigation
✔ Tempo + Jaeger fan-out
✔ Production-grade observability pipeline

This is exactly how modern cloud platforms do it.

Next power-ups (highly recommended)

I can add:

🔗 Service Graphs (who calls whom)

📦 Loki logs → trace correlation

🎯 Tail sampling (error-first traces)

⚡ High-cardinality control

📊 Custom SLO dashboards

Tell me what you want to enable next and I’ll wire it in cleanly.

Service Graphs (who calls whom), Custom SLO dashboards

Got it — sounds like you’re referring to observability features. I’ll give a concise, practical overview, and then I’ll ask one quick clarifying question at the end.

1. Service Graphs (Who Calls Whom)

What they are

A visual map of services and their dependencies

Shows caller → callee, request rates, latency, and error rates

Usually derived automatically from distributed traces

How they’re built

Instrument services with OpenTelemetry (or vendor SDKs)

Collect traces (trace/span IDs propagated across services)

Backend aggregates traces into a dependency graph

What you typically see

Nodes = services

Edges = calls between services

Metrics on edges:

Requests per second

p50/p95/p99 latency

Error rate

Often filterable by environment, region, or time range

Common tools

Grafana Tempo + Grafana Service Graphs

Datadog APM Service Map

New Relic Service Maps

Jaeger (basic dependency graph)

Honeycomb Service Map

Why they matter

Quickly spot:

Hidden dependencies

Bottlenecks

Cascading failures

Unexpected callers after deploys

2. Custom SLO Dashboards

What they are

Dashboards focused on user-facing reliability, not raw metrics

Based on SLIs (Service Level Indicators) and error budgets

Typical SLI signals

Latency (e.g., % of requests < 300ms)

Availability (successful requests / total requests)

Correctness (business-level success)

Freshness (for data pipelines)

Common SLO patterns

“99.9% of requests succeed over 30 days”

“95% of requests complete under 500ms over 7 days”

Dashboard components

Current SLO compliance (%)

Error budget remaining

Error budget burn rate (fast vs slow)

Historical SLO performance

Correlation panels (deploys, incidents, traffic spikes)

Data sources

Metrics (Prometheus, Datadog, CloudWatch)

Traces (latency-based SLIs)

Logs (for correctness/business SLIs)

Popular implementations

Grafana SLO (Prometheus-based)

Datadog SLOs + dashboards

New Relic SLO dashboards

Nobl9 (SLO-native)

Sloth (SLOs as code for Prometheus)

How These Fit Together

Service Graphs answer:
“Where is the problem and who depends on whom?”

SLO Dashboards answer:
“Is the user experience within our reliability targets?”

Used together:

SLO alerts fire (error budget burn)

Service graph shows which downstream dependency is causing impact

Traces/logs provide root cause

Quick clarifying question

Are you:

Designing these for a platform/team?

Evaluating tools (Grafana, Datadog, New Relic, etc.)?

Or asking how to implement them (instrumentation, metrics, dashboards)?

If you want, I can give:

A reference architecture

Example SLO definitions

Grafana/Datadog dashboard layouts

OpenTelemetry instrumentation guidance

```