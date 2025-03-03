package example;

import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.RequestStreamHandler;

import software.amazon.awssdk.services.s3.S3Client;
import software.amazon.awssdk.services.s3.model.Bucket;
import software.amazon.awssdk.services.s3.model.ListBucketsResponse;
import software.amazon.awssdk.services.s3.model.S3Exception;

import software.amazon.awssdk.regions.Region;
import software.amazon.awssdk.services.s3.S3Client;
import software.amazon.awssdk.services.s3.model.Bucket;
import software.amazon.awssdk.services.s3.model.ListBucketsResponse;
import software.amazon.awssdk.services.s3.model.S3Exception;

import java.io.*;
import org.json.JSONObject;

public class MyStreamLambdaHandler implements RequestStreamHandler {
    @Override
    public void handleRequest(InputStream inputStream, OutputStream outputStream, Context context) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));
        
        StringBuilder inputStringBuilder = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            inputStringBuilder.append(line);
        }
        
        // Parse API Gateway JSON event
        JSONObject eventJson = new JSONObject(inputStringBuilder.toString());
        String body = eventJson.optString("body", "{}");
        JSONObject inputJson = new JSONObject(body);
        String name = inputJson.optString("name", "World");
        
        String httpMethod = eventJson.optString("httpMethod", "GET");
        context.getLogger().log("HTTP Method: " + httpMethod);
        String resource = eventJson.optString("resource", "null");
        context.getLogger().log("Resource: " + resource);
        String path = eventJson.optString("path", "null");
        context.getLogger().log("Path: " + path);
        context.getLogger().log("Body: " + body);

        // Create response JSON
        JSONObject responseJson = new JSONObject();
        responseJson.put("statusCode", 200);
        responseJson.put("headers", new JSONObject().put("Content-Type", "application/json"));
        
        JSONObject responseBody = new JSONObject();
        responseBody.put("message", "xxx-Hello, " + name + "!");
        responseBody.put("S3Call", getS3buckets());
        responseJson.put("body", responseBody.toString());
        
        // Write response
        writer.write(responseJson.toString());
        writer.flush();
    }

    private static S3Client s3 = null;
    String getS3buckets() {
        Region region = Region.US_WEST_2; // or your preferred region
        if (s3 == null) {
            s3 = S3Client.builder()
                    .region(region)
                    .build();
        }
        StringBuilder strResponse = new StringBuilder();
        strResponse.append("S3 Buckets: ");
        try {
            ListBucketsResponse response = s3.listBuckets();
            for (Bucket bucket : response.buckets()) {
                strResponse.append("   ").append(bucket.name()).append("   ");
            }
        } catch (S3Exception e) {
            strResponse.append("Error listing buckets: ").append(e.getMessage());
        }

        return strResponse.toString();
    }
}


