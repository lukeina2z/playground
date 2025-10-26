package org.example;

import io.opentelemetry.api.GlobalOpenTelemetry;
import io.opentelemetry.api.OpenTelemetry;
import io.opentelemetry.api.trace.Tracer;

public class MyOTel {
    private volatile OpenTelemetry openTelemetry;
    private volatile Tracer tracer;

    private static class Holder {
        private static final MyOTel INSTANCE = new MyOTel();
    }

    public static MyOTel getInstance() {
        return Holder.INSTANCE;
    }

    private MyOTel() {
    }

    public OpenTelemetry getOpenTelemetry() {
        if (openTelemetry == null) {
            synchronized (this) {
                if (openTelemetry == null) {
                    openTelemetry = GlobalOpenTelemetry.get();
                }
            }
        }
        return openTelemetry;
    }

    public Tracer getTracer() {
        if (tracer == null) {
            synchronized (this) {
                if (tracer == null) {
                    tracer = getOpenTelemetry().getTracer("Java-Lambda-01-SVC");
                }
            }
        }
        return tracer;
    }
}
