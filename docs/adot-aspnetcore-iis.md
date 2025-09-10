
## Enable Application Signals for ASP.NET Core App on EC2 Windows

1. Create a Windows 2022 server on EC2.
2. Right click this EC2 instance, "Security-> Modify IAM Role". Ensure you have the role set. This role should have policies attached as instructed by this article https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Application-Signals-Enable-EC2Main.html#CloudWatch-Application-Signals-Enable-Other-agent
3. Login windows, "Start->Server Manager->Add roles and features->Role-based or feature-based installation->"Web Server(IIS)".
4. Install Visual Studio https://visualstudio.microsoft.com. Enable "ASP.NET and web development" on installer UI.
5. Download "ADOT .NET Integration Testing App". https://github.com/aws-observability/aws-otel-dotnet-instrumentation/tree/main/sample-applications/integration-test-app
6. Launch Visual Studio and load "integration-test-app.sln". Build and run with "IIS Express", ensure you can access http://localhost:8080, http://localhost:8080/aws-sdk-call, and http://localhost:8080/outgoing-http-call.
7. Follow this doc and publish this testing ASP.NET Core app to IIS. Browse this new web site, ensure it works. <br>
    Publish an ASP.NET Core app to IIS <br>
    https://learn.microsoft.com/en-us/aspnet/core/tutorials/publish-to-iis?view=aspnetcore-9.0&tabs=visual-studio

8. Download and start the CloudWatch agent.

    https://github.com/aws-observability/aws-otel-dotnet-instrumentation/blob/main/SETUP_GUIDE.md#set-up-cloudwatch-agent-with-application-signals-enabled-1
        
    Note: The command to boot agent is wrong in that doc. Use this one.
    ```PowerShell
    & $Env:ProgramFiles\Amazon\AmazonCloudWatchAgent\amazon-cloudwatch-agent-ctl.ps1 -m ec2 -a fetch-config -s -c file:C:\tmp\application-signals-cwagent-config.txt
    ```

    Manual installation on Amazon EC2
    https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/manual-installation.html

9.  Download "AWS.Otel.DotNet.Auto.psm1" from ADOT .NET release https://github.com/aws-observability/aws-otel-dotnet-instrumentation/releases. Open a PowerShell console with Admin permission.
    ```PowerShell
    Import-Module AWS.Otel.DotNet.Auto.psm1
    Get-Command -Module AWS.Otel.DotNet.Auto

    Install-OpenTelemetryCore

    Get-OpenTelemetryInstallVersion
    Get-OpenTelemetryInstallDirectory

    Register-OpenTelemetryForIIS
    ```
10. Now visit the web sites. It should upload traces to CloudWatch backend.

p.s. a. Check environment variables. Use Process Explorer to check W3WP.exe which has your web site's name. https://learn.microsoft.com/en-us/sysinternals/downloads/process-explorer

p.s. b. Set service name explicitly. In IIS manager, choose server name, double click "Configuration Editor". In "Section:", choose "appSettings->system.applicationHost->applicationPools". Click "..." at the end of  "(Collection)" row. Highlight your application pool, and click "environmentVariables" at bottom. Add OTEL_SERVICE_NAME  "your-service-name". Don't forget to click "Apply" at the end. Run "iisreset", visit the web site and check trace again.