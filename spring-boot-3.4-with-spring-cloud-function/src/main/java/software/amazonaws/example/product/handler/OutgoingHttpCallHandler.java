// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

package software.amazonaws.example.product.handler;

import java.util.Optional;
import java.util.function.Function;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import com.amazonaws.services.lambda.runtime.events.APIGatewayProxyRequestEvent;
import com.amazonaws.services.lambda.runtime.events.APIGatewayProxyResponseEvent;
import com.fasterxml.jackson.databind.ObjectMapper;

import software.amazon.awssdk.http.HttpStatusCode;

@Component
public class OutgoingHttpCallHandler implements Function<APIGatewayProxyRequestEvent, APIGatewayProxyResponseEvent> {

	@Autowired
	private ObjectMapper objectMapper;


	private static final Logger logger = LoggerFactory.getLogger(OutgoingHttpCallHandler.class);

	public APIGatewayProxyResponseEvent apply(APIGatewayProxyRequestEvent requestEvent) {
		return new APIGatewayProxyResponseEvent().withStatusCode(HttpStatusCode.OK)
			.withBody("Product with id = xxx not found");
	}
}
