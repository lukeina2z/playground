package org.example;

import software.amazon.awssdk.services.s3.S3Client;
import software.amazon.awssdk.services.s3.model.Bucket;
import software.amazon.awssdk.services.s3.model.ListBucketsResponse;
import software.amazon.awssdk.services.s3.model.S3Exception;
// import io.opentelemetry.api.trace.Span;
// import io.opentelemetry.api.trace.SpanKind;
// import io.opentelemetry.api.trace.Tracer;
// import io.opentelemetry.context.Scope;
import software.amazon.awssdk.regions.Region;
// import software.amazon.awssdk.services.s3.S3Client;
// import software.amazon.awssdk.services.s3.model.Bucket;
// import software.amazon.awssdk.services.s3.model.ListBucketsResponse;
// import software.amazon.awssdk.services.s3.model.S3Exception;

public class CallS3 {
    // private final Tracer tracer;

    public CallS3() {
        // tracer = MyOTel.getInstance().getTracer();
    }

    public void call() {
        // Span rootSpan = tracer.spanBuilder("Call-S3-Span")
        //         .setSpanKind(SpanKind.INTERNAL)
        //         .startSpan();

        // try (Scope scope = rootSpan.makeCurrent()) {
        //     listS3Buckets();
        // } finally {
        //     rootSpan.end();
        // }

        listS3Buckets();
    }

    protected String listS3Buckets() {
        // return String.format("aws-sdk-call: %s!", name);

        // Create S3 client
        Region region = Region.US_WEST_2; // or your preferred region
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
        return htmlContent.toString();
    }
}
