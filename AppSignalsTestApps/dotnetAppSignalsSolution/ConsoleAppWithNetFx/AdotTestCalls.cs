using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

using System.Diagnostics;
using Amazon.S3;


namespace ConsoleAppWithNetFx
{
    internal class AdotTestCalls
    {
        private readonly AmazonS3Client s3Client = new AmazonS3Client();
        private readonly HttpClient httpClient = new HttpClient();

        public AdotTestCalls()
        {
        }

        public string OutgoingHttp()
        {
            _ = this.httpClient.GetAsync("https://aws.amazon.com").Result;
            return this.GetTraceId();
        }

        public string AWSSDKCall()
        {
            _ = this.s3Client.ListBucketsAsync().Result;

            return this.GetTraceId();
        }

        private string GetTraceId()
        {
            if (Activity.Current == null)
            {
                return String.Empty;
            }
            var traceId = Activity.Current.TraceId.ToHexString();
            var version = "1";
            var epoch = traceId.Substring(0, 8);
            var random = traceId.Substring(8);
            return "{" + "\"traceId\"" + ": " + "\"" + version + "-" + epoch + "-" + random + "\"" + "}";
        }
    }

}
