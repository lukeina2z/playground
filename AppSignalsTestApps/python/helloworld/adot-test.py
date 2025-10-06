import time
import boto3

s3 = boto3.resource("s3")

def call_aws_sdk():
    for bucket in s3.buckets.all():
        if (bucket is None):
            print(bucket.name)

def main():
    while True:
        call_aws_sdk()
        time.sleep(0.06)

if __name__ == "__main__":
    main()
