

```sh



mac (25-09-19 7:11:38) <0> [~/github/otel-java/wk-adot-pr/adot-java-main]  
7cf34de09d4c % ./gradlew :otelagent:dependencies           

> Task :otelagent:dependencies

------------------------------------------------------------
Project ':otelagent'
------------------------------------------------------------

annotationProcessor - Annotation processors and their dependencies for source set 'main'.
\--- project :dependencyManagement
     +--- com.amazonaws:aws-java-sdk-bom:1.12.599
     +--- com.fasterxml.jackson:jackson-bom:2.16.0
     +--- com.google.guava:guava-bom:33.0.0-jre
     +--- com.google.protobuf:protobuf-bom:3.25.1
     +--- com.linecorp.armeria:armeria-bom:1.26.4
     +--- io.grpc:grpc-bom:1.59.1
     +--- io.netty:netty-bom:4.1.126.Final
     +--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom-alpha:2.18.1-alpha
     |    +--- io.opentelemetry:opentelemetry-bom:1.52.0
     |    +--- io.opentelemetry:opentelemetry-bom-alpha:1.52.0-alpha
     |    |    \--- io.opentelemetry:opentelemetry-bom:1.52.0
     |    \--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom:2.18.1
     |         \--- io.opentelemetry:opentelemetry-bom:1.52.0
     +--- org.apache.logging.log4j:log4j-bom:2.21.1
     +--- org.junit:junit-bom:5.10.1
     +--- org.springframework.boot:spring-boot-dependencies:2.7.17
     +--- org.testcontainers:testcontainers-bom:1.19.3
     \--- software.amazon.awssdk:bom:2.30.17

compileClasspath - Compile classpath for source set 'main'.
+--- io.opentelemetry.javaagent:opentelemetry-javaagent -> 2.18.1
\--- project :dependencyManagement
     +--- com.amazonaws:aws-java-sdk-bom:1.12.599
     +--- com.fasterxml.jackson:jackson-bom:2.16.0
     +--- com.google.guava:guava-bom:33.0.0-jre
     +--- com.google.protobuf:protobuf-bom:3.25.1
     +--- com.linecorp.armeria:armeria-bom:1.26.4
     +--- io.grpc:grpc-bom:1.59.1
     +--- io.netty:netty-bom:4.1.126.Final
     +--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom-alpha:2.18.1-alpha
     |    +--- io.opentelemetry:opentelemetry-bom:1.52.0
     |    +--- io.opentelemetry:opentelemetry-bom-alpha:1.52.0-alpha
     |    |    \--- io.opentelemetry:opentelemetry-bom:1.52.0
     |    \--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom:2.18.1
     |         +--- io.opentelemetry:opentelemetry-bom:1.52.0
     |         \--- io.opentelemetry.javaagent:opentelemetry-javaagent:2.18.1 (c)
     +--- org.apache.logging.log4j:log4j-bom:2.21.1
     +--- org.junit:junit-bom:5.10.1
     +--- org.springframework.boot:spring-boot-dependencies:2.7.17
     +--- org.testcontainers:testcontainers-bom:1.19.3
     +--- software.amazon.awssdk:bom:2.30.17
     \--- io.opentelemetry.javaagent:opentelemetry-javaagent:2.18.1 (c)

compileOnly - Compile-only dependencies for the 'main' feature. (n)
\--- io.opentelemetry.javaagent:opentelemetry-javaagent (n)

default - Configuration for default artifacts. (n)
No dependencies

dependencyManagement (n)
\--- project dependencyManagement (n)

implementation - Implementation dependencies for the 'main' feature. (n)
No dependencies

javaagentLibs
+--- project :dependencyManagement
|    +--- com.amazonaws:aws-java-sdk-bom:1.12.599
|    |    \--- com.amazonaws:aws-java-sdk-core:1.12.599 -> 1.12.773 (c)
|    +--- com.fasterxml.jackson:jackson-bom:2.16.0 -> 2.19.2
|    |    +--- com.fasterxml.jackson.core:jackson-annotations:2.19.2 (c)
|    |    +--- com.fasterxml.jackson.core:jackson-core:2.19.2 (c)
|    |    +--- com.fasterxml.jackson.core:jackson-databind:2.19.2 (c)
|    |    +--- com.fasterxml.jackson.dataformat:jackson-dataformat-cbor:2.19.2 (c)
|    |    \--- com.fasterxml.jackson.dataformat:jackson-dataformat-yaml:2.19.2 (c)
|    +--- com.google.guava:guava-bom:33.0.0-jre
|    +--- com.google.protobuf:protobuf-bom:3.25.1
|    +--- com.linecorp.armeria:armeria-bom:1.26.4
|    +--- io.grpc:grpc-bom:1.59.1
|    +--- io.netty:netty-bom:4.1.126.Final
|    |    +--- io.netty:netty-codec-http:4.1.126.Final (c)
|    |    +--- io.netty:netty-codec-http2:4.1.126.Final (c)
|    |    +--- io.netty:netty-codec:4.1.126.Final (c)
|    |    +--- io.netty:netty-transport:4.1.126.Final (c)
|    |    +--- io.netty:netty-common:4.1.126.Final (c)
|    |    +--- io.netty:netty-buffer:4.1.126.Final (c)
|    |    +--- io.netty:netty-handler:4.1.126.Final (c)
|    |    +--- io.netty:netty-transport-classes-epoll:4.1.126.Final (c)
|    |    +--- io.netty:netty-resolver:4.1.126.Final (c)
|    |    \--- io.netty:netty-transport-native-unix-common:4.1.126.Final (c)
|    +--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom-alpha:2.18.1-alpha
|    |    +--- io.opentelemetry:opentelemetry-bom:1.52.0
|    |    |    \--- io.opentelemetry:opentelemetry-sdk-trace:1.52.0 (c)
|    |    +--- io.opentelemetry:opentelemetry-bom-alpha:1.52.0-alpha
|    |    |    \--- io.opentelemetry:opentelemetry-bom:1.52.0 (*)
|    |    \--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom:2.18.1
|    |         \--- io.opentelemetry:opentelemetry-bom:1.52.0 (*)
|    +--- org.apache.logging.log4j:log4j-bom:2.21.1
|    +--- org.junit:junit-bom:5.10.1
|    +--- org.springframework.boot:spring-boot-dependencies:2.7.17
|    |    +--- com.fasterxml.jackson.core:jackson-annotations:2.13.5 -> 2.19.2 (c)
|    |    +--- com.fasterxml.jackson.core:jackson-core:2.13.5 -> 2.19.2 (c)
|    |    +--- com.fasterxml.jackson.core:jackson-databind:2.13.5 -> 2.19.2 (c)
|    |    +--- com.fasterxml.jackson.dataformat:jackson-dataformat-cbor:2.13.5 -> 2.19.2 (c)
|    |    +--- com.fasterxml.jackson.dataformat:jackson-dataformat-yaml:2.13.5 -> 2.19.2 (c)
|    |    +--- org.jetbrains.kotlin:kotlin-stdlib:1.6.21 -> 2.2.0 (c)
|    |    +--- com.squareup.okhttp3:okhttp:4.9.3 -> 5.1.0 (c)
|    |    +--- com.github.ben-manes.caffeine:caffeine:2.9.3 (c)
|    |    +--- commons-codec:commons-codec:1.15 -> 1.17.1 (c)
|    |    +--- org.apache.httpcomponents:httpclient:4.5.14 (c)
|    |    +--- org.yaml:snakeyaml:1.30 -> 2.4 (c)
|    |    +--- org.apache.httpcomponents:httpcore:4.4.16 (c)
|    |    +--- org.reactivestreams:reactive-streams:1.0.4 (c)
|    |    +--- org.slf4j:slf4j-api:1.7.36 (c)
|    |    +--- io.netty:netty-codec-http:4.1.100.Final -> 4.1.126.Final (c)
|    |    +--- io.netty:netty-codec-http2:4.1.100.Final -> 4.1.126.Final (c)
|    |    +--- io.netty:netty-codec:4.1.100.Final -> 4.1.126.Final (c)
|    |    +--- io.netty:netty-transport:4.1.100.Final -> 4.1.126.Final (c)
|    |    +--- io.netty:netty-common:4.1.100.Final -> 4.1.126.Final (c)
|    |    +--- io.netty:netty-buffer:4.1.100.Final -> 4.1.126.Final (c)
|    |    +--- io.netty:netty-handler:4.1.100.Final -> 4.1.126.Final (c)
|    |    +--- io.netty:netty-transport-classes-epoll:4.1.100.Final -> 4.1.126.Final (c)
|    |    +--- io.netty:netty-resolver:4.1.100.Final -> 4.1.126.Final (c)
|    |    \--- io.netty:netty-transport-native-unix-common:4.1.100.Final -> 4.1.126.Final (c)
|    +--- org.testcontainers:testcontainers-bom:1.19.3
|    +--- software.amazon.awssdk:bom:2.30.17
|    |    +--- software.amazon.awssdk:auth:2.30.17 (c)
|    |    +--- software.amazon.awssdk:http-auth-aws:2.30.17 (c)
|    |    +--- software.amazon.awssdk:sts:2.30.17 (c)
|    |    +--- software.amazon.awssdk:annotations:2.30.17 (c)
|    |    +--- software.amazon.awssdk:utils:2.30.17 (c)
|    |    +--- software.amazon.awssdk:sdk-core:2.30.17 (c)
|    |    +--- software.amazon.awssdk:identity-spi:2.30.17 (c)
|    |    +--- software.amazon.awssdk:regions:2.30.17 (c)
|    |    +--- software.amazon.awssdk:profiles:2.30.17 (c)
|    |    +--- software.amazon.awssdk:http-client-spi:2.30.17 (c)
|    |    +--- software.amazon.awssdk:json-utils:2.30.17 (c)
|    |    +--- software.amazon.awssdk:http-auth-aws-eventstream:2.30.17 (c)
|    |    +--- software.amazon.awssdk:http-auth:2.30.17 (c)
|    |    +--- software.amazon.awssdk:http-auth-spi:2.30.17 (c)
|    |    +--- software.amazon.awssdk:checksums-spi:2.30.17 (c)
|    |    +--- software.amazon.awssdk:checksums:2.30.17 (c)
|    |    +--- software.amazon.awssdk:aws-query-protocol:2.30.17 (c)
|    |    +--- software.amazon.awssdk:protocol-core:2.30.17 (c)
|    |    +--- software.amazon.awssdk:aws-core:2.30.17 (c)
|    |    +--- software.amazon.awssdk:metrics-spi:2.30.17 (c)
|    |    +--- software.amazon.awssdk:endpoints-spi:2.30.17 (c)
|    |    +--- software.amazon.awssdk:retries-spi:2.30.17 (c)
|    |    +--- software.amazon.awssdk:apache-client:2.30.17 (c)
|    |    +--- software.amazon.awssdk:netty-nio-client:2.30.17 (c)
|    |    +--- software.amazon.awssdk:retries:2.30.17 (c)
|    |    \--- software.amazon.awssdk:third-party-jackson-core:2.30.17 (c)
|    +--- commons-logging:commons-logging:1.2 (c)
|    +--- com.squareup.okhttp3:okhttp:4.12.0 -> 5.1.0 (c)
|    +--- io.opentelemetry.contrib:opentelemetry-aws-xray:1.48.0-adot1 (c)
|    +--- io.opentelemetry.contrib:opentelemetry-aws-resources:1.48.0-alpha (c)
|    \--- org.slf4j:slf4j-api:1.7.36 (c)
+--- project :awsagentprovider
|    +--- io.opentelemetry.contrib:opentelemetry-aws-xray -> 1.48.0-adot1
|    |    +--- com.squareup.okhttp3:okhttp:5.1.0
|    |    |    \--- com.squareup.okhttp3:okhttp-jvm:5.1.0
|    |    |         +--- com.squareup.okio:okio:3.15.0
|    |    |         |    \--- com.squareup.okio:okio-jvm:3.15.0
|    |    |         |         \--- org.jetbrains.kotlin:kotlin-stdlib:2.1.21 -> 2.2.0
|    |    |         |              \--- org.jetbrains:annotations:13.0
|    |    |         \--- org.jetbrains.kotlin:kotlin-stdlib:2.2.0 (*)
|    |    +--- com.fasterxml.jackson.core:jackson-core:2.19.2
|    |    |    \--- com.fasterxml.jackson:jackson-bom:2.19.2 (*)
|    |    +--- com.fasterxml.jackson.core:jackson-databind:2.19.2
|    |    |    +--- com.fasterxml.jackson.core:jackson-annotations:2.19.2
|    |    |    |    \--- com.fasterxml.jackson:jackson-bom:2.19.2 (*)
|    |    |    +--- com.fasterxml.jackson.core:jackson-core:2.19.2 (*)
|    |    |    \--- com.fasterxml.jackson:jackson-bom:2.19.2 (*)
|    |    +--- com.github.ben-manes.caffeine:caffeine:2.9.3
|    |    |    +--- org.checkerframework:checker-qual:3.19.0
|    |    |    \--- com.google.errorprone:error_prone_annotations:2.10.0
|    |    \--- io.opentelemetry:opentelemetry-sdk-trace:1.52.0
|    +--- io.opentelemetry.contrib:opentelemetry-aws-resources -> 1.48.0-alpha
|    |    +--- com.fasterxml.jackson.core:jackson-core:2.19.2 (*)
|    |    \--- com.squareup.okhttp3:okhttp:5.1.0 (*)
|    +--- com.fasterxml.jackson.core:jackson-databind:2.16.1 -> 2.19.2 (*)
|    +--- com.fasterxml.jackson.dataformat:jackson-dataformat-yaml:2.16.1 -> 2.19.2
|    |    +--- com.fasterxml.jackson.core:jackson-databind:2.19.2 (*)
|    |    +--- org.yaml:snakeyaml:2.4
|    |    +--- com.fasterxml.jackson.core:jackson-core:2.19.2 (*)
|    |    \--- com.fasterxml.jackson:jackson-bom:2.19.2 (*)
|    +--- com.amazonaws:aws-java-sdk-core:1.12.773
|    |    +--- commons-logging:commons-logging:1.1.3 -> 1.2
|    |    +--- commons-codec:commons-codec:1.15 -> 1.17.1
|    |    +--- org.apache.httpcomponents:httpclient:4.5.13 -> 4.5.14
|    |    |    +--- org.apache.httpcomponents:httpcore:4.4.16
|    |    |    \--- commons-codec:commons-codec:1.11 -> 1.17.1
|    |    +--- com.fasterxml.jackson.core:jackson-databind:2.17.2 -> 2.19.2 (*)
|    |    +--- com.fasterxml.jackson.dataformat:jackson-dataformat-cbor:2.17.2 -> 2.19.2
|    |    |    +--- com.fasterxml.jackson.core:jackson-databind:2.19.2 (*)
|    |    |    +--- com.fasterxml.jackson.core:jackson-core:2.19.2 (*)
|    |    |    \--- com.fasterxml.jackson:jackson-bom:2.19.2 (*)
|    |    \--- joda-time:joda-time:2.12.7
|    +--- software.amazon.awssdk:auth -> 2.30.17
|    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    +--- software.amazon.awssdk:utils:2.30.17
|    |    |    +--- org.reactivestreams:reactive-streams:1.0.4
|    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    \--- org.slf4j:slf4j-api:1.7.36
|    |    +--- software.amazon.awssdk:sdk-core:2.30.17
|    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    +--- software.amazon.awssdk:http-client-spi:2.30.17
|    |    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    |    +--- software.amazon.awssdk:metrics-spi:2.30.17
|    |    |    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |    |    \--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    |    \--- org.reactivestreams:reactive-streams:1.0.4
|    |    |    +--- software.amazon.awssdk:metrics-spi:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:endpoints-spi:2.30.17
|    |    |    |    \--- software.amazon.awssdk:annotations:2.30.17
|    |    |    +--- software.amazon.awssdk:http-auth-spi:2.30.17
|    |    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    |    +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|    |    |    |    +--- org.reactivestreams:reactive-streams:1.0.4
|    |    |    |    \--- software.amazon.awssdk:identity-spi:2.30.17
|    |    |    |         +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |         \--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:http-auth-aws:2.30.17
|    |    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    |    +--- software.amazon.awssdk:identity-spi:2.30.17 (*)
|    |    |    |    +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|    |    |    |    +--- software.amazon.awssdk:http-auth-spi:2.30.17 (*)
|    |    |    |    +--- software.amazon.awssdk:checksums-spi:2.30.17
|    |    |    |    |    \--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |    \--- software.amazon.awssdk:checksums:2.30.17
|    |    |    |         +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |         +--- software.amazon.awssdk:checksums-spi:2.30.17 (*)
|    |    |    |         \--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:checksums-spi:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:checksums:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:identity-spi:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:profiles:2.30.17
|    |    |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    |    \--- software.amazon.awssdk:annotations:2.30.17
|    |    |    +--- software.amazon.awssdk:retries-spi:2.30.17
|    |    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |    \--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:retries:2.30.17
|    |    |    |    +--- software.amazon.awssdk:retries-spi:2.30.17 (*)
|    |    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |    \--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    +--- org.slf4j:slf4j-api:1.7.36
|    |    |    \--- org.reactivestreams:reactive-streams:1.0.4
|    |    +--- software.amazon.awssdk:identity-spi:2.30.17 (*)
|    |    +--- software.amazon.awssdk:regions:2.30.17
|    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:sdk-core:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:profiles:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:json-utils:2.30.17
|    |    |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    |    \--- software.amazon.awssdk:third-party-jackson-core:2.30.17
|    |    |    \--- org.slf4j:slf4j-api:1.7.36
|    |    +--- software.amazon.awssdk:profiles:2.30.17 (*)
|    |    +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|    |    +--- software.amazon.awssdk:json-utils:2.30.17 (*)
|    |    +--- software.amazon.awssdk:http-auth-aws:2.30.17 (*)
|    |    +--- software.amazon.awssdk:http-auth-aws-eventstream:2.30.17
|    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    \--- software.amazon.eventstream:eventstream:1.0.1
|    |    +--- software.amazon.awssdk:http-auth:2.30.17
|    |    |    +--- software.amazon.awssdk:annotations:2.30.17
|    |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|    |    |    +--- software.amazon.awssdk:http-auth-spi:2.30.17 (*)
|    |    |    \--- software.amazon.awssdk:identity-spi:2.30.17 (*)
|    |    +--- software.amazon.awssdk:http-auth-spi:2.30.17 (*)
|    |    \--- software.amazon.eventstream:eventstream:1.0.1
|    +--- software.amazon.awssdk:http-auth-aws -> 2.30.17 (*)
|    \--- software.amazon.awssdk:sts -> 2.30.17
|         +--- software.amazon.awssdk:aws-query-protocol:2.30.17
|         |    +--- software.amazon.awssdk:protocol-core:2.30.17
|         |    |    +--- software.amazon.awssdk:sdk-core:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:annotations:2.30.17
|         |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|         |    |    \--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|         |    +--- software.amazon.awssdk:aws-core:2.30.17
|         |    |    +--- software.amazon.awssdk:annotations:2.30.17
|         |    |    +--- software.amazon.awssdk:regions:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:auth:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:http-auth-spi:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:identity-spi:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:http-auth:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:profiles:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:sdk-core:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:metrics-spi:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:endpoints-spi:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:retries-spi:2.30.17 (*)
|         |    |    +--- software.amazon.awssdk:retries:2.30.17 (*)
|         |    |    \--- software.amazon.eventstream:eventstream:1.0.1
|         |    +--- software.amazon.awssdk:sdk-core:2.30.17 (*)
|         |    +--- software.amazon.awssdk:annotations:2.30.17
|         |    +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|         |    \--- software.amazon.awssdk:utils:2.30.17 (*)
|         +--- software.amazon.awssdk:protocol-core:2.30.17 (*)
|         +--- software.amazon.awssdk:profiles:2.30.17 (*)
|         +--- software.amazon.awssdk:http-auth-aws:2.30.17 (*)
|         +--- software.amazon.awssdk:sdk-core:2.30.17 (*)
|         +--- software.amazon.awssdk:auth:2.30.17 (*)
|         +--- software.amazon.awssdk:http-auth-spi:2.30.17 (*)
|         +--- software.amazon.awssdk:http-auth:2.30.17 (*)
|         +--- software.amazon.awssdk:identity-spi:2.30.17 (*)
|         +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|         +--- software.amazon.awssdk:regions:2.30.17 (*)
|         +--- software.amazon.awssdk:annotations:2.30.17
|         +--- software.amazon.awssdk:utils:2.30.17 (*)
|         +--- software.amazon.awssdk:aws-core:2.30.17 (*)
|         +--- software.amazon.awssdk:metrics-spi:2.30.17 (*)
|         +--- software.amazon.awssdk:json-utils:2.30.17 (*)
|         +--- software.amazon.awssdk:endpoints-spi:2.30.17 (*)
|         +--- software.amazon.awssdk:retries-spi:2.30.17 (*)
|         +--- software.amazon.awssdk:apache-client:2.30.17
|         |    +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|         |    +--- software.amazon.awssdk:metrics-spi:2.30.17 (*)
|         |    +--- software.amazon.awssdk:utils:2.30.17 (*)
|         |    +--- software.amazon.awssdk:annotations:2.30.17
|         |    +--- org.apache.httpcomponents:httpclient:4.5.13 -> 4.5.14 (*)
|         |    +--- org.apache.httpcomponents:httpcore:4.4.16
|         |    \--- commons-codec:commons-codec:1.17.1
|         \--- software.amazon.awssdk:netty-nio-client:2.30.17
|              +--- software.amazon.awssdk:annotations:2.30.17
|              +--- software.amazon.awssdk:http-client-spi:2.30.17 (*)
|              +--- software.amazon.awssdk:utils:2.30.17 (*)
|              +--- software.amazon.awssdk:metrics-spi:2.30.17 (*)
|              +--- io.netty:netty-codec-http:4.1.118.Final -> 4.1.126.Final
|              |    +--- io.netty:netty-common:4.1.126.Final
|              |    +--- io.netty:netty-buffer:4.1.126.Final
|              |    |    \--- io.netty:netty-common:4.1.126.Final
|              |    +--- io.netty:netty-transport:4.1.126.Final
|              |    |    +--- io.netty:netty-common:4.1.126.Final
|              |    |    +--- io.netty:netty-buffer:4.1.126.Final (*)
|              |    |    \--- io.netty:netty-resolver:4.1.126.Final
|              |    |         \--- io.netty:netty-common:4.1.126.Final
|              |    +--- io.netty:netty-codec:4.1.126.Final
|              |    |    +--- io.netty:netty-common:4.1.126.Final
|              |    |    +--- io.netty:netty-buffer:4.1.126.Final (*)
|              |    |    \--- io.netty:netty-transport:4.1.126.Final (*)
|              |    \--- io.netty:netty-handler:4.1.126.Final
|              |         +--- io.netty:netty-common:4.1.126.Final
|              |         +--- io.netty:netty-resolver:4.1.126.Final (*)
|              |         +--- io.netty:netty-buffer:4.1.126.Final (*)
|              |         +--- io.netty:netty-transport:4.1.126.Final (*)
|              |         +--- io.netty:netty-transport-native-unix-common:4.1.126.Final
|              |         |    +--- io.netty:netty-common:4.1.126.Final
|              |         |    +--- io.netty:netty-buffer:4.1.126.Final (*)
|              |         |    \--- io.netty:netty-transport:4.1.126.Final (*)
|              |         \--- io.netty:netty-codec:4.1.126.Final (*)
|              +--- io.netty:netty-codec-http2:4.1.118.Final -> 4.1.126.Final
|              |    +--- io.netty:netty-common:4.1.126.Final
|              |    +--- io.netty:netty-buffer:4.1.126.Final (*)
|              |    +--- io.netty:netty-transport:4.1.126.Final (*)
|              |    +--- io.netty:netty-codec:4.1.126.Final (*)
|              |    +--- io.netty:netty-handler:4.1.126.Final (*)
|              |    \--- io.netty:netty-codec-http:4.1.126.Final (*)
|              +--- io.netty:netty-codec:4.1.118.Final -> 4.1.126.Final (*)
|              +--- io.netty:netty-transport:4.1.118.Final -> 4.1.126.Final (*)
|              +--- io.netty:netty-common:4.1.118.Final -> 4.1.126.Final
|              +--- io.netty:netty-buffer:4.1.118.Final -> 4.1.126.Final (*)
|              +--- io.netty:netty-handler:4.1.118.Final -> 4.1.126.Final (*)
|              +--- io.netty:netty-transport-classes-epoll:4.1.118.Final -> 4.1.126.Final
|              |    +--- io.netty:netty-common:4.1.126.Final
|              |    +--- io.netty:netty-buffer:4.1.126.Final (*)
|              |    +--- io.netty:netty-transport:4.1.126.Final (*)
|              |    \--- io.netty:netty-transport-native-unix-common:4.1.126.Final (*)
|              +--- io.netty:netty-resolver:4.1.118.Final -> 4.1.126.Final (*)
|              +--- org.reactivestreams:reactive-streams:1.0.4
|              \--- org.slf4j:slf4j-api:1.7.36
+--- project :instrumentation:log4j-2.13.2
+--- project :instrumentation:aws-sdk
+--- project :instrumentation:logback-1.0
\--- project :instrumentation:jmx-metrics

javadocElements - javadoc elements for main. (n)
No dependencies

mainSourceElements - List of source directories contained in the Main SourceSet. (n)
No dependencies

runtimeClasspath - Runtime classpath of source set 'main'.
\--- project :dependencyManagement
     +--- com.amazonaws:aws-java-sdk-bom:1.12.599
     +--- com.fasterxml.jackson:jackson-bom:2.16.0
     +--- com.google.guava:guava-bom:33.0.0-jre
     +--- com.google.protobuf:protobuf-bom:3.25.1
     +--- com.linecorp.armeria:armeria-bom:1.26.4
     +--- io.grpc:grpc-bom:1.59.1
     +--- io.netty:netty-bom:4.1.126.Final
     +--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom-alpha:2.18.1-alpha
     |    +--- io.opentelemetry:opentelemetry-bom:1.52.0
     |    +--- io.opentelemetry:opentelemetry-bom-alpha:1.52.0-alpha
     |    |    \--- io.opentelemetry:opentelemetry-bom:1.52.0
     |    \--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom:2.18.1
     |         \--- io.opentelemetry:opentelemetry-bom:1.52.0
     +--- org.apache.logging.log4j:log4j-bom:2.21.1
     +--- org.junit:junit-bom:5.10.1
     +--- org.springframework.boot:spring-boot-dependencies:2.7.17
     +--- org.testcontainers:testcontainers-bom:1.19.3
     \--- software.amazon.awssdk:bom:2.30.17

runtimeElements - Runtime elements for the 'main' feature. (n)
No dependencies

runtimeOnly - Runtime-only dependencies for the 'main' feature. (n)
No dependencies

shadow
No dependencies

shadowClasspath
+--- project :dependencyManagement
|    +--- com.amazonaws:aws-java-sdk-bom:1.12.599
|    +--- com.fasterxml.jackson:jackson-bom:2.16.0
|    +--- com.google.guava:guava-bom:33.0.0-jre
|    +--- com.google.protobuf:protobuf-bom:3.25.1
|    +--- com.linecorp.armeria:armeria-bom:1.26.4
|    +--- io.grpc:grpc-bom:1.59.1
|    +--- io.netty:netty-bom:4.1.126.Final
|    +--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom-alpha:2.18.1-alpha
|    |    +--- io.opentelemetry:opentelemetry-bom:1.52.0
|    |    +--- io.opentelemetry:opentelemetry-bom-alpha:1.52.0-alpha
|    |    |    \--- io.opentelemetry:opentelemetry-bom:1.52.0
|    |    \--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom:2.18.1
|    |         +--- io.opentelemetry:opentelemetry-bom:1.52.0
|    |         \--- io.opentelemetry.javaagent:opentelemetry-javaagent:2.18.1 (c)
|    +--- org.apache.logging.log4j:log4j-bom:2.21.1
|    +--- org.junit:junit-bom:5.10.1
|    +--- org.springframework.boot:spring-boot-dependencies:2.7.17
|    +--- org.testcontainers:testcontainers-bom:1.19.3
|    +--- software.amazon.awssdk:bom:2.30.17
|    \--- io.opentelemetry.javaagent:opentelemetry-javaagent:2.18.1 (c)
\--- io.opentelemetry.javaagent:opentelemetry-javaagent -> 2.18.1

shadowRuntimeElements (n)
No dependencies

signatures (n)
No dependencies

sourcesElements - sources elements for main. (n)
No dependencies

testAnnotationProcessor - Annotation processors and their dependencies for source set 'test'.
\--- project :dependencyManagement
     +--- com.amazonaws:aws-java-sdk-bom:1.12.599
     +--- com.fasterxml.jackson:jackson-bom:2.16.0
     +--- com.google.guava:guava-bom:33.0.0-jre
     +--- com.google.protobuf:protobuf-bom:3.25.1
     +--- com.linecorp.armeria:armeria-bom:1.26.4
     +--- io.grpc:grpc-bom:1.59.1
     +--- io.netty:netty-bom:4.1.126.Final
     +--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom-alpha:2.18.1-alpha
     |    +--- io.opentelemetry:opentelemetry-bom:1.52.0
     |    +--- io.opentelemetry:opentelemetry-bom-alpha:1.52.0-alpha
     |    |    \--- io.opentelemetry:opentelemetry-bom:1.52.0
     |    \--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom:2.18.1
     |         \--- io.opentelemetry:opentelemetry-bom:1.52.0
     +--- org.apache.logging.log4j:log4j-bom:2.21.1
     +--- org.junit:junit-bom:5.10.1
     +--- org.springframework.boot:spring-boot-dependencies:2.7.17
     +--- org.testcontainers:testcontainers-bom:1.19.3
     \--- software.amazon.awssdk:bom:2.30.17

testCompileClasspath - Compile classpath for source set 'test'.
+--- project :dependencyManagement
|    +--- com.amazonaws:aws-java-sdk-bom:1.12.599
|    +--- com.fasterxml.jackson:jackson-bom:2.16.0
|    +--- com.google.guava:guava-bom:33.0.0-jre
|    +--- com.google.protobuf:protobuf-bom:3.25.1
|    +--- com.linecorp.armeria:armeria-bom:1.26.4
|    +--- io.grpc:grpc-bom:1.59.1
|    +--- io.netty:netty-bom:4.1.126.Final
|    +--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom-alpha:2.18.1-alpha
|    |    +--- io.opentelemetry:opentelemetry-bom:1.52.0
|    |    +--- io.opentelemetry:opentelemetry-bom-alpha:1.52.0-alpha
|    |    |    \--- io.opentelemetry:opentelemetry-bom:1.52.0
|    |    \--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom:2.18.1
|    |         \--- io.opentelemetry:opentelemetry-bom:1.52.0
|    +--- org.apache.logging.log4j:log4j-bom:2.21.1
|    +--- org.junit:junit-bom:5.10.1
|    |    +--- org.junit.jupiter:junit-jupiter-api:5.10.1 (c)
|    |    +--- org.junit.jupiter:junit-jupiter-params:5.10.1 (c)
|    |    \--- org.junit.platform:junit-platform-commons:1.10.1 (c)
|    +--- org.springframework.boot:spring-boot-dependencies:2.7.17
|    |    +--- org.junit.jupiter:junit-jupiter-api:5.8.2 -> 5.10.1 (c)
|    |    +--- org.junit.jupiter:junit-jupiter-params:5.8.2 -> 5.10.1 (c)
|    |    +--- org.assertj:assertj-core:3.22.0 -> 3.24.2 (c)
|    |    +--- net.bytebuddy:byte-buddy:1.12.23 -> 1.14.10 (c)
|    |    \--- org.junit.platform:junit-platform-commons:1.8.2 -> 1.10.1 (c)
|    +--- org.testcontainers:testcontainers-bom:1.19.3
|    +--- software.amazon.awssdk:bom:2.30.17
|    +--- org.assertj:assertj-core:3.24.2 (c)
|    \--- net.bytebuddy:byte-buddy:1.14.10 (c)
+--- org.assertj:assertj-core -> 3.24.2
|    \--- net.bytebuddy:byte-buddy:1.12.21 -> 1.14.10
+--- org.junit.jupiter:junit-jupiter-api -> 5.10.1
|    +--- org.junit:junit-bom:5.10.1 (*)
|    +--- org.opentest4j:opentest4j:1.3.0
|    +--- org.junit.platform:junit-platform-commons:1.10.1
|    |    +--- org.junit:junit-bom:5.10.1 (*)
|    |    \--- org.apiguardian:apiguardian-api:1.1.2
|    \--- org.apiguardian:apiguardian-api:1.1.2
\--- org.junit.jupiter:junit-jupiter-params -> 5.10.1
     +--- org.junit:junit-bom:5.10.1 (*)
     +--- org.junit.jupiter:junit-jupiter-api:5.10.1 (*)
     \--- org.apiguardian:apiguardian-api:1.1.2

testCompileOnly - Compile only dependencies for source set 'test'. (n)
No dependencies

testImplementation - Implementation only dependencies for source set 'test'. (n)
+--- org.assertj:assertj-core (n)
+--- org.junit.jupiter:junit-jupiter-api (n)
\--- org.junit.jupiter:junit-jupiter-params (n)

testRuntimeClasspath - Runtime classpath of source set 'test'.
+--- project :dependencyManagement
|    +--- com.amazonaws:aws-java-sdk-bom:1.12.599
|    +--- com.fasterxml.jackson:jackson-bom:2.16.0
|    +--- com.google.guava:guava-bom:33.0.0-jre
|    +--- com.google.protobuf:protobuf-bom:3.25.1
|    +--- com.linecorp.armeria:armeria-bom:1.26.4
|    +--- io.grpc:grpc-bom:1.59.1
|    +--- io.netty:netty-bom:4.1.126.Final
|    +--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom-alpha:2.18.1-alpha
|    |    +--- io.opentelemetry:opentelemetry-bom:1.52.0
|    |    +--- io.opentelemetry:opentelemetry-bom-alpha:1.52.0-alpha
|    |    |    \--- io.opentelemetry:opentelemetry-bom:1.52.0
|    |    \--- io.opentelemetry.instrumentation:opentelemetry-instrumentation-bom:2.18.1
|    |         \--- io.opentelemetry:opentelemetry-bom:1.52.0
|    +--- org.apache.logging.log4j:log4j-bom:2.21.1
|    +--- org.junit:junit-bom:5.10.1
|    |    +--- org.junit.jupiter:junit-jupiter-api:5.10.1 (c)
|    |    +--- org.junit.jupiter:junit-jupiter-engine:5.10.1 (c)
|    |    +--- org.junit.jupiter:junit-jupiter-params:5.10.1 (c)
|    |    +--- org.junit.platform:junit-platform-commons:1.10.1 (c)
|    |    \--- org.junit.platform:junit-platform-engine:1.10.1 (c)
|    +--- org.springframework.boot:spring-boot-dependencies:2.7.17
|    |    +--- org.junit.jupiter:junit-jupiter-api:5.8.2 -> 5.10.1 (c)
|    |    +--- org.junit.jupiter:junit-jupiter-engine:5.8.2 -> 5.10.1 (c)
|    |    +--- org.junit.jupiter:junit-jupiter-params:5.8.2 -> 5.10.1 (c)
|    |    +--- org.assertj:assertj-core:3.22.0 -> 3.24.2 (c)
|    |    +--- net.bytebuddy:byte-buddy:1.12.23 -> 1.14.10 (c)
|    |    +--- org.junit.platform:junit-platform-commons:1.8.2 -> 1.10.1 (c)
|    |    \--- org.junit.platform:junit-platform-engine:1.8.2 -> 1.10.1 (c)
|    +--- org.testcontainers:testcontainers-bom:1.19.3
|    +--- software.amazon.awssdk:bom:2.30.17
|    +--- org.assertj:assertj-core:3.24.2 (c)
|    \--- net.bytebuddy:byte-buddy:1.14.10 (c)
+--- org.assertj:assertj-core -> 3.24.2
|    \--- net.bytebuddy:byte-buddy:1.12.21 -> 1.14.10
+--- org.junit.jupiter:junit-jupiter-api -> 5.10.1
|    +--- org.junit:junit-bom:5.10.1 (*)
|    +--- org.opentest4j:opentest4j:1.3.0
|    \--- org.junit.platform:junit-platform-commons:1.10.1
|         \--- org.junit:junit-bom:5.10.1 (*)
+--- org.junit.jupiter:junit-jupiter-params -> 5.10.1
|    +--- org.junit:junit-bom:5.10.1 (*)
|    \--- org.junit.jupiter:junit-jupiter-api:5.10.1 (*)
\--- org.junit.jupiter:junit-jupiter-engine -> 5.10.1
     +--- org.junit:junit-bom:5.10.1 (*)
     +--- org.junit.platform:junit-platform-engine:1.10.1
     |    +--- org.junit:junit-bom:5.10.1 (*)
     |    +--- org.opentest4j:opentest4j:1.3.0
     |    \--- org.junit.platform:junit-platform-commons:1.10.1 (*)
     \--- org.junit.jupiter:junit-jupiter-api:5.10.1 (*)

testRuntimeOnly - Runtime only dependencies for source set 'test'. (n)
\--- org.junit.jupiter:junit-jupiter-engine (n)

(c) - A dependency constraint, not a dependency. The dependency affected by the constraint occurs elsewhere in the tree.
(*) - Indicates repeated occurrences of a transitive dependency subtree. Gradle expands transitive dependency subtrees only once per project; repeat occurrences only display the root of the subtree, followed by this annotation.

(n) - A dependency or dependency configuration that cannot be resolved.

A web-based, searchable dependency report is available by adding the --scan option.

[Incubating] Problems report is available at: file:///Users/lukezha/github/otel-java/wk-adot-pr/adot-java-main/build/reports/problems/problems-report.html

Deprecated Gradle features were used in this build, making it incompatible with Gradle 9.0.

You can use '--warning-mode all' to show the individual deprecation warnings and determine if they come from your own scripts or plugins.

For more on this, please refer to https://docs.gradle.org/8.14.3/userguide/command_line_interface.html#sec:command_line_warnings in the Gradle documentation.

BUILD SUCCESSFUL in 1s
4 actionable tasks: 1 executed, 3 up-to-date






```