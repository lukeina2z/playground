const {
    CloudWatchLogsClient,
    GetLogEventsCommand
} = require('@aws-sdk/client-cloudwatch-logs');

const { fromIni } = require('@aws-sdk/credential-provider-ini');

const fs = require('fs');
const path = require('path');

const client = new CloudWatchLogsClient({
    credentials: fromIni({ profile: 'demo-readonly' }),
    region: "us-east-1"
});

const LOG_GROUP_NAME = 'aws/spans';
const LOG_STREAM_NAME = 'default';

function toReadableUtcTime(ms) {
    return new Date(ms).toISOString();
}

function toReadableLocalTime(ms) {
    return new Date(ms).toLocaleString();
}

function fromUnixNanoToReadableTime(nanoTime) {
    if (!nanoTime || isNaN(nanoTime)) return null;

    const millis = Math.floor(nanoTime / 1_000_000);
    return new Date(millis).toISOString(); // Or `.toLocaleString()` for local time
}

const now = Date.now();
// const twoHoursAgo = now - 2 * 60 * 60 * 1000;
// const tenMinutuesAgo = now - 7 * 24 * 60 * 60 * 1000;

const tenMinutuesAgo = now - 3 * 60 * 1000;


async function getLogs() {
    let nextToken;
    let allEvents = [];

    console.log('Fetching logs...');

    while (true) {
        const command = new GetLogEventsCommand({
            logGroupName: LOG_GROUP_NAME,
            logStreamName: LOG_STREAM_NAME,
            // startTime: twoHoursAgo,
            startTime: tenMinutuesAgo,
            endTime: now,
            nextToken: nextToken,
            startFromHead: true,
            limit: 10000,
        });

        try {
            const response = await client.send(command);
            // allEvents.push(...response.events);

            // Format each event's timestamps
            const formattedEvents = response.events.map(event => {
                let parsedMessage;
                try {
                    parsedMessage = JSON.parse(event.message);
                } catch (err) {
                    console.error(`Failed to parse message from log ${event.eventId}: ${event.message}`);
                    // Fallback in case it's not valid JSON
                    parsedMessage = event.message;
                }

                const newMsg = {
                    logEventId: event.eventId,
                    logTimestampReadableUtc: toReadableUtcTime(event.timestamp),
                    logTimestampReadableLocal: toReadableLocalTime(event.timestamp),
                    logIngestionTimeReadableUtc: toReadableUtcTime(event.ingestionTime),
                    logIngestionTimeReadableLocal: toReadableLocalTime(event.ingestionTime),
                    trace_id: parsedMessage.traceId,
                    span_name: parsedMessage.name,
                    span_id: parsedMessage.spanId,
                    span_kind: parsedMessage.kind,
                    parent_span_id: parsedMessage.parentSpanId ?? "",
                    status: parsedMessage.status?.code ?? "",
                    start_time: fromUnixNanoToReadableTime(parsedMessage.startTimeUnixNano),
                    end_time: fromUnixNanoToReadableTime(parsedMessage.endTimeUnixNano),
                    duration_nano: parsedMessage.durationNano,
                    rsc_cloud_platform: parsedMessage.resource?.attributes?.['cloud.platform'] ?? "",
                    rsc_cloud_provider: parsedMessage.resource?.attributes?.['cloud.provider'] ?? "",
                    rsc_container_id: parsedMessage.resource?.attributes?.['container.id'] ?? "",
                    rsc_host_id: parsedMessage.resource?.attributes?.['host.id'] ?? "",
                    rsc_host_image_id: parsedMessage.resource?.attributes?.['host.image.id'] ?? "",
                    rsc_host_type: parsedMessage.resource?.attributes?.['host.type'] ?? "",
                    message: parsedMessage,
                }
                return newMsg
            });

            allEvents.push(...formattedEvents);
            if (response.nextForwardToken === nextToken) break;
            nextToken = response.nextForwardToken;
        } catch (err) {
            console.error('Error fetching logs:', err.message);
            break;
        }
    }

    const logFilePath = path.join(__dirname, 'cw-logs.json');
    fs.writeFileSync(logFilePath, JSON.stringify(allEvents, null, 2));
    console.log(`✅ Logs saved to ${logFilePath}`);
}

getLogs();

