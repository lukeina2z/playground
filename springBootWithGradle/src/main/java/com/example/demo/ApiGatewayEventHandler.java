package com.example.demo;

import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.LambdaLogger;
import com.amazonaws.services.lambda.runtime.RequestHandler;
import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.RequestHandler;
import com.amazonaws.services.lambda.runtime.LambdaLogger;
import com.amazonaws.services.lambda.runtime.events.APIGatewayProxyRequestEvent;
import com.amazonaws.services.lambda.runtime.events.APIGatewayProxyResponseEvent;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.JsonNode;
import java.util.HashMap;
import java.util.Map;

public class ApiGatewayEventHandler implements RequestHandler<APIGatewayProxyRequestEvent, APIGatewayProxyResponseEvent> {
    @Override
    public APIGatewayProxyResponseEvent handleRequest(APIGatewayProxyRequestEvent event, Context context) {
        LambdaLogger logger = context.getLogger();
        logger.log("EVENT TYPE: " + event.getClass().toString());

        ObjectMapper objectMapper = new ObjectMapper();
        Map<String, Object> responseBody = new HashMap<>();
        Map<String, Object> eventInfo = new HashMap<>();
        Map<String, Object> contextInfo = new HashMap<>();

        try {
            eventInfo.put("path", event.getPath());
            eventInfo.put("httpMethod", event.getHttpMethod());
            eventInfo.put("headers", event.getHeaders());
            eventInfo.put("queryStringParameters", event.getQueryStringParameters());
            eventInfo.put("pathParameters", event.getPathParameters());
            eventInfo.put("stageVariables", event.getStageVariables());
            eventInfo.put("requestContext", event.getRequestContext());

            String body = event.getBody();
            if (body != null && !body.isEmpty()) {
                try {
                    JsonNode jsonNode = objectMapper.readTree(body);
                    eventInfo.put("body", jsonNode);
                } catch (Exception e) {
                    eventInfo.put("body", body);
                }
            } else {
                eventInfo.put("body", body);
            }

            eventInfo.put("isBase64Encoded", event.getIsBase64Encoded());

            contextInfo.put("functionName", context.getFunctionName());
            contextInfo.put("functionVersion", context.getFunctionVersion());
            contextInfo.put("invokedFunctionArn", context.getInvokedFunctionArn());
            contextInfo.put("memoryLimitInMB", context.getMemoryLimitInMB());
            contextInfo.put("remainingTimeInMillis", context.getRemainingTimeInMillis());
            contextInfo.put("awsRequestId", context.getAwsRequestId());
            contextInfo.put("logGroupName", context.getLogGroupName());
            contextInfo.put("logStreamName", context.getLogStreamName());

            responseBody.put("event", eventInfo);
            responseBody.put("context", contextInfo);

            APIGatewayProxyResponseEvent response = new APIGatewayProxyResponseEvent()
                    .withStatusCode(200)
                    .withHeaders(new HashMap<String, String>() {
                        {
                            put("Content-Type", "application/json");
                        }
                    })
                    .withBody(objectMapper.writeValueAsString(responseBody));

            return response;

        } catch (Exception e) {
            logger.log("Error processing request: " + e.getMessage());
            return new APIGatewayProxyResponseEvent()
                    .withStatusCode(500)
                    .withHeaders(new HashMap<String, String>() {
                        {
                            put("Content-Type", "application/json");
                        }
                    })
                    .withBody("{\"error\": \"Error processing request\"}");
        }
    }

}