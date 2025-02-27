package software.amazonaws.example;

import java.util.function.Function;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import com.amazonaws.services.lambda.runtime.events.APIGatewayProxyRequestEvent;
import com.amazonaws.services.lambda.runtime.events.APIGatewayProxyResponseEvent;
import com.fasterxml.jackson.databind.ObjectMapper;

import software.amazon.awssdk.http.HttpStatusCode;
import software.amazon.awssdk.regions.Region;
import software.amazon.awssdk.services.s3.S3Client;
import software.amazon.awssdk.services.s3.model.Bucket;
import software.amazon.awssdk.services.s3.model.ListBucketsResponse;
import software.amazon.awssdk.services.s3.model.S3Exception;

import software.amazon.awssdk.core.client.config.ClientOverrideConfiguration;
import com.amazonaws.xray.interceptors.TracingInterceptor;

@Component
public class AwsSdkCallHandler implements Function<APIGatewayProxyRequestEvent, APIGatewayProxyResponseEvent> {

	@Autowired
	private ObjectMapper objectMapper;


	private static final Logger logger = LoggerFactory.getLogger(AwsSdkCallHandler.class);

	public APIGatewayProxyResponseEvent apply(APIGatewayProxyRequestEvent requestEvent) {

        Region region = Region.US_WEST_2;
        S3Client s3 = S3Client.builder()
                .region(region)
                .overrideConfiguration(
                    ClientOverrideConfiguration.builder()
                        .addExecutionInterceptor(new TracingInterceptor())
                        .build())
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

		return new APIGatewayProxyResponseEvent().withStatusCode(HttpStatusCode.OK)
			.withBody(htmlContent.toString());
	}
}
