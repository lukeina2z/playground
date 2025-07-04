/*
 * This file was generated by the Gradle 'init' task.
 *
 * This generated file contains a sample Java library project to get you started.
 * For more details on building Java & JVM projects, please refer to https://docs.gradle.org/8.14.2/userguide/building_java_projects.html in the Gradle documentation.
 */

plugins {
    // Apply the java-library plugin for API and implementation separation.
    `java-library`
         id("com.github.johnrengelman.shadow") version "8.1.1"
}

repositories {
    // Use Maven Central for resolving dependencies.
    mavenCentral()
}

dependencies {
    // Use JUnit Jupiter for testing.
    testImplementation(libs.junit.jupiter)

    testRuntimeOnly("org.junit.platform:junit-platform-launcher")

    // This dependency is exported to consumers, that is to say found on their compile classpath.
    api(libs.commons.math3)

    implementation("com.amazonaws:aws-lambda-java-core:1.3.0")
    implementation("software.amazon.awssdk:s3:2.28.29")
    implementation("org.slf4j:slf4j-nop:2.0.16")
    implementation("com.amazonaws:aws-lambda-java-events:3.11.4")
    implementation("com.fasterxml.jackson.core:jackson-databind:2.15.2")

    implementation("io.opentelemetry:opentelemetry-api:1.39.0")
    implementation("io.opentelemetry:opentelemetry-context:1.39.0")

    // This dependency is used internally, and not exposed to consumers on their own compile classpath.
    implementation(libs.guava)
}

// Apply a specific Java toolchain to ease working on different environments.
java {
    toolchain {
        languageVersion = JavaLanguageVersion.of(11)
    }
}

tasks.named<Test>("test") {
    // Use JUnit Platform for unit tests.
    useJUnitPlatform()
}



// Set up the jar task for Lambda
tasks {
    named<com.github.jengelman.gradle.plugins.shadow.tasks.ShadowJar>("shadowJar") {
        archiveBaseName.set("lambda")
        archiveClassifier.set("") // Removes the '-all' suffix
        archiveVersion.set("")
        mergeServiceFiles()
    }

    build {
        dependsOn(shadowJar)
    }
}