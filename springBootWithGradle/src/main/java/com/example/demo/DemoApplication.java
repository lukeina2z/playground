package com.example.demo;
import java.util.concurrent.atomic.AtomicLong;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

record Greeting(long id, String content) { }

@SpringBootApplication
@RestController
public class DemoApplication {
    private static final String template = "Hello, %s!";
    private final AtomicLong counter = new AtomicLong();

    public static void main(String[] args) {
      SpringApplication.run(DemoApplication.class, args);
    }

    @GetMapping("/")
    public String home(String name) {
        return """
                <html>
                <body>
                    <p>Two web methods are provided:</p>
                    <ul>
                        <li><a href="/hello" target="_blank">/hello</a></li>
                        <li><a href="/aws-sdk-call" target="_blank">/aws-sdk-call</a></li>
                        <li><a href="/outgoing-http-call" target="_blank">/outgoing-http-call</a></li>
                    </ul>
                </body>
                </html>
               """;
    }

    @GetMapping("/hello")
    public Greeting hello(@RequestParam(value = "name", defaultValue = "World") String name) {
      // return String.format("Hello %s!", name);
      return new Greeting(counter.incrementAndGet(), String.format(template, name));
    }

    @GetMapping("/aws-sdk-call")
    public String awsSdkCall(@RequestParam(value = "name", defaultValue = "World") String name) {
      return String.format("aws-sdk-call: %s!", name);
    }

    @GetMapping("/outgoing-http-call")
    public String outgoingHttpCall(@RequestParam(value = "name", defaultValue = "World") String name) {
      return String.format("outgoing-http-call: %s!", name);
    }
}