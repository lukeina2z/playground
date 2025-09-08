
import boto3

s3 = boto3.resource("s3")

def call_aws_sdk():
    for bucket in s3.buckets.all():
        print(bucket.name)


if __name__ == "__main__":
    call_aws_sdk()