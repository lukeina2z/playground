# DevFooSol: Debugging sign-in and sign-out

`DevFooSol.sln` contains `FirstADWebApp`, an ASP.NET Core MVC application
targeting .NET 8. Authentication uses Microsoft Identity Web and OpenID Connect
with Microsoft Entra ID.

## Where the authentication code lives

The sign-in and sign-out actions come from the `Microsoft.Identity.Web.UI`
NuGet package. There is no local `AccountController.cs` in this project.

| Location | Purpose |
| --- | --- |
| `FirstADWebApp\Program.cs:14` | Registers authentication with `AddMicrosoftIdentityWebApp`. |
| `FirstADWebApp\Program.cs:22` | Requires authenticated users through the global authorization policy. |
| `FirstADWebApp\Program.cs:27` | Registers the package's account controller and Razor pages with `AddMicrosoftIdentityUI`. |
| `FirstADWebApp\Views\Shared\_LoginPartial.cshtml:8` | Links to the `MicrosoftIdentity` area's `Account.SignOut` action. |
| `FirstADWebApp\Views\Shared\_LoginPartial.cshtml:14` | Links to the `MicrosoftIdentity` area's `Account.SignIn` action. |
| `FirstADWebApp\appsettings.json:7` | Configures the sign-in callback path as `/signin-oidc`. |
| `FirstADWebApp\Controllers\HomeController.cs:25` | Calls Microsoft Graph after the request has been authenticated. |

Line numbers describe the code at the time this guide was written; use the
method names if the files change.

An unauthenticated request to the home page triggers an OpenID Connect challenge,
redirects the browser to Microsoft sign-in, and returns to `/signin-oidc`.
The authentication middleware processes that callback before the browser returns
to the requested page.

Signing out invokes the package's account controller, which requests sign-out
from both the application's cookie authentication scheme and OpenID Connect.
This clears the application's authentication cookie and redirects the browser
to Microsoft sign-out.

## 1. Enable debugging library code in Visual Studio

Open **Tools > Options > Debugging** and configure:

| Settings page | Setting |
| --- | --- |
| General | Uncheck **Enable Just My Code**. |
| General | Check **Enable Source Link support**. |
| Symbols | Enable **Microsoft Symbol Servers**. |
| Symbols | Enable **NuGet.org Symbol Server**. |

These settings allow Visual Studio to retrieve matching debugging symbols and
library source. Downloading them requires network access.

## 2. Set breakpoints on the sign-in and sign-out actions

Choose **Debug > New Breakpoint > Function Breakpoint**. Add each of the
following fully qualified function names as a separate breakpoint:

```text
Microsoft.Identity.Web.UI.Areas.MicrosoftIdentity.Controllers.AccountController.SignIn
Microsoft.Identity.Web.UI.Areas.MicrosoftIdentity.Controllers.AccountController.SignOut
```

Select the **Debug** build configuration, set **FirstADWebApp** as the startup
project, and press **F5** to start with the debugger attached. Do not use
**Ctrl+F5**, which starts without debugging.

The launch profiles in `FirstADWebApp\Properties\launchSettings.json` use:

| Visual Studio launch profile | HTTPS address |
| --- | --- |
| `https` | `https://localhost:7076` |
| `IIS Express` | `https://localhost:44305` |

Use the address for the selected profile. The corresponding sign-in redirect URI
in the Entra app registration must match that origin plus `/signin-oidc`.

Click **Sign out** while signed in to hit the sign-out action breakpoint.
To invoke the sign-in action explicitly, navigate to
`/MicrosoftIdentity/Account/SignIn` on the running site, for example:

```text
https://localhost:7076/MicrosoftIdentity/Account/SignIn
```

## 3. Follow the authentication redirects and callback

**The initial home-page request can bypass `AccountController.SignIn`.**
Because the app requires authentication globally, authorization can challenge
an unauthenticated request directly. A sign-in redirect does not necessarily
mean the sign-in controller action ran.

Add these function breakpoints to follow the underlying OpenID Connect flow:

```text
Microsoft.AspNetCore.Authentication.OpenIdConnect.OpenIdConnectHandler.HandleChallengeAsync
Microsoft.AspNetCore.Authentication.OpenIdConnect.OpenIdConnectHandler.HandleRemoteAuthenticateAsync
Microsoft.AspNetCore.Authentication.OpenIdConnect.OpenIdConnectHandler.SignOutAsync
```

| Method | What it catches |
| --- | --- |
| `HandleChallengeAsync` | The outgoing redirect to Microsoft sign-in, including automatic authentication challenges. |
| `HandleRemoteAuthenticateAsync` | Processing the sign-in response received at `/signin-oidc`. |
| `SignOutAsync` | The outgoing redirect to Microsoft sign-out. |

`/signin-oidc` is handled by authentication middleware, not by a local MVC
controller action. The Microsoft-hosted sign-in page runs outside this
application and cannot be stepped through with the local debugger.

## 4. Break in application code after authentication

Open `FirstADWebApp\Controllers\HomeController.cs` and place a breakpoint on
this statement in `Index` (line 25):

```csharp
var user = await _graphServiceClient.Me.Request().GetAsync();
```

Click the left gutter or place the cursor on the statement and press **F9**.
When execution pauses here, inspect `User.Identity`,
`User.Identity?.IsAuthenticated`, and `User.Claims` in Watch or QuickWatch.
After the Graph call completes, inspect `user`.

| Key | Action |
| --- | --- |
| F9 | Toggle a breakpoint on an executable line. |
| F10 | Step over the current statement. |
| F11 | Step into a call when source and symbols are available. |
| F5 | Continue execution, or start debugging when stopped. |

## If breakpoints are not hit

- If a library breakpoint stays hollow after the app starts, open
  **Debug > Windows > Modules**. Find `Microsoft.Identity.Web.UI.dll` or
  `Microsoft.AspNetCore.Authentication.OpenIdConnect.dll`, right-click it, and
  select **Load Symbols**. **Symbol Load Information** explains failed symbol
  searches. A breakpoint may remain pending until its module is loaded.
- Confirm the app was started with **F5** and the breakpoint is enabled.
- If the sign-in action breakpoint is not hit, use the explicit sign-in URL
  above or the `HandleChallengeAsync` breakpoint.
- If the browser already has a valid application authentication cookie, simply
  visiting the home page will not start a fresh sign-in flow. Sign out first or
  use a private browser window for a fresh application session.
- Breakpoints on authentication registration in `Program.cs` run at startup,
  not once per sign-in or sign-out.

## Library source and debugger documentation

- [Microsoft Identity Web UI account controller (3.15.1)](https://github.com/AzureAD/microsoft-identity-web/blob/3.15.1/src/Microsoft.Identity.Web.UI/Areas/MicrosoftIdentity/Controllers/AccountController.cs)
- [ASP.NET Core OpenID Connect handler (8.0.29)](https://github.com/dotnet/aspnetcore/blob/v8.0.29/src/Security/Authentication/OpenIdConnect/src/OpenIdConnectHandler.cs)
- [Visual Studio source and symbol debugging settings](https://learn.microsoft.com/en-us/visualstudio/debugger/how-to-debug-dotnet-framework-source?view=vs-2022)
