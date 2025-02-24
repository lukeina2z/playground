import { context, SpanKind, trace } from "@opentelemetry/api";
import serverless from "serverless-http";
import webApp from "./src/webapi.mjs"

// const port = 3000;
// webApp.listen(port, () => {
//     console.log(`Server is running at http://localhost:${port}`);
// });

export async function handler(event, context) {
    console.info('xxx Start serving lambda request.');

    // Extract API Gateway details from the event object
    const requestContext = event.requestContext || {};
    const domain = requestContext.domainName || 'unknown-domain';
    const path = requestContext.path || '/';
    const apiGatewayUrl = `https://${domain}${path}`;
    const httpMethod = event.httpMethod || 'UNKNOWN';

    const spanName = `xSpan-${httpMethod}-${apiGatewayUrl}`;
    console.log(`root span name: ${spanName}`);
    const tracer = trace.getTracer('lambda-express-tracer');

    return tracer.startActiveSpan(spanName,
        { kind: SpanKind.SERVER},
        async (span) => {
            try {
                // Add API Gateway URL to the span
                span.setAttribute('api.gateway.url', apiGatewayUrl);
                span.setAttribute('http.method', event.httpMethod || 'UNKNOWN');
                span.setAttribute('http.path', path);

                const paramEvent = "param-event:\r\n\r\n" + JSON.stringify(event, null, 2) + "\r\n\r\n";
                console.log(`event: ${paramEvent}`);
                const paramContext = "param-context:\r\n\r\n" + JSON.stringify(context, null, 2) + "\r\n\r\n";
                console.log(`context: ${paramContext}`);

                const serverlessHandler = serverless(webApp);
                let retObj = await serverlessHandler(event, context);
                console.log(`retObj: ${JSON.stringify(retObj, null, 2)}`);

                retObj.body += ("\r\n\r\n" + paramEvent + paramContext);
                return retObj;
            } catch (error) {
                span.setAttribute('error', true);
                span.recordException(error);
                throw error;
            } finally {
                span.end(); // Ensure span is ended
            }
        });
}

/// handler({ key1: 'value1', key2: 'value2' }, { /* context object */ });

