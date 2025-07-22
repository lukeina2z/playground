package org.example;

import com.amazonaws.xray.AWSXRayRecorder;
import com.amazonaws.xray.AWSXRayRecorderBuilder;
import com.amazonaws.xray.emitters.Emitter;

class SmokeTest {

    private Emitter emitter;

    void emits() {
        AWSXRayRecorder recorder = AWSXRayRecorderBuilder.standard()
                                                         .withEmitter(emitter)
                                                         .build();

        recorder.beginSegment("test");
        recorder.endSegment();
    }
}