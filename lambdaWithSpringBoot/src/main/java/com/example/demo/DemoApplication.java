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

@SpringBootApplication
@RestController
public class DemoApplication {
    private static final String template = "Hello, %s!";
    private final AtomicLong counter = new AtomicLong();

    // Use a named tracer, ideally using your library's package or name
    private final Tracer tracer = GlobalOpenTelemetry.getTracer("com.xyxyxy.mylibrary");

    public void doSomething() {
        // This will be a no-op if the user doesn't configure OpenTelemetry
        Span span = tracer.spanBuilder("doSomething").startSpan();
        try {
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
        Span span = tracer.spanBuilder("xyxy-call-s3").startSpan();
        StringBuilder htmlContent = new StringBuilder();
        try {
            Region region = Region.US_WEST_2;
            S3Client s3 = S3Client.builder()
                    .region(region)
                    .build();

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
        } catch (Exception ex) {
            span.recordException(ex);
            Thread.currentThread().interrupt();
        } finally {
            span.end();
        }

        return htmlContent.toString();
    }

    record ApiResponse(String content, int statusCode, String message) {
    }

    @GetMapping(value = "/outgoing-http-call", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity<ApiResponse> outgoingHttpCall(String name) {
        Span span = tracer.spanBuilder("xyxy-http-call").startSpan();
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

            ApiResponse apiResponse = new ApiResponse(
                    response.body(),
                    response.statusCode(),
                    "Success");

            return ResponseEntity
                    .status(response.statusCode())
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