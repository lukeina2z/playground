package example;

import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.RequestStreamHandler;
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
        responseJson.put("body", responseBody.toString());
        
        // Write response
        writer.write(responseJson.toString());
        writer.flush();
    }
}
