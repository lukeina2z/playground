import boto3
import json
from datetime import datetime, timezone
import time
import os
from botocore.exceptions import ClientError
from configparser import ConfigParser

# Constants
LOG_GROUP_NAME = 'aws/spans'
LOG_STREAM_NAME = 'default'

# Get timestamps
now = int(time.time() * 1000)
# start_time = now - 10 * 60 * 1000   # 10 minutes ago
start_time = now - 3 * 1000    # 3 seconds

# Read AWS credentials profile
session = boto3.Session(profile_name='demo-readonly', region_name='us-east-1')
client = session.client('logs')

def to_readable_utc_time(ms):
    return datetime.fromtimestamp(ms / 1000, tz=timezone.utc).isoformat()

def to_readable_local_time(ms):
    return datetime.fromtimestamp(ms / 1000).astimezone().isoformat()

def from_unix_nano_to_readable_time(nano):
    if not nano or not isinstance(nano, int):
        return None
    millis = nano // 1_000_000
    return datetime.fromtimestamp(millis / 1000, tz=timezone.utc).isoformat()

def get_logs():
    print('Fetching logs...')
    next_token = None
    all_events = ""

    while True:
        try:
            params = {
                'logGroupName': LOG_GROUP_NAME,
                'logStreamName': LOG_STREAM_NAME,
                'startTime': start_time,
                'endTime': now,
                'startFromHead': True,
                'limit': 10000
            }

            if next_token:
                params['nextToken'] = next_token

            response = client.get_log_events(**params)
            print(f"Got {len(response['events'])} events.")
            print("#################")
            for event in response['events']:
                try:
                    parsed_message = json.loads(event['message'])
                except json.JSONDecodeError:
                    print(f"Failed to parse message: {event['message']}")
                    parsed_message = event['message']

                # all_events.append(parsed_message)

                if isinstance(parsed_message, dict):
                    spanContent = f"Begin open telemetry span {parsed_message.get('spanId')}. "
                    spanContent += f"Trace id is {parsed_message.get('traceId')}. "
                    spanContent += f"Span name is {parsed_message.get('name')}. "
                    spanContent += f"Span kind is {parsed_message.get('kind')}. "
                    spanContent += f"Parent span id is {parsed_message.get('parentSpanId')}. "
                    spanContent += f"Status is {parsed_message.get('status', {}).get('code', '')}. "
                    spanContent += f"Span started at  {from_unix_nano_to_readable_time(parsed_message.get('startTimeUnixNano'))}. "
                    spanContent += f"Span ended at  {from_unix_nano_to_readable_time(parsed_message.get('endTimeUnixNano'))}. "
                    spanContent += f"Span duration in nano seconds is {parsed_message.get('durationNano')}. "

                    formatted = {
                        'trace_id': parsed_message.get('traceId'),
                        'span_name': parsed_message.get('name'),
                        'span_id': parsed_message.get('spanId'),
                        'span_kind': parsed_message.get('kind'),
                        'parent_span_id': parsed_message.get('parentSpanId', ''),
                        'status': parsed_message.get('status', {}).get('code', ''),
                        'start_time': from_unix_nano_to_readable_time(parsed_message.get('startTimeUnixNano')),
                        'end_time': from_unix_nano_to_readable_time(parsed_message.get('endTimeUnixNano')),
                        'duration_nano': parsed_message.get('durationNano'),
                        'rsc_cloud_platform': parsed_message.get('resource', {}).get('attributes', {}).get('cloud.platform', ''),
                        'rsc_cloud_provider': parsed_message.get('resource', {}).get('attributes', {}).get('cloud.provider', ''),
                        'rsc_container_id': parsed_message.get('resource', {}).get('attributes', {}).get('container.id', ''),
                        'rsc_host_id': parsed_message.get('resource', {}).get('attributes', {}).get('host.id', ''),
                        'rsc_host_image_id': parsed_message.get('resource', {}).get('attributes', {}).get('host.image.id', ''),
                        'rsc_host_type': parsed_message.get('resource', {}).get('attributes', {}).get('host.type', ''),
                        'message': parsed_message,
                    }

                    spanContent += f"End of open telemetry span {parsed_message.get('spanId')}. \n\n"

                    all_events += (spanContent)

            new_token = response.get('nextForwardToken')
            if new_token == next_token:
                break
            next_token = new_token

        except ClientError as e:
            print(f"Error fetching logs: {e}")
            break

    log_file_path = os.path.join(os.path.dirname(__file__), './data/readable-spans/spans.txt')

    # Ensure the directory exists
    os.makedirs(os.path.dirname(log_file_path), exist_ok=True)

    with open(log_file_path, 'w') as f:
        f.write(str(all_events))
        # json.dump(all_events, f, indent=2)
    print(f"✅ Logs saved to {log_file_path}")


if __name__ == '__main__':
    get_logs()
    print("done!")
