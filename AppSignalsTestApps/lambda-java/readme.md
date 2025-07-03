
## How to deploy this Java Lambda
1. Build.
    ```sh
    ./gradlew clean build shadowJar
    ```
2. Create Java Lambda with the build output.
   ```sh
   ./lib/build/libs/lambda.jar
   ```
3. Set handler
   ```sh
   org.example.MyLambda::handleRequest
   ```
4. Enable Application Signals and Lambda service traces.
5. Enable debug log.
   ```sh
   OTEL_JAVAAGENT_DEBUG=true
   OTEL_LOG_LEVEL=debug
   ```



