package org.example;

import java.net.URI;

import io.opentelemetry.api.trace.Span;
import io.opentelemetry.api.trace.SpanKind;
import io.opentelemetry.api.trace.Tracer;
import io.opentelemetry.context.Scope;

import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;

public class CallHttp {
    private final Tracer tracer;

    public CallHttp() {
        tracer = MyOTel.getInstance().getTracer();
    }

    public void call() {
        Span rootSpan = tracer.spanBuilder("Call-HTTP-Span")
                .setSpanKind(SpanKind.INTERNAL)
                .startSpan();

        try (Scope scope = rootSpan.makeCurrent()) {
            getHttpContent();
        } finally {
            rootSpan.end();
        }
    }

    String getHttpContent() {
        try {
            final HttpClient httpClient = HttpClient.newBuilder()
                    .connectTimeout(Duration.ofSeconds(10))
                    .build();

            HttpRequest request = HttpRequest.newBuilder()
                    .GET()
                    .uri(URI.create("http://aws.amazon.com"))
                    .header("Accept", "application/json")
                    .build();

            HttpResponse<String> response = httpClient.send(request,
                    HttpResponse.BodyHandlers.ofString());

            return response.statusCode() + " " + response.body().substring(0, 100);

        } catch (Exception e) {
            return ("Error: " + e.getMessage());
        }
    }
}
