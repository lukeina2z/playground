def display_llm_response(response):
    parts = str(response).split("</think>")
    thought = parts[0].strip() if len(parts) > 1 else "N/A"
    answer = parts[1].strip() if len(parts) > 1 else str(response)

    print("\n\n=== Thought ===\n\n")
    print(thought)

    print("\n\n=== Final Answer ===\n\n")
    print(answer)

def read_file_content(file_path: str) -> str:
    try:
        with open(file_path, "r", encoding="utf-8") as file:
            content = file.read()
        return content
    except FileNotFoundError:
        return f"File not found: {file_path}"
    except Exception as e:
        return f"An error occurred while reading the file: {str(e)}"
    
def get_single_sample_span() -> str:
    return  """
        {
            "resource": {
                "attributes": {
                    "cloud.provider": "aws",
                    "service.name": "appointment-service-gateway",
                    "aws.api_gateway.stage": "prod",
                    "cloud.account.id": "140023401067",
                    "cloud.resource_id": "arn:aws:apigateway:us-east-1::/restapis/vg2r8xjefg/stages/prod",
                    "aws.api_gateway.rest_api_id": "vg2r8xjefg",
                    "cloud.platform": "aws_api_gateway"
                }
            },
            "traceId": "6880250e4fc5b1c42f7b40fc4801f9fd",
            "spanId": "0a5d33388552b5f5",
            "parentSpanId": "30ed105a9aa5beb1",
            "name": "awslambda.Invoke",
            "kind": "CLIENT",
            "startTimeUnixNano": 1753228558420999936,
            "endTimeUnixNano": 1753228558460000000,
            "durationNano": 39000064,
            "attributes": {
                "aws.local.service": "appointment-service-gateway",
                "telemetry.extended": "true",
                "rpc.service": "awslambda",
                "http.url": "https://lambda.us-east-1.amazonaws.com/2015-03-31/functions/arn:aws:lambda:us-east-1:140023401067:function:appointment-service-get:prod/invocations",
                "rpc.system": "aws-api",
                "aws.remote.service": "appointment-service-get",
                "aws.remote.operation": "Invoke",
                "aws.local.environment": "api-gateway:prod",
                "aws.local.operation": "GET /get",
                "http.status_code": 502,
                "aws.span.kind": "CLIENT",
                "http.request.method": "GET",
                "aws.region": "us-east-1",
                "aws.operation": "Invoke",
                "rpc.method": "Invoke",
                "aws.function_name": "appointment-service-get",
                "PlatformType": "Generic",
                "http.method": "GET",
                "url.full": "https://lambda.us-east-1.amazonaws.com/2015-03-31/functions/arn:aws:lambda:us-east-1:140023401067:function:appointment-service-get:prod/invocations",
                "http.response.status_code": 502
            },
            "status": {
                "code": "UNSET"
            },
            "_aws": {
                "xray": {
                    "name": "awslambda",
                    "namespace": "aws",
                    "type": "subsegment"
                }
            }
        }
    
    """