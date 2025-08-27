//using System;
//using System.Collections.Generic;
//using System.Diagnostics;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;

//namespace ConsoleApp
//{
//    internal class OTelTraceTest
//    {
//    }
//}


using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

using System.Diagnostics;
using Amazon.S3;


namespace ConsoleApp
{
    internal class OTelTraceTest
    {
        private readonly AmazonS3Client s3Client = new AmazonS3Client();
        private readonly HttpClient httpClient = new HttpClient();

        public OTelTraceTest()
        {
        }

        public string OutgoingHttp()
        {
            var ret = this.httpClient.GetAsync("http://www.amazon.com").Result;
            System.Console.WriteLine(ret);
            return this.GetTraceId();
        }

        public string AWSSDKCall()
        {
            var ret = this.s3Client.ListBucketsAsync().Result;

            foreach (var bucket in ret.Buckets)
            {
                Console.WriteLine(bucket.BucketName);
            }

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
