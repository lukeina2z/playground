package com.example.demo;

import java.util.concurrent.atomic.AtomicLong;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.client.RestTemplate;

import io.opentelemetry.api.GlobalOpenTelemetry;
import io.opentelemetry.api.trace.Tracer;

import org.springframework.http.ResponseEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.HttpStatusCode;
import org.springframework.http.MediaType;

import software.amazon.awssdk.regions.Region;
import software.amazon.awssdk.services.s3.S3Client;
import software.amazon.awssdk.services.s3.model.Bucket;
import software.amazon.awssdk.services.s3.model.ListBucketsResponse;
import software.amazon.awssdk.services.s3.model.S3Exception;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;

import io.opentelemetry.api.trace.Span;
import io.opentelemetry.api.trace.Tracer;
import io.opentelemetry.api.GlobalOpenTelemetry;
import io.opentelemetry.context.Scope;
import io.opentelemetry.api.trace.SpanKind;

@SpringBootApplication
@RestController
public class DemoApplication {
    private static final String template = "Hello, %s!";
    private final AtomicLong counter = new AtomicLong();
    private String s3CallHtmlResponse = "";

    // Use a named tracer, ideally using your library's package or name
    private final Tracer tracer = GlobalOpenTelemetry.getTracer("com.xyxyxy.mylibrary");

    public void doSomething() {
        // This will be a no-op if the user doesn't configure OpenTelemetry
        Span span = tracer.spanBuilder("xyxy-doSomething")
                .setSpanKind(SpanKind.SERVER)
                .startSpan();

        try (Scope scope = span.makeCurrent()) {
            span.addEvent("doing some important work");
            // Simulated work
            Thread.sleep(100);
        } catch (InterruptedException e) {
            span.recordException(e);
            Thread.currentThread().interrupt();
        } finally {
            span.end();
        }
    }

    public void clientFoo() {
        Span span = tracer.spanBuilder("xyxy-client-foo")
                .setSpanKind(SpanKind.CLIENT)
                .startSpan();

        try (Scope scope = span.makeCurrent()) {
            serverFoo();
            Thread.sleep(100);
        } catch (InterruptedException e) {
            span.recordException(e);
            Thread.currentThread().interrupt();
        } finally {
            span.end();
        }
    }

    public void serverFoo() {
        Span span = tracer.spanBuilder("xyxy-server-foo")
                .setSpanKind(SpanKind.SERVER)
                .startSpan();

        try (Scope scope = span.makeCurrent()) {
            span.addEvent("doing some important work in server foo.");
            clientCallS3();
            Thread.sleep(100);
        } catch (InterruptedException e) {
            span.recordException(e);
            Thread.currentThread().interrupt();
        } finally {
            span.end();
        }
    }

    public void clientCallS3() {
        Span span = tracer.spanBuilder("xyxy-client-S3")
                .setSpanKind(SpanKind.CLIENT)
                .startSpan();

        try (Scope scope = span.makeCurrent()) {

            Region region = Region.US_WEST_2;
            S3Client s3 = S3Client.builder()
                    .region(region)
                    .build();

            StringBuilder htmlContent = new StringBuilder();
            htmlContent.append("<html><body>");
            htmlContent.append("<h2>S3 Buckets:</h2><ul>");
            try {
                ListBucketsResponse response = s3.listBuckets();
                for (Bucket bucket : response.buckets()) {
                    htmlContent.append("<li>").append(bucket.name()).append("</li>");
                }
            } catch (S3Exception e) {
                htmlContent.append("<p>Error listing buckets: ").append(e.getMessage()).append("</p>");
            }

            htmlContent.append("</ul></body></html>");
            this.s3CallHtmlResponse = htmlContent.toString();
        } catch (Exception e) {
            span.recordException(e);
            Thread.currentThread().interrupt();
        } finally {
            span.end();
        }
    }

    public static void main(String[] args) {
        SpringApplication.run(DemoApplication.class, args);
    }

    @GetMapping("/")
    public String home(String name) {
        return """
                 <html>
                 <body>
                     <p>Two web methods are provided:</p>
                     <ul>
                         <li>/aws-sdk-call</li>
                         <li>/outgoing-http-call</li>
                     </ul>
                 </body>
                 </html>
                """;
    }

    @GetMapping("/aws-sdk-call")
    public String awsSdkCall(@RequestParam(value = "name", defaultValue = "World") String name) {
        Span span = tracer.spanBuilder("xyxy-SprintBoot-S3-Handler")
                .setSpanKind(SpanKind.SERVER)
                .startSpan();

        try (Scope scope = span.makeCurrent()) {
            clientFoo();
        } catch (Exception ex) {
            span.recordException(ex);
            Thread.currentThread().interrupt();
        } finally {
            span.end();
        }

        return this.s3CallHtmlResponse;
    }

    record ApiResponse(String content, int statusCode, String message) {
    }

    @GetMapping(value = "/outgoing-http-call", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity<ApiResponse> outgoingHttpCall(String name) {
        Span span = tracer.spanBuilder("xyxy-http-call")
                .setSpanKind(SpanKind.CLIENT)
                .startSpan();

        try (Scope scope = span.makeCurrent()) {
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

            ApiResponse apiResponse = new ApiResponse(
                    response.body(),
                    response.statusCode(),
                    "Success");

            return ResponseEntity
                    .status(HttpStatus.OK)
                    .body(apiResponse);

        } catch (Exception e) {
            ApiResponse errorResponse = new ApiResponse(
                    "Error: " + e.getMessage(),
                    HttpStatus.INTERNAL_SERVER_ERROR.value(),
                    "Internal error");

            // Return error response with status code 500
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body(errorResponse);
        } finally {
            span.end();
        }
    }
}