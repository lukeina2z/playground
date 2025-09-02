using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using System.Web.Mvc;
using System.Runtime.Remoting.Messaging;

using Amazon.S3;

namespace HttpServer.Controllers
{
    public class HttpCallController : Controller
    {
        private string GetTraceId()
        {
            // For .NET Framework, we'll use a placeholder until OpenTelemetry is properly configured
            // The actual trace ID will be available when OpenTelemetry auto-instrumentation is enabled
            return CallContext.LogicalGetData("TraceId")?.ToString() ?? "Trace will be available with OpenTelemetry";
        }

        // GET: /outgoing-http-call
        public async Task<ActionResult> OutgoingHttpCall()
        {
            using (HttpClient client = new HttpClient())
            {
                client.Timeout = TimeSpan.FromSeconds(10);

                try
                {
                    HttpResponseMessage response = await client.GetAsync("https://aws.amazon.com");
                    response.EnsureSuccessStatusCode();

                    string responseBody = await response.Content.ReadAsStringAsync();

                    StringBuilder sb = new StringBuilder();
                    sb.AppendLine($"Trace ID: {GetTraceId()}");
                    sb.AppendLine();
                    sb.AppendLine(responseBody.Substring(0, 1000));
                    
                    ViewBag.ResponseContent = sb.ToString();
                    return View();
                }
                catch (Exception ex)
                {
                    ViewBag.ResponseContent = $"Trace ID: {GetTraceId()}\n\nError: " + ex.Message;
                    return View();
                }
            }
        }

        public async Task<ActionResult> AwsSdkCall()
        {
            try
            {
                using (AmazonS3Client s3Client = new AmazonS3Client())
                {
                    Amazon.S3.Model.ListBucketsResponse resp = await s3Client.ListBucketsAsync();
                    StringBuilder sb = new StringBuilder();
                    
                    sb.AppendLine($"Trace ID: {GetTraceId()}");
                    sb.AppendLine();
                    
                    foreach (var bucket in resp.Buckets)
                    {
                        sb.AppendLine(bucket.BucketName);
                    }
                    
                    ViewBag.ResponseContent = sb.ToString();
                }
            }
            catch (Exception ex)
            {
                ViewBag.ResponseContent = $"Trace ID: {GetTraceId()}\n\nError: " + ex.Message;
            }
            
            return View();
        }
    }
}