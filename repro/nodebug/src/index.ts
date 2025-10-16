import http from 'http';

function pingWebSite(url: string): Promise<string> {
  console.log(`Ping web site.`);

  return new Promise((resolve, reject) => {
    const httpReq = http.get(url, (httpResponse) => {
      console.log('Response status code:', httpResponse.statusCode);
      let data = `XRayTraceID: ${process.env["_X_AMZN_TRACE_ID"] || "Trace Id not available"}\r\n`;
      httpResponse.on('data', (chunk) => {
        data += chunk;
      });

      httpResponse.on('end', () => {
        console.log(`Response body: ${data}`);
        resolve(data);
      });
    });

    httpReq.on('error', (error) => {
      console.error(`Error in outgoing-http-call:  ${error.message}`);
      reject(error);
    });
  });
};

const fn = async () => {
  await pingWebSite("http://www.msn.com");
  const retFoo = await pingWebSite("http://www.msn.com");
  console.log(retFoo);
}

fn();

