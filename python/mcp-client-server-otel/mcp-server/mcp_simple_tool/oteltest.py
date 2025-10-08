
print("Test OTel auto instrumenation...!")

import requests
try:
    response = requests.get("http://www.aws.com", timeout=5)
    print(f"Status: {response.status_code}, Response time: {response.elapsed.total_seconds():.2f}s")
except Exception as e:
    print( f"!!! Error: {str(e)}")

print("End of testing OTel auto instrumenation...!")


import time
import boto3

s3 = boto3.resource("s3")

def call_aws_sdk():
    bucket_names = [bucket.name for bucket in s3.buckets.all()]
    return ",".join(bucket_names)

def call_http() -> str:
    try:
        response = requests.get("http://www.aws.com", timeout=120)
        return f"HTTP status code: {response.status_code}"
    except Exception as e:
        return f"Error: {str(e)}"


def otel_test_call(count):
    if count <= 0:
          count = 10;
    while count > 0:
        call_http()
        time.sleep(0.03)
        call_aws_sdk()
        time.sleep(0.03)
        count = count - 1

def main():
    otel_test_call(1000)

if __name__ == "__main__":
    main()




