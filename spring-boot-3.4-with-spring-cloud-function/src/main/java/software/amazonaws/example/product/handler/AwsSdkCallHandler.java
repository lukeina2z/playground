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
public class AwsSdkCallHandler implements Function<APIGatewayProxyRequestEvent, APIGatewayProxyResponseEvent> {


	@Autowired
	private ObjectMapper objectMapper;


	private static final Logger logger = LoggerFactory.getLogger(AwsSdkCallHandler.class);

	public APIGatewayProxyResponseEvent apply(APIGatewayProxyRequestEvent requestEvent) {



		return new APIGatewayProxyResponseEvent().withStatusCode(HttpStatusCode.OK)
			.withBody("Product with id = xxx not found");


		
		// String id = requestEvent.getPathParameters().get("id");
		// Optional<Product> optionalProduct = productDao.getProduct(id);
		// try {
		// 	if (optionalProduct.isEmpty()) {
		// 		logger.info(" product with id " + id + " not found ");
		// 		return new APIGatewayProxyResponseEvent().withStatusCode(HttpStatusCode.NOT_FOUND)
		// 				.withBody("Product with id = " + id + " not found");
		// 	}
		// 	logger.info(" product " + optionalProduct.get() + " found ");
		// 	return new APIGatewayProxyResponseEvent().withStatusCode(HttpStatusCode.OK)
		// 			.withBody(objectMapper.writeValueAsString(optionalProduct.get()));
		// } catch (Exception je) {
		// 	je.printStackTrace();
		// 	return new APIGatewayProxyResponseEvent().withStatusCode(HttpStatusCode.INTERNAL_SERVER_ERROR)
		// 			.withBody("Internal Server Error :: " + je.getMessage());
		// }
	}
}
