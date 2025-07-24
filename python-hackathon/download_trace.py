#!/usr/bin/env python3
"""
CloudWatch Logs Trace Search Function

This module provides functionality to search for specific trace IDs in CloudWatch logs
and return formatted results as a string.
"""

import boto3
import json
import time
from datetime import datetime, timedelta
from typing import Optional, Dict, Any, List


def search_trace_in_cloudwatch(
    trace_id: str,
    log_group: str = "aws/spans",
    days_back: int = 8,
    profile_name: str = "demo-readonly",
    region: str = "us-east-1",
    max_wait_time: int = 300
) -> str:
    """
    Search for a specific trace ID in CloudWatch logs and return formatted results.
    
    Args:
        trace_id (str): The trace ID to search for
        log_group (str): CloudWatch log group name (default: "aws/spans")
        days_back (int): Number of days to search back (default: 8)
        profile_name (str): AWS profile name (default: "demo-readonly")
        region (str): AWS region (default: "us-east-1")
        max_wait_time (int): Maximum time to wait for query completion in seconds (default: 300)
    
    Returns:
        str: Formatted string containing all log events and analysis
    
    Raises:
        Exception: If query fails or times out
    """
    
    # Initialize boto3 session with profile
    session = boto3.Session(profile_name=profile_name)
    logs_client = session.client('logs', region_name=region)
    
    # Calculate time range
    end_time = datetime.utcnow()
    start_time = end_time - timedelta(days=days_back)
    
    # Convert to Unix timestamps (seconds)
    start_timestamp = int(start_time.timestamp())
    end_timestamp = int(end_time.timestamp())
    
    # Construct CloudWatch Insights query
    query_string = f"fields @timestamp, @message | filter @message like /{trace_id}/ | sort @timestamp desc"
    
    try:
        # Start the query
        print(f"Starting CloudWatch Logs query for trace ID: {trace_id}")
        print(f"Log group: {log_group}")
        print(f"Time range: {start_time.strftime('%Y-%m-%d %H:%M:%S')} to {end_time.strftime('%Y-%m-%d %H:%M:%S')} UTC")
        
        response = logs_client.start_query(
            logGroupName=log_group,
            startTime=start_timestamp,
            endTime=end_timestamp,
            queryString=query_string
        )
        
        query_id = response['queryId']
        print(f"Query ID: {query_id}")
        
        # Poll for results
        start_poll_time = time.time()
        while True:
            if time.time() - start_poll_time > max_wait_time:
                raise Exception(f"Query timed out after {max_wait_time} seconds")
            
            result = logs_client.get_query_results(queryId=query_id)
            status = result['status']
            
            print(f"Query status: {status}")
            
            if status == 'Complete':
                break
            elif status == 'Failed':
                raise Exception("Query failed")
            elif status in ['Running', 'Scheduled']:
                time.sleep(2)  # Wait 2 seconds before checking again
            else:
                raise Exception(f"Unknown query status: {status}")
        
        # Process results
        events = result.get('results', [])
        statistics = result.get('statistics', {})
        
        return format_trace_results(trace_id, events, statistics, log_group, start_time, end_time)
        
    except Exception as e:
        error_msg = f"Error searching for trace ID {trace_id}: {str(e)}"
        print(error_msg)
        return error_msg


def format_trace_results(
    trace_id: str,
    events: List[List[Dict[str, str]]],
    statistics: Dict[str, Any],
    log_group: str,
    start_time: datetime,
    end_time: datetime
) -> str:
    """
    Format the CloudWatch query results into a readable string.
    
    Args:
        trace_id (str): The searched trace ID
        events (List): List of log events from CloudWatch
        statistics (Dict): Query statistics
        log_group (str): Log group name
        start_time (datetime): Search start time
        end_time (datetime): Search end time
    
    Returns:
        str: Formatted results string
    """
    
    output = []
    output.append("=" * 80)
    output.append(f"CLOUDWATCH LOGS TRACE SEARCH RESULTS")
    output.append("=" * 80)
    output.append(f"Trace ID: {trace_id}")
    output.append(f"Log Group: {log_group}")
    output.append(f"Search Period: {start_time.strftime('%Y-%m-%d %H:%M:%S')} to {end_time.strftime('%Y-%m-%d %H:%M:%S')} UTC")
    output.append(f"Total Events Found: {len(events)}")
    output.append("")
    
    # Add statistics
    if statistics:
        output.append("QUERY STATISTICS:")
        output.append("-" * 40)
        for key, value in statistics.items():
            if isinstance(value, float):
                output.append(f"{key}: {value:,.0f}")
            else:
                output.append(f"{key}: {value}")
        output.append("")
    
    if not events:
        output.append("No events found for the specified trace ID.")
        return "\n".join(output)
    
    # Process and format each event
    output.append("LOG EVENTS:")
    output.append("-" * 40)
    
    for i, event in enumerate(events, 1):
        # Extract timestamp and message from the event
        timestamp = ""
        message = ""
        
        for field in event:
            if field.get('field') == '@timestamp':
                timestamp = field.get('value', '')
            elif field.get('field') == '@message':
                message = field.get('value', '')
        
        output.append(f"EVENT #{i}")
        output.append(f"Timestamp: {timestamp}")
        output.append("")
        
        # Try to parse the message as JSON for better formatting
        try:
            parsed_message = json.loads(message)
            
            # Extract key information
            service_name = parsed_message.get('resource', {}).get('attributes', {}).get('service.name', 'Unknown')
            span_name = parsed_message.get('name', 'Unknown')
            span_kind = parsed_message.get('kind', 'Unknown')
            status = parsed_message.get('status', {}).get('code', 'Unknown')
            span_id = parsed_message.get('spanId', 'Unknown')
            parent_span_id = parsed_message.get('parentSpanId', 'None')
            
            output.append(f"Service: {service_name}")
            output.append(f"Span Name: {span_name}")
            output.append(f"Span Kind: {span_kind}")
            output.append(f"Status: {status}")
            output.append(f"Span ID: {span_id}")
            output.append(f"Parent Span ID: {parent_span_id}")
            
            # Extract duration if available
            duration_nano = parsed_message.get('durationNano')
            if duration_nano:
                duration_ms = duration_nano / 1_000_000
                output.append(f"Duration: {duration_ms:.3f} ms")
            
            # Extract HTTP information if available
            attributes = parsed_message.get('attributes', {})
            if 'http.method' in attributes:
                output.append(f"HTTP Method: {attributes['http.method']}")
            if 'http.url' in attributes:
                output.append(f"HTTP URL: {attributes['http.url']}")
            if 'http.status_code' in attributes:
                output.append(f"HTTP Status: {attributes['http.status_code']}")
            
            # Extract error information if available
            events_list = parsed_message.get('events', [])
            for event_item in events_list:
                if event_item.get('name') == 'exception':
                    exception_attrs = event_item.get('attributes', {})
                    output.append("")
                    output.append("EXCEPTION DETAILS:")
                    output.append(f"Type: {exception_attrs.get('exception.type', 'Unknown')}")
                    output.append(f"Message: {exception_attrs.get('exception.message', 'Unknown')}")
                    
                    stacktrace = exception_attrs.get('exception.stacktrace', '')
                    if stacktrace:
                        output.append("Stack Trace:")
                        for line in stacktrace.split('\\n'):
                            output.append(f"  {line}")
            
            output.append("")
            output.append("RAW JSON MESSAGE:")
            output.append(json.dumps(parsed_message, indent=2))
            
        except json.JSONDecodeError:
            # If not valid JSON, just display the raw message
            output.append("RAW MESSAGE:")
            output.append(message)
        
        output.append("")
        output.append("-" * 60)
        output.append("")
    
    # Add summary analysis
    output.append("TRACE ANALYSIS SUMMARY:")
    output.append("-" * 40)
    
    # Analyze the trace for common patterns
    services = set()
    error_count = 0
    total_duration = 0
    
    for event in events:
        for field in event:
            if field.get('field') == '@message':
                try:
                    parsed = json.loads(field.get('value', '{}'))
                    service_name = parsed.get('resource', {}).get('attributes', {}).get('service.name')
                    if service_name:
                        services.add(service_name)
                    
                    if parsed.get('status', {}).get('code') == 'ERROR':
                        error_count += 1
                    
                    duration = parsed.get('durationNano', 0)
                    if duration:
                        total_duration += duration / 1_000_000  # Convert to ms
                        
                except json.JSONDecodeError:
                    continue
    
    output.append(f"Services Involved: {', '.join(sorted(services)) if services else 'Unknown'}")
    output.append(f"Error Events: {error_count}")
    output.append(f"Total Duration: {total_duration:.3f} ms")
    
    return "\n".join(output)


def main():
    """
    Example usage of the search function.
    """
    # Example trace ID - replace with actual trace ID
    trace_id = "6880250e4fc5b1c42f7b40fc4801f9fd"
    
    try:
        result = search_trace_in_cloudwatch(
            trace_id=trace_id,
            log_group="aws/spans",
            days_back=8,
            profile_name="demo-readonly",
            region="us-east-1"
        )
        
        print(result)
        
        # Optionally save to file
        with open(f"trace_{trace_id}_results.txt", "w") as f:
            f.write(result)
        print(f"\nResults saved to trace_{trace_id}_results.txt")
        
    except Exception as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    main()
